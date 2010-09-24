# add subdirectories
SET(PROJECTFRAMEWORK_LIB_SUBPROJECTS
	Converters
	FiltersAndFormats
	ProjectData
	StreamFormatters
)

FOREACH(subproject ${PROJECTFRAMEWORK_LIB_SUBPROJECTS})
    ADD_SUBDIRECTORY(${subproject})
	SET_PROPERTY(TARGET ${subproject} PROPERTY FOLDER "ProjectFramework")
ENDFOREACH(subproject) 


ADD_SUBDIRECTORY(ProjectFrameworkLibraryStatic)
SET_PROPERTY(TARGET ProjectFrameworkLibrary PROPERTY FOLDER "ProjectFramework")
install(FILES ProjectFramework-config.cmake DESTINATION ${INSTALL_PREFIX})