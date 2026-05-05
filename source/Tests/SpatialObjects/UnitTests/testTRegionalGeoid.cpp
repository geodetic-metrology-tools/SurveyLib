// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <tut/tut.hpp>
#include <gdal_raster_cpp.h>
#include <TPositionVector.h>
#include <TSpatialPosition.h>
#include <TRefFrameInfo.h>
#include <TRegionalGeoid.h>
#include <TReferenceEllipsoid.h>
#include <fstream>


namespace tut
{
struct test_TRegionalGeoid
{
};
typedef test_group<test_TRegionalGeoid> factory;
typedef factory::object object;
}

namespace
{
tut::factory tf("Test TRegionalGeoid class");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	const std::string filename("C:\\Users\\bweyer\\Downloads\\AUSGeoid2020_20180201.gsb");
	GDALAllRegister();

	GDALDataset *dataset = static_cast<GDALDataset *>(GDALOpen(filename.c_str(), GA_ReadOnly));

	if (!dataset)
	{
		std::cerr << "Failed to open file\n";
		return;
	}

	std::cout << "Size: " << dataset->GetRasterXSize() << " x " << dataset->GetRasterYSize() << "\n";
	std::cout << "SRS: " << dataset->GetSpatialRef()->GetName() << "\n";
	std::cout << "ProjectionRef: " << dataset->GetProjectionRef() << "\n";
	double geoidHeight = 0.0;
	OGRSpatialReference	src, dst;
	src.SetWellKnownGeogCS("WGS84");
	dst.importFromWkt(dataset->GetProjectionRef());

	src.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
	dst.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

	auto *ct = OGRCreateCoordinateTransformation(&src, &dst);

	double x = 140.333;
	double y = -31.6989;

	//ct->Transform(1, &x, &y);

	// Now interpolate WITHOUT CRS
	dataset->GetRasterBand(1)->InterpolateAtGeolocation(x, y, &src, GRIORA_Bilinear, &geoidHeight);




	OGRSpatialReference srs;
	srs.SetWellKnownGeogCS("WGS84");
	//srs.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
	dataset->GetRasterBand(1)->InterpolateAtGeolocation(y, x, &srs, GRIORA_Bilinear, &geoidHeight);
	std::cout << "bilinear geoid height: " << geoidHeight << "\n";

	GDALClose(dataset);



}

template<>
template<>
void object::test<2>()
{
	set_test_name("Test N");
	//TAngle lambda(6.04866331086255, TAngle::kDeciDegs); // longitude P0 (CHTRF95)
	//TAngle phi (46.23215612104025, TAngle::kDeciDegs); // latitude P0 (CHTRF95)
	//TLength h(483.624043488, TLength::kMetres); // ellipsoidal height P0 (CHTRF95)
	TLength x(4395448.303144970), y(465755.018889440), z(4583484.782265396);

	TPositionVector p0(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95), p0);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCHGeo2004_ETRS));
	std::cout << "Geoid height: " << geoidModel->getN(position).getMetresValue() << "\n";
	//ensure_equals("N", geoidModel->getN(position).getMetresValue(), 0.0);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("Test Eta");
	// TAngle lambda(6.04866331086255, TAngle::kDeciDegs); // longitude P0 (CHTRF95)
	// TAngle phi (46.23215612104025, TAngle::kDeciDegs); // latitude P0 (CHTRF95)
	// TLength h(483.624043488, TLength::kMetres); // ellipsoidal height P0 (CHTRF95)
	TLength x(4395448.303144970), y(465755.018889440), z(4583484.782265396);

	TPositionVector p0(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95), p0);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCHGeo2004_ETRS));
	std::cout << "Eta: " << geoidModel->getEta(position).getSignedCCValue() << "\n";
	//ensure_equals("Eta", geoidModel->getN(position).getMetresValue(), 0.0);
}

template<>
template<>
void object::test<4>()
{
	set_test_name("Test Xi");
	// TAngle lambda(6.04866331086255, TAngle::kDeciDegs); // longitude P0 (CHTRF95)
	// TAngle phi (46.23215612104025, TAngle::kDeciDegs); // latitude P0 (CHTRF95)
	// TLength h(483.624043488, TLength::kMetres); // ellipsoidal height P0 (CHTRF95)
	TLength x(4395448.303144970), y(465755.018889440), z(4583484.782265396);

	TPositionVector p0(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95), p0);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCHGeo2004_ETRS));
	std::cout << "Xi: " << geoidModel->getXi(position).getSignedCCValue() << "\n";
	// ensure_equals("Eta", geoidModel->getN(position).getMetresValue(), 0.0);
}

template<>
template<>
void object::test<5>()
{
	set_test_name("Test N, Lambda, Xi compared to Python Script");
	// Coordinate of the point 53 in the geodetic control profile
	//TLength x(4394452.09397), y(463492.09023), z(4583991.77052);

	// Coordinate of the point 85 in the geodetic control profile
	//TLength x(4407162.31964), y(470865.84975), z(4571453.66808);
	// Coordinate of the point 53 in the geodetic control profile
	TLength x(4394624.03962), y(463510.22570), z(4584172.34127);

	TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95), p);

	TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCHGeo2004_ETRS));
	std::cout << "N: " << geoidModel->getN(position).getMetresValue() << "\n";
	std::cout << "Eta: " << geoidModel->getEta(position).getSecondsValue() << "\n";
	std::cout << "Xi: " << geoidModel->getXi(position).getSecondsValue() << "\n";
	// ensure_equals("Eta", geoidModel->getN(position).getMetresValue(), 0.0);
}

template<>
template<>
void object::test<6>()
{
	set_test_name("Test for the whole dataset");
	std::ifstream infile("C:\\Users\\bweyer\\Downloads\\GeocentricDoVControl.txt");
	std::ofstream outfile("C:\\Users\\bweyer\\Downloads\\GeocentricDoVControl_withModel.txt");

	if (!infile.is_open())
	{
		std::cerr << "Error opening input file\n";
	}

	if (!outfile.is_open())
	{
		std::cerr << "Error opening output file\n";
	}

	std::string line;

	// Skip header
	std::getline(infile, line);

	// Write output header
	outfile << "Point\tEta\tXi\tEtaModel\tXiModel\tDeltaEta\tDeltaXi\n";
	outfile << std::fixed << std::setprecision(6);

	// Initialize geoid model once
	TAReferenceFrame *CHTRF95(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCHTRF95));
	TRegionalGeoid *FCC_G2025 = new TRegionalGeoid("CHGeo2004_ETRS", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, CHTRF95,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80),
		CHTRF95, "C:\\Users\\bweyer\\cernbox\\Documents\\FCC\\Geoid\\JuliaComparison\\Julia\\FCC-G2025_V1.0.tif");


	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);

		int point;
		double X, Y, Z;
		double Eta, Xi;

		iss >> point >> X >> Y >> Z >> Eta >> Xi;

		// Build position
		TLength x(X), y(Y), z(Z);
		TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95), p);

		// Compute model values
		double EtaModel = FCC_G2025->getEta(position).getSecondsValue();
		double XiModel = FCC_G2025->getXi(position).getSecondsValue();

		// Differences
		double deltaEta = EtaModel - Eta;
		double deltaXi = XiModel - Xi;

		// Write results
		outfile << point << "\t" << Eta << "\t" << Xi << "\t" << EtaModel << "\t" << XiModel << "\t" << deltaEta << "\t" << deltaXi << "\n";
	}

	infile.close();
	outfile.close();

	std::cout << "Processing completed.\n";
}

} // namespace tut
