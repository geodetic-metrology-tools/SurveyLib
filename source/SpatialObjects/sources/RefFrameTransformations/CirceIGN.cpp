#include <CirceIGN.h>
#include <TNotInGeoidGridException.h>

#include <array>
#include <sstream>


#include <windows.h>


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
	//From https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
	std::string	strResult;
	HANDLE hPipeRead, hPipeWrite;

	SECURITY_ATTRIBUTES saAttr = {sizeof(SECURITY_ATTRIBUTES)};
	saAttr.bInheritHandle = TRUE; // Pipe handles are inherited by child process.
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe to get results from child's stdout.
	if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0))
		return strResult;

	STARTUPINFO si = {sizeof(STARTUPINFOW)};
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.hStdOutput = hPipeWrite;
	si.hStdError = hPipeWrite;
	si.wShowWindow = SW_HIDE; // Prevents cmd window from flashing.
							  // Requires STARTF_USESHOWWINDOW in dwFlags.

	PROCESS_INFORMATION pi = {0};

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	if (!fSuccess)
	{
		DWORD dw = GetLastError();
		CloseHandle(hPipeWrite);
		CloseHandle(hPipeRead);
		return strResult;
	}

	bool bProcessEnded = false;
	for (; !bProcessEnded;)
	{
		// Give some timeslice (50 ms), so we won't waste 100% CPU.
		bProcessEnded = WaitForSingleObject(pi.hProcess, 50) == WAIT_OBJECT_0;

		// Even if process exited - we continue reading, if
		// there is some data available over pipe.
		for (;;)
		{
			char buf[1024];
			DWORD dwRead = 0;
			DWORD dwAvail = 0;

			if (!::PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL))
				break;

			if (!dwAvail) // No data available, return
				break;

			if (!::ReadFile(hPipeRead, buf, min(sizeof(buf) - 1, dwAvail), &dwRead, NULL) || !dwRead)
				// Error, the child process might ended
				break;

			buf[dwRead] = 0;
			strResult += buf;
		}
	} // for

	CloseHandle(hPipeWrite);
	CloseHandle(hPipeRead);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// Stop the computation if the point is outside the computation area
	if (strResult == "Le point est en-dehors du SRC géodésique source\n" || strResult == "Transformation verticale introuvable pour ce point\n")
	{
		std::stringstream ss;
		ss << "TNotInGeoidGridException: Point outside RAF20 grid ";
		throw TNotInGeoidGridException(ss.str());
	}


	return strResult;
} // ExecCmd

void readCirceResult(std::string result, double &h) 
{
	std::stringstream ss(result);
	double x, y, conv, scale, sigmaZ;
	std::string infoGeoid1, infoGeoid2, sep, unit;

	ss >> x >> y >> h >> conv >> scale >> infoGeoid1 >> infoGeoid2 >> sep >> sigmaZ >> unit;
}
}
