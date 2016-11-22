// Ourselves:
#include <protobuftools/protobuf_utils.h>

// Third party:
// - Boost:
#include <boost/algorithm/string/trim.hpp>

namespace {

  static const std::string tag("|-- ");
  static const std::string last_tag("`-- ");
  static const std::string skip_tag("|   ");
  static const std::string last_skip_tag("    ");
}

namespace protobuftools {

  void tree_print(const google::protobuf::FileDescriptor & filedesc_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Name      : '" << filedesc_.name() << "'" << std::endl;
    out_ << indent_ << tag << "Package   : '" << filedesc_.package() << "'" << std::endl;
    out_ << indent_ << tag << "Dependencies : " << filedesc_.dependency_count() << "\n";
    for (int i = 0; i < filedesc_.dependency_count(); i++) {
      const google::protobuf::FileDescriptor * fd = filedesc_.dependency(i);
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag;
      if (i == filedesc_.dependency_count() - 1) {
        indent2 << tag;
      } else {
        indent2 << tag;
      }
      out_ << indent2.str();
      out_ << "Dependency: '" << fd->name() << "'" << std::endl;
    }
    out_ << indent_ << skip_tag << tag << "Public dependencies : " << filedesc_.public_dependency_count() << "\n";
    for (int i = 0; i < filedesc_.public_dependency_count(); i++) {
      const google::protobuf::FileDescriptor * fd = filedesc_.public_dependency(i);
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag << skip_tag;
      if (i == filedesc_.public_dependency_count() - 1) {
        indent2 << last_tag;
      } else {
        indent2 << tag;
      }
      out_ << indent2.str();
      out_ << "Public dependency: '" << fd->name() << "'" << std::endl;
    }
    out_ << indent_ << skip_tag << last_tag << "Weak dependencies : " << filedesc_.weak_dependency_count() << "\n";
    for (int i = 0; i < filedesc_.weak_dependency_count(); i++) {
      const google::protobuf::FileDescriptor * fd = filedesc_.weak_dependency(i);
      std::ostringstream indent2;
      indent2 << indent_ << last_skip_tag << skip_tag;
      if (i == filedesc_.weak_dependency_count() - 1) {
        indent2 << last_tag;
      } else {
        indent2 << tag;
      }
      out_ << indent2.str();
      out_ << "Weak dependency: '" << fd->name() << "'" << std::endl;
    }

    out_ << indent_ << tag << "Message types : " << filedesc_.message_type_count() << "\n";
    for (int i = 0; i < filedesc_.message_type_count(); i++) {
      const google::protobuf::Descriptor * desc = filedesc_.message_type(i);
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag;
      out_ << indent_ << skip_tag;
      if (i == filedesc_.message_type_count() - 1) {
        indent2 << last_skip_tag;
        out_ << last_tag;
      } else {
        indent2 << skip_tag;
        out_ << tag;
      }
      out_ << "Message type: '" << desc->full_name() << "'" << std::endl;
    }

    out_ << indent_ << tag << "Enum types : " << filedesc_.enum_type_count() << "\n";
    for (int i = 0; i < filedesc_.enum_type_count(); i++) {
      const google::protobuf::EnumDescriptor * desc = filedesc_.enum_type(i);
      std::ostringstream indent2;
      indent2 << indent_ << last_skip_tag;
      out_ << indent_ << skip_tag;
      if (i == filedesc_.enum_type_count() - 1) {
        indent2 << last_tag;
        out_ << last_tag;
      } else {
        indent2 << tag;
        out_ << tag;
      }
      out_ << "Enum: '" << desc->full_name() << "'" << std::endl;
    }

    out_ << indent_ << tag << "Services : " << filedesc_.service_count() << "\n";
    for (int i = 0; i < filedesc_.service_count(); i++) {
      const google::protobuf::ServiceDescriptor * sdesc = filedesc_.service(i);
      std::ostringstream indent2;
      indent2 << indent_ << last_skip_tag;
      out_ << indent_ << skip_tag;
      if (i == filedesc_.service_count() - 1) {
        indent2 << last_tag;
        out_ << last_tag;
      } else {
        indent2 << tag;
        out_ << tag;
      }
      out_ << "Service: '" << sdesc->full_name() << "'" << std::endl;
    }

    out_ << indent_ << tag << "Extensions : " << filedesc_.extension_count() << "\n";
    for (int i = 0; i < filedesc_.extension_count(); i++) {
      const google::protobuf::FieldDescriptor * xdesc = filedesc_.extension(i);
      std::ostringstream indent2;
      indent2 << indent_ << last_skip_tag;
      out_ << indent_ << skip_tag;
      if (i == filedesc_.extension_count() - 1) {
        indent2 << last_tag;
        out_ << last_tag;
      } else {
        indent2 << tag;
        out_ << tag;
      }
      out_ << "Extension: '" << xdesc->full_name() << "'" << std::endl;
    }

    out_ << indent_ << last_tag << "Syntax : '" << filedesc_.SyntaxName(filedesc_.syntax()) << "'" << std::endl;

    return;
  }

