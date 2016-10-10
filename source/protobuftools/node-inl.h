// -*- mode: c++; -*-

// Standard Library:
#include <type_traits>
#include <iostream>

// // This project:
// #include <protobuftools/core.h>

namespace protobuftools {

  template<typename T>
  message_node_value_default<T> message_node_value::operator%(T & x_)
  {
    BX_LOG_DEBUG(get_logging(),
                 "Message node of type '"
                 << get_message().GetDescriptor()->full_name()
                 << "'");
    if (is_serializing()) {
      BX_LOG_DEBUG(get_logging(),
                   "Serializing using 'converter<T>::protobufize'... ");
      converter<T>::protobufize(*this, x_);
      _default_value_needed = false;
    } else if (not _default_value_needed) {
      BX_LOG_DEBUG(get_logging(),
                   "Deserializing using 'converter<T>::deprotobufize'... ");
      converter<T>::deprotobufize(*this, x_);
    }
    return message_node_value_default<T>(x_, _default_value_needed);
  }

  template<typename T>
  message_node_value_default<T>::message_node_value_default(T & t_,
                                                            const bool need_default_value_)
    : _t(t_), _need_default_value(need_default_value_)
  {
    return;
  }

  template<typename T>
  void message_node_value_default<T>::operator or(const T & t_)
  {
    if (_need_default_value) {
      _t = t_;
      _need_default_value = false;
    }
    return;
  }

} // end of namespace protobuftools

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
