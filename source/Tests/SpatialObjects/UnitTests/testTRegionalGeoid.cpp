// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <fstream>

#include <tut/tut.hpp>

#include <TPositionVector.h>
#include <TRefFrameInfo.h>
#include <TReferenceEllipsoid.h>
#include <TRegionalGeoid.h>
#include <TSpatialPosition.h>
#include <gdal_raster_cpp.h>

namespace tut
{
struct test_TRegionalGeoid
{
};
typedef test_group<test_TRegionalGeoid> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test TRegionalGeoid class");
}

namespace
{
const std::string kGeoidDir("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\ScriptGetDoV\\");

struct TGeoidRefPoint
{
	std::string id;
	double lat, lon, h; // deg, deg (negative west), m
	double N, xi, eta; // m, arcsec, arcsec
};

std::vector<TGeoidRefPoint> readGeoidReference(const std::string &path)
{
	std::ifstream in(path);
	if (!in)
	{
		throw std::runtime_error("Cannot open reference file " + path);
	}

	std::vector<TGeoidRefPoint> pts;
	std::string line;
	std::getline(in, line); // header: id,lat,lon,h,N,xi,eta
	while (std::getline(in, line))
	{
		if (!line.empty() && line.back() == '\r')
		{
			line.pop_back();
		}
		if (line.empty() || line[0] == '#')
		{
			continue;
		}

		std::vector<std::string> f;
		std::stringstream ss(line);
		std::string tok;
		while (std::getline(ss, tok, ','))
		{
			f.push_back(tok);
		}
		if (f.size() != 7)
		{
			throw std::runtime_error("Malformed line in " + path + ": " + line);
		}

		try
		{
			TGeoidRefPoint p;
			p.id = f[0];
			p.lat = std::stod(f[1]);
			p.lon = std::stod(f[2]);
			p.h = std::stod(f[3]);
			p.N = std::stod(f[4]); // an empty field throws: all references must be filled
			p.xi = std::stod(f[5]);
			p.eta = std::stod(f[6]);
			pts.push_back(p);
		}
		catch (const std::exception &)
		{
			throw std::runtime_error("Missing or invalid value in " + path + ": " + line);
		}
	}
	return pts;
}

struct TDiffStats
{
	std::string name;
	std::string unit;
	double tol;
	double maxAbs = 0.0;
	double sumSq = 0.0;
	std::string worstId;
	int n = 0;
	int fails = 0;

	TDiffStats(const std::string &nm, const std::string &u, double t) : name(nm), unit(u), tol(t) {}

	void add(const std::string &id, double diff, std::ostream &log)
	{
		++n;
		sumSq += diff * diff;
		if (std::fabs(diff) > maxAbs)
		{
			maxAbs = std::fabs(diff);
			worstId = id;
		}
		if (!(std::fabs(diff) <= tol)) // also catches NaN
		{
			++fails;
			log << "  " << id << "  " << name << " diff = " << diff << " " << unit << " (tol " << tol << ")\n";
		}
	}

	void error(const std::string &id, const std::string &what, std::ostream &log)
	{
		++fails;
		log << "  " << id << "  " << name << " exception: " << what << "\n";
	}

	void check(const std::string &id, double ref, const std::function<double()> &compute, std::ostream &log)
	{
		try
		{
			add(id, compute() - ref, log);
		}
		catch (const std::exception &e)
		{
			error(id, e.what(), log);
		}
	}

