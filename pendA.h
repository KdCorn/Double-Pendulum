//============================================================================
// pendA.h
// class for simulating a simple pendulum, derived from Sim
//============================================================================
#pragma once
#include "sim.h"

class PendA : public Sim
{
public:
	PendA();
	~PendA();

	void setTheta1(double th1) { x[0] = th1; }
	void setTheta1Dot(double thd1) { x[1] = thd1; }
	void setTheta2(double th2) { x[2] = th2; }
	void setTheta2Dot(double thd2) { x[3] = thd2; }

	void setG(double);
	void setL(double, double);
	void setM(double, double);

	double getEnergy();
	double getEnergy(double&, double&);

protected:
	void rhs(double*, double*, double);
	void drawInitSys();
	void drawSys();

private:
	double g;      // gravitational acceleration
	double len1;   // pendulum 1 length
	double len2;   // pendulum 2 length
	double m1;     // mass 1
	double m2;     // mass 2
};