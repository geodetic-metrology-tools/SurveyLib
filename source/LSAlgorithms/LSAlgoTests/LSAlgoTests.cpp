// LSInputMatricesFillerTest.cpp

// includes for LGCProject
#include "TAStreamFormatter.h"
#include "TSeparatedFormatTStream.h"
#include "TLGCFileReader.h"
#include "TLGCDataSet.h"
#include "TLGCProject.h"
#include "TLGCApplication.h"
//#include "TGeodeticRefFrame.h"

// includes for ObsMkr
#include "TObservationMaker.h"

// includes for LSCalcObsMkr
#include "TLSCalcObservationMaker.h"

// includes for input matrices filling
#include "TLSInputMatricesFiller.h"
#include "TLSLocalSysContribGenFactory.h"
#include "TLSInputMatrices.h"

// includes for calculation
#include "TLSParametricMtdComputer.h"
#include "TLSResultsMatricesExtractor.h"
#include "TLSResultsMatrices.h"

#include "TLGCFileWriter.h"


void main()
{
	//////////////////////////////////////////////////////////////
	//Read a input LGCFilevv with the load function of TLGCProject
	//////////////////////////////////////////////////////////////

	const char * LGCFile;
	LGCFile = "C:\\Temp\\TI8Horizontal\\TI8Horizontal1.inp";

	// settings for file parameters
	TFileParameters fp;
	fp.setFileName(LGCFile);

	cout << fp.getPath() << "\\" << fp.getName() << endl;
	cout << fp.defined() << endl;

	// creating an (empty) application and a project
	//TLGCApplication application;
	TLGCProject project;

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
			cout << "LSCalc observations processed " << endl;
			// CALCUL NORMAL
			TLSLocalSysContribGenFactory* facto = new TLSLocalSysContribGenFactory(); // local factory of contribution generators for observations
			TLSInputMatricesFiller		  filler(facto);	// matrices filler initialized with the factory
			TLSInputMatrices			  matrices;
			// Updates of the data set's indices
			dataset.updateIndices();
			if (dataset.indicesConsistency()) {
				cout << "indices consistent" << endl;
				// Filling
				bool filling = filler.fillMatrices(dataset,matrices);	
				if (filling) {
					cout << "input matrices filled " << endl;
//					matrices.saveMatricesToFile(1);
					const TMatrix& A = matrices.getFirstDgnMtrx();
					const TMatrix& P = matrices.getWeightMtrx();
					const TColumnVector& w = matrices.getMisclosureVctr();
					int ninc = A.numCols();

					TLSResultsMatrices	resMat(dataset.getDimensions());

					TColumnVector* sol = resMat.getSolutionVctr();
					TMatrix* unkCov = resMat.getUnkCovarMtrx();
					
					TMatrix* N = new TMatrix(ninc,ninc);
					TMatrix* inter = new TMatrix(ninc,ninc);

					int n_pivot(ninc-1);
					int* pivot_i;
					int* pivot_j;

					pivot_i = new int [n_pivot+1];
					pivot_j = new int [n_pivot+1];

					(*N) = A.transposed() * P * A;
					
					(*sol) = A.transposed() * P * w;

					(*inter)  = N->dfact(&n_pivot,pivot_i,pivot_j);

					if (!(inter->isNull()))
					{
						(*sol) = inter->dfeqn(sol,n_pivot,pivot_i,pivot_j);
						(*unkCov) = inter->dfinv(&n_pivot,pivot_i,pivot_j);
//						resMat.saveMatricesToFile(1);

						TLSResultsMatricesExtractor* extractor = new TLSResultsMatricesExtractor(&dataset);
						extractor->setReferenceSurface(project.getCalcParams()->getRefSurface());
						bool DSextracted(false);
						DSextracted = extractor->extractResults(resMat, *(project.getCalcParams()));//						TLGCFileWriter()
						if (DSextracted)
						{
							TLGCFileWriter file;
							file.setOutputOptions(project.getOutputOptions());
							file.setCalcParams(project.getCalcParams());
							file.writeFile(data,&dataset);
						}
					}
					else
						cout << "erreur " << endl;

					delete N,inter,sol,unkCov;

				}
			}
		}
	}
	return;
}


//					TMatrix* invN = new TMatrix(ninc,ninc);


//					cout << "after N is computed " << endl;
//					TMatrix& invN = N.inverseAasen();
//					TMatrix& invN = N.inverseSym();
//					TMatrix& NbigId = invN * N;
					
