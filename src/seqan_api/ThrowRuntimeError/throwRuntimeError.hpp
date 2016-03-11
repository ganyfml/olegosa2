#pragma once

#include <string>
#include <stdexcept>

#define THROW_RUNTIME_ERROR throw std::runtime_error(throw_string(__PRETTY_FUNCTION__, __FILE__, __LINE__))
#define THROW_RUNTIME_ERROR_MSG(message) throw std::runtime_error(throw_string(__PRETTY_FUNCTION__, __FILE__, __LINE__, message))
#define THROW_RUNTIME_ERROR_MSG2(message1, message2) throw std::runtime_error(std::string(message1) + "\n" + throw_string(__PRETTY_FUNCTION__, __FILE__, __LINE__, message2))

// nonamespace {

std::string throw_string(const char *pretty_function, const char *file, int line, const std::string &message = "");

//}
