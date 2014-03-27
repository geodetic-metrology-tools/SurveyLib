# Create a variable containing all .cpp files:
SET(CalcElements_SOURCES 
	TALSCalcParameter.cpp
	TALSComputer.cpp
	TLSInputMatrices.cpp
	TLSResultsMatrices.cpp	
	TLSParametricMtdComputer.cpp
)

# Create a variable containing all .h files:
SET(CalcElements_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TALSCalcParameter.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TALSComputer.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/UEOIndices.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSInputMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSResultsMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/lsalgo/TLSParametricMtdComputer.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})
#####