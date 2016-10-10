// Ourselves:
#include <protobuftools/exception.h>

namespace protobuftools {

  /* Basic exception */

  exception::exception(const std::string & what_)
    : _what_(what_)
  {
    return;
  }

  const char * exception::what() const noexcept
  {
    return _what_.c_str();
  }

  /* Protobuf message exception */

  message_exception::message_exception(const google::protobuf::Message & message_,
                                       const std::string & what_)
    : exception(what_)
    , _message_(&message_)
  {
    return;
  }

  const google::protobuf::Message &
  message_exception::get_message() const
  {
    return *_message_;
  }

  /* Protobuf message field exception */

  message_field_exception::message_field_exception(const google::protobuf::Message & message_,
                                                   const google::protobuf::FieldDescriptor & fdesc_,
                                                   const std::string & what_)
    : message_exception(message_, what_)
    , _field_descriptor_(&fdesc_)
  {
    return;
  }

  const google::protobuf::FieldDescriptor &
  message_field_exception::get_field_descriptor() const
  {
    return *_field_descriptor_;
  }

  /* Protobuf wrong field type exception */

  wrong_type_field_exception::wrong_type_field_exception(const google::protobuf::Message & message_,
                                                         const google::protobuf::FieldDescriptor & fdesc_,
                                                         const std::string & what_)
    : message_field_exception(message_, fdesc_, what_)
  {
    return;
  }

  /* Protobuf bad size field exception */

  bad_size_field_exception::bad_size_field_exception(const google::protobuf::Message & message_,
                                                     const google::protobuf::FieldDescriptor & fdesc_,
                                                     const std::string & what_)
    : message_field_exception(message_, fdesc_, what_)
  {
    return;
  }

  /* Protobuf missing required field exception */

  missing_required_field_exception::missing_required_field_exception(const google::protobuf::Message & message_,
                                                                     const google::protobuf::FieldDescriptor & fdesc_,
                                                                     const std::string & what_)
    : message_field_exception(message_, fdesc_, what_)
  {
    return;
  }

  /* Protobuf invalid value field exception */

  invalid_value_field_exception::invalid_value_field_exception(const google::protobuf::Message & message_,
                                                               const google::protobuf::FieldDescriptor & fdesc_,
                                                               const std::string & what_)
    : message_field_exception(message_, fdesc_, what_)
  {
    return;
  }

} // end of namespace protobuftools
