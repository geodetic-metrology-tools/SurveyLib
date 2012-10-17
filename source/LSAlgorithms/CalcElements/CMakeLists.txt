# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(CalcElements_SOURCES 
	TALSCalcParameter.cpp
	TALSComputer.cpp
	
	TLSInputMatrices.cpp
	TLSResultsMatrices.cpp
	
	TLSParametricMtdComputer.cpp
)
#	TLSInputSparseMatrices.cpp
#	TLSResultsSparseMatrices.cpp
#	TLSComputer.cpp
#	TLSSparseMatrixComputer.cpp

# Create a variable containing all .h files:
set(CalcElements_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TALSCalcParameter.h
	${SURVEYLIB_INCLUDE_PATH}/TALSComputer.h
	${SURVEYLIB_INCLUDE_PATH}/UEOIndices.h
	
	${SURVEYLIB_INCLUDE_PATH}/TLSInputMatrices.h
	${SURVEYLIB_INCLUDE_PATH}/TLSResultsMatrices.h

	${SURVEYLIB_INCLUDE_PATH}/TLSParametricMtdComputer.h
)
#	${SURVEYLIB_INCLUDE_PATH}/TLSInputSparseMatrices.h
#	${SURVEYLIB_INCLUDE_PATH}/TLSResultsSparseMatrices.h
#	${SURVEYLIB_INCLUDE_PATH}/TLSSparseMatrixComputer.h
#	${SURVEYLIB_INCLUDE_PATH}/TLSComputer.h


# Create a static library from sources:
add_library(CalcElements STATIC ${CalcElements_SOURCES} ${CalcElements_HEADERS})
install(FILES ${CalcElements_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####