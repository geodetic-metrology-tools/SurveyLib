FOREACH(lib ${SPATIAL_LIBRARIES})
	ADD_SUBDIRECTORY(${lib})
ENDFOREACH(lib)

IF(NOT MINGW)
# This is the DLL project to access spatial objects as C-style functions through a DLL
ADD_SUBDIRECTORY(SpatialObjects)
ENDIF(NOT MINGW)