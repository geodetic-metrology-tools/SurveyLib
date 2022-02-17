# set include directories needed by this library
include_directories(${SURVEYLIB_ROOT}/source/SpatialObjects/headers/AffineTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ReferenceSurfaces
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/RefFrameTransformations
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ShortestPath
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialObj
					${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialSystems
					${SURVEYLIB_ROOT}/source/Logs
					# Eigen
					${EIGEN_INCLUDE_PATH}

)

add_definitions(-DCIRCE_EXEC_DIR="${CIRCE_EXEC_DIR}")

IF(USE_SWISSTOPO)
	include_directories(C:/Windows/System32
		${REFRAME_LIBRARY_DIR}
	)
	link_directories(${REFRAME_LIBRARY_DIR})
ENDIF()

# Create a variable containing all .cpp files:
set(SpatialObject_SOURCES 
	sources/AffineTransformations/TAAffineTransformation.cpp
	sources/AffineTransformations/TAffineTransformWrapper.cpp
	sources/AffineTransformations/TCompositeAffTransform.cpp
	sources/AffineTransformations/THelmertTransformation.cpp
	sources/AffineTransformations/TReflection.cpp
	sources/AffineTransformations/TRotation.cpp
	sources/AffineTransformations/TScaleFactor.cpp
	sources/AffineTransformations/TTranslation.cpp
	sources/MathematicalConcepts/Quad.cpp
	sources/MathematicalConcepts/T2DCartesianCoordSys.cpp
	sources/MathematicalConcepts/T2DCartesianPlusHSys.cpp
	sources/MathematicalConcepts/T3DCartesianCoordSys.cpp
	sources/MathematicalConcepts/T3DMatrix.cpp
	sources/MathematicalConcepts/TACoordinateSystem.cpp
	sources/MathematicalConcepts/TACoordSysMatrix.cpp
	sources/MathematicalConcepts/TACoordSysVector.cpp
	sources/MathematicalConcepts/TAngle.cpp
	sources/MathematicalConcepts/TColumnVector.cpp
	sources/MathematicalConcepts/TCoordSysFactory.cpp
	sources/MathematicalConcepts/TDist.cpp
	sources/MathematicalConcepts/TDouble.cpp
	sources/MathematicalConcepts/TFreeVector.cpp
	sources/MathematicalConcepts/TGeodeticCoordSys.cpp
	sources/MathematicalConcepts/TLength.cpp
	sources/MathematicalConcepts/TMatrix.cpp
	sources/MathematicalConcepts/TMatrixImpl.cpp
	sources/MathematicalConcepts/TPositionVector.cpp
	sources/MathematicalConcepts/TRotationMatrix.cpp
	sources/MathematicalConcepts/TScalar.cpp
	sources/MathematicalConcepts/TSparseMatrix.cpp
	sources/ReferenceSurfaces/T3DLocalRefFrame.cpp
	sources/ReferenceSurfaces/TA2DPlus1MapProjection.cpp
	sources/ReferenceSurfaces/TA3DEuclideanRefFrame.cpp
	sources/ReferenceSurfaces/TAGeoidModel.cpp
	sources/ReferenceSurfaces/TAModifiedLocalAstronomicalRF.cpp
	sources/ReferenceSurfaces/TAReferenceFrame.cpp
	sources/ReferenceSurfaces/TCernGridGeoid.cpp
	sources/ReferenceSurfaces/TCernParabolicGeoid.cpp
	sources/ReferenceSurfaces/TCernSphereGeoid.cpp
	sources/ReferenceSurfaces/TGeodeticRefFrame.cpp
	sources/ReferenceSurfaces/TGeoidValues.cpp
	sources/ReferenceSurfaces/TGraphLocalAstronomicalRF.cpp
	sources/ReferenceSurfaces/TGraphMLARF.cpp
	sources/ReferenceSurfaces/TModifiedLocalAstronomicalRF.cpp
	sources/ReferenceSurfaces/TModifiedLocalGeodeticRF.cpp
	sources/ReferenceSurfaces/TTerrestrialReferenceFrame.cpp
	sources/ReferenceSurfaces/TReferenceEllipsoid.cpp
	sources/ReferenceSurfaces/TX0Y0HeProjection.cpp
	sources/ReferenceSurfaces/TXYHeProjection.cpp
	sources/ReferenceSurfaces/TXYHgProjection.cpp
	sources/RefFrameTransformations/TARefFrameTransformation.cpp
	sources/RefFrameTransformations/TGC2LGTransformation.cpp
	sources/RefFrameTransformations/TGC2MLATransformation.cpp
	sources/RefFrameTransformations/THelmertRefFrameTransform.cpp
	sources/RefFrameTransformations/TLA2LGTransformation.cpp
	sources/RefFrameTransformations/TLambert93Transformation.cpp
	sources/RefFrameTransformations/TLG2GCTransformation.cpp
	sources/RefFrameTransformations/TLG2LATransformation.cpp
	sources/RefFrameTransformations/TMLA2GCTransformation.cpp
	sources/RefFrameTransformations/TMLA2XYHeTransformation.cpp
	sources/RefFrameTransformations/TMLA2XYHsTransformation.cpp
	sources/RefFrameTransformations/TRGF93CC46Transformation.cpp
	sources/RefFrameTransformations/TTrf2TrfTransformation.cpp
	sources/RefFrameTransformations/TX0Y0He2XYHeTransformation.cpp
	sources/RefFrameTransformations/TXYHe2MLATransformation.cpp
	sources/RefFrameTransformations/TXYHe2X0Y0HeTransformation.cpp
	sources/RefFrameTransformations/TXYHe2XYHgTransformation.cpp
	sources/RefFrameTransformations/TXYHg2XYHeTransformation.cpp
	sources/RefFrameTransformations/TXYHs2MLATransformation.cpp
	sources/RefFrameTransformations/TXYH2CCS.cpp
	sources/RefFrameTransformations/CirceIGN.cpp
	sources/ShortestPath/TGraph.cpp
	sources/ShortestPath/TLocalSystemOrigin.cpp
	sources/ShortestPath/TRefFrameInfo.cpp
	sources/ShortestPath/TRefFrameWrapper.cpp
	sources/ShortestPath/TRefSystemFactory.cpp
	sources/ShortestPath/TTransformWrapper.cpp
	sources/ShortestPath/TCoordSysInfo.cpp
	sources/ShortestPath/TAngularUnitsInfo.cpp
	sources/SpatialObj/SpatialObjFns.cpp
	sources/SpatialObj/TASpatialPtListener.cpp
	sources/SpatialObj/TSpatialLine.cpp
	sources/SpatialObj/TSpatialLineName.cpp
	sources/SpatialObj/TSpatialPlane.cpp
	sources/SpatialObj/TSpatialPlaneName.cpp
	sources/SpatialObj/TSpatialPoint.cpp
	sources/SpatialObj/TSpatialPointName.cpp
	sources/SpatialObj/TVSpatialPtListener.cpp
	sources/SpatialSystems/TASpatialAttribute.cpp
	sources/SpatialSystems/TSpatialOrientation.cpp
	sources/SpatialSystems/TSpatialPosition.cpp
	sources/SpatialSystems/TSpatialStatus.cpp
	sources/SpatialSystems/TSpatialVector.cpp
)

# Create a variable containing all .h files:
set(SpatialObject_HEADERS 
	headers/AffineTransformations/TAAffineTransformation.h
	headers/AffineTransformations/TAffineTransformWrapper.h
	headers/AffineTransformations/TCompositeAffTransform.h
	headers/AffineTransformations/THelmertTransformation.h
	headers/AffineTransformations/TReflection.h
	headers/AffineTransformations/TRotation.h
	headers/AffineTransformations/TScaleFactor.h
	headers/AffineTransformations/TTranslation.h
	headers/AffineTransformations/TVAffineTransformation.h
	headers/MathematicalConcepts/Quad.h
	headers/MathematicalConcepts/T2DCartesianCoordSys.h
	headers/MathematicalConcepts/T2DCartesianPlusHSys.h
	headers/MathematicalConcepts/T3DCartesianCoordSys.h
	headers/MathematicalConcepts/T3DMatrix.h
	headers/MathematicalConcepts/TACoordinateSystem.h
	headers/MathematicalConcepts/TACoordSysMatrix.h
	headers/MathematicalConcepts/TACoordSysVector.h
	headers/MathematicalConcepts/TAngle.h
	headers/MathematicalConcepts/TColumnVector.h
	headers/MathematicalConcepts/TConstants.h
	headers/MathematicalConcepts/TCoordSysFactory.h
	headers/MathematicalConcepts/TDist.h
	headers/MathematicalConcepts/TDouble.h
	headers/MathematicalConcepts/TFreeVector.h
	headers/MathematicalConcepts/TGeodeticCoordSys.h
	headers/MathematicalConcepts/TLength.h
	headers/MathematicalConcepts/TMatrix.h
	headers/MathematicalConcepts/TMatrixImpl.h
	headers/MathematicalConcepts/TPositionVector.h
	headers/MathematicalConcepts/TRotationMatrix.h
	headers/MathematicalConcepts/TScalar.h
	headers/MathematicalConcepts/TSparseMatrix.h
	headers/MathematicalConcepts/TVCoordinateSystem.h
	headers/ReferenceSurfaces/T3DLocalRefFrame.h
	headers/ReferenceSurfaces/TA2DPlus1MapProjection.h
	headers/ReferenceSurfaces/TA3DEuclideanRefFrame.h
	headers/ReferenceSurfaces/TAGeoidModel.h
	headers/ReferenceSurfaces/TAModifiedLocalAstronomicalRF.h
	headers/ReferenceSurfaces/TAReferenceFrame.h
	headers/ReferenceSurfaces/TCernGridGeoid.h
	headers/ReferenceSurfaces/TCernParabolicGeoid.h
	headers/ReferenceSurfaces/TCernSphereGeoid.h
	headers/ReferenceSurfaces/TGeodeticRefFrame.h
	headers/ReferenceSurfaces/TGeoidValues.h
	headers/ReferenceSurfaces/TGraphLocalAstronomicalRF.h
	headers/ReferenceSurfaces/TGraphMLARF.h
	headers/ReferenceSurfaces/TLambert93Projection.h
	headers/ReferenceSurfaces/TLV03Projection.h
	headers/ReferenceSurfaces/TLV95Projection.h
	headers/ReferenceSurfaces/TModifiedLocalAstronomicalRF.h
	headers/ReferenceSurfaces/TModifiedLocalGeodeticRF.h
	headers/ReferenceSurfaces/TNotInGeoidGridException.h
	headers/ReferenceSurfaces/TNotInLepGridException.h
	headers/ReferenceSurfaces/TReferenceEllipsoid.h
	headers/ReferenceSurfaces/TReferenceFrameServer.h
	headers/ReferenceSurfaces/TRGF93CC46Projection.h
	headers/ReferenceSurfaces/TTerrestrialReferenceFrame.h
	headers/ReferenceSurfaces/TVGeoidModel.h
	headers/ReferenceSurfaces/TVReferenceFrame.h
	headers/ReferenceSurfaces/TX0Y0HeProjection.h
	headers/ReferenceSurfaces/TXYHeProjection.h
	headers/ReferenceSurfaces/TXYHgProjection.h
	headers/RefFrameTransformations/TARefFrameTransformation.h
	headers/RefFrameTransformations/TGC2LGTransformation.h
	headers/RefFrameTransformations/TGC2MLATransformation.h
	headers/RefFrameTransformations/THelmertRefFrameTransform.h
	headers/RefFrameTransformations/TLA2LGTransformation.h
	headers/RefFrameTransformations/TLambert93Transformation.h
	headers/RefFrameTransformations/TLG2GCTransformation.h
	headers/RefFrameTransformations/TLG2LATransformation.h
	headers/RefFrameTransformations/TMLA2GCTransformation.h
	headers/RefFrameTransformations/TMLA2XYHeTransformation.h
	headers/RefFrameTransformations/TMLA2XYHsTransformation.h
	headers/RefFrameTransformations/TRGF93CC46Transformation.h
	headers/RefFrameTransformations/TTrf2TrfTransformation.h
	headers/RefFrameTransformations/TVRefFrameTransformation.h
	headers/RefFrameTransformations/TVTransformation.h
	headers/RefFrameTransformations/TX0Y0He2XYHeTransformation.h
	headers/RefFrameTransformations/TXYHe2MLATransformation.h
	headers/RefFrameTransformations/TXYHe2X0Y0HeTransformation.h
	headers/RefFrameTransformations/TXYHe2XYHgTransformation.h
	headers/RefFrameTransformations/TXYHg2XYHeTransformation.h
	headers/RefFrameTransformations/TXYHs2MLATransformation.h
	headers/RefFrameTransformations/TXYH2CCS.h
	headers/RefFrameTransformations/GeodeticConstants.h
	headers/RefFrameTransformations/CirceIGN.h
	headers/ShortestPath/DynamicPriorityQueue.h
	headers/ShortestPath/PtrGreater.h
	headers/ShortestPath/TGraph.h
	headers/ShortestPath/TLocalSystemOrigin.h
	headers/ShortestPath/TRefFrameInfo.h
	headers/ShortestPath/TRefFrameWrapper.h
	headers/ShortestPath/TRefSystemFactory.h
	headers/ShortestPath/TTransformWrapper.h
	headers/ShortestPath/TNotInGraphException.h
	headers/ShortestPath/TCoordSysInfo.h
	headers/ShortestPath/TAngularUnitsInfo.h
	headers/SpatialObj/SpatialObjFns.h
	headers/SpatialObj/TASpatialPtListener.h
	headers/SpatialObj/TPtrWrapper.h
	headers/SpatialObj/TSpatialLine.h
	headers/SpatialObj/TSpatialLineName.h
	headers/SpatialObj/TSpatialPlane.h
	headers/SpatialObj/TSpatialPlaneName.h
	headers/SpatialObj/TSpatialPoint.h
	headers/SpatialObj/TSpatialPointName.h
	headers/SpatialObj/TVSpatialPtListener.h
	headers/SpatialSystems/counted_ptr.h
	headers/SpatialSystems/TASpatialAttribute.h
	headers/SpatialSystems/TSpatialOrientation.h
	headers/SpatialSystems/TSpatialPosition.h
	headers/SpatialSystems/TSpatialStatus.h
	headers/SpatialSystems/TSpatialVector.h
)

#Add transformations if Swisstopo is used
IF(USE_SWISSTOPO)
	set(SpatialObject_SOURCES 
		${SpatialObject_SOURCES}
		sources/RefFrameTransformations/TLV03Transformation.cpp
		sources/RefFrameTransformations/TLV95Transformation.cpp
	)
	set(SpatialObject_HEADERS 
		${SpatialObject_HEADERS}
		headers/RefFrameTransformations/TLV03Transformation.h
		headers/RefFrameTransformations/TLV95Transformation.h
	)
ENDIF(USE_SWISSTOPO)

# Define VS folders:
file(GLOB AFFINETRANSFORMATION_H 		headers/AffineTransformations/*.*)
file(GLOB AFFINETRANSFORMATION_CPP		sources/AffineTransformations/*.*)
file(GLOB MATHEMATICALCONCEPT_H 		headers/MathematicalConcepts/*.*)
file(GLOB MATHEMATICALCONCEPT_CPP		sources/MathematicalConcepts/*.*)
file(GLOB REFSURFACES_H 				headers/ReferenceSurfaces/*.*)
file(GLOB REFSURFACES_CPP				sources/ReferenceSurfaces/*.*)
file(GLOB REFRAMETRANSFO_H 				headers/RefFrameTransformations/*.*)
file(GLOB REFRAMETRANSFO_CPP			sources/RefFrameTransformations/*.*)
file(GLOB SHORTESPATH_H 				headers/ShortestPath/*.*)
file(GLOB SHORTESPATH_CPP				sources/ShortestPath/*.*)
file(GLOB SPATIALOBJ_H 				    headers/SpatialObj/*.*)
file(GLOB SPATIALOBJ_CPP				sources/SpatialObj/*.*)
file(GLOB SPATIALSYSTEM_H 				headers/SpatialSystems/*.*)
file(GLOB SPATIALSYSTEM_CPP				sources/SpatialSystems/*.*)

source_group("AffineTransformations\\Headers"   	FILES ${AFFINETRANSFORMATION_H})
source_group("AffineTransformations\\Sources"   	FILES ${AFFINETRANSFORMATION_CPP})
source_group("MathematicalConcepts\\Headers"   		FILES ${MATHEMATICALCONCEPT_H})
source_group("MathematicalConcepts\\Sources"   		FILES ${MATHEMATICALCONCEPT_CPP})
source_group("ReferenceSurfaces\\Headers"   		FILES ${REFSURFACES_H})
source_group("ReferenceSurfaces\\Sources"   		FILES ${REFSURFACES_CPP})
source_group("RefFrameTransformations\\Headers"   	FILES ${REFRAMETRANSFO_H})
source_group("RefFrameTransformations\\Sources"   	FILES ${REFRAMETRANSFO_CPP})
source_group("ShortestPath\\Headers"   				FILES ${SHORTESPATH_H})
source_group("ShortestPath\\Sources"   				FILES ${SHORTESPATH_CPP})
source_group("SpatialObj\\Headers"   				FILES ${SPATIALOBJ_H})
source_group("SpatialObj\\Sources"   				FILES ${SPATIALOBJ_CPP})
source_group("SpatialSystems\\Headers"   			FILES ${SPATIALSYSTEM_H})
source_group("SpatialSystems\\Sources"   			FILES ${SPATIALSYSTEM_CPP})

# Create a static library from sources:
add_library(SpatialObjects STATIC ${SpatialObject_SOURCES} ${SpatialObject_HEADERS})
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(SpatialObjects PRIVATE optimized OpenMP::OpenMP_CXX)
endif()

# link directories
target_include_directories(SpatialObjects PUBLIC
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/AffineTransformations
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/MathematicalConcepts
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ReferenceSurfaces
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/RefFrameTransformations
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/ShortestPath
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialObj
	${SURVEYLIB_ROOT}/source/SpatialObjects/headers/SpatialSystems
	${SURVEYLIB_ROOT}/source/Logs
	# Eigen
	${EIGEN_INCLUDE_PATH}
)

# needed for linux compilation
set_target_properties(SpatialObjects PROPERTIES POSITION_INDEPENDENT_CODE ON)

# disable multi-process compilation for swisstopo
if(USE_SWISSTOPO AND MSVC)
	target_compile_options(SpatialObjects PRIVATE "/MP1")
endif()

# Define IDE folders:
set_target_properties(SpatialObjects PROPERTIES FOLDER "SurveyLib")
