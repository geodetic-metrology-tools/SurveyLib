# set include directories needed by this library

message ("BOOST : ${BOOST_ROOT}")

include_directories(${BOOST_ROOT}
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/CalcParams)

# Create a variable containing all .cpp files:
SET(CalcElements_SOURCES 
	TALSCalcParameter.cpp
	TALSComputer.cpp
	TLSInputMatrices.cpp
	TLSParametricMtdComputer.cpp
	TLSWeightedUnkMtdComputer.cpp
	TLSCombinedMtdComputer.cpp
	TLSCnstMtdComputer.cpp
	TLSResultsMatrices.cpp
	QuantileFunctions.cpp
)

# Create a variable containing all .h files:
SET(CalcElements_HEADERS 
	TALSCalcParameter.h
	TALSComputer.h
	TLSCalcWorkingUnknown.h
	TLSInputMatrices.h
	TLSParametricMtdComputer.h
	TLSWeightedUnkMtdComputer.h
	TLSCombinedMtdComputer.h
	TLSCnstMtdComputer.h
	TLSResultsMatrices.h
	UEOIndices.h
	QuantileFunctions.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})