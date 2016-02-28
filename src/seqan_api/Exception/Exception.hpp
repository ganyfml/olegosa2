#include <exception>

class IndexCreateException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Index Create Failed!";
  }
};

class IndexOpenException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Index File Open Failed!";
  }
};

class IndexSaveException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Index File Save Failed!";
  }
};
