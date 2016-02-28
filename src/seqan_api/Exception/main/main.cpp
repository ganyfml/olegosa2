#include "../Exception.hpp"
#include <iostream>

using namespace std;

int main()
{
  try
  {
    throw IndexCreateException();
  }
  catch (exception& e)
  {
    cout << e.what() << '\n';
  }

  try
  {
    throw IndexOpenException();
  }
  catch (exception& e)
  {
    cout << e.what() << '\n';
  }

  try
  {
    throw IndexSaveException();
  }
  catch (exception& e)
  {
    cout << e.what() << '\n';
  }
  return 0;
}
