#include <seqan_api/ThrowRuntimeError.hpp>
#include <sstream>

// nonamespace {

std::string throw_string(const char *pretty_function, const char *file, int line, const std::string &message) {
  std::ostringstream oss;
  oss << file << ":"  << line << ": " << pretty_function;
  if(message != "") {
    oss << ": " << message;
  }

  return oss.str();
}

//}
