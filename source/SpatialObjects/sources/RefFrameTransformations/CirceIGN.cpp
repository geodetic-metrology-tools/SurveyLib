#include <CirceIGN.h>
#include <TNotInGeoidGridException.h>

#include <array>
#include <sstream>



#ifdef CIRCE_EXEC_DIR
#	define CIRCE_DIR CIRCE_EXEC_DIR
#endif



namespace circeIGN
{

	void circeTransfoRafToH(bool lambert, const double &X, const double &Y, double &h) 
{
	std::string circePath = CIRCE_DIR;

	std::string sourceCRS, targetCRS;
	if (lambert)
	{
		sourceCRS = "RGF93LAMB93.IGN69 ";
		targetCRS = "RGF93LAMB93. ";

	}
	else
	{
		sourceCRS = "RGF93CC46.IGN69 ";
		targetCRS = "RGF93CC46. ";
	}

	std::string circeOption = "--sourceCRS=" + sourceCRS + 
							  "--sourceFormat=ENV.METERS.RADIANS "
							  "--targetCRS=" + targetCRS +
							  "--targetFormat=ENHCS.METERS.DEGREES "
							  "--displayPrecision=0.00001 --plainDMS --gridLoading=BINARY";

	std::string cmdString = "\"" + circePath + "/circeFR.exe\"" + " --metadataFile=" + circePath + "/Data/DataFRnew.txt " + circeOption + " " + std::to_string(X) + " "
		+ std::to_string(Y) + " " + std::to_string(h);

	const char *cmd = cmdString.c_str();
	std::string result = execCirce(cmd);
	readCirceResult(result, h);
}

void circeTransfoHToRaf(bool lambert, const double &X, const double &Y, double &h) 
{
	std::string circePath = CIRCE_DIR;

	std::string sourceCRS, targetCRS;
	if (lambert)
	{
		sourceCRS = "RGF93LAMB93. ";
		targetCRS = "RGF93LAMB93.IGN69 ";
	}
	else
	{
		sourceCRS = "RGF93CC46. ";
		targetCRS = "RGF93CC46.IGN69 ";
	}

	std::string circeOption = "--sourceCRS=" + sourceCRS +
							  "--sourceFormat=ENH.METERS.RADIANS "
							  "--targetCRS=" + targetCRS + 
							  "--targetFormat=ENVCS.METERS.DEGREES "
							  "--displayPrecision=0.00001 --plainDMS --gridLoading=BINARY";

	std::string cmdString = "\"" + circePath + "/circeFR.exe\"" + " --metadataFile=" + circePath + "/Data/DataFRnew.txt " + circeOption + " " + std::to_string(X) + " "
		+ std::to_string(Y) + " " + std::to_string(h);

	const char *cmd = cmdString.c_str();
	std::string result = execCirce(cmd);
	readCirceResult(result, h);
}

std::string execCirce(const char *cmd) 
{
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe)
		throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get()))
	{
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
			result += buffer.data();
	}

	// Stop the computation if the point is outside the computation area
	if (result == "Le point est en-dehors du SRC géodésique source\n" || result == "Transformation verticale introuvable pour ce point\n")
	{
		std::stringstream ss;
		ss << "TNotInGeoidGridException: Point outside RAF20 grid ";
		throw TNotInGeoidGridException(ss.str());
	}

	return result;
}

void readCirceResult(std::string result, double &h) 
{
	std::stringstream ss(result);
	double x, y, conv, scale, sigmaZ;
	std::string infoGeoid1, infoGeoid2, sep, unit;

	ss >> x >> y >> h >> conv >> scale >> infoGeoid1 >> infoGeoid2 >> sep >> sigmaZ >> unit;
}
}