  void tree_print(const google::protobuf::EnumValueDescriptor & evdesc_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Name       : '" << evdesc_.name() << "'" << std::endl;
    out_ << indent_ << tag << "Full name  : '" << evdesc_.full_name() << "'" << std::endl;
    out_ << indent_ << tag << "Index      : " << evdesc_.index() << std::endl;
    out_ << indent_ << tag << "Number     : " << evdesc_.number() << std::endl;
    out_ << indent_ << last_tag << "Type       : '" << evdesc_.type()->full_name() << "'" << std::endl;

    return;
  }

  void tree_print(const google::protobuf::EnumDescriptor & fdesc_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    return;
  }

  void tree_print(const google::protobuf::OneofDescriptor & desc_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Name      : '" << desc_.name() << "'\n";
    out_ << indent_ << tag << "Full name : '" << desc_.full_name() << "'\n";
    out_ << indent_ << tag << "Index     : " << desc_.index() << " \n";

    if (desc_.containing_type() != nullptr) {
      out_ << indent_ << tag << "Containing type : '"
           << desc_.containing_type()->full_name()<< "'\n";
    } else {
      out_ << indent_ << tag << "Containing type : <none>\n";
    }

    out_ << indent_ << tag << "Field count : " << desc_.field_count() << "\n";
    for (int i = 0; i < desc_.field_count(); i++) {
      const google::protobuf::FieldDescriptor * fdesc = desc_.field(i);
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag;
      out_ << indent_ << skip_tag;
      if (i == desc_.field_count() - 1) {
        indent2 << last_skip_tag;
        out_ << last_tag;
      } else {
        indent2 << skip_tag;
        out_ << tag;
      }
      out_ << "Field descriptor #" << i << " : \n";
      tree_print(*fdesc, out_, "", indent2.str());
    }

    out_ << indent_ << last_tag << "Debug string: [" << desc_.DebugString() << "]"  << "\n";

    return;
  }

