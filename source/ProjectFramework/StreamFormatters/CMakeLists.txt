CMAKE_POLICY(SET CMP0038 NEW)

# Create a variable containing all .cpp files:
set(StreamFormatters_SOURCES
	#TAFixedColFormatTStream.cpp
	#TAQtStreamFormatter.cpp
	TAStreamFormatter.cpp
	#TBDFixedColFormatTStream.cpp
	TFixedColFormatTStream.cpp
	TFreeFormatTStream.cpp
	#TIStreamFormatterCatalogue.cpp
	#TLGCTStream.cpp
	#TQtFreeFormatTStream.cpp
	#TQtStreamFormatterFactory.cpp
	TSeparatedFormatTStream.cpp
	TStreamFormatterFactory.cpp
)

# Create a variable containing all .h files:
set(StreamFormatters_HEADERS 
	TAStreamFormatter.h
	TFixedColFormatTStream.h
	TFreeFormatTStream.h
	TSeparatedFormatTStream.h
	TStreamFormatterFactory.h
)

# Create a static library from sources:
add_library(StreamFormatters STATIC ${StreamFormatters_SOURCES} ${StreamFormatters_HEADERS})

#link used libraries
#target_link_libraries(StreamFormatters ${PROJECTFRAMEWORK_LIBRARIES} ${SPATIAL_LIBRARIES})