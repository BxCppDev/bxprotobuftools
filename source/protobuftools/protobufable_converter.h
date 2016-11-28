// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_PROTOBUFABLE_CONVERTER_H
#define BXPROTOBUFTOOLS_PROTOBUFABLE_CONVERTER_H

// Standard library:
#include <iostream>
#include <type_traits>

// This project:
#include <protobuftools/core.h>
#include <protobuftools/node.h>
#include <protobuftools/i_protobufable.h>

namespace protobuftools {


  /// \brief Generic converter from object of class T
  ///        to a protobuf message wrapper node.
  ///
  ///        The class T is expected to inherit the
  ///        protobuftools::i_protobufable interface.
  template<typename T>
  class converter<T, typename std::enable_if<std::is_base_of<::protobuftools::i_protobufable, T>::value>::type>
  {
  public:

    // Generic serialization method using protobufize method
    static void protobufize(::protobuftools::message_node & node_,
                            T & x_)
    {
      BX_LOG_DEBUG(node_.get_logging(),
                   "Protobufize a field node with message inherited from 'protobuftools::i_protobufable'...");
      x_.protobufize(node_, 0);
      return;
    }

    // Generic deserialization method using _deprotobufize wrapper function
    static void deprotobufize(message_node & node_, T & x_)
    {
       _deprotobufize(node_, x_, 0);
      return;
    }

  };

  // Deserialization method uses explicit T::deprotobufize method if provided
  template<typename T>
  auto _deprotobufize(message_node & node_, T & x_, int)
    -> decltype(x_.deprotobufize(node_, 0))
  {
    x_.deprotobufize(node_, 0);
    return;
  }

  // Deserialization method uses explicit T::protobufize method
  template<typename T>
  auto _deprotobufize(message_node & node_, T & x_, long)
    -> decltype(x_.protobufize(node_, 0))
  {
    x_.protobufize(node_, 0);
    return;
  }

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_PROTOBUFABLE_CONVERTER_H
