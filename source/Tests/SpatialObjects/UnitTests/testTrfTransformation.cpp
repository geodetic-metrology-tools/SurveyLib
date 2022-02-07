#include <tut/tut.hpp>

#include <TRefFrameInfo.h>
#include <TSpatialPosition.h>
#include <TTrf2TrfTransformation.h>

namespace tut
{
struct test_TTrfTransformation
{
};
typedef test_group<test_TTrfTransformation> factory;
typedef factory::object object;
} // namespace tut

namespace
{
tut::factory tf("Test TTrf2TrfTransformation class");
}

namespace tut
{
template<>
template<>
void object::test<1>()
{
	//Comparison with coordinates computed using Circe software developped by IGN
	set_test_name("Transforming a TSpatialPosition from ITRF2014 at epoch 2014.5 into RGF93v2b");
	TPositionVector pv(4390911.4301, 465773.3452, 4587934.7338, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 2014.5, "ITRF 2014"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93)));

	ensure_equals("RGF93 v2b X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4390911.819), static_cast<TReal>(0.001));
	ensure_equals("RGF93 v2b Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(465772.922), static_cast<TReal>(0.001));
	ensure_equals("RGF93 v2b Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4587934.399), static_cast<TReal>(0.001));

	
}
/*
template<>
template<>
void object::test<2>()
{
	// Comparison with coordinates computed using Circe software developped by IGN
	set_test_name("Transforming a TSpatialPosition from RGF93v2b into ITRF2014 at epoch 2014.5 ");
	TPositionVector pv(4390911.819, 465772.922, 4587934.399, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 2014.5, "ITRF 2014"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kRGF93)));

	ensure_equals("RGF93 v2b X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4390911.4301), static_cast<TReal>(0.001));
	ensure_equals("RGF93 v2b Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(465773.3452), static_cast<TReal>(0.001));
	ensure_equals("RGF93 v2b Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4587934.7338), static_cast<TReal>(0.001));
}
*/
template<>
template<>
void object::test<3>()
{
	
	// CERN coordinates from  ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_I14.CRD 
	//NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	//302 CERN 19762M0011    4393400.5036    466460.9505   4585421.8415    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003


	// CERN coordinates to ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	//NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	//209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003
	set_test_name("Transforming a TSpatialPosition from ITRF 2014 at epoch 2009.0 into ETRF 2000 at epoch 2009.0");
	
	TPositionVector pv(4393400.5036, 466460.9505, 4585421.8415, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 2009.0, "ITRF 2014"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFout, nullptr, 2009.0, "ETRF 2000")));

	ensure_equals("ETRF2000 at 2009.0 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8207),static_cast<TReal>(0.001));
	ensure_equals("ETRF2000 at 2009.0 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6301),static_cast<TReal>(0.001));
	ensure_equals("ETRF2000 at 2009.0 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5734),static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<4>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// CERN coordinates to  ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_I14.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 302 CERN 19762M0011    4393400.5036    466460.9505   4585421.8415    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 2014 at epoch 2009");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2009.0, "ITRF 2014")));

	ensure_equals("ITRF 2014 at 2009.0 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.5036),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2014 at 2009.0 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.9505),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2014 at 2009.0 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.8415),
		static_cast<TReal>(0.001));
}


template<>
template<>
void object::test<5>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 2014 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2014")));

	ensure_equals("ITRF 2014 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.1889),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2014 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3218),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2014 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.6039),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<6>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 2008 at epoch 2022.5");

	TPositionVector pv(4395209.5309, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2008")));

	ensure_equals("ITRF 2008 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.1921),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2008 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3239),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2008 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.6067),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<7>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 2005 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2005")));

	ensure_equals("ITRF 2005 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2009),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2005 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3234),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2005 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.6063),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<8>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 2000 at epoch 2022.5");

	TPositionVector pv(4395209.5309, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2000")));

	ensure_equals("ITRF 2000 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2062),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2000 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3259),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2000 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.5701),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<9>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 97 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 97")));

	ensure_equals("ITRF 97 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2197),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 97 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3284),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 97 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.5242),
		static_cast<TReal>(0.001));
}


