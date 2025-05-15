// SPDX-FileCopyrightText: 2025 CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later

﻿#include <string>

#include "TGraph.h"
#include "TReferenceEllipsoid.h"
#include "TInstrumentMLARF.h"

#include "TSpatialPosition.h"

#include "TIMLA2GCTransformation.h"


void main()
{

	string grs("GRS80"), cgrf("CGRF"), ccs("CCS");
	TReferenceEllipsoid* pGRS80 = TGraph::getGraph()
		->getEllipsoid(TGraph::kGRS80);

	TGeodeticRefFrame* pCGRF = new TGeodeticRefFrame(cgrf);

	
	TSpatialPosition pos(pCGRF);
	TLength coord(0);
	
	TFreeVector falseOrigin(2000, 2097, 2000);
	pos.setXCoord(coord);
	pos.setYCoord(coord);
	pos.setZCoord(coord);

	TInstrumentMLARF* pCCS = new TInstrumentMLARF(ccs, pos,
		TGraph::kGRS80,
		TGraph::kCG2000,
		falseOrigin, TGraph::kCGRF);

	
	TPositionVector P0, P0cgrf;

	P0.setX(2000.00000);
	P0.setY(2097.79265);
	P0.setZ(2000.00097);



	TIMLA2GCTransformation transfo;

	transfo.setSourceFrame(pCCS);
	transfo.setDestinationFrame(pCGRF);

	P0cgrf = transfo.transform(P0);

	cout << P0cgrf.getX() << endl;
	cout << P0cgrf.getY() << endl;
	cout << P0cgrf.getZ() << endl << endl;


	return;
}


