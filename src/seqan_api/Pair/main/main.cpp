// vim: set noexpandtab tabstop=2:

#include <iostream>
#include "../Pair.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	Pair test(1, 2);
	printf("First: %d, Second: %d\n", test.first(), test.second());
}
