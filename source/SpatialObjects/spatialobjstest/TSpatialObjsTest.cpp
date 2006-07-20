/*test	TSpatialLine
		TSpatialPlane

  02/2003*/

/*#include <iostream>
using namespace std;*/

#include  "TSpatialLine.h"
#include  "TSpatialPlane.h"


void main()
{
	//TSpatialLine
	cout<<"Test TSpatialLine"<<endl<<endl;

	string name1 = "point1";
	string name2 = "point2";
	TSpatialPointName pointName1 (name1);
	TSpatialPointName pointName2 (name2);

	TAngle angle (3.59);
	TAngle angle2 (6.1);

	TSpatialLine line1, line2, line6, line7;
	TSpatialLine line3 (pointName2);
	TSpatialLine line4 (pointName1, pointName2);
	TSpatialLine line5 (line3);


	//Equality operator
	cout<<"line5 == line3 : "<< (line5==line3) <<endl;
	cout<<"line5 == line2 : "<< (line5==line2) <<endl;
	
	//operator =
	line2 = line5;
	cout<<"line5 == line2 : "<< (line5==line2) <<endl;

	//return true if the line is define with the new arguments*/
	cout<<"line5 redefinition : "<<line5.ifNotDoneDefinePlane(pointName1)<<endl;
	cout<<"line5 redefinition : "<<line5.ifNotDoneDefinePlane(pointName1, pointName2)<<endl;
	cout<<"line6 redefinition : "<<line6.ifNotDoneDefinePlane(pointName1)<<endl;
	cout<<"line7 redefinition : "<<line7.ifNotDoneDefinePlane(pointName1, pointName2)<<endl;

	//point name
	cout<<"line1's first end name : "<<line1.getFirstEndName().getName()<<endl;
	cout<<"line2's first end name : "<<line2.getFirstEndName().getName()<<endl;
	cout<<"line3's first end name : "<<line3.getFirstEndName().getName()<<endl;
	cout<<"line4's first end name : "<<line4.getFirstEndName().getName()<<endl;
	cout<<"line5's first end name : "<<line5.getFirstEndName().getName()<<endl;
	cout<<"line6's first end name : "<<line6.getFirstEndName().getName()<<endl;
	cout<<"line7's first end name : "<<line7.getFirstEndName().getName()<<endl<<endl;


	cout<<"line1's second end name : "<<line1.getSecondEndName().getName()<<endl;
	cout<<"line2's second end name : "<<line2.getSecondEndName().getName()<<endl;
	cout<<"line3's second end name : "<<line3.getSecondEndName().getName()<<endl;
	cout<<"line4's second end name : "<<line4.getSecondEndName().getName()<<endl;
	cout<<"line5's second end name : "<<line5.getSecondEndName().getName()<<endl;
	cout<<"line6's second end name : "<<line6.getSecondEndName().getName()<<endl;
	cout<<"line7's second end name : "<<line7.getSecondEndName().getName()<<endl<<endl;


	//line name
	cout<<"line1's name : "<<line1.getName()<<endl;
	cout<<"line2's name : "<<line2.getName()<<endl;
	cout<<"line3's name : "<<line3.getName()<<endl;
	cout<<"line4's name : "<<line4.getName()<<endl;
	cout<<"line5's name : "<<line5.getName()<<endl;
	cout<<"line6's name : "<<line6.getName()<<endl;
	cout<<"line7's name : "<<line7.getName()<<endl<<endl;

	//buildNameError
	line1.buildErrorName();
	line2.buildErrorName();
	line3.buildErrorName();
	line4.buildErrorName();
	line5.buildErrorName();
	line6.buildErrorName();
	line7.buildErrorName();

	//line name
	cout<<"line1's name : "<<line1.getName()<<endl;
	cout<<"line2's name : "<<line2.getName()<<endl;
	cout<<"line3's name : "<<line3.getName()<<endl;
	cout<<"line4's name : "<<line4.getName()<<endl;
	cout<<"line5's name : "<<line5.getName()<<endl;
	cout<<"line6's name : "<<line6.getName()<<endl;
	cout<<"line7's name : "<<line7.getName()<<endl<<endl<<endl<<endl;


	///////////////////////////////////////////////////////////////////////////////
	//TSpatialPlane
	cout<<"Test TSpatialPlane"<<endl<<endl;

	TSpatialPlane plane1, plane2, plane6, plane7;
	TSpatialPlane plane3 (pointName1, pointName2);
	TSpatialPlane plane4 (pointName2,angle);
	TSpatialPlane plane5 (plane3);


	//Equality operator
	cout<<"plane5 == plane3 : "<< (plane5==plane3) <<endl;
	cout<<"plane5 == plane2 : "<< (plane5==plane2) <<endl;
	
	//operator =
	plane2 = plane5;
	cout<<"plane5 == plane2 : "<< (plane5==plane2) <<endl;

	//return true if the plane is define with the new arguments*/
	cout<<"plane5 redefinition : "<<plane5.ifNotDoneDefinePlane(pointName2, pointName1)<<endl;
	cout<<"plane5 redefinition : "<<plane5.ifNotDoneDefinePlane(pointName2, angle)<<endl;
	cout<<"plane6 redefinition : "<<plane6.ifNotDoneDefinePlane(pointName2, pointName1)<<endl;
	cout<<"plane7 redefinition : "<<plane7.ifNotDoneDefinePlane(pointName2, angle2)<<endl;

	//point name
	cout<<"plane1's first point name : "<<plane1.getFirstPointName().getName()<<endl;
	cout<<"plane2's first point name : "<<plane2.getFirstPointName().getName()<<endl;
	cout<<"plane3's first point name : "<<plane3.getFirstPointName().getName()<<endl;
	cout<<"plane4's first point name : "<<plane4.getFirstPointName().getName()<<endl;
	cout<<"plane5's first point name : "<<plane5.getFirstPointName().getName()<<endl;
	cout<<"plane6's first point name : "<<plane6.getFirstPointName().getName()<<endl;
	cout<<"plane7's first point name : "<<plane7.getFirstPointName().getName()<<endl<<endl;

	cout<<"plane1's second point name : "<<plane1.getSecondPointName().getName()<<endl;
	cout<<"plane2's second point name : "<<plane2.getSecondPointName().getName()<<endl;
	cout<<"plane3's second point name : "<<plane3.getSecondPointName().getName()<<endl;
	cout<<"plane4's second point name : "<<plane4.getSecondPointName().getName()<<endl;
	cout<<"plane5's second point name : "<<plane5.getSecondPointName().getName()<<endl;
	cout<<"plane6's second point name : "<<plane6.getSecondPointName().getName()<<endl;
	cout<<"plane7's second point name : "<<plane7.getSecondPointName().getName()<<endl<<endl;

	//angle value
	cout<<"plane1's angle value : "<<plane1.getAngle().getRadiansValue()<<endl;
	cout<<"plane2's angle value : "<<plane2.getAngle().getRadiansValue()<<endl;
	cout<<"plane3's angle value : "<<plane3.getAngle().getRadiansValue()<<endl;
	cout<<"plane4's angle value : "<<plane4.getAngle().getRadiansValue()<<endl;
	cout<<"plane5's angle value : "<<plane5.getAngle().getRadiansValue()<<endl;
	cout<<"plane6's angle value : "<<plane6.getAngle().getRadiansValue()<<endl;
	cout<<"plane7's angle value : "<<plane7.getAngle().getRadiansValue()<<endl<<endl;

	//angle status
	cout<<"plane1's angle status : "<<plane1.getAngle().getStatus()<<endl;
	cout<<"plane2's angle status : "<<plane2.getAngle().getStatus()<<endl;
	cout<<"plane3's angle status : "<<plane3.getAngle().getStatus()<<endl;
	cout<<"plane4's angle status : "<<plane4.getAngle().getStatus()<<endl;
	cout<<"plane5's angle status : "<<plane5.getAngle().getStatus()<<endl;
	cout<<"plane6's angle status : "<<plane6.getAngle().getStatus()<<endl;
	cout<<"plane7's angle status : "<<plane7.getAngle().getStatus()<<endl<<endl;

	//plane name
	cout<<"plane1's name : "<<plane1.getName()<<endl;
	cout<<"plane2's name : "<<plane2.getName()<<endl;
	cout<<"plane3's name : "<<plane3.getName()<<endl;
	cout<<"plane4's name : "<<plane4.getName()<<endl;
	cout<<"plane5's name : "<<plane5.getName()<<endl;
	cout<<"plane6's name : "<<plane6.getName()<<endl;
	cout<<"plane7's name : "<<plane7.getName()<<endl<<endl;

	//buildNameError
	plane1.buildErrorName();
	plane2.buildErrorName();
	plane3.buildErrorName();
	plane4.buildErrorName();
	plane5.buildErrorName();
	plane6.buildErrorName();
	plane7.buildErrorName();

	//plane name
	cout<<"plane1's name : "<<plane1.getName()<<endl;
	cout<<"plane2's name : "<<plane2.getName()<<endl;
	cout<<"plane3's name : "<<plane3.getName()<<endl;
	cout<<"plane4's name : "<<plane4.getName()<<endl;
	cout<<"plane5's name : "<<plane5.getName()<<endl;
	cout<<"plane6's name : "<<plane6.getName()<<endl;
	cout<<"plane7's name : "<<plane7.getName()<<endl<<endl;

	cout<<"line5==line6 : "<<(line5==line6)<<endl;
	cout<<"line5==line3 : "<<(line5==line3)<<endl;




};