// -*- mode: c++; -*-

// Standard library:
#include <fstream>

// This project:
#include <protobuftools/exception.h>
#include <protobuftools/node.h>

namespace protobuftools {

  template<typename T>
  void load(const std::string & file_, T & data_, uint32_t flags_ = 0)
  {
    std::ifstream ifs(file_);
    if (ifs.fail()) {
      throw ::protobuftools::exception("Opening file '" + file_ + "' failed");
    }
    load(ifs, data_, flags_);
    return;
  }

  template<typename T>
  void store(const std::string & file_, const T & data_, uint32_t flags_ = 0)
  {
    std::ofstream ofs(file_);
    if (ofs.fail()) {
      throw ::protobuftools::exception("Opening file '" + file_ + "' failed");
    }
    store(ofs, data_, flags_);
    return;
  }

} // end of namespace protobuftools
