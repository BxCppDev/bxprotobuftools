// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_STD_SET_CONVERTERS_H
#define BXPROTOBUFTOOLS_STD_SET_CONVERTERS_H

// Standard library:
#include <set>

// Third party:
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

// This project:
#include <protobuftools/exception.h>
#include <protobuftools/core.h>
#include <protobuftools/node.h>

namespace protobuftools {

  template<typename T>
  class converter<std::set<T>>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, std::set<T> & x_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception,
                                   node_.get_message(), "Missing field descriptor!");
      const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "' with field descriptor of type '" << field_descriptor->type_name() << "'");
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(not field_descriptor->is_repeated(),
                                         message_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                   "expected repeated");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      std::size_t elem_counter = 0;
      for (auto xelem : x_) {
        if (field_descriptor->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
          // Special case for MESSAGE:
          BX_LOG_DEBUG(node_.get_logging(),
                       "Message node of type '"
                       << node_.get_message().GetDescriptor()->full_name()
                       << "' with field of type '" << field_descriptor->type_name() << "' at index [" << elem_counter << "]"
                       );
          google::protobuf::Message * msg_field
            = reflection->AddMessage(&node_.grab_message(), field_descriptor);
          message_node_value item_node(*msg_field,
                                       nullptr, //field_descriptor,
                                       node_.is_serializing(),
                                       false,
                                       node_.get_logging());
          converter<T>::protobufize(item_node, xelem);
        } else {
          // General case with basic types:
          message_node_value item_node(node_.grab_message(),
                                       field_descriptor,
                                       node_.is_serializing(),
                                       false,
                                       node_.get_logging());
          item_node.set_repeated_index(elem_counter);
          converter<T>::protobufize(item_node, xelem);
        }
        elem_counter++;
      }
      return;
    }

    // Generic deserialization method for a string value
    static void deprotobufize(message_node & node_, std::set<T> & x_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception,
                                   node_.get_message(), "Missing field descriptor!");
      const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "' with field descriptor of type '" << field_descriptor->type_name() << "'");
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(not field_descriptor->is_repeated(),
                                         message_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                         "expected repeated");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      x_.clear();
      std::size_t sz = (std::size_t) reflection->FieldSize(node_.get_message(), field_descriptor);
      for (std::size_t ielem = 0; ielem < sz; ++ielem) {
        T xelem;
        if (field_descriptor->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
          // Special case for MESSAGE:
          BX_LOG_DEBUG(node_.get_logging(),
                       "Message node of type '"
                       << node_.get_message().GetDescriptor()->full_name()
                       << "' with field of type '" << field_descriptor->type_name() << "' at index [" << ielem << "]"
                       );
          google::protobuf::Message * msg_field
            = reflection->MutableRepeatedMessage(&node_.grab_message(),
                                                 field_descriptor,
                                                 ielem);
          message_node_value item_node(*msg_field,
                                       nullptr, //field_descriptor,
                                       node_.is_serializing(),
                                       false,
                                       node_.get_logging());
          converter<T>::deprotobufize(item_node, xelem);
        } else {
          // General case with basic types:
          message_node_value item_node(node_.grab_message(),
                                       field_descriptor,
                                       node_.is_serializing(),
                                       false,
                                       node_.get_logging());
          item_node.set_repeated_index(ielem);
          converter<T>::deprotobufize(item_node, xelem);
        }
        x_.insert(xelem);
      }
      return;
    }

  };

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_STD_SET_CONVERTERS_H
