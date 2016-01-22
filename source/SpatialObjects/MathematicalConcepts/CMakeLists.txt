# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/MathematicalConcepts)

# Create a variable containing all .cpp files:
set(MathematicalConcepts_SOURCES 
	Quad.cpp
	T2DCartesianCoordSys.cpp
	T2DCartesianPlusHSys.cpp
	T3DCartesianCoordSys.cpp
	T3DMatrix.cpp
	TACoordinateSystem.cpp
	TACoordSysMatrix.cpp
	TACoordSysVector.cpp
	TAngle.cpp
	TColumnVector.cpp
	TCoordSysFactory.cpp
	TDist.cpp
	TDouble.cpp
	TFreeVector.cpp
	TGeodeticCoordSys.cpp
	TLength.cpp
	TMatrix.cpp
	TMatrixImpl.cpp
	TPositionVector.cpp
	TRotationMatrix.cpp
	TScalar.cpp
	TSparseMatrix.cpp
)

# Create a variable containing all .h files:
set(MathematicalConcepts_HEADERS 
	Quad.h
	T2DCartesianCoordSys.h
	T2DCartesianPlusHSys.h
	T3DCartesianCoordSys.h
	T3DMatrix.h
	TACoordinateSystem.h
	TACoordSysMatrix.h
	TACoordSysVector.h
	TAngle.h
	TColumnVector.h
	TConstants.h
	TCoordSysFactory.h
	TDist.h
	TDouble.h
	TFreeVector.h
	TGeodeticCoordSys.h
	TLength.h
	TMatrix.h
	TMatrixImpl.h
	TPositionVector.h
	TRotationMatrix.h
	TScalar.h
	TSparseMatrix.h
	TVCoordinateSystem.h
)

# Create a static library from sources:
add_library(MathematicalConcepts STATIC ${MathematicalConcepts_SOURCES} ${MathematicalConcepts_HEADERS})