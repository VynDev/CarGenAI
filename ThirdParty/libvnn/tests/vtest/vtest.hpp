#include <iostream>

enum {TEST_SUCCESS, TEST_FAILURE};

#define TEST_REGISTER(functionName) bool functionName();
#define TEST_EXECUTE(functionName) \
	if (functionName() == TEST_SUCCESS) \
		std::cout << "\033[32mTest " << #functionName << " passed successfully\033[0m"  << std::endl; \
	else \
		std::cout << "\033[31mTest " << #functionName << " failed\033[0m"  << std::endl; 

#define TEST_EXIT(value) return (value);

#define TEST(functionName) bool functionName()

#define CASE(x) if (true)

#define REQUIRE_(value, file, line) \
	if (!(value)) \
	{ \
		std::cout << "\033[31mError: " << file << ":" << line << "\033[0m" << std::endl; \
		TEST_EXIT(TEST_FAILURE); \
	}

#define REQUIRE(value) REQUIRE_((value), __FILE__, __LINE__)

#define WARN_(value, file, line) \
	if (!(value)) \
	{ \
		std::cout << "\033[33mWarning: " << file << ":" << line << "\033[0m" << std::endl; \
	}

#define WARN(value) WARN_((value), __FILE__, __LINE__)