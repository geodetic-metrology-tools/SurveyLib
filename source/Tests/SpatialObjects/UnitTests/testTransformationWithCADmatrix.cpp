// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later


#include <filesystem>

#include <tut/tut.hpp>

#include <TPositionVector.h>
#include <TRefFrameInfo.h>
#include <TSpatialPosition.h>

namespace tut
{
struct test_CADTransformations
{
};
typedef test_group<test_CADTransformations> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test CAD cordinate transformations");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Transform unit vector through each matching CAD matrix pair in folder");

	// Original unit vector
	TLength x(1.0);
	TLength y(0.0);
	TLength z(0.0);
	TPositionVector pv(x, y, z, TCoordSysFactory::k3DCartesian);

	// Path to folder containing transformation matrix files (ensure trailing backslash)
#ifdef _WIN32
	const std::string folder = "\\\\eosproject-smb\\eos\\project\\g\\geodetic-metrology\\Geodesy\\CAD_Systems\\TransformationMatrixCATIA\\";
#else
	const std::string folder = "/eos/project/g/geodetic-metrology/Geodesy/CAD_Systems/TransformationMatrixCATIA/";
#endif

	namespace fs = std::filesystem;

	fs::path dirPath(folder);
	ensure("Transformation matrices folder must exist", fs::exists(dirPath) && fs::is_directory(dirPath));

	// Map id -> pair<has_forward, has_back>
	std::map<std::string, std::pair<bool, bool>> pairs;

	for (const auto &entry : fs::directory_iterator(dirPath))
	{
		if (!entry.is_regular_file())
			continue;
		std::string filename = entry.path().filename().string();

		// Normalize to uppercase for matching
		std::string up = filename;
		std::transform(up.begin(), up.end(), up.begin(), [](unsigned char c) { return std::toupper(c); });

		// Look for patterns: "<ID>_SURVEY.TRSF" or "SURVEY_<ID>.TRSF"
		// Find extension position
		if (up.size() < 6)
			continue; // skip tiny names
		// Ensure extension contains ".TRSF" (case-insensitive)
		const std::string ext = ".TRSF";
		if (up.size() <= ext.size() || up.substr(up.size() - ext.size()) != ext)
			continue;

		// Remove extension
		std::string nameNoExt = up.substr(0, up.size() - ext.size());

		// Split by first underscore
		auto pos = nameNoExt.find('_');
		if (pos == std::string::npos)
			continue;

		std::string left = nameNoExt.substr(0, pos);
		std::string right = nameNoExt.substr(pos + 1);

		if (right == "SURVEY")
		{
			// pattern "<ID>_SURVEY"
			std::string id = left;
			auto &p = pairs[id];
			p.first = true; // forward
		}
		else if (left == "SURVEY")
		{
			// pattern "SURVEY_<ID>"
			std::string id = right;
			auto &p = pairs[id];
			p.second = true; // back
		}
	}

	// Collect ids that have both forward and back
	std::vector<std::string> ids;
	for (const auto &kv : pairs)
	{
		if (kv.second.first && kv.second.second)
			ids.push_back(kv.first);
	}

	ensure("At least one matching pair of transformation matrices must be present", !ids.empty());

	const double tol = 1e-5;

	for (const auto &id : ids)
	{
		// reconstruct filenames with original case-insensitive extension .TRSF
		std::string forwardFilename = id + "_SURVEY.TRSF";
		std::string backFilename = "SURVEY_" + id + ".TRSF";

		std::string pathToTransformationMatrixFor = folder + forwardFilename;
		std::string pathToTransformationMatrixBack = folder + backFilename;

		// Create position with CAD-in reference frame (forward matrix)
		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCADin, pathToTransformationMatrixFor));
		ensure(("Setting the coordinates of TSpatialPosition for id " + id).c_str(), position.setCoordinates(pv));

		// Transform to CCS
		bool ok1 = position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS));
		ensure(("Transform to CCS succeeded for id " + id).c_str(), ok1);

		// Transform back using CAD-out (back matrix)
		bool ok2 = position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCADout, pathToTransformationMatrixBack));
		ensure(("Transform back to CAD succeeded for id " + id).c_str(), ok2);

		// Compare coordinates
		double rx = position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue();
		double ry = position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue();
		double rz = position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue();

		ensure_equals(("CAD X for id " + id).c_str(), rx, x.getMetresValue(), tol);
		ensure_equals(("CAD Y for id " + id).c_str(), ry, y.getMetresValue(), tol);
		ensure_equals(("CAD Z for id " + id).c_str(), rz, z.getMetresValue(), tol);
	}
}

template<>
template<>
void object::test<2>()
{
	set_test_name("Transform translation point");
	const double tol = 1e-6;

	// Original unit vector
	TLength xTranslation(2202.2102702479288);
	TLength yTranslation(2710.6388201471618);
	TLength zTranslation(2359.0065601466191);

	TLength xOrig(0.0);
	TLength yOrig(0.0);
	TLength zOrig(0.0);

	TPositionVector pv(xOrig, yOrig, zOrig, TCoordSysFactory::k3DCartesian);

	// Path to folder containing transformation matrix files (ensure trailing backslash)
#ifdef _WIN32
	const std::string path = "\\\\eosproject-smb\\eos\\project\\g\\geodetic-metrology\\Geodesy\\CAD_Systems\\TransformationMatrixCATIA\\1101_SURVEY.TRSF";
#else
	const std::string path = "/eos/project/g/geodetic-metrology/Geodesy/CAD_Systems/TransformationMatrixCATIA/1101_SURVEY.TRSF";
#endif

	// Create position with CAD-in reference frame (forward matrix)
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCADin, path));
	position.setCoordinates(pv);
	bool ok1 = position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCCS));

	ensure_equals("CCS X is equal to translation", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX(), xTranslation, tol);
	ensure_equals("CCS Y is equal to translation", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY(), yTranslation, tol);
	ensure_equals("CCS Z is equal to translation", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ(), zTranslation, tol);
}

} // namespace tut
