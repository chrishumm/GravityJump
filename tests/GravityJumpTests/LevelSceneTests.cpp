#define CATCH_CONFIG_RUNNER //Defines we want a custom main. MUST use to use Google Mock lib.
#include "catch.hpp" //Our unit tests

#include "../../../../cocos2dx/include/cocos2d.h"
int main(int argc, char* argv[])
{
	// global setup...
	//::testing::GTEST_FLAG(throw_on_failure) = true;
	//::testing::InitGoogleMock(&argc,argv);
	int result = Catch::Session().run(argc, argv);

	// global clean-up...

	return result; //Returns test results to command line. RUN: runAllTests.bat to see tests. 
}