	std::string summary() const
	{
		std::ostringstream os;
		os << std::setw(4) << name << ": " << n << " pts, RMS " << (n ? std::sqrt(sumSq / n) : 0.0) << " " << unit << ", max |diff| " << maxAbs << " " << unit << " at "
		   << worstId << ", " << fails << " outside tol " << tol;
		return os.str();
	}
};

struct TGeoidComparison
{
	TDiffStats sN, sXi, sEta;
	std::string report;
	TGeoidComparison(double tolN, double tolDoV) : sN("N", "m", tolN), sXi("Xi", "\"", tolDoV), sEta("Eta", "\"", tolDoV) {}
};

// Compares the geoid with every reference point. If calcCsv is not empty,
// writes id,lat,lon,N,xi,eta as computed by the geoid (for plotting).
TGeoidComparison
	compareWithReference(const TRegionalGeoid &geoid, const std::vector<TGeoidRefPoint> &pts, double tolN, double tolDoV, const std::string &title, const std::string &calcCsv = "", bool verbose = false)
{
	TGeoidComparison c(tolN, tolDoV);
	std::ostringstream log;
	std::ofstream out;
	if (!calcCsv.empty())
	{
		out.open(calcCsv);
		if (!out)
		{
			throw std::runtime_error("Cannot write " + calcCsv);
		}
		out << "id,lat,lon,N,xi,eta\n" << std::setprecision(10);
	}
	if (verbose)
	{
		std::cout << "\n id                          N_calc     N_ref   Xi_calc  Xi_ref  Eta_calc Eta_ref\n";
	}

	for (const TGeoidRefPoint &p : pts)
	{
		TPositionVector pv(TCoordSysFactory::kGeodetic);
		pv.setPhiEllipsoid(TAngle(p.lat, TAngle::kDeciDegs));
		pv.setLambdaEllipsoid(TAngle(p.lon, TAngle::kDeciDegs));
		pv.setH(TLength(p.h));

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
		position.setCoordinates(pv);

		double n = NAN, xi = NAN, eta = NAN;
		c.sN.check(p.id, p.N, [&]() { return n = geoid.getN(position).getMetresValue(); }, log);
		c.sXi.check(p.id, p.xi, [&]() { return xi = geoid.getXi(position).getSecondsValue(); }, log);
		c.sEta.check(p.id, p.eta, [&]() { return eta = geoid.getEta(position).getSecondsValue(); }, log);

		if (out.is_open())
		{
			out << p.id << "," << p.lat << "," << p.lon << "," << n << "," << xi << "," << eta << "\n";
		}
		if (verbose)
		{
			std::cout << std::fixed << " " << std::left << std::setw(26) << p.id << std::right << std::setprecision(3) << std::setw(10) << n << std::setw(10) << p.N
					  << std::setprecision(2) << std::setw(9) << xi << std::setw(8) << p.xi << std::setw(9) << eta << std::setw(8) << p.eta << "\n";
			std::cout.unsetf(std::ios::fixed);
		}
	}

	c.report = "\n" + title + "\n" + c.sN.summary() + "\n" + c.sXi.summary() + "\n" + c.sEta.summary() + "\n" + log.str();
	return c;
}

std::unique_ptr<TRegionalGeoid> makeGeoid18()
{
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	// NB: use the GEOID18 enum value of TRefSystemFactory::EGeoid here (the single-point test passes kCHGeo2004_ETRS)
	return std::unique_ptr<TRegionalGeoid>(new TRegionalGeoid("GEOID18", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, kGeoidDir + "g2018u0.bin", 4326, GRIORA_Cubic));
}
} // namespace

