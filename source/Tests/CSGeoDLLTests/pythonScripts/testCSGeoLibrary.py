import os
import sys
import tempfile
import ctypes as ct
from ctypes import cdll
import unittest

  
# Initially loads the DLL or Shared Object module
if 'linux' in sys.platform:
    myDLL = cdll.LoadLibrary('../../../../build/staging/libCSGeoDLL.so')
else:
    myDLL = ct.WinDLL('C:\susoft\SurveyLib\build\staging\CSGeoDLL.dll')
 
 
# Definition of the structure containing reference-frame info
class PyPlainDataParameters(ct.Structure):
    _fields_ = [("refFrame", ct.c_int),
                ("coordSys", ct.c_int),
                ("angUnits", ct.c_int),
                ("epoch", ct.c_double),
                ("solution", ct.c_char_p),
                ("geoidPath", ct.c_char_p)]  # path to a geoid grid file (None: ellipsoidal heights)
                  
# Definition of the structure containing ORIGIN point info            
class PyPlainLocalSystemOrigin(ct.Structure):
    _fields_ = [("x", ct.c_double),
                ("y", ct.c_double),
                ("z", ct.c_double),
                ("gisement", ct.c_double),
                ("slope", ct.c_double)]
                  
# Description of the parameter types (essentially pointers on data)           
myDLL.transformPoint.argtypes = [ ct.POINTER(ct.c_double), ct.POINTER(ct.c_double), ct.POINTER(ct.c_double),
                                  ct.POINTER(PyPlainDataParameters), ct.POINTER(PyPlainLocalSystemOrigin),
                                  ct.POINTER(PyPlainDataParameters), ct.POINTER(PyPlainLocalSystemOrigin) ]
myDLL.transformPoint.restypes = ct.c_int

# Status codes returned by transformPoint (see EStatusCode in PlainTransform.h)
kOk = 0
kInvalidInputGeoid = 19
kInvalidOutputGeoid = 20

# Synthetic geoid grid (same field as source/Tests/SpatialObjects/UnitTests/GeoidTestGrid.h):
# the undulation is linear in longitude / latitude, so bilinear interpolation is exact
GRID_LON_MIN = 5.0
GRID_LAT_MIN = 45.0
GRID_STEP = 0.25
GRID_NB_LON = 16   # 5.0 -> 9.0
GRID_NB_LAT = 12   # 45.0 -> 48.0

def expectedN(lonDeg, latDeg):
    return 40.0 + 2.0 * (lonDeg - GRID_LON_MIN) + 1.0 * (latDeg - 45.0)

def createGeoidGrid():
    """Write the synthetic geoid as an ESRI ASCII grid (read by GDAL AAIGrid driver) and return its path as bytes"""
    path = os.path.join(tempfile.gettempdir(), 'surveylib_python_test_geoid_v1.asc')
    lines = ['ncols %d' % GRID_NB_LON,
             'nrows %d' % GRID_NB_LAT,
             'xllcorner %.2f' % GRID_LON_MIN,
             'yllcorner %.2f' % GRID_LAT_MIN,
             'cellsize %.2f' % GRID_STEP,
             'NODATA_value -9999']
    # rows from north to south, values at the cell centres
    for row in range(GRID_NB_LAT):
        lat = GRID_LAT_MIN + (GRID_NB_LAT - row - 0.5) * GRID_STEP
        lines.append(' '.join('%.6f' % expectedN(GRID_LON_MIN + (col + 0.5) * GRID_STEP, lat) for col in range(GRID_NB_LON)))
    with open(path, 'w') as f:
        f.write('\n'.join(lines) + '\n')
    return path.encode()

# Simple test checking that the Shared Object works correctly
# Theoretical values come from computation using CSGeo UI

