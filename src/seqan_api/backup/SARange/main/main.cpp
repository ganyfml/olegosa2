// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../SARange.hpp"

using namespace std;

int main(int, char* argv[])
{
	SARange test(1, 2);
	printf("low: %d, high: %d\n", test.low(), test.high());
}
