//============================================================================
// sim.h  Base class for reprsenting a simulator of a dynamic system
//
// MEE 381, 
//============================================================================
#pragma once

#include "simGraphicsItf.h"

class Sim
{
public:
	Sim();
	~Sim();

	void setTimestep(double d) { dt = d; }
	void setMaxIntegrationStep(double d) { maxDt = d; }
	double getTime() { return(time); }

	bool usingCustomStepper() { return(useCustomStepper); }
	void setSimMethodEuler() { simMethod = 1; }
	void setSimMethodRK2() { simMethod = 2; }
	void setSimMethodRK4() { simMethod = 4; }

	void step() { step(dt); }            //+++
	void stepEuler() { stepEuler(dt); }  //+++
	void stepRK2() { stepRK2(dt); }      //+++
	void stepRK4() { stepRK4(dt); }      //+++
	void stepCustom() { stepCustom(dt); }

	void step(double ddt);             //+++
	void stepEuler(double ddt);        //+++
	void stepRK2(double ddt);          //+++
	void stepRK4(double ddt);          //+++
	virtual void stepCustom(double ddt);

	void setState(int i, double v);
	double getState(int i);
	int  getNumStates() { return(n); }

	void drawInit();                                          //+++
	void draw();                                              //+++
	void setGraphicsModule(SimGraphicsItf* gg) { gfx = gg; }  //+++

protected:
	int n;                  // size of the state space;
	double* x;              // array of states

	bool useCustomStepper;  // whether to use custom stepper

	void allocateMemory();
	void clearMemory();
	virtual void rhs(double* ff, double* x, double tt) = 0;

	SimGraphicsItf defaultGfx;     // default graphics module that doesn't do anything //+++
	SimGraphicsItf* gfx;           //+++
	virtual void drawInitSys();    //+++
	virtual void drawSys();        //+++

	double pi;      // ratio of circle's circumference to diameter
	double piByTwo; // half pi
	double twoPi;

private:
	int simMethod;  // Simulation method 1=Euler; 2=RK2; 4=RK4;

	double time;    // simulation time
	double dt;      // nominal timestep
	double maxDt;   // absolute value of max timestep. If negative, then ignored.

	double* xi;     // array of intermediate states
	double** f;     // array of values for the rhs
};