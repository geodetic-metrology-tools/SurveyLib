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
	${SURVEYLIB_INCLUDE_PATH}/TALSCalcParameter.h
	${SURVEYLIB_INCLUDE_PATH}/TALSComputer.h
	${SURVEYLIB_INCLUDE_PATH}/UEOIndices.h
	${SURVEYLIB_INCLUDE_PATH}/TLSInputMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/TLSResultsMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/TLSParametricMtdComputer.h
)

#Create a static library from the object files
ADD_LIBRARY(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})

# Install the header files to the given destination
INSTALL(FILES ${CalcElements_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####