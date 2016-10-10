// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_STD_TYPE_CONVERTERS_H
#define BXPROTOBUFTOOLS_STD_TYPE_CONVERTERS_H

#include <protobuftools/std_string_converter.h>
#include <protobuftools/std_vector_converter.h>
#include <protobuftools/std_list_converter.h>
#include <protobuftools/std_set_converter.h>
#include <protobuftools/std_array_converter.h>


/*
// Standard library:
// #include <map>
namespace protobuftools {
  template<typename T1, typename T2>
  class converter<std::map<T1, T2>>
  {
  public:

  static void serialize(node & node_, std::map<T1, T2> & x_)
  {
  node_.grab_value() = Json::arrayValue;
  for (auto & e : x_) {
  T1   key   = e.first;
  T2 & value = e.second;
  google::protobuf::Message jsonValue;
  node_value(jsonValue["key"], true, false)   % key;
  node_value(jsonValue["value"], true, false) % value;
  node_.grab_value().append(jsonValue);
  }
  return;
  }

  static void deserialize(node & node_, std::map<T1, T2> & x_)
  {
  if (not node_.get_value().isArray()) {
  throw wrong_type(node_.get_value(), "expected array");
  }
  x_.clear();
  for (std::size_t i(0); i < node_.get_value().size(); ++i) {
  T1 key;
  T2 value;
  node_value(node_.grab_value()[i]["key"], false, false)   % key;
  node_value(node_.grab_value()[i]["value"], false, false) % value;
  x_[key] = std::move(value);
  }
  return;
  }

  };
} // end of namespace protobuftools
*/


#endif // BXPROTOBUFTOOLS_STD_TYPE_CONVERTERS_H
