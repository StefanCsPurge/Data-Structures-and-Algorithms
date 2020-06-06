
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {

	testNumberOfNonZeroElems();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}