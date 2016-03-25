#include "../throwRuntimeError.hpp"
#include <iostream>
#include <cassert>

int main()
{
	std::cout << throw_string(__PRETTY_FUNCTION__, __FILE__, __LINE__) << std::endl;
	std::cout << throw_string(__PRETTY_FUNCTION__, __FILE__, __LINE__, "some message") << std::endl;

	try {
		THROW_RUNTIME_ERROR;
	}
	catch(std::runtime_error &e) {
		std::cout << "catch std::runtime_error: " << e.what() << std::endl;
	}

	try {
		THROW_RUNTIME_ERROR_MSG("some message");
	}
	catch(std::runtime_error &e) {
		std::cout << "catch std::runtime_error: " << e.what() << std::endl;
	}

	//throw std::runtime_error(THROW_STRING_MSG("some message"));
	//throw valgrind_runtime_error(THROW_STRING_MSG("some message"));

	throw std::runtime_error(throw_string(__PRETTY_FUNCTION__, __FILE__, __LINE__, "some message").c_str());
}
