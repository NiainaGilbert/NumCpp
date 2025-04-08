#include "numCpp.h"
int main()
{
	ndarrays<int> test({2,2});
	test.printDim();
	test.resize({1,1, 9});
	test.printDim();
	return 0;
}