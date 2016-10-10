// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_STD_STRING_CONVERTERS_H
#define BXPROTOBUFTOOLS_STD_STRING_CONVERTERS_H

// Standard library:
#include <string>

// Third party:
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

// This project:
#include <protobuftools/exception.h>
#include <protobuftools/core.h>
#include <protobuftools/node.h>

namespace protobuftools {

  template<>
  class converter<std::string>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, std::string & x_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception, node_.get_message(), "Missing field descriptor!");
      const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "' with field descriptor of type '" << field_descriptor->type_name() << "'");
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->type() != google::protobuf::FieldDescriptor::TYPE_STRING,
                                         wrong_type_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                         "Expected STRING");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      if (field_descriptor->is_repeated()) {
        BX_LOG_DEBUG(node_.get_logging(),
                     "as repeated field of initial size=" << reflection->FieldSize(node_.get_message(), field_descriptor));
        reflection->AddString(&node_.grab_message(), field_descriptor, x_);
        BX_LOG_DEBUG(node_.get_logging(),
                     "as repeated field has new size = " << reflection->FieldSize(node_.get_message(), field_descriptor));
      } else {
        BX_LOG_DEBUG(node_.get_logging(), "as singular field");
        reflection->SetString(&node_.grab_message(), field_descriptor, x_);
      }
      return;
    }

    // Generic deserialization method for a string value
    static void deprotobufize(message_node & node_, std::string & x_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception, node_.get_message(), "Missing field descriptor!");
      const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "' with field descriptor of type '" << field_descriptor->type_name() << "'");
      BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->type() != google::protobuf::FieldDescriptor::TYPE_STRING,
                                         wrong_type_field_exception,
                                         node_.get_message(),
                                         *field_descriptor,
                                         "Expected STRING");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      if (field_descriptor->is_repeated()) {
        BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->is_required() && reflection->FieldSize(node_.get_message(), field_descriptor) == 0,
                                           missing_required_field_exception,
                                           node_.get_message(),
                                           *field_descriptor,
                                           "Missing required repeated STRING field '" << field_descriptor->full_name() << "'");
        BX_LOG_DEBUG(node_.get_logging(),
                     "As repeated field of size = " << reflection->FieldSize(node_.get_message(), field_descriptor));
        x_ = reflection->GetRepeatedString(node_.get_message(), field_descriptor, node_.get_repeated_index());
      } else {
        BX_LOG_DEBUG(node_.get_logging(), "As singular field");
        BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(field_descriptor->is_required() && !reflection->HasField(node_.get_message(), field_descriptor),
                                           missing_required_field_exception,
                                           node_.get_message(),
                                           *field_descriptor,
                                           "Missing required singular STRING field '" << field_descriptor->full_name() << "'");
        x_ = reflection->GetString(node_.get_message(), field_descriptor);
      }
      return;
    }

  };

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_STD_STRING_CONVERTERS_H