template<>
template<>
void object::test<10>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 96 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 96")));

	ensure_equals("ITRF 96 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2197),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 96 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3284),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 96 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.5242),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<11>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 94 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 94")));

	ensure_equals("ITRF 94 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2197),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 94 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3284),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 94 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.5242),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<12>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 93 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8897, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 93")));

	ensure_equals("ITRF 93 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395208.9982),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 93 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.4467),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 93 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.6522),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<13>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 92 at epoch 2022.5");

	TPositionVector pv(4395209.5309, 467745.8897, 4583513.3233, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 92")));

	ensure_equals("ITRF 92 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2246),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 92 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3300),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 92 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.5130),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<14>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 91 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8896, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 91")));

	ensure_equals("ITRF 91 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2427),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 91 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3446),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 91 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.5133),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<15>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 90 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3233, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 90")));

	ensure_equals("ITRF 90 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2420),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 90 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3407),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 90 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.4987),
		static_cast<TReal>(0.001));
}


template<>
template<>
void object::test<16>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 89 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8896, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 89")));

	ensure_equals("ITRF 89 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2620),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 89 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3663),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 89 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.4763),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<17>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ITRF 88 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 88")));

	ensure_equals("ITRF 88 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.2706),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 88 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467746.3295),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 88 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.4667),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<18>()
{
	// Comparison with http://ahgeodev.fr/tfo_plates_i14_sdk.htm
	// Online tool developed by Alain Harmel (head of Geodesy and Levelling service at IGN)

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 2000 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 2000")));

	ensure_equals("ETRF 2000 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.6852),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2000 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7510),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2000 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.1785),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<19>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau 

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837 

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 89 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 89")));

	ensure_equals("ETRF 89 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.7403),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 89 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7778),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 89 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.0777),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<20>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 90 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 90")));

	ensure_equals("ETRF 90 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.7394),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 90 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7802),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 90 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.0771),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<21>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 91 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 91")));

	ensure_equals("ETRF 91 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.7025),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 91 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7280),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 91 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.1210),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<22>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 92 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 92")));

	ensure_equals("ETRF 92 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.7014),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 92 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7284),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 92 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.1206),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<23>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 93 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 93")));

	ensure_equals("ETRF 93 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.6488),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 93 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7833),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 93 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.0986),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<24>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 94 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 94")));

	ensure_equals("ETRF 94 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.6823),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 94 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7565),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 94 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.1334),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<25>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 96 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 96")));

	ensure_equals("ETRF 96 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.6823),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 96 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7565),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 96 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.1334),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<26>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 97 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 97")));

	ensure_equals("ETRF 97 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4395209.6823),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 97 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(467745.7565),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 97 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4583513.1334),
		static_cast<TReal>(0.001));
}


/* To be implemented after bug fixed on http://epncb.oma.be/_productsservices/coord_trans/index.php
template<>
template<>
void object::test<27>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 2005 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 2005")));

	ensure_equals("ETRF 2005 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2005 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2005 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<28>()
{
	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau

	// Coordinates of point 225 in ITRF97 at epoch 1998.5: 4395209.5308 467745.8897 4583513.3232
	// Velocity in ITRF97 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ITRF 97 at epoch 1998.5 into ETRF 2014 at epoch 2022.5");

	TPositionVector pv(4395209.5308, 467745.8895, 4583513.3232, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFin, nullptr, 1998.5, "ITRF 97"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 2014")));

	ensure_equals("ETRF 2014 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2014 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2014 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(),
		static_cast<TReal>(0.001));
}


*/