class TestCSGeoDLL(unittest.TestCase):
    def test_rgf2xyhg(self): 
        # Example 1: 2D+H coordinates and decimal degree angular unit
        x = ct.c_double(6.06)
        y = ct.c_double(46.27)
        z = ct.c_double(620.5)
        inputParams = PyPlainDataParameters(209, 2, 5 , 0.0, None)    # Initial reference frame: RGF93, Geodetic coordinates, Decimal Degrees
        outputParams = PyPlainDataParameters(104, 4, 5 , 0.0, None)   # Final reference frame: CernXYHg00Machine, 2D+H, Decimal Degrees
        result = myDLL.transformPoint( ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(inputParams), None, ct.byref(outputParams), None )
        self.assertAlmostEqual(x.value, 372.01096243333177, places = 7)
        self.assertAlmostEqual(y.value, 6074.330057328176, places = 7)
        self.assertAlmostEqual(z.value, 570.4372216967596, places = 7)

    def test_ccs2MLA85machine(self):
        # Example 2: MLA with definition of an ORIGIN point and orientation
        x = ct.c_double(1753.43696)
        y = ct.c_double(2060.07526)
        z = ct.c_double(2434.94253)
        inputParams = PyPlainDataParameters(0, 1, 1 , 0.0, None)      # Initial Reference frame: CCS, 3DCartesian, Gons
        outputParams = PyPlainDataParameters(1000, 1, 1 , 0.0, None)  # Final Reference frame: MLA1985Machine, 3DCartesian, Gons
        outputLSO = PyPlainLocalSystemOrigin(1686.0, 2036.7, 2434.4, 278.1, 0.0)  # Origin with orientation (bearing in Gons and slope in mrads)
        result = myDLL.transformPoint( ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(inputParams), None, ct.byref(outputParams), ct.byref(outputLSO) )
        self.assertAlmostEqual(x.value, -0.7380206396142199, places = 7)
        self.assertAlmostEqual(y.value, -71.36949897715402, places = 7)
        self.assertAlmostEqual(z.value, 0.5391049916654976, places = 7)

    def test_itrf2xyhg(self):
        # Example 3: ITRF 2014 at epoch 2020.0 to CernXYHg00Machine
        x = ct.c_double(6.06)
        y = ct.c_double(46.27)
        z = ct.c_double(620.5)
        inputParams = PyPlainDataParameters(13, 2, 5 , 2020.0, b'ITRF 2014')    # Initial reference frame: ITRF2014, Geodetic coordinates, Decimal Degrees, epoch 2020.0
        outputParams = PyPlainDataParameters(104, 4, 5 , 0.0, None)   # Final reference frame: CernXYHg00Machine, 2D+H
        result = myDLL.transformPoint( ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(inputParams), None, ct.byref(outputParams), None )
        self.assertAlmostEqual(x.value, 371.8555184442446, places = 7)
        self.assertAlmostEqual(y.value, 6073.541802762913, places = 7)
        self.assertAlmostEqual(z.value, 570.4316797793465, places = 7)

    def test_ccs2lv95(self): 
        if 'linux' in sys.platform:    
            #CCS to lv95_ortho (Coordinate should remain the same, transformations using Reframe from Swisstopo are not available on Linux
            x = ct.c_double(1000.356)
            y = ct.c_double(540.1654)
            z = ct.c_double(142.023)
            inputParams = PyPlainDataParameters(0, 1, 1 , 0.0, None)    # Initial reference frame: CCS, 3D Cartesian, Gons
            outputParams = PyPlainDataParameters(111, 4, 1 , 0.0, None)   # Final reference frame: LV95_ortho, 2D+H, Decimal Degrees
            
            result1 = myDLL.transformPoint( ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(inputParams), None, ct.byref(outputParams), None )
            self.assertEqual(x.value, 1000.356)
            self.assertEqual(y.value, 540.1654)
            self.assertEqual(z.value, 142.023)
        else:
            #CCS to lv95_ortho
            x = ct.c_double(1000.356)
            y = ct.c_double(540.1654)
            z = ct.c_double(142.023)
            inputParams = PyPlainDataParameters(0, 1, 1 , 0.0, None)    # Initial reference frame: CCS, 3D Cartesian, Gons
            outputParams = PyPlainDataParameters(111, 4, 1 , 0.0, None)   # Final reference frame: LV95_ortho, 2D+H, Decimal Degrees
            
            result1 = myDLL.transformPoint( ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(inputParams), None, ct.byref(outputParams), None )
            self.assertAlmostEqual(x.value, 2491061.91033355, places = 7)
            self.assertAlmostEqual(y.value, 1120328.92804549, places = 7)
            self.assertAlmostEqual(z.value, -1857.70021907, places = 7)

    def test_ccs2chtrf95_customGeoid(self):
        # Example 5: CCS to CHTRF95 with heights above a custom geoid grid, and back
        geoidPath = createGeoidGrid()
        x0, y0, z0 = -884.48504, 2643.74293, 2402.50974
        inputParams = PyPlainDataParameters(0, 1, 1, 0.0, None)          # Initial reference frame: CCS, 3D Cartesian, Gons
        ellipsoidal = PyPlainDataParameters(210, 2, 5, 0.0, None)        # CHTRF95, Geodetic coordinates, Decimal Degrees, ellipsoidal height
        withGeoid = PyPlainDataParameters(210, 2, 5, 0.0, None, geoidPath)  # Same, with height above the custom geoid

        # Reference: ellipsoidal height
        xh, yh, zh = ct.c_double(x0), ct.c_double(y0), ct.c_double(z0)
        result = myDLL.transformPoint(ct.byref(xh), ct.byref(yh), ct.byref(zh), ct.byref(inputParams), None, ct.byref(ellipsoidal), None)
        self.assertEqual(result, kOk)

        # Height above the geoid: H = h - N, horizontal coordinates unchanged
        x, y, z = ct.c_double(x0), ct.c_double(y0), ct.c_double(z0)
        result = myDLL.transformPoint(ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(inputParams), None, ct.byref(withGeoid), None)
        self.assertEqual(result, kOk)
        self.assertAlmostEqual(x.value, xh.value, places = 10)
        self.assertAlmostEqual(y.value, yh.value, places = 10)
        # the geoid is defined in ETRF93: tolerance covers the (sub-millimetric) CHTRF95 / ETRF93 difference
        self.assertAlmostEqual(z.value, zh.value - expectedN(x.value, y.value), delta = 1e-3)

        # Back to CCS
        result = myDLL.transformPoint(ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(withGeoid), None, ct.byref(inputParams), None)
        self.assertEqual(result, kOk)
        self.assertAlmostEqual(x.value, x0, places = 6)
        self.assertAlmostEqual(y.value, y0, places = 6)
        self.assertAlmostEqual(z.value, z0, places = 6)

    def test_customGeoid_invalidOptions(self):
        # Example 6: invalid uses of a custom geoid grid are reported by a status code
        geoidPath = createGeoidGrid()
        x, y, z = ct.c_double(-884.48504), ct.c_double(2643.74293), ct.c_double(2402.50974)
        ccs = PyPlainDataParameters(0, 1, 1, 0.0, None)

        # 3D cartesian coordinates have no height
        output = PyPlainDataParameters(210, 1, 1, 0.0, None, geoidPath)
        result = myDLL.transformPoint(ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(ccs), None, ct.byref(output), None)
        self.assertEqual(result, kInvalidOutputGeoid)

        # Frame already using a vertical datum (Lambert93 NGF-IGN69)
        output = PyPlainDataParameters(208, 4, 5, 0.0, None, geoidPath)
        result = myDLL.transformPoint(ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(ccs), None, ct.byref(output), None)
        self.assertEqual(result, kInvalidOutputGeoid)

        # Missing grid file
        output = PyPlainDataParameters(210, 2, 5, 0.0, None, b'this/file/does/not/exist.tif')
        result = myDLL.transformPoint(ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(ccs), None, ct.byref(output), None)
        self.assertEqual(result, kInvalidOutputGeoid)

        # Geoid on a CCS input
        input = PyPlainDataParameters(0, 1, 1, 0.0, None, geoidPath)
        output = PyPlainDataParameters(210, 2, 5, 0.0, None)
        result = myDLL.transformPoint(ct.byref(x), ct.byref(y), ct.byref(z), ct.byref(input), None, ct.byref(output), None)
        self.assertEqual(result, kInvalidInputGeoid)

        # coordinates must not have been modified by the failed calls
        self.assertEqual(x.value, -884.48504)
        self.assertEqual(y.value, 2643.74293)
        self.assertEqual(z.value, 2402.50974)
            
        
