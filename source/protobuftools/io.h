// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_IO_H
#define BXPROTOBUFTOOLS_IO_H

// Standard library:
#include <iostream>

namespace protobuftools {

  enum io_flags {
    IO_DEBUG  = 0x1
  };

  /// Deserialize an object of given type from an input stream
  template<typename T>
  void load(std::istream & in_, T & data_, uint32_t flags_ = 0);

  /// Serialize an object of given type to an output stream
  template<typename T>
  void store(std::ostream & out_, const T & data_, uint32_t flags_ = 0);

} // end of namespace protobuftools

#include "io-inl.h"

#endif // BXPROTOBUFTOOLS_IO_H
