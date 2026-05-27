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
	tut::skip();
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

template<>
template<>
void object::test<7>()
{
	set_test_name("Test with australian geoid");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\AUSGeoid2020_20180201.gsb");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kITRFin));
	TRegionalGeoid *AUSGeoid2020 = new TRegionalGeoid("AUSGeoid2020", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia S28 26  0.000 E122 57  0.000 h200 xi = -5.64    eta = -2.65
	TLength x(-3053053.09282), y(4710283.39541), z(-3018916.88305);
	TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin), p);

	ensure_equals("N", AUSGeoid2020->getN(position).getMetresValue(), -14.714, tolHeight); // this value is at a grid node, so no interpolation error expected
	ensure_equals("Eta", AUSGeoid2020->getEta(position).getSecondsValue(), -2.65, tolDoV); // this value is at a grid node, so no interpolation error expected
	ensure_equals("Xi", AUSGeoid2020->getXi(position).getSecondsValue(), -5.64, tolDoV); // this value is at a grid node, so no interpolation error expected
}

template<>
template<>
void object::test<8>()
{
	set_test_name("Test with australian geoid");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\AUSGeoid2020_20180201.gsb");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kITRFin));
	TRegionalGeoid *AUSGeoid2020 = new TRegionalGeoid("AUSGeoid2020", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia 336.5544321470 (23.445567853S)    134.4456785300E    250.00000 ellipsoidalHeight
	// comparison with results given by the online tool https://geodesyapps.ga.gov.au/ausgeoid2020
	TLength x(-4099779.11805), y(4179885.17336), z(-2522166.01923);
	TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139), p);

	std::cout << "N: " << AUSGeoid2020->getN(position).getMetresValue() << "\n";
	std::cout << "Eta: " << AUSGeoid2020->getEta(position).getSecondsValue() << "\n";
	std::cout << "Xi: " << AUSGeoid2020->getXi(position).getSecondsValue() << "\n";
	ensure_equals("N", AUSGeoid2020->getN(position).getMetresValue(), 19.727, tolHeight);
	ensure_equals("Eta", AUSGeoid2020->getEta(position).getSecondsValue(), -6.07, tolDoV);
	ensure_equals("Xi", AUSGeoid2020->getXi(position).getSecondsValue(), -20.21, tolDoV);
}

template<>
template<>
void object::test<9>()
{
	set_test_name("Test with australian quasigeoid AGQ2017");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\AGQG_20201120.gsb");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kITRFin));
	TRegionalGeoid *AGQ2017 = new TRegionalGeoid("AGQ2017", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia 336.5544321470 (23.445567853S)    134.4456785300E    250.00000 ellipsoidalHeight
	// comparison with results given by the online tool https://geodesyapps.ga.gov.au/ausgeoid2020
	TLength x(-4099779.11805), y(4179885.17336), z(-2522166.01923);
	TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139), p);

	//ensure_equals("N", AGQ2017->getN(position).getMetresValue(), 19.727, tolHeight);
	//ensure_equals("Eta", AGQ2017->getEta(position).getSecondsValue(), -6.07, tolDoV);
	ensure_equals("Xi", AGQ2017->getXi(position).getSecondsValue(), -20.21, tolDoV);
}

template<>
template<>
void object::test<10>()
{
	set_test_name("Test with American Geoid18");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\g2018u0.bin");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *GEOID18 = new TRegionalGeoid("GEOID18", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in the US 35.9320N     97.2W    250.00000 ellipsoidalHeight
	// comparison with results given by the online tool https://www.ngs.noaa.gov/GEOID/DEFLEC18/computation.html
	TLength x(-648052.09354), y(-5129860.54005), z(3722231.58159);
	TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);
	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139), p);

	//ensure_equals("N", GEOID18->getN(position).getMetresValue(), 19.727, tolHeight);
	std::cout << "Eta: " << GEOID18->getEta(position).getSecondsValue() << "\n";
	std::cout << "Xi: " << GEOID18->getXi(position).getSecondsValue() << "\n";
	ensure_equals("Eta", GEOID18->getEta(position).getSecondsValue(), 1.32, tolDoV);
	ensure_equals("Xi", GEOID18->getXi(position).getSecondsValue(), 2.88, tolDoV);

	// See https://geodesy.noaa.gov/library/pdfs/NOAA_TR_NOS_NGS_0072.pdf
	// and https://ia801303.us.archive.org/31/items/heiskanen_morits_1967_physical_geodesy/heiskanen_morits_1967_physical_geodesy.pdf
}

