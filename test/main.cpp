#include "ITestClass.h"

//#include "class_name_TestClass.h"

#include <fmt/core.h>

template <class T>
void runTest()
{
	T test_class;
	test_class.runAllTests();
}

int main(int argc, char** argv)
{
	//runTest<class_name_TestClass>();
}