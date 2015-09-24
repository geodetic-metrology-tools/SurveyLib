# Create a variable containing all .cpp files:
set(SpatialObj_SOURCES 
	SpatialObjCFns.cpp
	SpatialObjFns.cpp
	SpatialObjJFns.cpp
	TASpatialPtListener.cpp
	TSpatialLine.cpp
	TSpatialLineName.cpp
	TSpatialPlane.cpp
	TSpatialPlaneName.cpp
	TSpatialPoint.cpp
	TSpatialPointName.cpp
	TVMeasurableEntityLstnr.cpp
	TVSpatialPtListener.cpp
	TWire.cpp
)

# Create a variable containing all .h files:
set(SpatialObj_HEADERS 
	SpatialObjCFns.h
	SpatialObjFns.h
	TASpatialPtListener.h
	TPtrWrapper.h
	TSpatialLine.h
	TSpatialLineName.h
	TSpatialPlane.h
	TSpatialPlaneName.h
	TSpatialPoint.h
	TSpatialPointName.h
	TVSpatialPtListener.h
)

# Create a static library from sources:
add_library(SpatialObj STATIC ${SpatialObj_SOURCES} ${SpatialObj_HEADERS})