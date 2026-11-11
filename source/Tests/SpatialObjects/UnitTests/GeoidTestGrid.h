// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

// GeoidTestGrid.h
//
// Generation of small synthetic geoid grids (GeoTIFF, EPSG:4937 / ETRS89) for the unit tests,
// so that no grid file has to be stored in the repository.
//
// The undulation is a linear function of longitude and latitude: bilinear interpolation
// is then exact and the expected value is known analytically (see expectedN).

#ifndef SU_TEST_GEOID_TEST_GRID
#define SU_TEST_GEOID_TEST_GRID

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <gdal_priv.h>
#include <ogr_spatialref.h>

namespace geoidtestgrid
{
// Grid extent, in decimal degrees (covers CERN, Geneva and Switzerland)
constexpr double kLonMin = 5.0;
constexpr double kLatMax = 48.0;
constexpr double kStep = 0.25;
constexpr int kNbLon = 16; // 5.0 -> 9.0
constexpr int kNbLat = 12; // 48.0 -> 45.0

/*! Analytical undulation of the synthetic grid, in metres. offset allows to build several different grids */
inline double expectedN(double lonDeg, double latDeg, double offset = 0.0)
{
	return 40.0 + offset + 2.0 * (lonDeg - kLonMin) + 1.0 * (latDeg - 45.0);
}

/*! Write the synthetic grid in the temporary directory and return its path.
	The content only depends on (fileName, offset): an existing file is reused, as it may still be
	opened by a geoid cached in TRefSystemFactory (rewriting it would fail on Windows). */
inline std::string createGrid(const std::string &fileName, double offset = 0.0)
{
	const std::filesystem::path path = std::filesystem::temp_directory_path() / fileName;
	const std::string pathStr = path.generic_string();

	if (std::filesystem::exists(path))
		return pathStr;

	GDALAllRegister();
	GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");
	if (driver == nullptr)
		throw std::runtime_error("GTiff GDAL driver not available");

	GDALDataset *dataset = driver->Create(pathStr.c_str(), kNbLon, kNbLat, 1, GDT_Float64, nullptr);
	if (dataset == nullptr)
		throw std::runtime_error("Unable to create the test geoid grid " + pathStr);

	// North-up grid, values are given at pixel centres
	double geoTransform[6] = {kLonMin, kStep, 0.0, kLatMax, 0.0, -kStep};
	dataset->SetGeoTransform(geoTransform);

	OGRSpatialReference srs;
	srs.importFromEPSG(4937);
	dataset->SetSpatialRef(&srs);

	std::vector<double> values(static_cast<size_t>(kNbLon) * kNbLat);
	for (int row = 0; row < kNbLat; ++row)
	{
		const double lat = kLatMax - (row + 0.5) * kStep;
		for (int col = 0; col < kNbLon; ++col)
		{
			const double lon = kLonMin + (col + 0.5) * kStep;
			values[static_cast<size_t>(row) * kNbLon + col] = expectedN(lon, lat, offset);
		}
	}

	const CPLErr err = dataset->GetRasterBand(1)->RasterIO(GF_Write, 0, 0, kNbLon, kNbLat, values.data(), kNbLon, kNbLat, GDT_Float64, 0, 0);
	GDALClose(dataset);
	if (err != CE_None)
		throw std::runtime_error("Unable to write the test geoid grid " + pathStr);

	return pathStr;
}

/*! Write the same synthetic grid as an ESRI ASCII grid (no SRS in the file) and return its path */
inline std::string createAsciiGrid(const std::string &fileName, double offset = 0.0)
{
	const std::filesystem::path path = std::filesystem::temp_directory_path() / fileName;
	const std::string pathStr = path.generic_string();

	if (std::filesystem::exists(path))
		return pathStr;

	std::ofstream out(path);
	if (!out)
		throw std::runtime_error("Unable to create the test geoid grid " + pathStr);

	out.precision(10);
	out << "ncols " << kNbLon << "\nnrows " << kNbLat << "\nxllcorner " << kLonMin << "\nyllcorner " << kLatMax - kNbLat * kStep << "\ncellsize " << kStep
		<< "\nNODATA_value -9999\n";
	for (int row = 0; row < kNbLat; ++row)
	{
		const double lat = kLatMax - (row + 0.5) * kStep;
		for (int col = 0; col < kNbLon; ++col)
			out << expectedN(kLonMin + (col + 0.5) * kStep, lat, offset) << (col + 1 < kNbLon ? " " : "\n");
	}
	return pathStr;
}
} // namespace geoidtestgrid

#endif // SU_TEST_GEOID_TEST_GRID