namespace tut
{
template<>
template<>
void object::test<1>()
{
	set_test_name("Test with australian geoid");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\Downloads\\AUSGeoid2020_20180201.gsb");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *AUSGeoid2020 = new TRegionalGeoid("AUSGeoid2020", TRefSystemFactory::EGeoid::kCUSTOMgeoid, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia 325.02592363760 (34.97407636240S)    138.70887100110E    727.2197 ellipsoidalHeight
	// comparison with results given by the online tool https://geodesyapps.ga.gov.au/ausgeoid2020
	TAngle lambda(138.70887100110, TAngle::kDeciDegs);
	TAngle phi(325.02592363760, TAngle::kDeciDegs);
	TLength h(727.2197);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
	position.setCoordinates(pv);

	std::cout << "N: " << AUSGeoid2020->getN(position).getMetresValue() << std::endl;
	std::cout << "Eta: " << AUSGeoid2020->getEta(position).getSecondsValue() << std::endl;
	std::cout << "Xi: " << AUSGeoid2020->getXi(position).getSecondsValue() << std::endl;
	std::cout << "DoV: "
			  << sqrt(AUSGeoid2020->getEta(position).getSecondsValue() * AUSGeoid2020->getEta(position).getSecondsValue()
					 + AUSGeoid2020->getXi(position).getSecondsValue() * AUSGeoid2020->getXi(position).getSecondsValue())
			  << std::endl;

	ensure_equals("N", AUSGeoid2020->getN(position).getMetresValue(), 0.419, tolHeight);
	ensure_equals("Eta", AUSGeoid2020->getEta(position).getSecondsValue(), -10.22, tolDoV);
	ensure_equals("Xi", AUSGeoid2020->getXi(position).getSecondsValue(), -2.97, tolDoV);
}

template<>
template<>
void object::test<2>()
{
	set_test_name("GEOID18: 50 points over CONUS vs NGS GEOID18 / DEFLEC18");

	const double tolHeight = 1e-3; // m
	const double tolDoV = 1e-2; // arcsec (DEFLEC18 online output is rounded to 0.01")

	std::unique_ptr<TRegionalGeoid> GEOID18 = makeGeoid18();
	const std::vector<TGeoidRefPoint> pts = readGeoidReference(kGeoidDir + "geoid18_reference_geoid.csv");
	ensure_equals("number of reference points", pts.size(), static_cast<size_t>(50));

	TGeoidComparison c = compareWithReference(*GEOID18, pts, tolHeight, tolDoV, "GEOID18 vs NGS over CONUS", kGeoidDir + "geoid18_calc_conus.csv");
	std::cout << c.report << std::endl;
	ensure(c.report.c_str(), c.sN.fails == 0 && c.sXi.fails == 0 && c.sEta.fails == 0);
}

template<>
template<>
void object::test<3>()
{
	set_test_name("GEOID18: local point set around N34W110");

	// N is asserted: most points lie between grid nodes, so this checks the
	// interpolation, not only the node values. The deflections are reported
	// only: this test is a diagnostic of how local the anomaly is.
	const double tolHeight = 1e-3; // m
	const double tolDoV = 1e-2; // arcsec, only used to list the points in the report

	std::unique_ptr<TRegionalGeoid> GEOID18 = makeGeoid18();
	// surface values: geoid18_local_N34W110.csv; projected to the geoid: geoid18_local_N34W110_geoid.csv
	const std::vector<TGeoidRefPoint> pts = readGeoidReference(kGeoidDir + "geoid18_local_N34W110_geoid.csv");
	ensure("local reference set is empty", !pts.empty());

	TGeoidComparison c = compareWithReference(*GEOID18, pts, tolHeight, tolDoV, "GEOID18 vs NGS around N34W110", kGeoidDir + "geoid18_calc_local_N34W110.csv", true);
	std::cout << c.report << std::endl;
	ensure(c.report.c_str(), c.sN.fails == 0);
}


template<>
template<>
void object::test<6>()
{
	set_test_name("Test for the whole dataset");
	std::ifstream infile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\CERN\\Codiac_dovObservations.txt");
	std::ofstream outfile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\CERN\\Codiac_dovObservations_FCC-G2025.txt");

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
	outfile << "Latitude_deg\tLongitude_deg\tEllipsoidalHeight_m\tSurfaceEta_arcsec\tSurfaceXi_arcsec\tSurfaceDoV_arcsec\tEtaModel_arcsec\tXiModel_arcsec\tDoVModel_"
			   "arcsec\tDeltaEta_arcsec\tDeltaXi_arcsec\tDeltaDoV_arcsec\n";
	outfile << std::fixed << std::setprecision(6);

	// Initialize geoid model once

	std::string pathToFile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\CERN\\FCC-G2025_V1.0.tif");
	// Initialize geoid model once
	TAReferenceFrame *ETRF93(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kETRF93));
	TRegionalGeoid *FCC_G2025 = new TRegionalGeoid("FCC-G2025", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, ETRF93,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), ETRF93, pathToFile, 4326, GRIORA_Cubic);

	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);

		int point;
		double lat, longi, h;
		double Eta, Xi;
		iss >> lat >> longi >> h >> Eta >> Xi;
		double doV = sqrt(Eta * Eta + Xi * Xi);

		// Build position
		TAngle lambda(longi, TAngle::kDeciDegs);
		TAngle phi(lat, TAngle::kDeciDegs);
		TLength height(h);
		TPositionVector pv(TCoordSysFactory::kGeodetic);
		pv.setPhiEllipsoid(phi);
		pv.setLambdaEllipsoid(lambda);
		pv.setH(height);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
		position.setCoordinates(pv);

		// Compute model values
		double EtaModel = FCC_G2025->getEta(position).getSecondsValue();
		double XiModel = FCC_G2025->getXi(position).getSecondsValue();
		double dovModel = sqrt(EtaModel * EtaModel + XiModel * XiModel);

		// Differences
		double deltaEta = EtaModel - Eta;
		double deltaXi = XiModel - Xi;
		double deltaDoV = dovModel - doV;

		// Write results
		outfile << phi.getDeciDegsValue() << "\t" << lambda.getDeciDegsValue() << "\t" << height.getMetresValue() << "\t" << Eta << "\t" << Xi << "\t" << doV << "\t"
				<< EtaModel << "\t" << XiModel << "\t" << dovModel << "\t" << deltaEta << "\t" << deltaXi << "\t" << deltaDoV << "\n";
	}

	infile.close();
	outfile.close();

	//TAngle lambda(LITERAL(6.7285948569), TAngle::kGons);
	//TAngle phi(LITERAL(51.3999292503), TAngle::kGons);
	//TLength height(LITERAL(509.58316));
	TAngle lambda(LITERAL(6.6865098047), TAngle::kGons);
	TAngle phi(LITERAL(51.3940662456), TAngle::kGons);
	TLength height(LITERAL(460.54006));

	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(height);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRF93));
	position.setCoordinates(pv);

	// Compute model values
	double EtaModel = FCC_G2025->getEta(position).getSecondsValue();
	double XiModel = FCC_G2025->getXi(position).getSecondsValue();
	double AlphaModel = FCC_G2025->getDAlpha(position, phi).getSecondsValue();
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
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *AUSGeoid2020 = new TRegionalGeoid("AUSGeoid2020", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in Australia S28 26  0.000 E122 57  0.000 h200 xi = -5.64    eta = -2.65
	// https://geodesyapps.ga.gov.au/ausgeoid2020
	TAngle lambda;
	lambda.setDMSValue(122, 57, 0.000);
	TAngle phi;
	phi.setDMSValue(-28, 26, 0.000);
	TLength h(200);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
	position.setCoordinates(pv);
	std::cout << "N" << AUSGeoid2020->getN(position).getMetresValue() << "\n";
	std::cout << "Eta: " << AUSGeoid2020->getEta(position).getSecondsValue() << "\n";
	std::cout << "Xi: " << AUSGeoid2020->getXi(position).getSecondsValue() << "\n";
	ensure_equals("N", AUSGeoid2020->getN(position).getMetresValue(), -14.714, tolHeight); // this value is at a grid node, so no interpolation error expected
	ensure_equals("Eta", AUSGeoid2020->getEta(position).getSecondsValue(), -2.65, tolDoV); // this value is at a grid node, so no interpolation error expected
	ensure_equals("Xi", AUSGeoid2020->getXi(position).getSecondsValue(), -5.64, tolDoV); // this value is at a grid node, so no interpolation error expected
}

