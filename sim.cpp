//============================================================================
// sim.cpp
// Methods for the base Sim class
//============================================================================
#include <iostream>
#include "sim.h"

using namespace std;

//----------------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------------
Sim::Sim()
{
	n = 0;
	simMethod = 4;

	useCustomStepper = false;

	time = 0.0;
	dt = 0.02;
	maxDt = -1.0;

	x = nullptr;
	xi = nullptr;
	f = nullptr;

	gfx = &defaultGfx;

	pi = 3.14159265358979;
	piByTwo = 0.5*pi;
	twoPi = 2.0*pi;
}

//----------------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------------
Sim::~Sim()
{
	clearMemory();
}

//----------------------------------------------------------------------------
// allocateMemory: Allocate memory for the state, intermediate state, and
//                 set of slopes
//----------------------------------------------------------------------------
void Sim::allocateMemory()
{
	if (n <= 0)
		return;

	int i, j;

	x = new double[n];
	xi = new double[n];
	for (i = 0; i < n; ++i) {
		x[i] = xi[i] = 0.0;
	}

	f = new double*[4];
	for (i = 0; i < 4; ++i) {
		f[i] = new double[n];
		for (j = 0; j < n; ++j)
			f[i][j] = 0.0;
	}
}

//----------------------------------------------------------------------------
// clearMemory: Delete allocated memory
//----------------------------------------------------------------------------
void Sim::clearMemory()
{
	if (x == nullptr)
		return;

	delete[] x;
	delete[] xi;
	for (int i = 0; i < 4; ++i)
		delete[] f[i];
	delete[] f;

	n = 0;
}

//----------------------------------------------------------------------------
// setState: Sets the value of a state
//----------------------------------------------------------------------------
void Sim::setState(int i, double v)
{
	// check if index out of range
	if (i < 0 || i >= n) {
		cerr << "Sim::setState: ERROR index out of range: " << i << endl;
		return;
	}

	x[i] = v;
}

//----------------------------------------------------------------------------
// getState: returns the value in the state[i]
//----------------------------------------------------------------------------
double Sim::getState(int i)
{
	// check if index out of range
	if (i < 0 || i >= n) {
		cerr << "Sim::getState: ERROR index out of range: " << i << endl;
		return(0.0);
	}

	return(x[i]);
}

//----------------------------------------------------------------------------
// step: Perform one integration step using the selected method
//----------------------------------------------------------------------------
void Sim::step(double ddt)
{
	if (simMethod == 1) {
		stepEuler(ddt);
	}
	else if (simMethod == 2) {
		stepRK2(ddt);
	}
	else if (simMethod == 4) {
		stepRK4(ddt);
	}
	else
		cout << "Error in Sim::step: invalid simMethod." << endl;
}

//----------------------------------------------------------------------------
// stepEuler: Perform one Euler integration timestep
//----------------------------------------------------------------------------
void Sim::stepEuler(double ddt)
{
	int i;

	rhs(f[0], x, time);
	for (i = 0; i < n; ++i) {
		x[i] += f[0][i] * ddt;
	}

	time += ddt;
}

//----------------------------------------------------------------------------
// stepRK2: Perform one RK2 integration time step
//----------------------------------------------------------------------------
void Sim::stepRK2(double ddt)
{

}

//----------------------------------------------------------------------------
// stepRK4: Perform one RK4 integration time step
//----------------------------------------------------------------------------
void Sim::stepRK4(double ddt)
{
	//stepEuler(ddt);

	int i;

	double dtByTwo = 0.5*ddt;
	double dtBySix = ddt / 6.0;

	rhs(f[0], x, time);
	for (i = 0; i < n; ++i) {
		xi[i] = x[i] + f[0][i] * dtByTwo;
	}

	rhs(f[1], xi, time + dtByTwo);
	for (i = 0; i < n; ++i) {
		xi[i] = x[i] + f[1][i] * dtByTwo;
	}

	rhs(f[2], xi, time + dtByTwo);
	for (i = 0; i < n; ++i) {
		xi[i] = x[i] + f[2][i] * ddt;
	}

	rhs(f[3], xi, time + ddt);
	for (i = 0; i < n; ++i) {
		x[i] = x[i] + (f[0][i] + 2.0*f[1][i] + 2.0*f[2][i] + f[3][i])*dtBySix;
	}

	time += ddt;
}

//----------------------------------------------------------------------------
// stepCustom: place holder for custom stepper to be defined, possibly, by
//             derived class.
//----------------------------------------------------------------------------
void Sim::stepCustom(double ddt)
{
	cout << "Sim::stepCustom" << endl;
}

//----------------------------------------------------------------------------
// drawInit: Initialize the graphics
//----------------------------------------------------------------------------
void Sim::drawInit()
{
	drawInitSys();
	gfx->processDrawInit();
}

//----------------------------------------------------------------------------
// draw: perform the drawing operations
//----------------------------------------------------------------------------
void Sim::draw()
{
	drawSys();
	gfx->processDraw();
}

//----------------------------------------------------------------------------
// drawInitSys: place holder drawInitSys method. Derived classes should 
//              provide their own version of this if they are drawing.
//----------------------------------------------------------------------------
void Sim::drawInitSys()
{

}

//----------------------------------------------------------------------------
// drawSys: place-holder drawSys method. Derived classes should provide their
//          own method if they are drawing
//----------------------------------------------------------------------------
void Sim::drawSys()
{

}