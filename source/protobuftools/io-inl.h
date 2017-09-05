// -*- mode: c++; -*-

// Standard library:
#include <memory>
#include <string>
#include <sstream>

// Third party:
#include <google/protobuf/message.h>

// This project:
#include <protobuftools/exception.h>
#include <protobuftools/protobuf_factory.h>
#include <protobuftools/node.h>
#include <protobuftools/protobuf_utils.h>

namespace protobuftools {

  template<typename T>
  void load(std::istream & in_, T & data_, uint32_t flags_)
  {
    protobuftools::logger::priority logging = protobuftools::logger::PRIO_FATAL;
    if (flags_ & IO_DEBUG) {
      logging = protobuftools::logger::PRIO_DEBUG;
    }
    std::string the_binded_protobuf_guid = ::protobuftools::binded_protobuf_guid<T>();
    BX_LOG_DEBUG(logging, "Binded protobuf message GUID = '" << the_binded_protobuf_guid << "'");
    BX_THROW_IF(the_binded_protobuf_guid.empty(), std::logic_error,
                "Protobuf parsing failed: class has no binded protobuf message GUID!");
    BX_THROW_IF(!::protobuftools::protobuf_factory::system_factory().has_factory_function(the_binded_protobuf_guid),
                std::logic_error,
                "No binded protobuf message '" << the_binded_protobuf_guid << "' is registered in the binded protobuf message factory system register!");
    BX_LOG_DEBUG(logging, "Instantiating a working protobuf message with GUID = '" << the_binded_protobuf_guid << "'");
    std::shared_ptr<google::protobuf::Message> root_msg(::protobuftools::protobuf_factory::system_factory().create_message_instance(the_binded_protobuf_guid));
    BX_LOG_DEBUG(logging, "Parsing the working protobuf message with GUID = '" << the_binded_protobuf_guid << "'")
      bool ok = root_msg->ParseFromIstream(&in_);
    BX_THROW_IF(!ok, std::logic_error, "Protobuf message '" << the_binded_protobuf_guid << "' parsing failed: !");
    try {
      BX_LOG_DEBUG(logging, "Importing the object from the working protobuf message with GUID = '" << the_binded_protobuf_guid << "'");
      message_node_value node(*root_msg, nullptr, false, false, logging);
      node % data_;
    } catch (const std::exception & error) {
      BX_THROW(std::logic_error, "Protobuf message parsing failed : " << error.what());
    }
    return;
  }

  template<typename T>
  void store(std::ostream & out_, const T & data_, uint32_t flags_)
  {
    protobuftools::logger::priority logging = protobuftools::logger::PRIO_FATAL;
    if (flags_ & IO_DEBUG) {
      logging = protobuftools::logger::PRIO_DEBUG;
    }
    std::string the_binded_protobuf_guid = ::protobuftools::binded_protobuf_guid<T>();
    BX_LOG_DEBUG(logging, "Binded protobuf message GUID = '" << the_binded_protobuf_guid << "'")
    BX_THROW_IF(the_binded_protobuf_guid.empty(), std::logic_error,
                "Protobuf storing failed: class has no binded protobuf message GUID!");
    BX_THROW_IF(!::protobuftools::protobuf_factory::system_factory().has_factory_function(the_binded_protobuf_guid),
                std::logic_error,
                "No binded protobuf message '" << the_binded_protobuf_guid << "' is registered in the binded protobuf message factory system register!");
    BX_LOG_DEBUG(logging, "Instantiating a working protobuf message with GUID = '" << the_binded_protobuf_guid << "'");
    std::shared_ptr<google::protobuf::Message> root_msg(::protobuftools::protobuf_factory::system_factory().create_message_instance(the_binded_protobuf_guid));
    try {
      BX_LOG_DEBUG(logging, "Exporting the object to the working protobuf message with GUID = '" << the_binded_protobuf_guid << "'");
      message_node_value node(*root_msg, nullptr, true, false, logging);
      node % const_cast<T &>(data_);
    } catch (const std::exception & error) {
      BX_THROW(std::logic_error, "Protobuf message storing failed : " << error.what());
    }
    BX_LOG_DEBUG(logging, "Serializing the working protobuf message with GUID = '" << the_binded_protobuf_guid << "'");
    bool ok = root_msg->SerializeToOstream(&out_);
    BX_THROW_IF(!ok, std::logic_error, "Protobuf message '" << the_binded_protobuf_guid << "' serialization failed: !");
    return;
  }

} // end of namespace protobuftools