//					TMatrix* unkCov = resMat.getUnkCovarMtrx();
//					*unkCov = LITERAL(0.0);
//					*unkCov = N.inverseAasen();
/*					TMatrix* Ninv = new TMatrix(N.numCols(),N.numRows());
					TMatrix* Nbig0 = new TMatrix(N.numCols(),N.numRows());
					*Ninv = N.inverseSym();
					cout << "after N is inverted" << endl;
					*Nbig0 = (*Ninv)*N - N*(*Ninv);
					real max = LITERAL(0.0);
					for (int i=0;i<N.numRows();i++)
					{
						for (int j=0;j<N.numCols();j++)
						{
							if (__fabsq((*Nbig0)(i,j))>max)
								max = __fabsq((*Nbig0)(i,j));
						}
					}
					cout << "max " << max << endl;*/
/*					ostringstream oss;
					oss << "C:\\temp\\NId" << ".txt";
					string fileName = oss.str();

					ofstream of(fileName.c_str(), ios::out);
					if (!of){
						//cout << "Impossible d'ouvrir le fichier C:\\temp\\resultsMatrices.txt" << '\n';
						exit (1);
					}

					of << setprecision(9);
					of << "**********" << endl;
					of << "* NBigId *" << endl;
					of << "**********" << endl << endl;
					
					for (int i=0; i<NbigId.numRows() ; i++){

						for (int j=0; j<NbigId.numRows() ; j++)
							of << (NbigId)(i,j) << '\t';
						of << endl;
					}
					of << endl << endl;

					of << "**************" << endl;
					of << "* NBigIdDiag *" << endl;
					of << "**************" << endl << endl;
					
					for (i=0; i<NbigId.numRows() ; i++){

						of << (NbigId)(i,i) << endl;
					}
					of << endl << endl;

					of.close();
					
					cout << "copied" << endl;*/

/*					TColumnVector* sol = resMat.getSolutionVctr();
					*sol = LITERAL(0.0);
					*sol = *unkCov * A.transposed() * P * matrices.getMisclosureVctr();

					TLSResultsMatricesExtractor extractor(&dataset);
					bool DSextracted = extractor.extractResults(A,resMat,*(project.getCalcParams()));
					if (DSextracted) {
						cout << "copying results matrices..." << endl;
						resMat.saveMatricesToFile(1);
					}

				}
			}*/
		
			// CALCUL LIBRE
/*			dataset.updateIndices();
			TLSConstraintIdentifier freeConstraint;
			freeConstraint.initCnstrIdentifier(dataset.getLSWorkingPosVector(), obs);
			dataset.setFreeConstraints(freeConstraint);
			TLSInputMatricesFiller* inpMtrFiller = new TLSInputMatricesFiller(new TLSLocalSysContribGenFactory);
			TLSInputMatrices* im = new TLSInputMatrices();

			bool mtrFilled = inpMtrFiller->fillMatrices(dataset, *im);
//			inputMtr->saveMatricesToFile(fNumberOfMadeIterations);

			TLSResultsMatrices* rm = new TLSResultsMatrices(dataset.getDimensions());
			cout << "Entered computer\n";

			const TMatrix& firstDM = im->getFirstDgnMtrx(); //A1
			const TMatrix& weightM = im->getWeightMtrx();  //P
			const TColumnVector& misclV = im->getMisclosureVctr(); //W1

			const TMatrix& cnstrFirstDM = im->getCnstrFirstDgnMtrx(); //A2
			const TColumnVector& cnstrMisclV = im->getCnstrMisclosureVctr(); //W2      

			int nbUnk = firstDM.numCols();
			int nbObs = firstDM.numRows();
			int nbCnstr = cnstrFirstDM.numRows();

			//intermediate N = (A1tPA1) matrix
			TMatrix	N (nbUnk, nbUnk);
			N = LITERAL(0.0);
			
			N = firstDM.transposed() * weightM * firstDM;

			TMatrix	Nbig (nbUnk + nbCnstr, nbUnk + nbCnstr);
			Nbig = LITERAL(0.0);

			//insert N in Nbig
			int i = 0;
			while( i < nbUnk )
			{
				int j = 0;
				while(j < nbUnk)
				{
					Nbig(i,j) = N(i,j);
					j++;
				}
				i++;
			}

			//insert A2 in Nbig
			i = nbUnk;
			int I = 0;
			while( I < nbCnstr )
			{
				int j = 0;
				while(j < nbUnk)
				{
					Nbig(i,j) = cnstrFirstDM(I,j);
					j++;
				}
				i++;
				I++;
			}

			//insert A2t in Nbig
			TMatrix	A2t = cnstrFirstDM.transposed();
			i = 0;
			while( i < nbUnk )
			{
				int	j = nbUnk;
				int J = 0;
				while(J < nbCnstr)
				{
					Nbig(i,j) = A2t(i,J);
					j++;
					J++;
				}
				i++;
			}
			
			TMatrix* NbigId = new TMatrix(nbUnk + nbCnstr,nbUnk + nbCnstr);
			cout << "Nb lignes: " << nbUnk + nbCnstr << endl << endl;
			*NbigId = Nbig.inverseSym() * Nbig;
			// inverse Nbig
//			TMatrix* unkCov = rm->getUnkCovarMtrx();
//			*unkCov = LITERAL(0.0);
//			*unkCov = Nbig * Nbig.inverseSym();
//			TLSResultsMatricesExtractor extractor(&dataset);
//			bool DSextracted = extractor.extractResults(firstDM,*rm,*(project.getCalcParams()));
//			if (DSextracted) {
				cout << "copying NbigId..." << endl;
//				rm->saveMatricesToFile(1);
				ostringstream oss;
				oss << "C:\\temp\\NbigId" << ".txt";
				string fileName = oss.str();

				ofstream of(fileName.c_str(), ios::out);
				if (!of){
					//cout << "Impossible d'ouvrir le fichier C:\\temp\\resultsMatrices.txt" << '\n';
					exit (1);
				}

				of << setprecision(9);
				of << "**********" << endl;
				of << "* NBigId *" << endl;
				of << "**********" << endl << endl;
				
				for (i=0; i<NbigId->numRows() ; i++){

					for (int j=0; j<NbigId->numRows() ; j++)
						of << (*NbigId)(i,j) << '\t';
					of << endl;
				}
				of << endl << endl;

				of.close();
				
				cout << "copied" << endl;

//			}
			
		}*/


