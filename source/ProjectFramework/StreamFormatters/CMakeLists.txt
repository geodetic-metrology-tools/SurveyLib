# Setting the include path - to include a given directory
include_directories (
	.
	${SURVEYLIB_INCLUDE_PATH}
	${NAGC_INCLUDE_PATH}
)




##### This will correspond to one VS project!

# Create a variable containing all .cpp files:
set(StreamFormatters_SOURCES 
	TAStreamFormatter.cpp
	TFixedColFormatTStream.cpp
	TSeparatedFormatTStream.cpp
	TStreamFormatterFactory.cpp
	
	TAFixedColFormatTStream.cpp
	TBDFixedColFormatTStream.cpp
	TFreeFormatTStream.cpp
	TIStreamFormatterCatalogue.cpp
)

# We want these files to appear in the VS project, but not take place in the compilation
set_source_files_properties(
	TAFixedColFormatTStream.cpp
	TBDFixedColFormatTStream.cpp
	TFreeFormatTStream.cpp
	TIStreamFormatterCatalogue.cpp
	${SURVEYLIB_INCLUDE_PATH}/TAFixedColFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TBDFixedColFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TFreeFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TIStreamFormatterCatalogue.h
	${SURVEYLIB_INCLUDE_PATH}/TStreamFormatterFactory.h
	PROPERTIES HEADER_FILE_ONLY TRUE)


# Create a variable containing all .h files:
set(StreamFormatters_HEADERS 
	${SURVEYLIB_INCLUDE_PATH}/TAStreamFormatter.h
	${SURVEYLIB_INCLUDE_PATH}/TFixedColFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TSeparatedFormatTStream.h
	
	${SURVEYLIB_INCLUDE_PATH}/TAFixedColFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TBDFixedColFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TFreeFormatTStream.h
	${SURVEYLIB_INCLUDE_PATH}/TIStreamFormatterCatalogue.h
	${SURVEYLIB_INCLUDE_PATH}/TStreamFormatterFactory.h
)

# Create a static library from sources:
add_library(StreamFormatters STATIC ${StreamFormatters_SOURCES} ${StreamFormatters_HEADERS})
install(FILES ${StreamFormatters_HEADERS} DESTINATION ${INSTALL_PREFIX}/include)
#####