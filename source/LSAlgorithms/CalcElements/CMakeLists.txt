# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/CalcParams
					${BOOST_ROOT})

# Create a variable containing all .cpp files:
SET(CalcElements_SOURCES 
	TALSCalcParameter.cpp
	TALSComputer.cpp
	#TLSCalcDataSet.cpp
	#TLSCalculation.cpp
	#TLSComputer.cpp
	#TLSConstraintIdentifier.cpp
	TLSInputMatrices.cpp
	#TLSInputSparseMatrices.cpp
	TLSParametricMtdComputer.cpp
	TLSResultsMatrices.cpp
	#TLSResultsSparseMatrices.cpp
	#TLSSparseMatrixComputer.cpp
	#TUnknownAngle.cpp
	#TUnknownLength.cpp
	#TUnknownParameter.cpp
	QuantileFunctions.cpp
	TLSCnstMtdComputer.cpp
	TLSCombinedMtdComputer.cpp
	TLSWeightedUnkMtdComputer.cpp
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
	QuantileFunctions.h
	TLSCnstMtdComputer.h
	TLSCombinedMtdComputer.h
	TLSWeightedUnkMtdComputer.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})