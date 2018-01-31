//============================================================================
// pendA.cpp
// Methods for the class
//============================================================================
#include <iostream>
#include "pendA.h"

using namespace std;

//----------------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------------
PendA::PendA()
{
	n = 4;
	allocateMemory();

	// initial conditions
	setTheta1(2.0);
	setTheta1Dot(0.0);
	setTheta2(3.1415/2.0);
	setTheta2Dot(0.0);

	// default parameters
	g = 9.81;

	len1 = 10;
	len2 = 10;

	m1 = 5;
	m2 = 5;
}

//----------------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------------
PendA::~PendA()
{

}

//----------------------------------------------------------------------------
// setG:  Sets the parameter g.
//----------------------------------------------------------------------------
void PendA::setG(double gg)
{
	if (gg <= 0.0) {
		cerr << "PendA::setG: Parameter g must be positive. Ignoring" << endl;
		return;
	}

	g = gg;
}

//----------------------------------------------------------------------------
// setL:  Sets the parameter lengths.
//----------------------------------------------------------------------------
void PendA::setL(double length1, double length2)
{
	if (length1 <= 0.0 || length2 <= 0.0) {
		cerr << "PendA::setL: A parameter length must be positive. Ignoring" << endl;
		return;
	}

	len1 = length1;

	len2 = length2;
}

//----------------------------------------------------------------------------
// setL:  Sets the parameter masses.
//----------------------------------------------------------------------------
void PendA::setM(double mass1, double mass2)
{
	if (mass1 <= 0.0 || mass2 <= 0.0) {
		cerr << "PendA::setL: A parameter mass must be positive. Ignoring" << endl;
		return;
	}

	m1 = mass1;

	m2 = mass2;
}

//----------------------------------------------------------------------------
// rhs:  Calculates the right hand side of the differential equation for the 
//       system
//----------------------------------------------------------------------------
void PendA::rhs(double* ff, double* xx, double tt)
{
	double theta1 = xx[0];    // these just make the code more readable
	double omega1 = xx[1];
	double theta2 = xx[2];
	double omega2 = xx[3];

	double c1 = cos(theta1);
	double c2 = cos(theta2);
	double s1 = sin(theta1);
	double s2 = sin(theta2);
	double c12 = cos(theta1 - theta2);
	double s12 = sin(theta1 - theta2);

	double mT = m1 + m2;

	ff[0] = omega1;
	//ff[1] = (-len1*m2*omega1*omega1*c12*s12 + m2*g*c12*s12 - mT*g*s1 - m2*len2*omega2*omega2*s12) / (mT*len1 - len1*m2*c12*c12);                                 //BY HAND
	ff[1] = (c12*(-len1*m2*s12*omega1*omega1 + g*m2*s2)) / (-len1*m2*c12*c12 + len1*mT) - (len2*m2*s12*omega2*omega2 + g*mT*s1) / (-len1*m2*c12*c12 + len1*mT);    //MATLAB
	ff[2] = omega2;
	//ff[3] = (g*mT*s1*c12 + len2*m2*omega2*omega2*c12*s12 + len1*mT*omega1*omega1*s12 - g*mT*s2) / (len2*mT - m2*len2*c12*c12);                                               //BY HAND
	ff[3] = (mT*(-len1*m2*s12*omega1*omega1 + g*m2*s2)) / (len2*c12*c12 * m2*m2 - len2*mT*m2) + (c12*(len2*m2*s12*omega2*omega2 + g*mT*s1)) / (-len2*m2*c12*c12 + len2*mT);    //MATLAB
}

//----------------------------------------------------------------------------
// getEnergy: Calculate and return total energy (kinetic + potential)
// ****************************************************************
//----------------------------------------------------------------------------
double PendA::getEnergy()
{
	double ke, pe;
	return(getEnergy(ke, pe));
}

double PendA::getEnergy(double& ke, double& pe)
{
	double theta1 = x[0];    // these just make the code more readable
	double omega1 = x[1];
	double theta2 = x[2];
	double omega2 = x[3];

	double c1 = cos(theta1);
	double c2 = cos(theta2);
	double s1 = sin(theta1);
	double s2 = sin(theta2);
	double c12 = cos(theta1 - theta2);

	double mT = m1 + m2;

	ke = .5*m1*len1*len1*omega1*omega1 + .5*m2*(len1*len1*omega1*omega1 + len2*len2*omega2*omega2 + 2*len1*len2*omega1*omega2*c12);
	pe = -g*len1*c1*mT - m2*g*len2*c2;

	return(ke + pe);
}

//----------------------------------------------------------------------------
// drawInitSys: Initialize graphics
//----------------------------------------------------------------------------
void PendA::drawInitSys()
{
	double theta1 = x[0];

	double theta2 = x[2];
}

//----------------------------------------------------------------------------
// drawSys: Update graphics display
//----------------------------------------------------------------------------
void PendA::drawSys()
{
	double theta1 = x[0];

	double theta2 = x[2];
}