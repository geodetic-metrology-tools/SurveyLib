# Create a variable containing all .cpp files:
set(SpatialSystems_SOURCES 
	TASpatialAttribute.cpp
	#TPositionStatus.cpp
	TSpatialOrientation.cpp
	#TSpatialOrientationError.cpp
	TSpatialPosition.cpp
	#TSpatialPositionError.cpp
	TSpatialStatus.cpp
	TSpatialVector.cpp
	#TSpatialVectorError.cpp
	#TSpatialVectorStatus.cpp
)

# Create a variable containing all .h files:
set(SpatialSystems_HEADERS 
	TASpatialAttribute.h
	#TPositionStatus.h
	TSpatialOrientation.h
	TSpatialPosition.h
	#TSpatialPositionError.h
	TSpatialStatus.h
	TSpatialVector.h
	#TSpatialVectorError.h
	#TSpatialVectorStatus.h
)

# Create a static library from sources:
add_library(SpatialSystems STATIC ${SpatialSystems_SOURCES} ${SpatialSystems_HEADERS})