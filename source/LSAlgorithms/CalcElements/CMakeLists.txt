# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(CalcElements_SOURCES 
	TALSCalcParameter.cpp
	TALSComputer.cpp
	TLSInputMatrices.cpp
	TLSParametricMtdComputer.cpp
	TLSResultsMatrices.cpp
)

# Create a variable containing all .h files:
set(CalcElements_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TALSCalcParameter.h
	${SURVEYLIB_INCLUDE_PATH}/TALSComputer.h
	${SURVEYLIB_INCLUDE_PATH}/TLSInputMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/TLSParametricMtdComputer.h
	${SURVEYLIB_INCLUDE_PATH}/TLSResultsMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/UEOIndices.h
)

# Create a static library from sources:
add_library(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})
install(FILES ${CalcElements_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####