template<>
template<>
void object::test<8>()
{
	tut::skip();
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
	TAngle lambda(134.4456785300, TAngle::kDeciDegs);
	TAngle phi(336.5544321470, TAngle::kDeciDegs);
	TLength h(250.00000);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kCHTRF95));
	position.setCoordinates(pv);
	// TLength x(-4099779.11805), y(4179885.17336), z(-2522166.01923);
	// TPositionVector p(x, y, z, TCoordSysFactory::k3DCartesian);
	// TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139), p);

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
	tut::skip();
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

	// ensure_equals("N", AGQ2017->getN(position).getMetresValue(), 19.727, tolHeight);
	// ensure_equals("Eta", AGQ2017->getEta(position).getSecondsValue(), -6.07, tolDoV);
	ensure_equals("Xi", AGQ2017->getXi(position).getSecondsValue(), -20.21, tolDoV);
}

template<>
template<>
void object::test<10>()
{
	set_test_name("Test with American Geoid18");
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\g2018u0.bin");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *GEOID18 = new TRegionalGeoid("GEOID18", TRefSystemFactory::EGeoid::kCUSTOMgeoid, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kGRS80), WGS84, pathToFile, 4326, GRIORA_Cubic);

	// Coordinate of a point in the US 35.9320N     97.2W    250.00000 ellipsoidalHeight
	// comparison with results given by the online tool https://www.ngs.noaa.gov/GEOID/DEFLEC18/computation.html
	// and https://geodesy.noaa.gov/GEOID/GEOID18/computation.html
	TAngle lambda(-97.2, TAngle::kDeciDegs);
	TAngle phi(35.932, TAngle::kDeciDegs);
	TLength h(250.00000);
	TPositionVector pv(TCoordSysFactory::kGeodetic);
	pv.setPhiEllipsoid(phi);
	pv.setLambdaEllipsoid(lambda);
	pv.setH(h);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
	position.setCoordinates(pv);

	std::cout << "N" << GEOID18->getN(position).getMetresValue() << "\n";
	std::cout << "Eta: " << GEOID18->getEta(position).getSecondsValue() << "\n";
	std::cout << "Xi: " << GEOID18->getXi(position).getSecondsValue() << "\n";

	ensure_equals("N", GEOID18->getN(position).getMetresValue(), -27.929, tolHeight);
	ensure_equals("Eta", GEOID18->getEta(position).getSecondsValue(), 1.32, tolDoV);
	ensure_equals("Xi", GEOID18->getXi(position).getSecondsValue(), 2.88, tolDoV);

	// See https://geodesy.noaa.gov/library/pdfs/NOAA_TR_NOS_NGS_0072.pdf
	// and https://ia801303.us.archive.org/31/items/heiskanen_morits_1967_physical_geodesy/heiskanen_morits_1967_physical_geodesy.pdf
}

