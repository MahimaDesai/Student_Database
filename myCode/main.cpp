// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>
#include "SimpleUI.h"

using namespace std;

// Main program
int main ()
{
	StudentDb s1;
	SimpleUI u1(s1);
	u1.run();

	return 0;
}
