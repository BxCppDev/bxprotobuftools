//! \file    datatools/exception.h
//! \brief   Utility macros for exception handling
//! \details Exceptions are often thrown based on the value of a boolean
//!          expression. The exception, if it holds a string based
//!          message about what went wrong, should report where it was
//!          thrown from.
//!
//!          To help developers throwing exceptions in this fashion,
//!          datatools supplies some macros to assist in simplifying this
//!          work, and making the intent clearer in code.
//
// Copyright (c) 2016 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2016 by The University of Warwick
// Copyright (c) 2016 by François Mauger <mauger@lpccaen.in2p3.fr>
// Copyright (c) 2016 by Univesité de Caen Normandie
//
// This file is part of protobuftools.
//
// protobuftools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// protobuftools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with protobuftools.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BXPROTOBUFTOOLS_EXCEPTION_H
#define BXPROTOBUFTOOLS_EXCEPTION_H

// Standard library:
#include <string>
#include <stdexcept>
#include <sstream>

// Third Party:
// - Boost:
#include <boost/current_function.hpp>
// - Protobuf:
#include <google/protobuf/message.h>

namespace protobuftools {

  /// \brief Basic exception
  class exception : public std::exception
  {
  public:

    /// Constructor
    exception(const std::string & what_);

    /// Return the embedded error message
    const char * what() const noexcept;

  private:

    std::string _what_; ///< Embedded error message

  };

  /// \brief Protobuf message exception
  class message_exception : public exception
  {
  public:

    /// Constructor
    message_exception(const google::protobuf::Message & message_,
                      const std::string & what_);

    /// Return the referenced protobuf message
    const  google::protobuf::Message & get_message() const;

  private:

    const google::protobuf::Message * _message_ = nullptr; ///< Referenced protobuf message value

  };

  /// \brief Protobuf message field exception
  class message_field_exception : public message_exception
  {
  public:

    /// Constructor
    message_field_exception(const google::protobuf::Message & message_,
                            const google::protobuf::FieldDescriptor & fdesc_,
                            const std::string & what_);

    const google::protobuf::FieldDescriptor & get_field_descriptor() const;

  private:

    const google::protobuf::FieldDescriptor * _field_descriptor_ = nullptr; ///< Referenced protobuf message field descriptor

  };

  /// \brief Wrong type field exception
  class wrong_type_field_exception : public message_field_exception
  {
  public:

    /// Constructor
    wrong_type_field_exception(const google::protobuf::Message & message_,
			       const google::protobuf::FieldDescriptor & fdesc_,
			       const std::string & what_);

  };

  /// \brief Base size type field exception
  class bad_size_field_exception : public message_field_exception
  {
  public:

    /// Constructor
    bad_size_field_exception(const google::protobuf::Message & message_,
			     const google::protobuf::FieldDescriptor & fdesc_,
			     const std::string & what_);

  };

  /// \brief Missing required field exception
  class missing_required_field_exception : public message_field_exception
  {
  public:

    /// Constructor
    missing_required_field_exception(const google::protobuf::Message & message_,
                                     const google::protobuf::FieldDescriptor & fdesc_,
                                     const std::string & what_);

  };

  /// \brief Invalid value field exception
  class invalid_value_field_exception : public message_field_exception
  {
  public:

    /// Constructor
    invalid_value_field_exception(const google::protobuf::Message & message_,
                                  const google::protobuf::FieldDescriptor & fdesc_,
                                  const std::string & what_);

  };

} // end of namespace protobuftools

/*! Throw ExceptionType with What message if the expression Condition is true
  This macro is intended to simplify the common use case of throwing
  exceptions when a boolean condition is true, with the exception
  holding a string message indicating where and why the exception was
  thrown. This macro takes three arguments as follows

  @param Condition     Boolean expression
  @param ExceptionType Typename of object to throw, the type must take
  a string as its constructor argument
  @param What          Message to supply to ExceptionType, this must
  take the form of a string or output stream
  sequence

  The Message is formatted as

  @code
  [SIGNATURE:LINENUMBER: What]
  @endcode

  where SIGNATURE is the signature of the function from which the
  exception is thrown, and LINENUMBER is the line number where the
  throw occured.

  In the simplest case it may be used as

  @code
  BX_THROW_IF(i < 0, std::logic_error, "parameter i is negative");
  @endcode

  If Message is composed from several streamable objects, it can
  be composed using the streaming operator:

  @code
  BX_THROW_IF(i < 0, std::logic_error, "parameter i(" << i << ") is negative");
  @endcode
*/
#define BX_THROW_IF(Condition, ExceptionType, What)			\
  {                                                                     \
    if (Condition) {                                                    \
      std::stringstream sBX_THROW_IF_ONLY;				\
      sBX_THROW_IF_ONLY << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << ": " << What << "]"; \
      throw ExceptionType(sBX_THROW_IF_ONLY.str());			\
    }                                                                   \
  }

