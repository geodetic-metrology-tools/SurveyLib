# Create a variable containing all .cpp files:
set(Measurments_SOURCES 

)

# Create a variable containing all .h files:
set(Measurments_HEADERS 
	TAInstrumentStation.h
	TAngleConstants.h
	TDistConstants.h
)

# Create a static library from sources:
add_library(Measurments STATIC ${Measurments_SOURCES} ${Measurments_HEADERS})