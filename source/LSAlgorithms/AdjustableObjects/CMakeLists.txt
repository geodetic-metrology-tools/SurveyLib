include_directories(${CMAKE_SOURCE_DIR}
					${SURVEYLIB_ROOT}/source/LSAlgorithms/AdjustableObjects
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialSystems
					${SURVEYLIB_ROOT}/source/SpatialObjects/SpatialObj
					
)

set(ADJUSTABLE_HEADERS
	TAdjustablePoint.h
	TVAdjustableObject.h
	TAdjustableLine.h
	TAdjustableHelmertTransformation.h
	TAdjustableAngle.h
	TAdjustablePlane.h
	TAdjustableScalar.h
	TAdjustableLength.h
	TAdjustableObjectCollection.h
	TTransformParameters.h
)

set(ADJUSTABLE_SOURCES
	TAdjustablePoint.cpp
	TAdjustableLine.cpp
	TAdjustableHelmertTransformation.cpp
	TAdjustableAngle.cpp
	TAdjustablePlane.cpp
	TAdjustableScalar.cpp
	TAdjustableLength.cpp
)

#Create a static library from the object files
ADD_LIBRARY(AdjustableObjects STATIC ${ADJUSTABLE_HEADERS} ${ADJUSTABLE_SOURCES} )
