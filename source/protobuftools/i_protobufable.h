// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_I_PROTOBUFABLE_H
#define BXPROTOBUFTOOLS_I_PROTOBUFABLE_H

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
                             unsigned long int version_ = 0) = 0;

  };

  /// \brief Abstract interface for protobuf serializable class
  ///        with explicit implementation of a deserialization
  ///        method distinct from the i_protobufable::protobufize
  ///        method.
  class i_deprotobufable : public i_protobufable
  {
  public:

    /// Default constructor
    i_deprotobufable();

    /// Destructor
    virtual ~i_deprotobufable();

    /// Special Protobuf deserialization method
    virtual void deprotobufize(protobuftools::message_node & node_,
                               unsigned long int version_ = 0) = 0;

  };

} // end of namespace protobuftools

#endif // BXPROTOBUFTOOLS_I_PROTOBUFABLE_H