/*	const char * LGCFile;
	LGCFile = "C:\\temp\\LSAlgorithmsTest\\ALLOBS.inp";

	// settings for Data parameters
	TFileParameters fp;
	fp.setFileName(LGCFile);

	cout << fp.getPath() << "\\" << fp.getName() << endl;
	cout << fp.defined() << endl;

	// creating an (empty) application and a project
	//TLGCApplication application;
	TLGCProject project;

	// use of load function
	project.load(fp);


	// Definition of a pointer to the input data formatted in the project as a TLGCDataSet
	TLGCDataSet* data = new TLGCDataSet();
	data = project.getDataSet();
	ObservationSet obs;
	
	//Use of the maker in order to generate input data formatted as LGC++-defined observations
	TObservationMaker maker; // object used for the data conversion
	
	bool B = maker.processData(*data,obs); // processing of the data to observations

	// check of the processing validity
	if (B) 
		cout << "Observations processed" << endl;
	else
	{
		cout << "Processing failed" << endl;
		return;
	}

	// Use of the ls calc maker in order to generate input data for least-square calculation,
	// formatted as LGC++-defined LSCalc observations, and LSAlgorithms-defined parameters
	LSCalcDataSet dataset; // definition of the ls calc observation processing output (LGC++-defined LSCalc observations)
	TLSCalcObservationMaker lsmkr; // object used for the data conversion
	
	bool answer = lsmkr.processData(obs,dataset); // processing of the observations to ls calc observations & parameters

	// check of the processing validity
	if (answer) {
		cout << "LS Calc Observations & parameters processed" << endl;
	}
	else
	{
		cout << "LS Calc processing failed" << endl;
		return;
	}

	// Use of the LSInputMatricesFiller in order to format ls calc data into LSAlgorithms-defined input matrices
	TLSLocalSysContribGenFactory* facto = new TLSLocalSysContribGenFactory(); // local factory of contribution generators for observations
	TLSInputMatricesFiller		  filler(facto);	// matrices filler initialized with the factory
	TLSInputMatrices			  matrices;
	// Updates of the data set's indices
	dataset.updateIndices();

	//checks that the indices are consistent
	cout << "Update of indices" << endl;
	cout << "U " << dataset.getDimensions().UIndex << endl;
	cout << "E " << dataset.getDimensions().EIndex << endl;
	cout << "O " << dataset.getDimensions().OIndex << endl;	
	if (dataset.indicesConsistency()) {
		// Filling
		bool filling = filler.fillMatrices(dataset,matrices);	
		if (filling) {
			cout << "Input matrices filled" << endl;
			cout << "copying input matrices..." << endl;
			matrices.saveMatricesToFile(1);
			TLSParametricMtdComputer computer;
			TLSResultsMatrices	resMat(dataset.getDimensions());
			bool computed = computer.computeResultsMtrs(&matrices, &resMat);
			if (computed)
			{	// extract the results from the matrices
				TLSResultsMatricesExtractor extractor(&dataset);
				bool DSextracted = extractor.extractResults(resMat,LITERAL(0.1));
				if (DSextracted) {
					cout << "copying results matrices..." << endl;
					resMat.saveMatricesToFile(1);
					
					cout << "POINTS" << endl;
					LSPosVecIter iterPV = dataset.beginPV();
					while (iterPV!=dataset.endPV()) {
						cout << iterPV->getName() << endl;
						cout << iterPV->getCorrection().getX().getMMetresValue() << " // " << iterPV->getEstimatedPrecision().getX().getMMetresValue() << endl;
						cout << iterPV->getCorrection().getY().getMMetresValue() << " // " << iterPV->getEstimatedPrecision().getY().getMMetresValue() <<  endl;
						cout << iterPV->getCorrection().getZ().getMMetresValue() << " // " << iterPV->getEstimatedPrecision().getZ().getMMetresValue() <<  endl;
						iterPV++;
					}
					cout << endl;
					cout << "ORIENTATIONS" << endl;
					LSOrientIter iterO = dataset.beginOrient();
					while (iterO!=dataset.endOrient()) {
						cout << iterO->getName() << endl;
						cout << iterO->getCorrection().omega.getRadiansValue() << " // " << iterO->getEstimatedPrecision().omega.getGonsValue() << endl;
						cout << iterO->getCorrection().phi.getRadiansValue() << " // " << iterO->getEstimatedPrecision().phi.getGonsValue() << endl;
						cout << iterO->getCorrection().kappa.getRadiansValue() << " // " << iterO->getEstimatedPrecision().kappa.getGonsValue() << endl;
						iterO++;
					} 
					cout << endl;
					cout << "LONGUEUR" << endl;
					LSLengthIter iterL = dataset.beginLength();
					while (iterL!=dataset.endLength()) {
						cout << iterL->getName() << endl;
						cout << iterL->getCorrection().getMetresValue() << " // " << iterL->getEstimatedPrecision().getMMetresValue() << endl;
						iterL++;
					}
					cout << endl;*/

