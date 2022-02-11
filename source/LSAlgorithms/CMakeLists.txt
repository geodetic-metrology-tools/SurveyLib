include_directories(${CMAKE_SOURCE_DIR}
					${BOOST_ROOT}
					${SURVEYLIB_ROOT}/source/LSAlgorithms/headers/AdjustableObjects
					${SURVEYLIB_ROOT}/source/LSAlgorithms/headers/CalcElements
					${SURVEYLIB_ROOT}/source/LSAlgorithms/headers/CalcParams
					${SURVEYLIB_ROOT}/source/LSAlgorithms/headers/CalcAlternatives
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/AffineTransformations
					${SURVEYLIB_ROOT}/source/Tools/headers/
					${SURVEYLIB_ROOT}/source/Logs
)

set(ALGO_HEADERS
	headers/AdjustableObjects/TAdjustablePoint.h
	headers/AdjustableObjects/TVAdjustableObject.h
	headers/AdjustableObjects/TAdjustableHelmertTransformation.h
	headers/AdjustableObjects/TAdjustableAngle.h
	headers/AdjustableObjects/TAdjustableScalar.h
	headers/AdjustableObjects/TAdjustableLength.h
	headers/AdjustableObjects/TTransformParameters.h
	headers/CalcElements/TALSCalcParameter.h
	headers/CalcElements/TALSComputer.h
	headers/CalcElements/TLSCalcWorkingUnknown.h
	headers/CalcElements/TLSInputMatrices.h
	headers/CalcElements/TLSParametricMtdComputer.h
	headers/CalcElements/TLSWeightedUnkMtdComputer.h
	headers/CalcElements/TLSCombinedMtdComputer.h
	headers/CalcElements/TLSCnstMtdComputer.h
	headers/CalcElements/TLSResultsMatrices.h
	headers/CalcElements/UEOIndices.h
	headers/CalcElements/QuantileFunctions.h
	headers/CalcParams/TLSCalcFreeVectorParam.h
	headers/CalcParams/TLSCalcLengthParam.h
	headers/CalcParams/TLSCalcOrientationParam.h
	headers/CalcParams/TLSCalcPosVectorParam.h
	headers/CalcParams/TLSCalcScalarParam.h
	headers/CalcParams/TLSCalcWorkingPosVec.h
	headers/CalcAlternatives/TALTSvd.h
)

set(ALGO_SOURCES
	sources/AdjustableObjects/TAdjustablePoint.cpp
	sources/AdjustableObjects/TAdjustableHelmertTransformation.cpp
	sources/AdjustableObjects/TAdjustableAngle.cpp
	sources/AdjustableObjects/TAdjustableScalar.cpp
	sources/AdjustableObjects/TAdjustableLength.cpp
	sources/CalcElements/TALSCalcParameter.cpp
	sources/CalcElements/TALSComputer.cpp
	sources/CalcElements/TLSInputMatrices.cpp
	sources/CalcElements/TLSParametricMtdComputer.cpp
	sources/CalcElements/TLSWeightedUnkMtdComputer.cpp
	sources/CalcElements/TLSCombinedMtdComputer.cpp
	sources/CalcElements/TLSCnstMtdComputer.cpp
	sources/CalcElements/TLSResultsMatrices.cpp
	sources/CalcElements/QuantileFunctions.cpp
	sources/CalcParams/TLSCalcFreeVectorParam.cpp
	sources/CalcParams/TLSCalcLengthParam.cpp
	sources/CalcParams/TLSCalcOrientationParam.cpp
	sources/CalcParams/TLSCalcPosVectorParam.cpp
	sources/CalcParams/TLSCalcScalarParam.cpp
	sources/CalcParams/TLSCalcWorkingPosVec.cpp
	sources/CalcAlternatives/TALTSvd.cpp
)

#Create a static library from the object files
ADD_LIBRARY(LSAlgorithms STATIC ${ALGO_HEADERS} ${ALGO_SOURCES} )

# Specify the libraries to link against
target_link_libraries(LSAlgorithms Tools Logs SpatialObjects)


# Define VS folders:
file(GLOB ADJUSTABLEOBJECT_H				headers/AdjustableObjects/*.*)
file(GLOB ADJUSTABLEOBJECT_CPP				sources/AdjustableObjects/*.*)
file(GLOB CALCELMT_H						headers/CalcElements/*.*)
file(GLOB CALCELMT_CPP						sources/CalcElements/*.*)
file(GLOB CALCPARAMS_H						headers/CalcParams/*.*)
file(GLOB CALCPARAMS_CPP					sources/CalcParams/*.*)
file(GLOB CALCALT_H							headers/CalcAlternatives/*.*)
file(GLOB CALCALT_CPP						sources/CalcAlternatives/*.*)
source_group("AdjustableObject\\Headers"	FILES ${ADJUSTABLEOBJECT_H})
source_group("AdjustableObject\\Sources"	FILES ${ADJUSTABLEOBJECT_CPP})
source_group("CalcElements\\Headers"		FILES ${CALCELMT_H})
source_group("CalcElements\\Sources"		FILES ${CALCELMT_CPP})
source_group("CalcParams\\Headers"			FILES ${CALCPARAMS_H})
source_group("CalcParams\\Sources"			FILES ${CALCPARAMS_CPP})
source_group("CalcAlternatives\\Headers"	FILES ${CALCALT_H})
source_group("CalcAlternatives\\Sources"	FILES ${CALCALT_CPP})

set_target_properties(LSAlgorithms PROPERTIES FOLDER "SurveyLib")
