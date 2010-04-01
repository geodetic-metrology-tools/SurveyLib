///////////////////////////////////////////////////////////////
//test
//03/2003
///////////////////////////////////////////////////////////////

//#include <iostream>
//#include <string>
//using namespace std;

#include "TAStreamFormatter.h"
#include "TSeparatedFormatTStream.h"
#include "TLGCFileReader.h"
#include "TLGCDataSet.h"
#include "TLGCProject.h"
#include "TLGCApplication.h"

// includes for ObsMkr
#include "TObservationMaker.h"

// includes for LSCalcObsMkr
#include "TLSCalcObservationMaker.h"

// includes for input matrices filling
#include "TLSInputMatricesFiller.h"
#include "TLSLocalSysContribGenFactory.h"
#include "TLSGeoSysContribGenFactory.h"
#include "TLSInputMatrices.h"


// includes for calculation
#include "TLSCalculation.h"

// includes for writer
#include "TLGCFaultDetectionFileWriter.h"
#include "TLGCFileWriter.h"

#include "LSCalcDataSet.h"
#include	<cmath>
#include	<nag.h>
#include	<nagg01.h>

void  erel()
//void main()
{
/*	static NagError fail;
	fail.print = false;
	quad wmax = nag_deviates_normal(Nag_UpperTail,0.1,&fail);

	cout << wmax << endl;*/

	//////////////////////////////////////////////////////////////
	//Read a input LGCFilevv with the load function of TLGCProject
	//////////////////////////////////////////////////////////////

	const char * LGCFile;
	LGCFile = "C:\\temp\\resLGC\\allobs.inp";

	// settings for file parameters
	TFileParameters fp;
	fp.setFileName(LGCFile);

	cout << fp.getPath() << "\\" << fp.getName() << endl;
	cout << fp.defined() << endl;

	TLGCProject project;

	// use of load function
	project.load(fp);

	// Definition of a pointer to the input data formatted in the project as a TLGCDataSet
	TLGCDataSet* data = new TLGCDataSet();
	data = project.getDataSet();
	ObservationSet obs;
	
	//Use of the maker in order to generate input data formatted as LGC++-defined observations
	TObservationMaker maker; // object used for the data conversion
	
	bool B = maker.processData(*data,obs);

	if (B) {
		cout << "Observations processed" << endl;
		LSCalcDataSet dataset; // definition of the ls calc observation processing output (LGC++-defined LSCalc observations)
		TLSCalcObservationMaker lsmkr; // object used for the data conversion
	
		bool answer = lsmkr.processData(obs,dataset); // processing of the observations to ls calc observations & parameters

		if (answer) {
			cout << "LS Calc Observations & parameters processed" << endl;
			TLSCalculation	calc(*project.getCalcParams());
			calc.computeSolution(obs, dataset);

			LSRelErrorIter iterb = dataset.getLSWorkingRelErrors()->begin();

			while (iterb!=dataset.getLSWorkingRelErrors()->end()) {
				
				cout << "point 1: " << iterb->getPoint1()->getName() << endl;
				cout << "point 2: " << iterb->getPoint2()->getName() << endl << endl;

				cout << "sigmaL: " << iterb->getSigmaL().getMMetresValue() << endl;
				cout << "sigmaG: " << iterb->getSigmaG().getGonsValue() << endl;
				cout << "sigmaR: " << iterb->getSigmaR().getMMetresValue() << endl;
				cout << "sigmaZ: " << iterb->getSigmaZ().getMMetresValue() << endl;
				cout << "sigmaV: " << iterb->getSigmaV().getGonsValue() << endl << endl;
				iterb++;
			}
		}
	}

	return;
}
