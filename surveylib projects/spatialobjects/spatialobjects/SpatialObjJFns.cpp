
#include <jni.h>
#include <iostream>
#include  "SpatialObjJFns.h"
#include  "SpatialObjFns.h"
#include  "TSpatialPosition.h"
#include  "TGraph.h"
#include  "TRefSystemFactory.h"
#include  "TLength.h"
#include  "TVGeoidModel.h"
#include  "TVReferenceFrame.h"
#include  "TModifiedLocalAstronomicalRF.h"
//#include  "TTLength.h"


// N value for CG2000 at 0-level
JNIEXPORT jint JNICALL Java_SurveyLibJni_getCG2000N0_1JNI(JNIEnv *env, jobject obj, jdoubleArray xyNArray)
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x = arrayValues[0];
	double y = arrayValues[1];
	double pN = &arrayValues[2];

	double* pN = &N;
	int result = SpatialObjFns::getCG2000N0(x,y,pN);

	return result;
}


// N value for CG2000 at LEP-level
JNIEXPORT jint JNICALL Java_SurveyLibJni_getCG2000NMachine_1jni(JNIEnv *env, jobject obj, jdoubleArray xyNArray)

{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x = arrayValues[0];
	double y = arrayValues[1];
	double pN = &arrayValues[2];

	double* pN = &N;
	int result = SpatialObjFns::getCG2000NMachine(x,y,pN);

	return result;
}


// N value for CG1985 at 0-level
JNIEXPORT jint JNICALL Java_SurveyLibJni_getCG1985N0(JNIEnv *env, jobject obj, jdoubleArray xyNArray)
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x = arrayValues[0];
	double y = arrayValues[1];
	double pN = &arrayValues[2];

	double* pN = &N;
	int result = SpatialObjFns::getCG1985N0(x,y,pN);

	return result;
}

// N value for CG1985 at LEP-level
JNIEXPORT jint JNICALL Java_SurveyLibJni_getCG1985NMachine_1JNI(JNIEnv *env, jobject obj, jdoubleArray xyNArray)
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x = arrayValues[0];
	double y = arrayValues[1];
	double pN = &arrayValues[2];

	double* pN = &N;
	int result = SpatialObjFns::getCG1985NMachine(x,y,pN);

	return result;
}


// coordinates transformation to MLA system
JNIEXPORT jint JNICALL Java_SurveyLibJni_transformToMLA(JNIEnv * env, jobject obj, jdoubleArray vectorArray, jstring geoid))
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x0 = arrayValues[0];
	double y0 = arrayValues[1];
	double z0 = arrayValues[2];
	double *x = &arrayValues[3];
	double *y = &arrayValues[4];
	double *z = &arrayValues[5];

	char* cGeoid = env->GetStringUTFChars(geoid,JNI_FALSE);

	int result = SpatialObjFns::transformToMLA(x0,y0,z0,x,y,z,cGeoid);

	return result;
}



// coordinates transformation from MLA system to CCS
JNIEXPORT jint JNICALL Java_SurveyLibJni_transformFromMLA(JNIEnv * env, jobject obj, jdoubleArray vectorArray, jstring geoid)
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x0 = arrayValues[0];
	double y0 = arrayValues[1];
	double z0 = arrayValues[2];
	double *x = &arrayValues[3];
	double *y = &arrayValues[4];
	double *z = &arrayValues[5];

	char *cGeoid = env->GetStringUTFChars(geoid,JNI_FALSE);

	int result = SpatialObjFns::transformFromMLA(x0,y0,z0,x,y,z,cGeoid);

	return result;
}


// coordinates transformation to MLA system (with bearing, slope and false origin = 0)
JNIEXPORT jint JNICALL Java_SurveyLibJni_transformToMLA2(JNIEnv * env, jobject obj, jdouble x0, jdouble y0, jdouble z0, jdouble x, jdouble y, jdouble z, jchar jgeoid)
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)xyNArray);
	jdouble* arrayValues = env->GetDoubleArrayElements(xyNArray,JNI_FALSE);

	double x0 = arrayValues[0];
	double y0 = arrayValues[1];
	double z0 = arrayValues[2];
	double *x = &arrayValues[3];
	double *y = &arrayValues[4];
	double *z = &arrayValues[5];

	char *cGeoid = env->GetStringUTFChars(geoid,JNI_FALSE);

	int result = SpatialObjFns::transformToMLA2(x0,y0,z0,x,y,z,cGeoid);

	return result;
}


// coordinates transformation from MLA system to CCS (with bearing, slope and false origin = 0)
JNIEXPORT jint JNICALL Java_SurveyLibJni_transformFromMLA2(JNIEnv * env, jobject obj, jdouble x0, jdouble y0, jdouble z0, jdouble x, jdouble y, jdouble z, jchar jgeoid)
{	
	return 1;//SpatialObjFns::transformFromMLA2(x0,y0,z0,x,y,z,jgeoid);
}


// coordinates of a point on the vertical of another
JNIEXPORT jint JNICALL Java_SurveyLibJni_descenteVert(JNIEnv * env, jobject obj, jdouble x, jdouble y, jdouble h, jdouble deltaH, jdouble xt, jdouble yt, jdouble ht)
{
	return 1;//SpatialObjFns::descenteVert(x,y,h,deltaH,xt,yt,ht);
}

JNIEXPORT jint JNICALL Java_SurveyLibJni_testFunction
  (JNIEnv * env, jobject obj, jdoubleArray array)
{
	jint sum = 0;
	jsize size = env->GetArrayLength((jarray)array);
	jdouble* aint = env->GetDoubleArrayElements(array,NULL);
	aint[0] = 10.0;
	aint[1] = 20.0;
	aint[2] = 30.0;

	return 1;
}


