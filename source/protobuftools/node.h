#ifndef BXPROTOBUFTOOLS_NODE_H
#define BXPROTOBUFTOOLS_NODE_H

// Standard library:
#include <string>
#include <iostream>

// Third party:
#include <google/protobuf/message.h>

// This project:
#include <protobuftools/core.h>
#include <protobuftools/logger.h>

namespace protobuftools {

  /// \brief Base protobuf value accessor node
  class base_node
  {
  public:

    /// Constructor
    base_node(const bool serializing_, const logger::priority logging_);

    /// Destructor
    virtual ~base_node();

    /// Check serialization flag
    bool is_serializing() const;

    /// Check debug flag
    bool is_debug() const;

    /// Check debug flag
    bool is_trace() const;

    /// Return the logging priority threshold
    logger::priority get_logging() const;

    /// Smart print
    virtual void print(std::ostream & out_ = std::clog,
                       const std::string & title_ = "",
                       const std::string & indent_ = "",
                       bool inherit_ = false) const;

  protected:

    logger::priority _logging = logger::priority::PRIO_FATAL; ///< Logging threshold level

  private:

    bool _serializing_; ///< Serialize flag

  };

  class message_node_value;

  /// \brief Protobuf message accessor node
  class message_node : public base_node
  {
  public:

    /// Constructor
    message_node(google::protobuf::Message & message_,
                 const google::protobuf::FieldDescriptor * field_descriptor_,
                 const bool serializing_,
                 const logger::priority logging_ = logger::priority::PRIO_FATAL);

    /// Constructor
    message_node(google::protobuf::Message & message_,
                 const bool serializing_,
                 const logger::priority logging_ = logger::priority::PRIO_FATAL);

    /// Destructor
    virtual ~message_node();

    /// Return the embedded protobuf message
    const google::protobuf::Message & get_message() const;

    /// Return the embedded protobuf message
    google::protobuf::Message & grab_message();

    /// Return the field descriptor
    const google::protobuf::FieldDescriptor * get_field_descriptor() const;

    /// Set the field descriptor
    void set_field_descriptor(const google::protobuf::FieldDescriptor * field_descriptor_);

    /// Access to a node message item with given name
    message_node_value operator[](const std::string & s_);

    /// Check if node is a message field
    bool is_field() const;

    /// Check if node is singular
    bool is_singular() const;

    /// Check if node is repeated
    bool is_repeated() const;

    /// Set the repeated index
    void set_repeated_index(int index_);

    /// Return the repeated index
    int get_repeated_index() const;

    /// Smart print
    virtual void print(std::ostream & out_ = std::clog,
                       const std::string & title_ = "",
                       const std::string & indent_ = "",
                       bool inherit_ = false) const;

  protected:

    google::protobuf::Message & _message; ///< Handle to a protobuf message
    const google::protobuf::FieldDescriptor * _field_descriptor = nullptr; ///< Field descriptor
    int _repeated_index_ = -1; ///< Repeated field index

  };

  template<typename T>
  class message_node_value_default;

  /// \brief Message node value
  class message_node_value : public message_node
  {
  public:

    /// Constructor
    message_node_value(google::protobuf::Message & message_,
                       const google::protobuf::FieldDescriptor * fdesc_,
                       const bool serializing_,
                       const bool default_value_needed_,
                       const logger::priority logging_ = logger::priority::PRIO_FATAL);

    /// Destructor
    virtual ~message_node_value();

    template<typename T>
    message_node_value_default<T> operator%(T & x_);

  protected:

    bool _default_value_needed = false; ///< Flag for needed default value

  };

  /// \brief
  template<typename T>
  class message_node_value_default
  {
  public:

    /// Constructor
    message_node_value_default(T & t_, bool need_default_value_);

    /// Or operator
    void operator or(const T & t_);

  protected:

    T &  _t; ///< Reference to a default value
    bool _need_default_value; ///< Flag set if a default value is needed

  };

} // end of namespace protobuftools

#include "node-inl.h"

#endif // BXPROTOBUFTOOLS_NODE_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
