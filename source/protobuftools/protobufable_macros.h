// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_PROTOBUFABLE_MACROS_H
#define BXPROTOBUFTOOLS_PROTOBUFABLE_MACROS_H

// Standard library:
#include <string>

// This project:
#include <protobuftools/node.h>
#include <protobuftools/serdes.h>

namespace protobuftools {

  template<class T>
  class protobuf_message_factory_registrar {
  };

  template<class T>
  class protobuf_message_factory_registrar {
  public:
    protobuf_message_factory_registrar(std::string classname_)
    {
      // register the class factory function
      MyFactory::Instance()->RegisterFactoryFunction(classname_,
                                                     [](void) -> T * { return new T();});
    }
  };

} // end of namespace protobuftools



#endif // BXPROTOBUFTOOLS_PROTOBUFABLE_MACROS_H
