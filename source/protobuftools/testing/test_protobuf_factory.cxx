// Standard library:
#include <exception>
#include <cstdlib>
#include <iostream>
#include <sstream>

// This project:
#include <protobuftools/protobuf_utils.h>
#include <protobuftools/protobuf_factory.h>
#include "foo.h"
#include <protobuftools/testing/foo.pb.h>
#include <protobuftools/io.h>
#include <protobuftools/protobufable_converter.h>

BXPROTOBUFTOOLS_REGISTER_CLASS_LABELED("protobuftools.testing.Foo",
                                       protobuftools::testing::Foo,
                                       FooPbRegistrar)

BXPROTOBUFTOOLS_REGISTER_CLASS_LABELED("protobuftools.testing.Foo.Bar",
                                       protobuftools::testing::Foo::Bar,
                                       FooBarPbRegistrar)

BXPROTOBUFTOOLS_CLASS_BIND_TO_REGISTERED_PROTOBUF(protobuftools::testing::foo, "protobuftools.testing.Foo")

BXPROTOBUFTOOLS_CLASS_BIND_TO_REGISTERED_PROTOBUF(protobuftools::testing::foo::bar, "protobuftools.testing.Foo.Bar")

void test0();

int main( void )
{
  int error_code = EXIT_SUCCESS;
  try {

    test0();

  } catch (std::exception & x) {
    std::cerr << "ERROR: " << x.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "ERROR: " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}

void test0()
{
  protobuftools::protobuf_factory::system_factory().print(std::clog, "System protobuf message factory: ");
  std::clog << std::endl;

  std::string foo_binded_protobuf_guid = protobuftools::binded_protobuf_guid<protobuftools::testing::foo>();
  std::clog << "foo binded protobuf guid      = '" << foo_binded_protobuf_guid << "'" << std::endl;
  std::string foo_bar_binded_protobuf_guid = protobuftools::binded_protobuf_guid<protobuftools::testing::foo::bar>();
  std::clog << "foo::bar binded protobuf guid = '" << foo_bar_binded_protobuf_guid << "'" << std::endl;
  std::clog << std::endl;

  std::shared_ptr<google::protobuf::Message> fooMsg
    = protobuftools::protobuf_factory::system_factory().create_message_instance(foo_binded_protobuf_guid);
  if (!fooMsg) {
    throw std::logic_error("Could not instantiate a '" + foo_binded_protobuf_guid + "'!");
  }
  protobuftools::tree_print(*fooMsg.get(), std::clog, "Foo protobuf message: ");
  std::clog << std::endl;

  std::shared_ptr<google::protobuf::Message> fooBarMsg
    = protobuftools::protobuf_factory::system_factory().create_message_instance(foo_bar_binded_protobuf_guid);
  if (!fooBarMsg) {
    throw std::logic_error("Could not instantiate a '" + foo_bar_binded_protobuf_guid + "'!");
  }
  protobuftools::tree_print(*fooBarMsg.get(), std::clog, "Foo::Bar protobuf message: ");
  std::clog << std::endl;

  std::string buffer;

  {
    protobuftools::testing::foo f0;
    f0.status = protobuftools::testing::foo::ERR_MORE;
    f0.print(std::clog, "Default object 'f0' : ");
    std::clog << std::endl;
    f0.flag = false;
    f0.u16  = 345;
    f0.i32  = -1000;
    f0.f    = -1.234e5F;
    f0.d    = +765.423e32;
    f0.status = protobuftools::testing::foo::ERR_MORE;
    f0.code   = protobuftools::testing::CODE_THREE;
    f0.word   = "King Arthur";
    f0.vi32   = { 7, 6, 5, 4, 3, 2, 1, 0};
    f0.lf   = { 3.0F, 3.1F, 3.2F};
    f0.si16   = { 2, 3, 5, 7, 11, 13, 17, 19, 23};
    f0.ad   = {{ 1.e0, 1.e1, 1.e2, 1.e3 }};
    f0.dummy.name = "Bevedere";
    f0.dummy.value = 472;
    f0.dummy.z.open = true;
    f0.dummy.z.number = 511;
    f0.dummy.z.price = 8.50F;
    {
      protobuftools::testing::zoo z1;
      z1.open = true;
      z1.number = 57;
      z1.price = 3.99F;
      f0.vz.push_back(z1);
      protobuftools::testing::zoo z2;
      z2.open = false;
      z2.number = 23;
      z2.price = 7.99F;
      f0.vz.push_back(z2);
      protobuftools::testing::zoo z3;
      z3.open = true;
      z3.number = 100;
      z3.price = 15.99F;
      f0.vz.push_back(z3);
    }
    {
      protobuftools::testing::zoo z1;
      z1.open = true;
      z1.number = 99;
      z1.price = 111.F;
      f0.lz.push_back(z1);
      protobuftools::testing::zoo z2;
      z2.open = false;
      z2.number = 88;
      z2.price = 222.F;
      f0.lz.push_back(z2);
      protobuftools::testing::zoo z3;
      z3.open = true;
      z3.number = 77;
      z3.price = 333.F;
      f0.lz.push_back(z3);
      protobuftools::testing::zoo z4;
      z4.open = false;
      z4.number = 66;
      z4.price = 444.F;
      f0.lz.push_back(z4);
    }
    {
      protobuftools::testing::zoo z1;
      z1.open = false;
      z1.number = 17;
      z1.price = 3.14F;
      f0.sz.insert(z1);
      protobuftools::testing::zoo z2;
      z2.open = false;
      z2.number = 16;
      z2.price = 2.718F;
      f0.sz.insert(z2);
    }
    {
      protobuftools::testing::zoo z1;
      z1.open = false;
      z1.number = 1003;
      z1.price = 17.718F;
      f0.az[0] = z1;
      protobuftools::testing::zoo z2;
      z2.open = false;
      z2.number = 1002;
      z2.price = 16.718F;
      f0.az[1] = z2;
      protobuftools::testing::zoo z3;
      z3.open = false;
      z3.number = 1001;
      z3.price = 15.718F;
      f0.az[2] = z3;
    }
    f0.time = boost::posix_time::microsec_clock::universal_time();


    f0.print(std::clog, "Modified object 'f0' : ");
    std::clog << std::endl;
    {
      // Protobufization:
      std::clog << "Protobufization...\n";
      std::ostringstream obuffer;
      protobuftools::store(obuffer, f0, protobuftools::IO_DEBUG);
      // std::clog << "Output buffer: " << obuffer.str().length() << "\n";
      // std::clog << obuffer.str();
      buffer = obuffer.str();
    }
  }

  std::clog << "\nBuffer size = " << buffer.length() << "  Bytes=\n" << buffer << "\nEOB\n";

  bool load = true;
  // load = false;
  if (load) {
    protobuftools::testing::foo f0;
    {
      // Deprotobufization:
      std::clog << "Deprotobufization...\n";
      std::istringstream ibuffer(buffer);
      protobuftools::load(ibuffer, f0, protobuftools::IO_DEBUG);
    }
    f0.print(std::clog, "Loaded object 'f0' : ");
    std::clog << std::endl;
  }

  return;
}