template<>
template<>
void object::test<11>()
{
	tut::skip();

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
	// TAReferenceFrame *CHTRF95(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kCHTRF95));
	// TRegionalGeoid *FCC_G2025 = new TRegionalGeoid("CHGeo2004_ETRS", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, CHTRF95,
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
				<< XiModel << "\t" << deltaEta << "\t" << deltaXi << "\n";
	}

	infile.close();
	outfile.close();

	std::cout << "Processing completed.\n";
}

template<>
template<>
void object::test<12>()
{
	tut::skip();

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
	TLength h(921 + 51.1);
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

template<>
template<>
void object::test<14>()
{
	tut::skip();
	set_test_name("Test Australian AusGeoid compared to online calculator)");
	std::ifstream infile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\Australia\\VerticalDeflections_August2017.csv");
	std::ofstream outfile(
		"C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\Australia\\VerticalDeflections_August2017_AusGeoid2020_pizzeti.txt");

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
	outfile << "Longitude\tLatitude\th\tEta\tXi\tNModel\tEtaModel\tXiModel\tDeltaEta\tDeltaXi\n";
	outfile << std::fixed << std::setprecision(6);

	// Initialize geoid model once
	const double tolHeight = 1e-3;
	const double tolDoV = 1e-2;
	std::string pathToFile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\Australia\\AUSGeoid2020_20180201.gsb");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *AGQG2020 = new TRegionalGeoid("AGQG2020", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);

		int point;
		double lat, longi, h;
		double Eta, Xi;

		iss >> lat >> longi >> h >> Xi >> Eta;

		// Build position
		TAngle lambda(longi, TAngle::kDeciDegs);
		TAngle phi(lat, TAngle::kDeciDegs);
		TLength height(h);
		TPositionVector pv(TCoordSysFactory::kGeodetic);
		pv.setPhiEllipsoid(phi);
		pv.setLambdaEllipsoid(lambda);
		pv.setH(height);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
		position.setCoordinates(pv);

		// Compute model values
		double NModel = AGQG2020->getN(position).getMetresValue();
		double EtaModel = AGQG2020->getEta(position).getSecondsValue();
		double XiModel = AGQG2020->getXi(position).getSecondsValue();

		// Differences
		double deltaEta = EtaModel - Eta;
		double deltaXi = XiModel - Xi;

		// Write results
		outfile << lambda.getDeciDegsValue() << "\t" << phi.getDeciDegsValue() - 360.0 << "\t" << height.getMetresValue() << "\t" << Eta << "\t" << Xi << "\t" << NModel << "\t" << EtaModel
				<< "\t" << XiModel << "\t" << deltaEta << "\t" << deltaXi << "\n";
	}

	infile.close();
	outfile.close();

	std::cout << "Processing completed.\n";
}