template<>
template<>
void object::test<29>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 89 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 89")));

	ensure_equals("ETRF 89 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8720),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 89 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6535),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 89 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.4656),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<30>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 90 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 90")));

	ensure_equals("ETRF 90 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8711),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 90 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6559), static_cast<TReal>(0.001));
	ensure_equals("ETRF 90 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.4650),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<31>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 91 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 91")));

	ensure_equals("ETRF 91 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8343),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 91 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6037), static_cast<TReal>(0.001));
	ensure_equals("ETRF 91 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5089),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<32>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 92 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 92")));

	ensure_equals("ETRF 92 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8331),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 92 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6040), static_cast<TReal>(0.001));
	ensure_equals("ETRF 92 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5084),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<33>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 93 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 93")));

	ensure_equals("ETRF 93 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.7806),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 93 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6589), static_cast<TReal>(0.001));
	ensure_equals("ETRF 93 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.4865),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<34>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 94 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 94")));

	ensure_equals("ETRF 94 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8141),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 94 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6322), static_cast<TReal>(0.001));
	ensure_equals("ETRF 94 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5212),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<35>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 96 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 96")));

	ensure_equals("ETRF 96 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8141),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 96 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6322), static_cast<TReal>(0.001));
	ensure_equals("ETRF 96 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5212),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<36>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 97 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 97")));

	ensure_equals("ETRF 97 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8141),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 97 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6322), static_cast<TReal>(0.001));
	ensure_equals("ETRF 97 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5212),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<37>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 2000 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 2000")));

	ensure_equals("ETRF 2000 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8169),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2000 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6270),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2000 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5662),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<38>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 2005 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 2005")));

	ensure_equals("ETRF 2005 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.8337),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2005 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.6495),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2005 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.5914),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<39>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ETRF 2014 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ETRF 2014")));

	ensure_equals("ETRF 2014 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.7745),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2014 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466460.5846),
		static_cast<TReal>(0.001));
	ensure_equals("ETRF 2014 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.6191),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<40>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 88 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 88")));

	ensure_equals("ITRF 88 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.4024),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 88 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2052),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 88 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.8544),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<41>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 89 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 89")));

	ensure_equals("ITRF 89 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3938),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 89 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2420), static_cast<TReal>(0.001));
	ensure_equals("ITRF 89 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.8640),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<42>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 90 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 90")));

	ensure_equals("ITRF 90 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3738),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 90 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2164), static_cast<TReal>(0.001));
	ensure_equals("ITRF 90 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.8864),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<43>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 91 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 91")));

	ensure_equals("ITRF 91 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3745),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 91 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2203), static_cast<TReal>(0.001));
	ensure_equals("ITRF 91 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9010),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<44>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 92 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 92")));

	ensure_equals("ITRF 92 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3564),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 92 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2056), static_cast<TReal>(0.001));
	ensure_equals("ITRF 92 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9006),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<45>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 93 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 93")));

	ensure_equals("ITRF 93 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.1299),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 93 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.3223), static_cast<TReal>(0.001));
	ensure_equals("ITRF 93 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585422.0398),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<46>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 94 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 94")));

	ensure_equals("ITRF 94 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3515),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 94 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2039), static_cast<TReal>(0.001));
	ensure_equals("ITRF 94 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9118),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<47>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 97 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 97")));

	ensure_equals("ITRF 97 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3515),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 97 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2039), static_cast<TReal>(0.001));
	ensure_equals("ITRF 97 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9118),
		static_cast<TReal>(0.001));
}


template<>
template<>
void object::test<48>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 2000 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2000")));

	ensure_equals("ITRF 2000 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3380),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2000 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.2014),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2000 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9577),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<49>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 2005 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2005")));

	ensure_equals("ITRF 2005 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3327),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2005 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.1990),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2005 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9940),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<50>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 2008 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2008")));

	ensure_equals("ITRF 2008 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3239),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2008 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.1994),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2008 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9943),
		static_cast<TReal>(0.001));
}

template<>
template<>
void object::test<51>()
{
	// CERN coordinates from ftp://rgpdata.ign.fr/pub/products/ITRF_coord/RGP19_E00.CRD
	// NUM  STATION NAME           X (M)          Y (M)          Z (M)     FLAG   FM           TO           RMV MIN_VAR_EP        SE       SN       SU
	// 209 CERN 19762M0011    4393400.8207    466460.6301   4585421.5734    I    11:009:00000                  2014.76647      0.0001   0.0001   0.0003

	// Comparison with http://epncb.oma.be/_productsservices/coord_trans/index.php
	// Online tool developed by the EPN Central Bureau
	// Velocity in ETRF 2000 from http://ahgeodev.fr/tfo_plates_i14_sdk.htm : -0.01296 0.01828 0.00837

	set_test_name("Transforming a TSpatialPosition from ETRF 2000 at epoch 2009 into ITRF 2014 at epoch 2022.5");

	TPositionVector pv(4393400.8207, 466460.6301, 4585421.5734, TCoordSysFactory::k3DCartesian);

	TSpatialPosition position(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kETRFin, nullptr, 2009.0, "ETRF 2000"));
	ensure("Setting the coordinates of TSpatialPosition", position.setCoordinates(pv));
	ensure("Transform returns true", position.transform(TRefFrameInfo::getReferenceFrame(TRefSystemFactory::kITRFout, nullptr, 2022.5, "ITRF 2014")));

	ensure_equals("ITRF 2014 at 2022.5 X", position.getCoordinates(TCoordSysFactory::k3DCartesian).getX().getMetresValue(), static_cast<TReal>(4393400.3207),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2014 at 2022.5 Y", position.getCoordinates(TCoordSysFactory::k3DCartesian).getY().getMetresValue(), static_cast<TReal>(466461.1974),
		static_cast<TReal>(0.001));
	ensure_equals("ITRF 2014 at 2022.5 Z", position.getCoordinates(TCoordSysFactory::k3DCartesian).getZ().getMetresValue(), static_cast<TReal>(4585421.9916),
		static_cast<TReal>(0.001));
}

} // namespace tut
