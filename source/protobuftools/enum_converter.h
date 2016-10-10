// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_ENUM_CONVERTER_H
#define BXPROTOBUFTOOLS_ENUM_CONVERTER_H

// Standard library:
#include <iostream>
#include <type_traits>

// This project:
#include <protobuftools/core.h>
#include <protobuftools/node.h>
#include <protobuftools/exception.h>

namespace protobuftools {

  /// \brief Converter from object of enumeration class T
  ///        to a protobuf message wrapper node.
  ///
  ///        The class T is expected to check std::is_enum<T>::value.
  template<typename T>
  class converter<T, typename std::enable_if<std::is_enum<T>::value>::type>
  {
  public:

    // Generic serialization method for enumeration value
    static void protobufize(::protobuftools::message_node & node_, T & x_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception, node_.get_message(), "Missing field descriptor!");
      const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "' with field descriptor of type '" << field_descriptor->type_name() << "'");
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->type() != google::protobuf::FieldDescriptor::TYPE_ENUM,
                                         wrong_type_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                         "Expected ENUM");
      const google::protobuf::EnumDescriptor * enum_desc = field_descriptor->enum_type();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Protobufize an ENUM field of type '" << enum_desc->full_name() << "'");
      const google::protobuf::EnumValueDescriptor * enum_value_desc = enum_desc->FindValueByNumber(x_);
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(enum_value_desc == nullptr,
                                         wrong_type_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                         "Unknown enumeration value");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      if (field_descriptor->is_repeated()) {
        BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->is_required()
                                           && reflection->FieldSize(node_.get_message(), field_descriptor) == 0,
                                           missing_required_field_exception,
                                           node_.get_message(),
                                           *field_descriptor,
                                           "Missing required repeated ENUM field '" << field_descriptor->full_name() << "'");
        BX_LOG_DEBUG(node_.get_logging(),
                     "As repeated field of size = " << reflection->FieldSize(node_.get_message(), field_descriptor));
        reflection->AddEnum(&node_.grab_message(), field_descriptor, enum_value_desc);
        BX_LOG_DEBUG(node_.get_logging(),
                     "as repeated field has new size = " << reflection->FieldSize(node_.get_message(), field_descriptor));
      } else {
        BX_LOG_DEBUG(node_.get_logging(), "as singular field");
        reflection->SetEnum(&node_.grab_message(), field_descriptor, enum_value_desc);
      }
      return;
    }

    // Generic deserialization method for enumeration value
    static void deprotobufize(message_node & node_, T & x_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception, node_.get_message(), "Missing field descriptor!");
      const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "' with field descriptor of type '" << field_descriptor->type_name() << "'");
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->type() != google::protobuf::FieldDescriptor::TYPE_ENUM,
                                         wrong_type_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                         "Expected ENUM");
      const google::protobuf::EnumDescriptor * enum_desc = field_descriptor->enum_type();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Deprotobufize an ENUM field of type '" << enum_desc->full_name() << "'");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      if (field_descriptor->is_repeated()) {
        BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->is_required()
                                           && reflection->FieldSize(node_.get_message(), field_descriptor) == 0,
                                           missing_required_field_exception,
                                           node_.get_message(),
                                           *field_descriptor,
                                           "Missing required repeated ENUM field '" << field_descriptor->full_name() << "'");
        BX_LOG_DEBUG(node_.get_logging(),
                     "As repeated field of size = " << reflection->FieldSize(node_.get_message(), field_descriptor));
        const google::protobuf::EnumValueDescriptor * enum_value_desc =
          reflection->GetRepeatedEnum(node_.get_message(), field_descriptor, node_.get_repeated_index());
        x_ = static_cast<T>(enum_value_desc->number());
      } else {
        BX_LOG_DEBUG(node_.get_logging(), "As singular field");
        BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->is_required()
                                           && !reflection->HasField(node_.get_message(), field_descriptor),
                                           missing_required_field_exception,
                                           node_.get_message(),
                                           *field_descriptor,
                                           "Missing required singular ENUM field '" << field_descriptor->full_name() << "'");
        const google::protobuf::EnumValueDescriptor * enum_value_desc =
          reflection->GetEnum(node_.get_message(), field_descriptor);
        x_ = static_cast<T>(enum_value_desc->number());
      }
      return;
    }

  };

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_ENUM_CONVERTER_H
