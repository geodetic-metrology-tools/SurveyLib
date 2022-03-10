#include <FrenchRAF20.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TConstants.h"
#include <TNotInGeoidGridException.h>



void FrenchRAF20::circeTransfoRafToH(const double &latitude_rgf93_rad, const double &longitude_rgf93_rad, double &h)
{
	h += interpolRAF20(latitude_rgf93_rad * RAD2DEG, longitude_rgf93_rad * RAD2DEG);
}

void FrenchRAF20::circeTransfoHToRaf(const double &latitude_rgf93_rad, const double &longitude_rgf93_rad, double &h)
{
	h -= interpolRAF20(latitude_rgf93_rad * RAD2DEG, longitude_rgf93_rad * RAD2DEG);
}

double FrenchRAF20::interpolRAF20(const double &latitude_rgf93_deg, const double &longitude_rgf93_deg)
{
	//RAF 20 grid constants
	const double maxLat_deg = 51.5; //Latitude maximale en degrés décimaux comptée positivement vers le nord
	const double minLat_deg = 42.0; //Latitude minimale en degrés décimaux comptée positivement vers le nord 
	const double maxLong_deg = 8.5; //Longitude maximale en degrés décimaux comptée positivement vers l’est
	const double minLong_deg = -5.5; //	Longitude minimale en degrés décimaux comptée positivement vers l’est
	const double stepLong_deg = 0.0333333333333; //Pas en longitude en degrés décimaux
	const double stepLat_deg = 0.025; // Pas en latitude en degrés décimaux

	//Other informations (provided by IGN in the description of the file format)
	//
	/*
	Ordre de rangement(voir « ordre de rangement »): 2 : à latitude constante maximale, longitude croissante, puis latitude décroissante
	Présence des coordonnées de chaque noeud : 0 (non)
	Nombre de valeurs par noeud(hors code de précision, cf.ci - dessous) 1
	Présence du code de précision : 1 (oui)
	Translation appliquée aux valeurs de la grille(autant que de valeurs par noeud) : 0.

	Code de précision:
	Code	Signification
	00		aucune information
	01		< 5 cm
	02		5 à 10 cm
	03		10 à 20 cm
	04		20 à 50 cm
	07		< 2 cm (à venir)
	99		> 1 m

	https://geodesie.ign.fr/contenu/fichiers/documentation/grilles/notices/Grilles-MNT-TXT_Formats.pdf 
	*/

	const int nbLong = floor((maxLong_deg - minLong_deg) / stepLong_deg + 1); // 420
	const int nbLat = floor((maxLat_deg - minLat_deg) / stepLat_deg + 1); // 381
	const int longPerLine = 10;
	const int linePerLat = nbLong / longPerLine + 1; //43


	std::string line;
	std::ifstream rafGridFile ("C:/susoft/ext/Circe/Data/RAF20.tac");

	double gridValue = 0.0;
	std::vector<double> vGridValue;
	int lineNumber = 0;

	// Stop the computation if the point is outside the computation area
	if (latitude_rgf93_deg < minLat_deg || latitude_rgf93_deg > maxLat_deg || longitude_rgf93_deg < minLong_deg || longitude_rgf93_deg > maxLong_deg)
	{
		std::stringstream ss;
		ss << "TNotInGeoidGridException: Point outside RAF20 grid ";
		throw TNotInGeoidGridException(ss.str());
	}

	if (rafGridFile.is_open())
	{

		/*
		Le premier bloc est à latitude max et de longitude min à longitude max avec un pas de 0.03333333
		Le deuxième bloc est à latitude max - 0.025 et de longitude min à longitude max avec un pas de 0.03333333
		Le dernier bloc est à latitude min et de longitude min à longitude max avec un pas de 0.03333333

		*/
		//Find line to get latitude and position of longitude
		double deltaLat = maxLat_deg - latitude_rgf93_deg;
		int blockLatStart = floor(deltaLat / stepLat_deg) * linePerLat + 2;
		double latSup_deg = maxLat_deg - floor(deltaLat / stepLat_deg) * stepLat_deg;
		double latInf_deg = maxLat_deg - (floor(deltaLat / stepLat_deg) + 1) * stepLat_deg;

		double deltaLong = longitude_rgf93_deg - minLong_deg;
		int lineToAdd = floor(deltaLong / stepLong_deg / longPerLine);
		double longSup_deg = minLong_deg + (floor(deltaLong / stepLong_deg) + 1) * stepLong_deg;
		double longInf_deg = minLong_deg + floor(deltaLong / stepLong_deg) * stepLong_deg;

		int lineToStop = blockLatStart + lineToAdd;
		//int longIndexInf = (deltaLong / stepLong_deg - longPerLine * lineToAdd - 1) * 2;
		int longIndexInf = floor(deltaLong / stepLong_deg - longPerLine * lineToAdd) * 2;
		int longIndexSup = 20;

		GotoLine(rafGridFile, lineToStop);

		int valNb = 0;
		while (rafGridFile >> gridValue && valNb<longPerLine*2)
		{
			vGridValue.push_back(gridValue);
			valNb += 1;
		}
		

		double nUL = vGridValue[longIndexInf];

		if (longIndexInf != 10 * 2 - 2)
		{
			longIndexSup = longIndexInf + 2;
		}
		else
		{
			GotoLine(rafGridFile, lineToStop+1);
			longIndexSup = 0;
			valNb = 0;
			vGridValue.clear();
			while (rafGridFile >> gridValue && valNb < longPerLine * 2)
			{
				vGridValue.push_back(gridValue);
				valNb += 1;
			}
		}
		double nUR = vGridValue[longIndexSup];

		GotoLine(rafGridFile, lineToStop+linePerLat);
		valNb = 0;
		vGridValue.clear();
		while (rafGridFile >> gridValue && valNb < longPerLine * 2)
		{
			vGridValue.push_back(gridValue);
			valNb += 1;
		}

		double nLL = vGridValue[longIndexInf];
		if (longIndexInf != 10 * 2 - 2)
		{
			longIndexSup = longIndexInf + 2;
		}
		else
		{
			GotoLine(rafGridFile, lineToStop + linePerLat + 1);
			longIndexSup = 0;
			valNb = 0;
			vGridValue.clear();
			while (rafGridFile >> gridValue && valNb < longPerLine * 2)
			{
				vGridValue.push_back(gridValue);
				valNb += 1;
			}
		}
		double nLR = vGridValue[longIndexSup];

		// Bilinear interpolation
		double n = bilinearInterpolation(nLL, nUL, nLR, nUR, longInf_deg, longSup_deg, latInf_deg, latSup_deg, longitude_rgf93_deg, latitude_rgf93_deg);
		return n;	

	}

	return -9999.9;
}

std::ifstream& FrenchRAF20::GotoLine(std::ifstream &file, unsigned int num)
{
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i)
	{
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

double FrenchRAF20::bilinearInterpolation(float q11, float q12, float q21, float q22, float x1, float x2, float y1, float y2, float x, float y)
{
	float x2x1, y2y1, x2x, y2y, yy1, xx1;
	x2x1 = x2 - x1;
	y2y1 = y2 - y1;
	x2x = x2 - x;
	y2y = y2 - y;
	yy1 = y - y1;
	xx1 = x - x1;
	return 1.0 / (x2x1 * y2y1) * (q11 * x2x * y2y + q21 * xx1 * y2y + q12 * x2x * yy1 + q22 * xx1 * yy1);
}