template<>
template<>
void object::test<11>()
{
	set_test_name("Test compared to ICGEM");
	std::ifstream infile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\DoVObservations.txt");
	std::ofstream outfile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\DoVObservations_withModelCppNegCorrection.txt");

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
	outfile << "Point\tLongitude\tLatitude\th\tEta\tXi\tEtaModel\tXiModel\tDeltaEta\tDeltaXi\n";
	outfile << std::fixed << std::setprecision(6);

	// Initialize geoid model once
	//TAReferenceFrame *CHTRF95(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCHTRF95));
	//TRegionalGeoid *FCC_G2025 = new TRegionalGeoid("CHGeo2004_ETRS", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, CHTRF95,
	//	TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), CHTRF95,
	//	"C:\\Users\\bweyer\\cernbox\\Documents\\FCC\\Geoid\\JuliaComparison\\Julia\\FCC-G2025_V1.0.tif");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\geoid_EIGEN-6C4_AOI.tiff");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *EIGEN = new TRegionalGeoid("EIGEN", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);


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
		TAngle lambda(X, TAngle::kDeciDegs);
		TAngle phi(Y, TAngle::kDeciDegs);
		TLength h(Z);
		TPositionVector pv(TCoordSysFactory::kGeodetic);
		pv.setPhiEllipsoid(phi);
		pv.setLambdaEllipsoid(lambda);
		pv.setH(h);
		
		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
		position.setCoordinates(pv);

		// Compute model values
		double EtaModel = EIGEN->getEta(position).getSecondsValue();
		double XiModel = EIGEN->getXi(position).getSecondsValue();

		// Differences
		double deltaEta = EtaModel - Eta;
		double deltaXi = XiModel - Xi;

		// Write results
		outfile << point << "\t" << lambda.getDeciDegsValue() << "\t" << phi.getDeciDegsValue() << "\t" << h << "\t" << Eta << "\t" << Xi << "\t" << EtaModel << "\t"
				<< XiModel << "\t"
				<< deltaEta << "\t" << deltaXi << "\n";
	}

	infile.close();
	outfile.close();

	std::cout << "Processing completed.\n";
}

template<>
template<>
void object::test<12>()
{
/*
Name	ESSERTINES
Country	CH
Year of measurement	1996
Instrument	TZK3
Xi (CH1903) [arcseconds]	-13.09
Eta (CH1903) [arcseconds]	7.32
Xi (ETRS89) [arcseconds]	-8.5
Eta (ETRS89) [arcseconds]	9.23
Type of measurement station	Analoge Zenitkamera (1980-1996)
Approx WGS84~ETRF93 coordinates (lat, long, altitude):	46.599584, 7.239956 921 m
	*/

		set_test_name("CHGEO with true value");
TAngle lambda(7.239956, TAngle::kDeciDegs);
		TAngle phi(46.599584, TAngle::kDeciDegs);
TLength h(921+51.1);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95));
	position.setCoordinates(pv);

	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\Geoid_OGD\\chgeo2004_ETRS.agr");
	// Initialize geoid model once
	TAReferenceFrame *chtrf95(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCHTRF95));
	TRegionalGeoid *pCHGeo2004_ETRS = new TRegionalGeoid("CHGeo2004_ETRS", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, chtrf95,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), chtrf95, pathToFile);
	

//		TAGeoidModel *geoidModel(TRefSystemFactory::getRefSystemFactory()->getGeoid(TRefSystemFactory::kCHGeo2004_ETRS));
	std::cout << "Xi: " << pCHGeo2004_ETRS->getXi(position).getSecondsValue() << "\n";
	std::cout << "Eta: " << pCHGeo2004_ETRS->getEta(position).getSecondsValue() << "\n";
	std::cout << "N: " << pCHGeo2004_ETRS->getN(position).getMetresValue() << "\n";
	ensure_equals("Eta", pCHGeo2004_ETRS->getEta(position).getSecondsValue(), 9.23);
	ensure_equals("Xi", pCHGeo2004_ETRS->getXi(position).getSecondsValue(), -8.5);
	}


} // namespace tut
