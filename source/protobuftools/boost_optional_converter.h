// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_BOOST_OPTIONAL_CONVERTER_H
#define BXPROTOBUFTOOLS_BOOST_OPTIONAL_CONVERTER_H

// Standard library:
#include <ctime>
#include <memory>

// Third party:
// - Boost:
#include <boost/optional.hpp>
// - Protobuf:
#include <google/protobuf/any.pb.h>

// This project:
#include <protobuftools/core.h>
#include <protobuftools/node.h>
#include <protobuftools/exception.h>
#include <protobuftools/protobuf_utils.h>
#include <protobuftools/protobuf_factory.h>

namespace protobuftools {

  template<typename T>
  class converter<boost::optional<T>>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, boost::optional<T> & opt_)
    {
      // BX_PROTOBUF_MESSAGE_THROW_IF(! node_.is_field(), message_exception,
      //                              node_.get_message(), "Missing field descriptor!");
      // const google::protobuf::FieldDescriptor * field_descriptor = node_.get_field_descriptor();
      if (logger::is_debug(node_.get_logging())) {
        std::cerr << "\n\n";
        std::cerr << "*****************************\n";
        std::cerr << "*   Store boost::optional   *\n";
        std::cerr << "*****************************\n";
      }
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name() << "'");
      static const std::string DESC_NAME("protobuftools.boost.Optional");
      static const std::string TYPE_ID("type_id");
      BX_PROTOBUF_MESSAGE_THROW_IF(node_.get_message().GetDescriptor()->full_name() != DESC_NAME,
                                   message_exception,
                                   node_.get_message(),
                                   "Invalid descriptor '" << node_.get_message().GetDescriptor()->full_name()
                                   << "' (expected '" << DESC_NAME << "')!");
      if (logger::is_debug(node_.get_logging())) {
        // tree_print(*node_.get_message().GetDescriptor(), std::cerr, "Optional message descriptor:", "[debug] ");
      }
      BX_PROTOBUF_MESSAGE_THROW_IF(!has_field(*node_.get_message().GetDescriptor(), TYPE_ID),
                                   message_exception,
                                   node_.get_message(),
                                   "Missing field named '" << TYPE_ID << "' in descriptor!");
      bool init_flag = opt_.is_initialized();
      BX_LOG_DEBUG(node_.get_logging(), "init_flag = " << init_flag);
      std::string value_type_id;
      if (!init_flag) {
        value_type_id = "";
        node_[TYPE_ID] % value_type_id;
      } else {
        value_type_id = protobuftools::binded_protobuf_guid<T>();
        BX_LOG_DEBUG(node_.get_logging(), "value_type_id = '" << value_type_id << "'");
        node_[TYPE_ID] % value_type_id;
        std::string pb_value_type_id;
        std::ostringstream field_name_oss;
        if (cpp_type_match_base_protobuf_type(value_type_id)) {
          pb_value_type_id = cpp_type_as_protobuf_type(value_type_id);
          field_name_oss << pb_value_type_id << "_value";
        } else {
          field_name_oss << "any_value";
        }
        std::string field_name = field_name_oss.str();
        BX_LOG_DEBUG(node_.get_logging(), "value_type_id = '" << value_type_id << "'");
        BX_LOG_DEBUG(node_.get_logging(), "field_name    = '" << field_name << "'");
        BX_PROTOBUF_MESSAGE_THROW_IF(!has_field(*node_.get_message().GetDescriptor(), field_name),
                                     message_exception,
                                     node_.get_message(),
                                     "Missing field named '" << field_name << "' in descriptor!");
        const google::protobuf::FieldDescriptor * value_field_desc
          = node_.get_message().GetDescriptor()->FindFieldByName(field_name);
        BX_PROTOBUF_MESSAGE_THROW_IF(value_field_desc == nullptr,
                                     message_exception,
                                     node_.get_message(),
                                     "Cannot find field descriptor for field '" << field_name << "'!");
        if (field_name == "any_value") {
          std::shared_ptr<google::protobuf::Message> optMsg
            = protobuftools::protobuf_factory::system_factory().create_message_instance(value_type_id);
          if (optMsg) {
            if (logger::is_debug(node_.get_logging())) {
              // tree_print(*optMsg.get(), std::cerr, "Empty optMsg: ", "[debug] ");
            }
            message_node_value opt_item_node(*optMsg.get(),
                                             value_field_desc,
                                             node_.is_serializing(),
                                             false,
                                             node_.get_logging());
            converter<T>::protobufize(opt_item_node, opt_.get());
            const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
            google::protobuf::Message * anyMsg = reflection->MutableMessage(&node_.grab_message(), value_field_desc);
            google::protobuf::Any * any = dynamic_cast<google::protobuf::Any*>(anyMsg);
            any->PackFrom(*optMsg.get());
          }
        } else {
          BX_LOG_DEBUG(node_.get_logging(), "Field with basic type = '" << field_name << "'");
          BX_LOG_DEBUG(node_.get_logging(), "Field description = '" << value_field_desc->full_name() << "'");
          message_node_value opt_item_node(node_.grab_message(),
                                           value_field_desc,
                                           node_.is_serializing(),
                                           false,
                                           node_.get_logging());
          converter<T>::protobufize(opt_item_node, opt_.get());
        }
      }
      if (logger::is_debug(node_.get_logging())) {
        tree_print_short(node_.get_message(), std::cerr, "Filled Optional message: ", "[debug] ");
      }
      if (logger::is_debug(node_.get_logging())) {
        std::cerr << "\n";
        std::cerr << "***************************\n";
        std::cerr << "*           Done          *\n";
        std::cerr << "***************************\n";
        std::cerr << "\n";
      }
      return;
    }

    static void deprotobufize(::protobuftools::message_node & node_, boost::optional<T> & opt_)
    {
      if (logger::is_debug(node_.get_logging())) {
        std::cerr << "\n\n";
        std::cerr << "****************************\n";
        std::cerr << "*   Load boost::optional   *\n";
        std::cerr << "****************************\n";
      }
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name() << "'");
      static const std::string DESC_NAME("protobuftools.boost.Optional");
      static const std::string TYPE_ID("type_id");
      BX_PROTOBUF_MESSAGE_THROW_IF(node_.get_message().GetDescriptor()->full_name() != DESC_NAME,
                                   message_exception,
                                   node_.get_message(),
                                   "Invalid descriptor '" << node_.get_message().GetDescriptor()->full_name()
                                   << "' (expected '" << DESC_NAME << "')!");
      BX_PROTOBUF_MESSAGE_THROW_IF(!has_field(*node_.get_message().GetDescriptor(), TYPE_ID),
                                   message_exception,
                                   node_.get_message(),
                                   "Missing field named '" << TYPE_ID << "' in descriptor!");
      const google::protobuf::Reflection * reflection = node_.get_message().GetReflection();
      const google::protobuf::FieldDescriptor * type_id_field_desc
          = node_.get_message().GetDescriptor()->FindFieldByName(TYPE_ID);
      std::string value_type_id;
      if (reflection->HasField(node_.get_message(), type_id_field_desc)) {
        node_[TYPE_ID] % value_type_id;
      }
      if (value_type_id.empty()) {
        // Optional value is unset:
        opt_ = boost::none;
      } else {
        // Optional value is set:
        std::string expected_value_type_id = protobuftools::binded_protobuf_guid<T>();
        BX_LOG_DEBUG(node_.get_logging(), "expected_value_type_id = '" << expected_value_type_id << "'");
        BX_PROTOBUF_MESSAGE_THROW_IF(expected_value_type_id != value_type_id,
                                     message_exception,
                                     node_.get_message(),
                                     "Unexpected value type id '" << value_type_id
                                     << "' (expected '" << DESC_NAME << "')!");
        std::string pb_value_type_id;
        std::ostringstream field_name_oss;
        if (cpp_type_match_base_protobuf_type(value_type_id)) {
          pb_value_type_id = cpp_type_as_protobuf_type(value_type_id);
          field_name_oss << pb_value_type_id << "_value";
        } else {
          field_name_oss << "any_value";
        }
        std::string field_name = field_name_oss.str();
        BX_LOG_DEBUG(node_.get_logging(), "field_name    = '" << field_name << "'");
        const google::protobuf::FieldDescriptor * value_field_desc
          = node_.get_message().GetDescriptor()->FindFieldByName(field_name);
        BX_PROTOBUF_MESSAGE_THROW_IF(value_field_desc == nullptr,
                                     message_exception,
                                     node_.get_message(),
                                     "Cannot find field descriptor for field '" << field_name << "'!");
        BX_LOG_DEBUG(node_.get_logging(), "Field descriptor = '" << value_field_desc->full_name() << "'");
        if (field_name == "any_value") {
          std::shared_ptr<google::protobuf::Message> optMsg
            = protobuftools::protobuf_factory::system_factory().create_message_instance(value_type_id);
          if (logger::is_debug(node_.get_logging())) {
            tree_print_short(*optMsg.get(), std::cerr, "Optional message: ", "[debug] ");
          }
          const google::protobuf::Message & anyMsg
            = reflection->GetMessage(node_.get_message(), value_field_desc);
          const google::protobuf::Any & any = dynamic_cast<const google::protobuf::Any&>(anyMsg);
          if (logger::is_debug(node_.get_logging())) {
            tree_print_short(any, std::cerr, "Embedded any message: ", "[debug] ");
          }
          BX_PROTOBUF_MESSAGE_THROW_IF(!any.UnpackTo(optMsg.get()),
                                       message_exception,
                                       node_.get_message(),
                                       "Unpacking field '" << field_name << "' failed!");
          message_node_value opt_item_node(*optMsg.get(),
                                           value_field_desc,
                                           node_.is_serializing(),
                                           false,
                                           node_.get_logging());
          opt_ = T();
          converter<T>::deprotobufize(opt_item_node, opt_.get());
        } else {
          BX_LOG_DEBUG(node_.get_logging(), "Field with basic type = '" << field_name << "'");
          BX_LOG_DEBUG(node_.get_logging(), "Field description = '" << value_field_desc->full_name() << "'");
          message_node_value opt_item_node(node_.grab_message(),
                                           value_field_desc,
                                           node_.is_serializing(),
                                           false,
                                           node_.get_logging());
          opt_ = T();
          converter<T>::deprotobufize(opt_item_node, opt_.get());
        }
      }
      if (logger::is_debug(node_.get_logging())) {
        std::cerr << "\n";
        std::cerr << "***************************\n";
        std::cerr << "*           Done          *\n";
        std::cerr << "***************************\n";
        std::cerr << "\n";
      }
      return;
    }

  };

}

#endif // BXPROTOBUFTOOLS_BOOST_OPTIONAL_CONVERTER_H
