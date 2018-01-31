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

	cout << left << "|" << setw(6) << "time" << " | " << setw(6) << "Theta1" << " | " << setw(6) << "ThD1"
		<< " | " << setw(6) << "Theta2" << " | " << setw(6) << "ThD2" << " | " << setw(8) << "KE" << " | " << setw(9) << "PE" << " | "
		<< setw(7) << "Total E" << "|" << endl;

	while (pend.getTime() < tEnd - 0.5*dt) {
		pend.step();
		pend.getEnergy(ke, pe);
		cout << setprecision(3) << fixed
			<< "-----------------------------------------------------------------------------" << endl
			<< "|" << setw(6) << pend.getTime() << " | " << setw(6) << pend.getState(0) << " | " << setw(6) << pend.getState(1)
			<< " | " << setw(6) << pend.getState(2) << " | " << setw(6) << pend.getState(3)
			<< " | " << setw(8) << ke << " | " << setw(9) << pe << " | " << setw(7) << ke + pe << "|"
			<< endl;
	}
	char q; 
	cin >> q;
}