// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_I_PROTOBUFABLE_H
#define BXPROTOBUFTOOLS_I_PROTOBUFABLE_H

// Standard library:
#include <type_traits>

// This project:
#include <protobuftools/core.h>

namespace protobuftools {

  class message_node;

  /// \brief Abstract interface for protobuf serializable class
  class i_protobufable
  {
  public:

    /// Default constructor
    i_protobufable();

    /// Destructor
    virtual ~i_protobufable();

    /// Main Protobuf (de-)serialization method
    virtual void protobufize(protobuftools::message_node & node_,
                             const unsigned long int version_ = 0) = 0;

  };

  /// \brief Abstract interface for protobuf serializable class
  ///        with explicit implementation of a deserialization
  ///        method distinct from the i_protobufable::protobufize
  ///        method.
  class i_deprotobufable
    : public i_protobufable
  {
  public:

    /// Default constructor
    i_deprotobufable();

    /// Destructor
    virtual ~i_deprotobufable();

    /// Special Protobuf deserialization method
    virtual void deprotobufize(protobuftools::message_node & node_,
                               const unsigned long int version_ = 0) = 0;

  };

  /// \brief Specialized template converter for JSON-izable objects
  template<typename T>
  class converter<T, typename std::enable_if<std::is_base_of<::protobuftools::i_protobufable, T>::value>::type>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, T & x_)
    {
      x_.T::protobufize(node_, 0);
      return;
    }

    static void deprotobufize(::protobuftools::message_node & node_, T & x_)
    {
      x_.T::protobufize(node_, 0);
      return;
    }

  };

  /// \brief Specialized template converter for JSON-izable objects
  template<typename T>
  class converter<T, typename std::enable_if<std::is_base_of<::protobuftools::i_deprotobufable, T>::value>::type>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, T & x_)
    {
      x_.T::protobufize(node_, 0);
      return;
    }

    static void deprotobufize(::protobuftools::message_node & node_, T & x_)
    {
      x_.T::deprotobufize(node_, 0);
      return;
    }

  };

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_I_PROTOBUFABLE_H
