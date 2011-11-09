# add subdirectories that are a part of the library
SET(LSALGORITHMS_LIB_SUBPROJECTS
	CalcElements
	CalcParams
)

FOREACH(subproject ${LSALGORITHMS_LIB_SUBPROJECTS})
    ADD_SUBDIRECTORY(${subproject})
	SET_PROPERTY(TARGET ${subproject} PROPERTY FOLDER "LSAlgorithms")
ENDFOREACH(subproject) 

ADD_SUBDIRECTORY(LSAlgorithmsLibraryStatic)
SET_PROPERTY(TARGET LSAlgorithmsLibrary PROPERTY FOLDER "LSAlgorithms")
