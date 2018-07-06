#include  "TGraph.h"
#include  "TCernGridGeoid.h"
#include  "TGeodeticRefFrame.h"

#include  "TSpatialPosition.h"
#include  "TPositionStatus.h"

#include  <iomanip>


void main(){


//	TGeodeticRefFrame refFrame("Geodetic Reference Frame");
//	TGeodeticRefFrame* ref = &refFrame;
	
	
	
//	TRefSurfServer SurfacesServer;
	TVGeoidModel* geoid = 
		TGraph::getGraph()->getGeoid(TGraph::kCG2000);


	cout << geoid->getName() << endl;
	cout << geoid->getGeoidId() << endl;


	TSpatialPosition spos(TGraph::getGraph()->getRefFrame(TGraph::kCCS)),
		spos2(TGraph::getGraph()->getRefFrame(TGraph::kCCS)),
		spos3(TGraph::getGraph()->getRefFrame(TGraph::kCCS)),
		spos4(TGraph::getGraph()->getRefFrame(TGraph::kCCS)),
		spos5(TGraph::getGraph()->getRefFrame(TGraph::kCCS));
	
	TLength z(LITERAL(2000.0));
	TLength x(2000), y(LITERAL(2097.79265)), z1(LITERAL(2000.00079));
	spos.setXCoord(x);
	spos.setYCoord(y);
	spos.setZCoord(z1);

	TLength x2(-LITERAL(4999.9999999)), y2(0), z2(2000);
	spos2.setXCoord(x2);
	spos2.setYCoord(y2);
	spos2.setZCoord(z2);

	TLength x3(4200), y3(LITERAL(3720.569)), z3(2000);
	spos3.setXCoord(x3);
	spos3.setYCoord(y3);
	spos3.setZCoord(z3);

	TLength x4(-LITERAL(3758.345)), y4(11000);
	spos4.setXCoord(x4);
	spos4.setYCoord(y4);
	spos4.setZCoord(z);

	TLength x5(-LITERAL(4565.12580)), y5(LITERAL(1478.25020));
	spos5.setXCoord(x5);
	spos5.setYCoord(y5);
	spos5.setZCoord(z);

	spos.setPositionStatus(TPositionStatus::kCala);
	spos2.setPositionStatus(TPositionStatus::kCala);
	spos3.setPositionStatus(TPositionStatus::kCala);
	spos4.setPositionStatus(TPositionStatus::kCala);
	spos5.setPositionStatus(TPositionStatus::kCala);

	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(5);
	cout << spos.getXCoord().getMetresValue() << "   " << spos.getYCoord().getMetresValue();

	cout.precision(7);
	cout << "   " << geoid->getEta(spos).getGonsValue() << "   ";
	cout << geoid->getXi(spos).getGonsValue() << "   ";
	cout.precision(5);
	cout << geoid->getN(spos).getMetresValue() << " " << geoid->getDAlpha(spos).getGonsValue() << endl;

	cout << spos.getReferenceFrame()->getName() << endl << endl;


	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(5);
	cout << spos2.getXCoord().getMetresValue() << "   " << spos2.getYCoord().getMetresValue();

	cout.precision(7);
	cout << "   " << geoid->getEta(spos2).getGonsValue() << "   ";
	cout << geoid->getXi(spos2).getGonsValue() << "   ";
	cout.precision(5);
	cout << geoid->getN(spos2).getMetresValue() << " " << geoid->getDAlpha(spos2).getGonsValue() << endl << endl;


	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(5);
	cout << spos3.getXCoord().getMetresValue() << "   " << spos3.getYCoord().getMetresValue();

	cout.precision(7);
	cout << "   " << geoid->getEta(spos3).getGonsValue() << "   ";
	cout << geoid->getXi(spos3).getGonsValue() << "   ";
	cout.precision(5);
	cout << geoid->getN(spos3).getMetresValue() << " " << geoid->getDAlpha(spos3).getGonsValue() << endl << endl;


	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(5);
	cout << spos4.getXCoord().getMetresValue() << "   " << spos4.getYCoord().getMetresValue();

	cout.precision(7);
	cout << "   " << geoid->getEta(spos4).getGonsValue() << "   ";
	cout << geoid->getXi(spos4).getGonsValue() << "   ";
	cout.precision(5);
	cout << geoid->getN(spos4).getMetresValue() << " " << geoid->getDAlpha(spos4).getGonsValue() << endl << endl;


	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout.precision(5);
	cout << spos5.getXCoord().getMetresValue() << "   " << spos5.getYCoord().getMetresValue();

	cout.precision(7);
	cout << "   " << geoid->getEta(spos5).getGonsValue() << "   ";
	cout << geoid->getXi(spos5).getGonsValue() << "   ";
	cout.precision(5);
	cout << geoid->getN(spos5).getMetresValue() << " " << geoid->getDAlpha(spos5).getGonsValue() << endl << endl;


//	geoid.getN(spos);


	return;




};