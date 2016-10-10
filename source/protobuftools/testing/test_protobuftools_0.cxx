// Standard library:
#include <exception>
#include <cstdlib>
#include <iostream>

// This project:
#include <protobuftools/testing/test.h>

int main( void )
{
  int error_code = EXIT_SUCCESS;
  try {

    protobuftools::testing::test::run_test_0();
    protobuftools::testing::test::run_test_1();
    protobuftools::testing::test::run_test_2();
    protobuftools::testing::test::run_test_3();
    protobuftools::testing::test::run_test_4();

  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
