// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_IOFILE_H
#define BXPROTOBUFTOOLS_IOFILE_H

// Standard library:
#include <string>

// This project:
#include <protobuftools/io.h>

namespace protobuftools {

  template<typename T>
  void load(const std::string & file_, T & data_, uint32_t flags_ = 0);

  template<typename T>
  void store(const std::string & file_, const T & data_, uint32_t flags_ = 0);

} // end of namespace protobuftools

#include "iofile-inl.h"

#endif // BXPROTOBUFTOOLS_IOFILE_H