template<>
template<>
void object::test<15>()
{
	set_test_name("Test USA g2018 compared to online calculator)");
	std::ifstream infile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\GSV17_dovObservations.txt");
	std::ofstream outfile(
		"C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\GSV17_dovObservations_G2018dov.txt");

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
	outfile << "Latitude_deg\tLongitude_deg\tEllipsoidalHeight_m\tSurfaceEta_arcsec\tSurfaceXi_arcsec\tSurfaceDoV_arcsec\tEtaModel_arcsec\tXiModel_arcsec\tDoVModel_arcsec\tDeltaEta_arcsec\tDeltaXi_arcsec\tDeltaDoV_arcsec\n";
	outfile << std::fixed << std::setprecision(6);

	// Initialize geoid model once

	std::string pathToFile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\g2018u0.bin");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *G2018 = new TRegionalGeoid("G2018", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);

		int point;
		double lat, longi, h;
		double Eta, Xi;
		iss >> lat >> longi >> h >> Eta >> Xi;
		double doV = sqrt(Eta * Eta + Xi * Xi);

		// Build position
		TAngle lambda(longi, TAngle::kDeciDegs);
		TAngle phi(lat, TAngle::kDeciDegs);
		TLength height(h);
		TPositionVector pv(TCoordSysFactory::kGeodetic);
		pv.setPhiEllipsoid(phi);
		pv.setLambdaEllipsoid(lambda);
		pv.setH(height);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
		position.setCoordinates(pv);

		// Compute model values
		double EtaModel = G2018->getEta(position).getSecondsValue();
		double XiModel = G2018->getXi(position).getSecondsValue();
		double dovModel = sqrt(EtaModel * EtaModel + XiModel * XiModel);

		// Differences
		double deltaEta = EtaModel - Eta;
		double deltaXi = XiModel - Xi;
		double deltaDoV = dovModel - doV;

		// Write results
		outfile << phi.getDeciDegsValue() << "\t" << lambda.getDeciDegsValue() << "\t" << height.getMetresValue() << "\t" << Eta << "\t" << Xi << "\t" << doV
				<< "\t" << EtaModel << "\t" << XiModel << "\t" << dovModel << "\t" << deltaEta << "\t" << deltaXi << "\t" << deltaDoV << "\n";
	}

	infile.close();
	outfile.close();

	std::cout << "Processing completed.\n";
}

template<>
template<>
void object::test<16>()
{
	set_test_name("Test USA g2018 compared to online calculator)");
	std::ifstream infile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\GSV11_dovObservations.txt");
	std::ofstream outfile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\GSV11_dovObservations_G2018dov.txt");

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
	outfile << "Latitude_deg\tLongitude_deg\tEllipsoidalHeight_m\tSurfaceEta_arcsec\tSurfaceXi_arcsec\tSurfaceDoV_arcsec\tEtaModel_arcsec\tXiModel_arcsec\tDoVModel_"
			   "arcsec\tDeltaEta_arcsec\tDeltaXi_arcsec\tDeltaDoV_arcsec\n";
	outfile << std::fixed << std::setprecision(6);

	// Initialize geoid model once

	std::string pathToFile("C:\\Users\\bweyer\\cernbox\\Documents\\Development\\SurveyLib\\ImplementationGeoid\\USA\\g2018u0.bin");
	// Initialize geoid model once
	TAReferenceFrame *WGS84(TRefSystemFactory::getRefSystemFactory()->getRefFrame(TRefSystemFactory::kWGS84_G2139));
	TRegionalGeoid *G2018 = new TRegionalGeoid("G2018", TRefSystemFactory::EGeoid::kCHGeo2004_ETRS, WGS84,
		TRefSystemFactory::getRefSystemFactory()->getEllipsoid(TRefSystemFactory::kWGSEll), WGS84, pathToFile, 4326, GRIORA_Cubic);

	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;

		std::istringstream iss(line);

		int point;
		double lat, longi, h;
		double Eta, Xi;
		iss >> lat >> longi >> h >> Eta >> Xi;
		double doV = sqrt(Eta * Eta + Xi * Xi);

		// Build position
		TAngle lambda(longi, TAngle::kDeciDegs);
		TAngle phi(lat, TAngle::kDeciDegs);
		TLength height(h);
		TPositionVector pv(TCoordSysFactory::kGeodetic);
		pv.setPhiEllipsoid(phi);
		pv.setLambdaEllipsoid(lambda);
		pv.setH(height);

		TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kWGS84_G2139));
		position.setCoordinates(pv);

		// Compute model values
		double EtaModel = G2018->getEta(position).getSecondsValue();
		double XiModel = G2018->getXi(position).getSecondsValue();
		double dovModel = sqrt(EtaModel * EtaModel + XiModel * XiModel);

		// Differences
		double deltaEta = EtaModel - Eta;
		double deltaXi = XiModel - Xi;
		double deltaDoV = dovModel - doV;

		// Write results
		outfile << phi.getDeciDegsValue() << "\t" << lambda.getDeciDegsValue() << "\t" << height.getMetresValue() << "\t" << Eta << "\t" << Xi << "\t" << doV << "\t"
				<< EtaModel << "\t" << XiModel << "\t" << dovModel << "\t" << deltaEta << "\t" << deltaXi << "\t" << deltaDoV << "\n";
	}

	infile.close();
	outfile.close();

	std::cout << "Processing completed.\n";
}

} // namespace tut
