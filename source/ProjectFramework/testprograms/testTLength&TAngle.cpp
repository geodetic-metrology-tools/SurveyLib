//////////////////////////////////////////////////////
// test file for TLength and TAngle
//////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "TLength.h"
#include "TAngle.h"



void f()
{
	//try
	//{
		TLength taille(1.77);
		cout<<taille.getMetresValue()<<endl;
		TLength semelle(0.05);
		TLength hauteur;

		//test+
		hauteur = (taille+(semelle));
		cout<<hauteur.getMetresValue()<<endl;
		
		//test-
		hauteur = hauteur-semelle;
		cout<<hauteur.getMetresValue()<<endl;
		
		//test+=
		hauteur += semelle;
		cout<<hauteur.getMetresValue()<<endl;
		
		//test-=
		hauteur -= semelle;
		cout<<hauteur.getMetresValue()<<endl;
		
		//test * et friend
		TLength nain;
		nain = taille*0.5;
		cout<<nain.getMetresValue()<<endl;
		nain = 0.5*taille;
		cout<<nain.getMetresValue()<<endl;
		
		
		//test angle
		TAngle angle(7);
		cout<<angle.getRadiansValue()<<endl;
		TAngle anglesup(1.25);
		
		//test +
		TAngle angletot = (angle+(anglesup));
		cout<<angletot.getRadiansValue()<<endl;
		
		//test -
		angletot = angletot-anglesup;
		cout<<angletot.getRadiansValue()<<endl;
		
		//test +=
		angletot += anglesup;
		cout<<angletot.getRadiansValue()<<endl;
		
		//test -=
		angletot -= anglesup;
		cout<<angletot.getRadiansValue()<<endl;
		
		//test * et friend
		TAngle minus;
		minus = angle*0.5;
		cout<<minus.getRadiansValue()<<endl;
		minus = 0.5*angle;
		cout<<minus.getRadiansValue()<<endl;

		//test PI et cie
		minus +=TAngle::pi();
		cout<<minus.getRadiansValue()<<endl;
		minus -=TAngle::twoPi();
		cout<<minus.getRadiansValue()<<endl;
		minus +=TAngle::piBy2();
		cout<<minus.getRadiansValue()<<endl;
		minus -=TAngle::piBy4();
		cout<<minus.getRadiansValue()<<endl;

		//test cos, sin, tan...
		cout<<minus.sine()<<endl;
		cout<<minus.cosine()<<endl;
		cout<<minus.tangent()<<endl;
		cout<<minus.tangenth()<<endl;
		cout<<minus.cosineh()<<endl;
		cout<<minus.sineh()<<endl;
		double x = 0.5;
		minus = TAngle::aCos(x);
		cout<<minus.getRadiansValue()<<endl;
		minus = TAngle::aSin(x);
		cout<<minus.getRadiansValue()<<endl;
		minus = TAngle::aTan(x);
		cout<<minus.getRadiansValue()<<endl;

		//test try, throw, catch
		//minus.setRadiansValue(24);
		//minus.setGonsValue(2000);
		minus.setDMSValue(2000,0,0);
	//}
	//
	//catch (char* text) { cout<<text<<endl;};
	return;
}