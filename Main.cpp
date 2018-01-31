#include<iostream>
#include<iomanip>
#include "pendA.h"

using namespace std;

int main()
{
	PendA pend;

	double tEnd = 20.0;
	double dt = 0.02;
	double ke, pe;

	pend.setTimestep(dt);

	while (pend.getTime() < tEnd - 0.5*dt) {
		pend.step();
		pend.getEnergy(ke, pe);
		cout << setprecision(3) << fixed
			<< "--------------------------------------------------------------------------" << endl
			<< " | " << pend.getTime() << " | " << pend.getState(0) << " | " << pend.getState(1) << " | " << pend.getState(2) << " | " << pend.getState(3)
			<< " | " << ke << " | " << pe << " | " << ke + pe << " | "
			<< endl;
	}
	char q; 
	cin >> q;
}