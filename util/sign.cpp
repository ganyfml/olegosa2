// vim: set noexpandtab tabstop=2:

#include <iostream>

using namespace std;

int sign(int x)
{
  return (x > 0) - (x < 0);
}

int main()
{
	cout << sign(0) << endl;
	cout << sign(-1) << endl;
	cout << sign(1) << endl;
}
