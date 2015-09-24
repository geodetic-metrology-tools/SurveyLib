# Create a variable containing all .cpp files:
SET(CalcElements_SOURCES 
	TALSCalcParameter.cpp
	TALSComputer.cpp
	TLSCalcDataSet.cpp
	TLSCalculation.cpp
	TLSComputer.cpp
	TLSConstraintIdentifier.cpp
	TLSInputMatrices.cpp
	TLSInputSparseMatrices.cpp
	TLSParametricMtdComputer.cpp
	TLSResultsMatrices.cpp
	TLSResultsSparseMatrices.cpp
	TLSSparseMatrixComputer.cpp
	TUnknownAngle.cpp
	TUnknownLength.cpp
	TUnknownParameter.cpp
)

# Create a variable containing all .h files:
SET(CalcElements_HEADERS 
	TALSCalcParameter.h
	TALSComputer.h
	TLSCalcWorkingUnknown.h
	TLSInputMatrices.h
	TLSParametricMtdComputer.h
	TLSResultsMatrices.h
	UEOIndices.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})