/*					cout << "OBSERVATIONS ANGLES HOR." << endl;
					cout << "s0Post: " << dataset.getS0APosteriori().getValue() << endl;
					LSHorAngIter	iterha = dataset.beginLSHorAng();
					while (iterha!=dataset.endLSHorAng()) {
						cout << iterha->getObsAngle().getGonsValue() << " // " << iterha->getSigmaAPriori().getGonsValue() << endl;
						cout << iterha->getEstimatedAngle().getGonsValue() << " // " << iterha->getResidue().getGonsValue() << endl;
						cout << iterha->getSigmaAPosteriori().getGonsValue() << endl;
						iterha++;
					}
					cout << endl;*/
/*
					cout << "OBSERVATIONS DISTANCES HOR." << endl;
					cout << "s0Post: " << dataset.getS0APosteriori().getValue() << endl;
					LSHorDistIter	iterhd = dataset.beginLSHorDist();
					while (iterhd!=dataset.endLSHorDist()) {
						cout << iterhd->getObsDist().getMetresValue() << " // " << iterhd->getSigmaAPriori().getMMetresValue() << endl;
						cout << iterhd->getEstimatedDist().getMetresValue() << " // " << iterhd->getResidue().getMMetresValue() << endl;
						cout << iterhd->getSigmaAPosteriori().getMetresValue() << endl;
						iterhd++;
					}
*/
/*					cout << "OBSERVATIONS DISTANCES SPAT." << endl;
					cout << "s0Post: " << dataset.getS0APosteriori().getValue() << endl;
					LSSpaDistIter	itersd = dataset.beginLSSpaDist();
					while (itersd!=dataset.endLSSpaDist()) {
						cout << itersd->getObsDist().getMetresValue() << " // " << itersd->getSigmaAPriori().getMMetresValue() << endl;
						cout << itersd->getEstimatedDist().getMetresValue() << " // " << itersd->getResidue().getMMetresValue() << endl;
						cout << itersd->getSigmaAPosteriori().getMetresValue() << endl;
						itersd++;
					}*/

/*
					cout << "OBSERVATIONS ANGLES ZEN." << endl;
					cout << "s0Post: " << dataset.getS0APosteriori().getValue() << endl;
					LSZenDistIter	iterzd = dataset.beginLSZenDist();
					while (iterzd!=dataset.endLSZenDist()) {
						cout << iterzd->getObsAngle().getGonsValue() << " // " << iterzd->getSigmaAPriori().getGonsValue() << endl;
						cout << iterzd->getEstimatedAngle().getGonsValue() << " // " << iterzd->getResidue().getGonsValue() << endl;
						cout << iterzd->getSigmaAPosteriori().getGonsValue() << endl;
						iterzd++;
					}
					cout << endl;*/

/*				}
				else
					cout << extractor.getError() << endl;
			}
			else
				cout << computer.getError() << endl;
		}
		else
		{
			cout << "Input matrices filling failed" << endl;
			return;
		}
	}
	else {
		cout << "Not enough observations!!!" << endl;
		return;
	}

}*/