  void tree_print(const google::protobuf::FieldDescriptor & fdesc_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Name       : '" << fdesc_.name() << "'" << std::endl;
    out_ << indent_ << tag << "Full name  : '" << fdesc_.full_name() << "'" << std::endl;
    out_ << indent_ << tag << "File descriptor : '" << fdesc_.file() << "'" << std::endl;
    out_ << indent_ << tag << "Extension : " << (fdesc_.is_extension() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << tag << "Type          : " << fdesc_.type() << " as '" << google::protobuf::FieldDescriptor::TypeName(fdesc_.type()) << "'" << std::endl;
    out_ << indent_ << tag << "Type name     : '" << fdesc_.type_name() << "'" << std::endl;
    out_ << indent_ << tag << "C++ Type      : " << fdesc_.cpp_type() << std::endl;
    out_ << indent_ << tag << "C++ Type name : '" << fdesc_.cpp_type_name() << "'" << std::endl;
    out_ << indent_ << tag << "Label         : '" << fdesc_.label() << "'" << std::endl;
    out_ << indent_ << skip_tag << tag << "Required  : " << (fdesc_.is_required() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << skip_tag << tag << "Optional  : " << (fdesc_.is_optional() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << skip_tag << last_tag << "Repeated : " << (fdesc_.is_repeated() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << tag << "Packable  : " << (fdesc_.is_packable() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << tag << "Packed    : " << (fdesc_.is_packed() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << tag << "Map       : " << (fdesc_.is_map() ? "<yes>" : "<no>") << std::endl;
    out_ << indent_ << tag << "Index     : " << fdesc_.index() << std::endl;
    out_ << indent_ << tag << "Has default value : " << (fdesc_.has_default_value() ? "<yes>" : "<no>") << std::endl;
    if (fdesc_.has_default_value()) {
      switch (fdesc_.type()) {
      case google::protobuf::FieldDescriptor::TYPE_DOUBLE :
        out_ << indent_ << tag << "Default value (double) : " << fdesc_.default_value_double() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_FLOAT :
        out_ << indent_ << tag << "Default value (float) : " << fdesc_.default_value_float() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_INT64 :
        out_ << indent_ << tag << "Default value (int64) : " << fdesc_.default_value_int64() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_UINT64 :
        out_ << indent_ << tag << "Default value (uint64) : " << fdesc_.default_value_uint64() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_INT32 :
        out_ << indent_ << tag << "Default value (int32) : " << fdesc_.default_value_int32() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_UINT32 :
        out_ << indent_ << tag << "Default value (uint32) : " << fdesc_.default_value_uint32() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_FIXED64 :
        out_ << indent_ << tag << "Default value (uint64) : " << fdesc_.default_value_uint64() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_FIXED32 :
        out_ << indent_ << tag << "Default value (uint32) : " << fdesc_.default_value_uint32() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_BOOL :
        out_ << indent_ << tag << "Default value (bool) : " << fdesc_.default_value_bool() << "\n";
        break;
      case google::protobuf::FieldDescriptor::TYPE_STRING :
        out_ << indent_ << tag << "Default value (std::string) : " << fdesc_.default_value_string() << "\n";
        break;
      default:
        out_ << indent_ << tag << "Default value : " << "<unknown>" << std::endl;
      }
    }
    out_ << indent_ << tag << "Containing type : '" << fdesc_.containing_type()->full_name() << "'" << std::endl;

    out_ << indent_ << tag << "Containing oneof : ";
    if (fdesc_.containing_oneof()) {
      out_ << "'" << fdesc_.containing_oneof()->full_name() << "' (with index " << fdesc_.index_in_oneof() << ")";
    } else {
      out_<< "<none>";
    }
    out_ << std::endl;

    if (fdesc_.type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE
        || fdesc_.type() == google::protobuf::FieldDescriptor::TYPE_GROUP) {
      out_ << indent_ << tag << "Message type : '" << fdesc_.message_type()->full_name() << "'" << std::endl;
    }

    if (fdesc_.type() == google::protobuf::FieldDescriptor::TYPE_ENUM) {
      out_ << indent_ << tag << "Enum type : '" << fdesc_.enum_type()->full_name() << "'" << std::endl;
    }

    {
      std::string dbgstr = fdesc_.DebugString();
      boost::algorithm::trim(dbgstr);
      out_ << indent_ << last_tag << "Debug string : '" << dbgstr << "'" << std::endl;
    }

    return;
  }

  void tree_print(const google::protobuf::Descriptor & desc_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Name      : '" << desc_.name() << "'\n";
    out_ << indent_ << tag << "Full name : '" << desc_.full_name() << "'\n";
    out_ << indent_ << tag << "Index     : " << desc_.index() << " \n";
    out_ << indent_ << tag << "File      : @" << desc_.file() << "\n";
    {
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag;
      tree_print(*desc_.file(), out_, "", indent2.str());
    }

    if (desc_.containing_type() != nullptr) {
      out_ << indent_ << tag << "Containing type : '"
           << desc_.containing_type()->full_name()<< "'\n";
    } else {
      out_ << indent_ << tag << "Containing type : <none>\n";
    }

    out_ << indent_ << tag << "Field count : " << desc_.field_count() << "\n";
    for (int i = 0; i < desc_.field_count(); i++) {
      const google::protobuf::FieldDescriptor * fdesc = desc_.field(i);
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag;
      out_ << indent_ << skip_tag;
      if (i == desc_.field_count() - 1) {
        indent2 << last_skip_tag;
        out_ << last_tag;
      } else {
        indent2 << skip_tag;
        out_ << tag;
      }
      out_ << "Field descriptor #" << i << " : \n";
      tree_print(*fdesc, out_, "", indent2.str());
    }

    out_ << indent_ << tag << "Oneof count : " << desc_.oneof_decl_count() << "\n";
    for (int i = 0; i < desc_.oneof_decl_count(); i++) {
      const google::protobuf::OneofDescriptor * fdesc = desc_.oneof_decl(i);
      std::ostringstream indent2;
      indent2 << indent_ << skip_tag;
      out_ << indent_ << skip_tag;
      if (i == desc_.oneof_decl_count() - 1) {
        indent2 << last_skip_tag;
        out_ << last_tag;
      } else {
        indent2 << skip_tag;
        out_ << tag;
      }
      out_ << "Oneof #" << i << " : \n";
      tree_print(*fdesc, out_, "", indent2.str());
    }

    out_ << indent_ << tag << "Nested type : " << desc_.nested_type_count() << "\n";
    for (int i = 0; i < desc_.nested_type_count(); i++) {
      const google::protobuf::Descriptor * ndesc = desc_.nested_type(i);
      std::ostringstream indent2;
      indent2 << indent_;
      out_ << indent_ << skip_tag;
      if (i == desc_.nested_type_count() - 1) {
        indent2 << last_tag;
        out_ << last_tag;
      } else {
        indent2 << tag;
        out_ << tag;
      }
      out_ << "Nested type description : '" << ndesc->full_name() << "'" << std::endl;
      // tree_print(*ndesc, out_, "", indent2.str());
    }

    out_ << indent_ << tag << "Enum type : " << desc_.enum_type_count() << "\n";
    for (int i = 0; i < desc_.enum_type_count(); i++) {
      const google::protobuf::EnumDescriptor * edesc = desc_.enum_type(i);
      std::ostringstream indent2;
      indent2 << indent_;
      out_ << indent_ << skip_tag;
      if (i == desc_.enum_type_count() - 1) {
        indent2 << last_tag;
        out_ << last_tag;
      } else {
        indent2 << tag;
        out_ << tag;
      }
      out_ << "Enum type description #" << i << " : '" << edesc->full_name() << "'" << std::endl;
      // tree_print(*edesc, out_, "", indent2.str());
    }

    out_ << indent_ << tag << "Extension range : " << desc_.extension_range_count() << "\n";

    out_ << indent_ << tag << "Reserved range : " << desc_.reserved_range_count() << "\n";
    for (int i = 0; i < desc_.reserved_range_count(); i++) {
      const google::protobuf::Descriptor::ReservedRange *rr = desc_.reserved_range(i);
      std::ostringstream indent2;
      indent2 << indent_;
      if (i == desc_.field_count() - 1) {
        indent2 << last_tag;
      } else {
        indent2 << tag;
      }
      out_ << "Reserved range : [" << rr->start << ";" << rr->end << "]" << std::endl;
    }

    out_ << indent_ << last_tag << "Reserved name : " << desc_.reserved_name_count() << "\n";
    for (int i = 0; i < desc_.reserved_name_count(); i++) {
      const std::string & rn = desc_.reserved_name(i);
      std::ostringstream indent2;
      indent2 << indent_;
      if (i == desc_.field_count() - 1) {
        indent2 << last_skip_tag;
      } else {
        indent2 << skip_tag;
      }
      out_ << "Reserved name : '" << rn << "'" << std::endl;
    }

    return;
  }

  void tree_print_short(const google::protobuf::Message & msg_,
                        std::ostream & out_,
                        const std::string & title_,
                        const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Type name   : '" << msg_.GetTypeName() << "'\n";
    out_ << indent_ << tag << "Initialized : " << msg_.IsInitialized() << "\n";
    out_ << indent_ << tag << "Byte size   : " << msg_.ByteSize() << "\n";
    out_ << indent_ << tag << "Descriptor  : '" <<  msg_.GetDescriptor()->full_name() << "'\n";
    out_ << indent_ << last_tag << "Debug string : [" << msg_.ShortDebugString() << "]\n";

    return;
  }

  void tree_print(const google::protobuf::Message & msg_,
                  std::ostream & out_,
                  const std::string & title_,
                  const std::string & indent_)
  {
    if (!title_.empty()) {
      out_ << indent_ << title_ << std::endl;
    }

    out_ << indent_ << tag << "Type name   : '" << msg_.GetTypeName() << "'\n";
    out_ << indent_ << tag << "Initialized : " << msg_.IsInitialized() << "\n";
    out_ << indent_ << tag << "Byte size   : " << msg_.ByteSize() << "\n";

    const google::protobuf::Descriptor * desc = msg_.GetDescriptor();
    out_ << indent_ << last_tag << "Descriptor : \n";
    {
      std::ostringstream indent2;
      indent2 << indent_ << last_skip_tag;
      tree_print(*desc, out_, "", indent2.str());
    }

    out_ << indent_ << last_tag << "Debug string : [" << msg_.ShortDebugString() << "]\n";

    return;
  }

  bool cpp_type_match_base_protobuf_type(const std::string cpp_type_id_)
  {
    if (cpp_type_id_ == "bool") return true;
    if (cpp_type_id_ == "int8") return true;
    if (cpp_type_id_ == "uint8") return true;
    if (cpp_type_id_ == "int16") return true;
    if (cpp_type_id_ == "uint16") return true;
    if (cpp_type_id_ == "int32") return true;
    if (cpp_type_id_ == "uint32") return true;
    if (cpp_type_id_ == "int64") return true;
    if (cpp_type_id_ == "uint64") return true;
    if (cpp_type_id_ == "float") return true;
    if (cpp_type_id_ == "double") return true;
    if (cpp_type_id_ == "string") return true;
    return false;
  }

  std::string cpp_integral_type_as_protobuf_type(const std::string cpp_type_id_)
  {
    std::string tmp;
    if (cpp_type_id_ == "int8" ||
        cpp_type_id_ == "int16" ||
        cpp_type_id_ == "int32") {
      tmp = "sint32";
    } else if (cpp_type_id_ == "uint8" ||
               cpp_type_id_ == "uint16" ||
               cpp_type_id_ == "uint32") {
      tmp ="uint32";
    } else if (cpp_type_id_ == "int64") {
      tmp ="sint64";
    } else if (cpp_type_id_ == "uint64") {
      tmp ="uint64";
    }
    return tmp;
  }

  std::string cpp_type_as_protobuf_type(const std::string cpp_type_id_)
  {
    std::string tmp = cpp_integral_type_as_protobuf_type(cpp_type_id_);
    if (tmp.empty()) {
      tmp = cpp_type_id_;
    }
    return tmp;
  }

  bool has_field(const google::protobuf::Descriptor & desc_,
                 const std::string & name_)
  {
    if (desc_.field_count() == 0) return false;
    if (desc_.FindFieldByName(name_) == nullptr) return false;
    return true;
  }

  // bool has_oneof_desc(const google::protobuf::Descriptor & desc_,
  //                     const std::string & name_)
  // {
  //   if (desc_.oneof_desc_count() == 0) return false;
  //   if (desc_.FindOneofByName(name_) == nullptr) return false;
  //   return true;
  // }

  // bool has_enum_type(const google::protobuf::Descriptor & desc_,
  //                 const std::string & name_)
  // {
  //   if (desc_.enum_type_count() == 0) return false;
  //   if (desc_.FindEnumTypeByName(name_) == nullptr) return false;
  //   return true;
  // }

} // end of namespace protobuftools
