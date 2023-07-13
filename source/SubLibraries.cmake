# This variables are referenced in other projects, too!
SET(SURVEYLIB_LIBRARIES
	Logs
	LSAlgorithms
	Plugins
	ProjectFramework
	SpatialObjects
	SpatialObjDLL
	Tools
	CSGeoDLL
)

# External libs
# Silently check if the external libraries are available in the specified paths
# Show the version if yes

# Eigen 
IF(EXISTS ${EIGEN_INCLUDE_PATH}/Eigen/src/Core/util/Macros.h)
	file(READ ${EIGEN_INCLUDE_PATH}/Eigen/src/Core/util/Macros.h ver)
	
	string(REGEX MATCH "EIGEN_WORLD_VERSION ([0-9]*)" _ ${ver})
	set(ver_major ${CMAKE_MATCH_1})
	string(REGEX MATCH "EIGEN_MAJOR_VERSION ([0-9]*)" _ ${ver})
	set(ver_minor ${CMAKE_MATCH_1})
	string(REGEX MATCH "EIGEN_MINOR_VERSION ([0-9]*)" _ ${ver})
	set(ver_patch ${CMAKE_MATCH_1})
	
	message("-- Found Eigen at ${EIGEN_INCLUDE_PATH} (found version: ${ver_major}.${ver_minor}.${ver_patch})")
ENDIF(EXISTS ${EIGEN_INCLUDE_PATH}/Eigen/src/Core/util/Macros.h)

IF(USE_SERIALIZER)
	LIST(APPEND SURVEYLIB_LIBRARIES Serialization)
ENDIF(USE_SERIALIZER)

SET(SPATIAL_LIBRARIES
	AffineTransformations
	MathematicalConcepts
	ReferenceSurfaces
	RefFrameTransformations
	ShortestPath
	SpatialObj
	SpatialSystems
)

SET(PROJECTFRAMEWORK_LIBRARIES
	Converters
	FiltersAndFormats
	ProjectData
	StreamFormatters
)

SET(LSALGO_LIBRARIES
	CalcElements
	CalcParams
	AdjustableObjects
)

SET(ALL_SURVEYLIB_LIBS
	${SPATIAL_LIBRARIES}
	${PROJECTFRAMEWORK_LIBRARIES}
)
