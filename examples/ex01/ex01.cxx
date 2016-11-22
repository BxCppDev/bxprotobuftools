// Standard library:
#include <iostream>
#include <sstream>
#include <exception>

// This project:
#include "foo.h"
#include "bar.h"

// Bayeux/protobuftools:
#include <bayeux/protobuftools/io.h>
#include <bayeux/protobuftools/protobufable_converter.h>

// Declare a protobuf registrar instance for the FooMsg message class:
#include "FooMsg.pb.h"
BXPROTOBUFTOOLS_REGISTER_CLASS_LABELED("ex01/foo", FooMsg, FooPbRegistrar)
// Declare a protobuf registrar instance for the BarMsg message class:
#include "BarMsg.pb.h"
BXPROTOBUFTOOLS_REGISTER_CLASS_LABELED("ex01/bar", BarMsg, BarPbRegistrar)

int main()
{
  try {

    std::string buffer1;
    std::string buffer2;
    std::string buffer3;

    {
      foo f1(42);
      foo f2(12, 3.14);
      foo f3(12, 3.14, bar(true, "Hello, world!"));
      std::clog << "f1 = " << f1 << std::endl;
      std::clog << "f2 = " << f2 << std::endl;
      std::clog << "f3 = " << f3 << std::endl;

      // Protobufization:
      std::clog << "Protobufization... ";
      std::ostringstream obuffer1;
      protobuftools::store(obuffer1, f1);
      std::ostringstream obuffer2;
      protobuftools::store(obuffer2, f2);
      std::ostringstream obuffer3;
      protobuftools::store(obuffer3, f3);
      buffer1 = obuffer1.str();
      buffer2 = obuffer2.str();
      buffer3 = obuffer3.str();
      std::clog << "done\n";
    }

    std::clog << "\nBuffer #1 size = " << buffer1.length() << "  Bytes=[\n" << buffer1 << "\n]EOF\n";
    std::clog << "\nBuffer #2 size = " << buffer2.length() << "  Bytes=[\n" << buffer2 << "\n]EOF\n";
    std::clog << "\nBuffer #3 size = " << buffer3.length() << "  Bytes=[\n" << buffer3 << "\n]EOF\n";

    {
      foo f1;
      foo f2;
      foo f3;

      // Deprotobufization:
      std::clog << "Deprotobufization...";
      std::istringstream ibuffer1(buffer1);
      protobuftools::load(ibuffer1, f1);
      std::istringstream ibuffer2(buffer2);
      protobuftools::load(ibuffer2, f2);
      std::istringstream ibuffer3(buffer3);
      protobuftools::load(ibuffer3, f3);
      std::clog << "done\n";

      std::clog << "f1 = " << f1 << std::endl;
      std::clog << "f2 = " << f2 << std::endl;
      std::clog << "f3 = " << f3 << std::endl;
    }

  } catch (std::exception & error) {
    std::cerr << "error: " << error.what() << '\n';
    return 1;
  }
  return 0;
}
