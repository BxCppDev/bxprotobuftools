// Standard library:
#include <iostream>
#include <sstream>
#include <exception>

// This project:
#include "foo.h"
#include "bar.h"

// Bayeux/protobuftools:
#include <bayeux/protobuftools/io.h>

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
    std::string buffer4;

    {
      foo f1(42);
      foo f2(12, 3.14);
      foo f3(12, 3.14, bar(true, "Hello, world!"));
      boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
      std::clog << "now = " << boost::posix_time::to_iso_string(now) << std::endl;
      foo f4(12, 3.14, bar(true, "Hello, planet!"), now);
      std::clog << "f1 = " << f1 << std::endl;
      std::clog << "f2 = " << f2 << std::endl;
      std::clog << "f3 = " << f3 << std::endl;
      std::clog << "f4 = " << f4 << std::endl;

      // Protobufization:
      std::clog << "Protobufization... ";
      std::ostringstream obuffer1;
      protobuftools::store(obuffer1, f1);
      std::ostringstream obuffer2;
      protobuftools::store(obuffer2, f2);
      std::ostringstream obuffer3;
      protobuftools::store(obuffer3, f3);
      std::ostringstream obuffer4;
      protobuftools::store(obuffer4, f4);
      buffer1 = obuffer1.str();
      buffer2 = obuffer2.str();
      buffer3 = obuffer3.str();
      buffer4 = obuffer4.str();
      std::clog << "done\n";
    }

    std::clog << "\nBuffer #1 size = " << buffer1.length() << "  Bytes=[\n" << buffer1 << "\n]EOF\n";
    std::clog << "\nBuffer #2 size = " << buffer2.length() << "  Bytes=[\n" << buffer2 << "\n]EOF\n";
    std::clog << "\nBuffer #3 size = " << buffer3.length() << "  Bytes=[\n" << buffer3 << "\n]EOF\n";
    std::clog << "\nBuffer #4 size = " << buffer4.length() << "  Bytes=[\n" << buffer4 << "\n]EOF\n";

    {
      foo f1;
      foo f2;
      foo f3;
      foo f4;

      // Deprotobufization:
      std::clog << "Deprotobufization...";
      std::istringstream ibuffer1(buffer1);
      protobuftools::load(ibuffer1, f1);
      std::istringstream ibuffer2(buffer2);
      protobuftools::load(ibuffer2, f2);
      std::istringstream ibuffer3(buffer3);
      protobuftools::load(ibuffer3, f3);
      std::istringstream ibuffer4(buffer4);
      protobuftools::load(ibuffer4, f4);
      std::clog << "done\n";

      std::clog << "f1 = " << f1 << std::endl;
      std::clog << "f2 = " << f2 << std::endl;
      std::clog << "f3 = " << f3 << std::endl;
      std::clog << "f4 = " << f4 << std::endl;
    }

  } catch (std::exception & error) {
    std::cerr << "error: " << error.what() << '\n';
    return 1;
  }
  return 0;
}
