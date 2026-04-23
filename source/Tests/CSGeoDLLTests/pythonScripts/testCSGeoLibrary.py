import sys
import ctypes as ct
from ctypes import cdll
import unittest

  
# Initially loads the DLL or Shared Object module
if 'linux' in sys.platform:
    myDLL = cdll.LoadLibrary('../../../../build/staging/libCSGeoDLL.so')
else:
    myDLL = ct.WinDLL('../../../../CSGeoDLL.dll')
 
 
# Definition of the structure containing reference-frame info
class PyPlainDataParameters(ct.Structure):
    _fields_ = [("refFrame", ct.c_int),
                ("coordSys", ct.c_int),
                ("angUnits", ct.c_int),
                ("epoch", ct.c_double),
                ("solution", ct.c_char_p)]
                  
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
            
        
