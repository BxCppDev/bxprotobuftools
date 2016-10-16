// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_CORE_H
#define BXPROTOBUFTOOLS_CORE_H

namespace protobuftools {

  // template<typename ...T>
  // template <typename T, typename Enable = void>
  template <typename T, typename T2 = void, typename Enable = void>
  class converter;

  // // template<typename ...T>
  // template <typename T, typename Enable = void>
  // class converter_split;

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_CORE_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
