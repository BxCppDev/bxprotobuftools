// Ourselves:
#include "node.h"

// Standard library:
#include <iostream>
#include <sstream>

// Third party:
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

// This project:
#include "protobuf_utils.h"
#include "logger_macros.h"
#include "exception.h"

namespace protobuftools {

  /* Base node */

  base_node::base_node(const bool serializing_, const logger::priority logging_)
    : _serializing_(serializing_)
    , _logging(logging_)
  {
    BX_LOG_DEBUG(logging_, "Construct a " << (serializing_ ? "serializing" : "deserializing") << " base node.");
    return;
  }

  base_node::~base_node()
  {
    return;
  }

  bool base_node::is_serializing() const
  {
    return _serializing_;
  }

  bool base_node::is_debug() const
  {
    return logger::is_debug(_logging);
  }

  bool base_node::is_trace() const
  {
    return logger::is_trace(_logging);
  }

  logger::priority base_node::get_logging() const
  {
    return _logging;
  }

  // virtual
  void base_node::print(std::ostream & out_,
                        const std::string & title_,
                        const std::string & indent_,
                        bool inherit_) const
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << "|-- "
         << "Serializing : " << (_serializing_ ? "<yes>": "<no>") << std::endl;

    out_ << indent_ << (inherit_ ? "|-- " : "`--")
         << "Logging : " << _logging << " [debug=" << (is_debug() ? "<yes>": "<no>") << "]" << std::endl;