/*! Throw ExceptionType with What
  This macro is intended to simplify the common use case of throwing
  exceptions, with the exception
  holding a string message indicating where and why the exception was
  thrown. This macro takes two arguments as follows

  @param ExceptionType Typename of object to throw, the type must take
  a string as its constructor argument
  @param What       What to supply to ExceptionType, this must
  take the form of a string or output stream
  sequence

  The What is formatted as

  @code
  [SIGNATURE:LINENUMBER: What]
  @endcode

  where SIGNATURE is the signature of the function from which the
  exception is thrown, and LINENUMBER is the line number where the
  throw occured.

  In the simplest case it may be used as

  @code
  BX_THROW(std::domain_error, "parameter i is negative");
  @endcode

  If What is composed from several streamable objects, it can
  be composed using the streaming operator:

  @code
  BX_THROW(std::domain_error, "parameter i(" << i << ") is negative");
  @endcode
*/
#define BX_THROW(ExceptionType, What)                                   \
  {                                                                     \
    std::stringstream sBX_THROW_ONLY;                                   \
    sBX_THROW_ONLY << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << ": " << What << "]"; \
    throw ExceptionType(sBX_THROW_ONLY.str());                          \
  }

/*! Throw ExceptionType with Message if the expression Condition is true
  This macro is intended to simplify the common use case of throwing
  exceptions when a boolean condition is true, with the exception
  holding a string message indicating where and why the exception was
  thrown. This macro takes three arguments as follows

  @param Condition     Boolean expression
  @param ProtobufMsgExceptionType Typename of object to throw, the type must take
  a string as its constructor argument, it must inherit the protobuftools::message_exception class
  @param ProtobufMsg   Reference to a protobuf message object from which the exception is related
  @param What          Message to supply to ExceptionType, this must take the form of a string or
  output stream sequence

  The Message is formatted as

  @code
  [SIGNATURE:LINENUMBER: What]
  @endcode

  where SIGNATURE is the signature of the function from which the
  exception is thrown, and LINENUMBER is the line number where the
  throw occured.

  In the simplest case it may be used as

  @code
  google::protobuf::Message gpb_msg;
  ...
  BX_PROTOBUF_MESSAGE_THROW_IF(i < 0, protobuftools::message_exception, gpb_msg, "Malformed protobuf message");
  @endcode

  If Message is composed from several streamable objects, it can
  be composed using the streaming operator:

  @code
  google::protobuf::Message gpb_msg;
  ...
  BX_PROTOBUF_MESSAGE_THROW_IF(i < 0,
  protobuftools::missing_required_field_exception,
  gpb_msg,
  "Invalid protobuf message with missing attribute '" << attrname << "'");
  @endcode
*/
#define BX_PROTOBUF_MESSAGE_THROW_IF(Condition, ProtobufMsgExceptionType, ProtobufMsg, What) \
  {                                                                     \
    if (Condition) {                                                    \
      std::stringstream sBX_THROW_IF_ONLY;				\
      sBX_THROW_IF_ONLY << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << ": " << What << "]"; \
      throw ProtobufMsgExceptionType(ProtobufMsg, sBX_THROW_IF_ONLY.str()); \
    }                                                                   \
  }

#define BX_PROTOBUF_MESSAGE_FIELD_THROW_IF(Condition, ProtobufMsgFieldExceptionType, ProtobufMsg, ProtobufMsgFieldDesc, What) \
  {                                                                     \
    if (Condition) {                                                    \
      std::stringstream sBX_THROW_IF_ONLY;                              \
      sBX_THROW_IF_ONLY << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << ": " << What << "]"; \
      throw ProtobufMsgFieldExceptionType(ProtobufMsg, ProtobufMsgFieldDesc, sBX_THROW_IF_ONLY.str()); \
    }                                                                   \
  }

#endif // BXPROTOBUFTOOLS_EXCEPTION_H