    return;
  }

  /* Message node */

  message_node::message_node(google::protobuf::Message & message_,
                             const bool serializing_,
                             const logger::priority logging_)
    : message_node(message_, nullptr, serializing_, logging_)
  {
    return;
  }

  message_node::message_node(google::protobuf::Message & message_,
                             const google::protobuf::FieldDescriptor * field_descriptor_,
                             const bool serializing_,
                             const logger::priority logging_)
    : base_node(serializing_, logging_)
    , _message(message_)
    , _field_descriptor(field_descriptor_)
    , _repeated_index_(-1)
  {
    BX_LOG_DEBUG(logging_, "Construct a " << (serializing_ ? "serializing" : "deserializing")
                 << " message node of type '" << message_.GetDescriptor()->full_name()
                 << "'" << (field_descriptor_ != nullptr? " with field descriptor named '" : "")
                 << (field_descriptor_ != nullptr? field_descriptor_->name() + "'" : "")
                 );
    return;
  }

  message_node::~message_node()
  {
    return;
  }

  const google::protobuf::Message & message_node::get_message() const
  {
    return _message;
  }

  google::protobuf::Message & message_node::grab_message()
  {
    return _message;
  }

  const google::protobuf::FieldDescriptor *
  message_node::get_field_descriptor() const
  {
    return _field_descriptor;
  }

  void message_node::set_field_descriptor(const google::protobuf::FieldDescriptor * field_descriptor_)
  {
    _field_descriptor = field_descriptor_;
    return;
  }

  bool message_node::is_field() const
  {
    return _field_descriptor != nullptr;
  }

  bool message_node::is_singular() const
  {
    if (!is_field()) {
      return false;
    }
    if (_field_descriptor->is_repeated()) return false;
    if (_repeated_index_ >= 0) return false;
    return true;
  }

  bool message_node::is_repeated() const
  {
    if (!is_field()) {
      return false;
    }
    if (!_field_descriptor->is_repeated()) return false;
    if (_repeated_index_ < 0) return false;
    return true;
  }

  void message_node::set_repeated_index(int index_)
  {
    if (index_ < 0) {
      _repeated_index_ = -1;
      return;
    }
    BX_PROTOBUF_MESSAGE_THROW_IF(is_field() && !_field_descriptor->is_repeated(),
                                 message_exception,
                                 _message,
                                 "Cannot set repeated index because the target field node is singular!");
    _repeated_index_ = index_;
    return;
  }

  int message_node::get_repeated_index() const
  {
    return _repeated_index_;
  }

  // virtual
  void message_node::print(std::ostream & out_,
                           const std::string & title_,
                           const std::string & indent_,
                           bool inherit_) const
  {
    this->base_node::print(out_, title_, indent_, true);

    out_ << indent_ << "|-- "
         << "Message : '" << _message.GetDescriptor()->full_name() << "'" << std::endl;

    out_ << indent_ << "|-- "
         << "Field : " << (is_field() ? "<yes>": "<no>");
    out_ << std::endl;

    out_ << indent_ << "|-- "
         << "Field descriptor : ";
    if (_field_descriptor) {
      out_ << _field_descriptor->full_name();
    } else {
      out_ << "<none>";
    }
    out_ << std::endl;

    out_ << indent_ << "|-- "
         << "Singular : " << (is_singular() ? "<yes>": "<no>");
    out_ << std::endl;

    out_ << indent_ << "|-- "
         << "Repeated : " << (is_repeated() ? "<yes>": "<no>");
    out_ << std::endl;

    out_ << indent_ << (inherit_ ? "|-- " : "`-- ")
         << "Repeated index : ";
    if (get_repeated_index() >= 0) {
      out_ << get_repeated_index();
    } else {
      out_ << "<none>";
    }
    out_ << std::endl;

    return;
  }


  /* Message node value */

  bool message_node::has_field(const std::string & s_) const
  {
    const google::protobuf::Descriptor * descriptor = _message.GetDescriptor();
    bool found_attribute = false;
    const google::protobuf::FieldDescriptor * field_desc = nullptr;
    if (!found_attribute) {
      // First we try to find a field attribute with name s_:
      if (::protobuftools::has_field(*descriptor, s_)) {
        found_attribute = true;
      }
    }
    return found_attribute;
  }

  message_node_value message_node::operator[](const std::string & s_)
  {
    const google::protobuf::Descriptor * descriptor = _message.GetDescriptor();
    BX_LOG_DEBUG(_logging, "Accessing field '" << s_ << "' from message node of type '"
                 << descriptor->full_name()
                 << "'");
    BX_LOG_DEBUG(_logging, "Message type full name : '" << descriptor->full_name() << "'");
    bool found_attribute = false;
    const google::protobuf::FieldDescriptor * field_desc = nullptr;
    if (!found_attribute) {
      // First we try to find a field attribute with name s_:
      if (::protobuftools::has_field(*descriptor, s_)) {
        found_attribute = true;
        BX_LOG_DEBUG(_logging, "Message '" << descriptor->full_name() << "' "
                     << "has field named : '" << s_ << "'");
        field_desc = descriptor->FindFieldByName(s_);
        BX_PROTOBUF_MESSAGE_THROW_IF(field_desc == nullptr,
                                     message_exception,
                                     _message,
                                     "Message type full name : '"  << descriptor->full_name() << "' "
                                     << "does not have a field descriptor for field named '" << s_ << "'!");
        bool defaultValueNeeded = false;
        if (field_desc->message_type() != nullptr && ! field_desc->is_repeated()) {
          // We found a singular field member of type MESSAGE:
          const google::protobuf::Descriptor * msg_desc = field_desc->message_type();
          BX_LOG_DEBUG(_logging, "Message '" << descriptor->full_name() << "' "
                       << "has singular sub message field named : '" << s_ << "' of type '"
                       << msg_desc->full_name() << "'");
          const google::protobuf::Reflection * reflection = _message.GetReflection();
          google::protobuf::Message * submsg = reflection->MutableMessage(&_message, field_desc);
          return message_node_value(*submsg, nullptr, is_serializing(), defaultValueNeeded, get_logging());
        // } else if (field_desc->message_type() != nullptr && field_desc->is_repeated()) {
        //   const google::protobuf::Descriptor * msg_desc = field_desc->message_type();
        //   BX_LOG_DEBUG(_logging, "=====> Message '" << descriptor->full_name() << "' "
        //                << "has repeated sub message field named : '" << s_ << "' of type '"
        //                << msg_desc->full_name() << "'");
        //   const google::protobuf::Reflection * reflection = _message.GetReflection();
        //   BX_LOG_DEBUG(_logging, "=====> reflection ok");
        //   google::protobuf::Message * submsg = reflection->MutableMessage(&_message, field_desc);
        //   BX_LOG_DEBUG(_logging, "=====> submsg = " << submsg->DebugString());
        //   const google::protobuf::Descriptor * submsg_descriptor = submsg->GetDescriptor();
        //   const google::protobuf::FieldDescriptor * submsg_field_desc = submsg_descriptor->FindFieldByName(s_);
        //   // const google::protobuf::Descriptor * submsg_desc = field_desc->message_type();
        //   // const google::protobuf::FieldDescriptor * sub_field_desc = descriptor->FindFieldByName(s_);
        //   return message_node_value(*submsg, submsg_field_desc, is_serializing(), defaultValueNeeded, get_logging());
        } else {
          // Any other case is handled here:
          BX_LOG_DEBUG(_logging, "Message '" << descriptor->full_name() << "' "
                       << "has field named : '" << s_ << "' of type '"
                       << field_desc->full_name() << "'");
          return message_node_value(_message, field_desc, is_serializing(), defaultValueNeeded, get_logging());
        }
      }
    }
    if (!found_attribute) {
      // Next we try to find a oneof attribute with name s_:
      // if (has_oneof(*descriptor, s_)) {
      //   const google::protobuf::OneofDescriptor * oneof_desc = descriptor->FindOneofByName(s_);
      // }
    }
    BX_PROTOBUF_MESSAGE_THROW_IF(!found_attribute,
                                 message_exception,
                                 _message,
                                 "Could not find an attribute named '" << s_
                                 << "' in message named : '"  << descriptor->full_name() << "' !");
    // const google::protobuf::Reflection * reflection = _value.GetReflection();
    // bool defaultValueNeeded = not reflection->HasField(_value, field_desc);
    // google::protobuf::Message * fieldMsg = reflection->MutableMessage(&_value, field_desc);
    // return message_node_value(*fieldMsg, is_serializing(), defaultValueNeeded);
  }

  /* Message node value */

  message_node_value::message_node_value(google::protobuf::Message & message_,
                                         const google::protobuf::FieldDescriptor * field_descriptor_,
                                         const bool serializing_,
                                         const bool default_value_needed_,
                                         const logger::priority logging_)
    : message_node(message_, field_descriptor_, serializing_, logging_)
    , _default_value_needed(default_value_needed_)
  {
    BX_LOG_DEBUG(logging_, "Construct a " << (serializing_ ? "serializing" : "deserializing")
                 << " message node value of type '" << message_.GetDescriptor()->full_name()
                 << "'" << (field_descriptor_ != nullptr? " with field descriptor named '" : "")
                 << (field_descriptor_ != nullptr? field_descriptor_->name() + "'" : "")
                 );
    return;
  }

  message_node_value::~message_node_value()
  {
    return;
  }

} // end of namespace protobuftools
