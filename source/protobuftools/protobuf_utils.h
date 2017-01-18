// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_PROTOBUF_UTILS_H
#define BXPROTOBUFTOOLS_PROTOBUF_UTILS_H

// Standard library:
#include <iostream>
#include <sstream>
#include <string>

// Third party:
// - Prootobuf:
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

namespace protobuftools {

  //! Smart print of the description of a protobuf file descriptor object:
  void tree_print(const google::protobuf::FileDescriptor & filedesc_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Smart print of the description of a protobuf enum value descriptor object:
  void tree_print(const google::protobuf::EnumValueDescriptor & fdesc_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Smart print of the description of a protobuf enum descriptor object:
  void tree_print(const google::protobuf::EnumDescriptor & fdesc_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Smart print of the description of a protobuf OneOf descriptor object:
  void tree_print(const google::protobuf::OneofDescriptor & odesc_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Smart print of the description of a protobuf field descriptor object:
  void tree_print(const google::protobuf::FieldDescriptor & fdesc_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Smart print of the description of a protobuf descriptor object:
  void tree_print(const google::protobuf::Descriptor & desc_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Smart print of the description of a protobuf message object:
  void tree_print(const google::protobuf::Message & msg_,
                  std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "");

  //! Short print of the description of a protobuf message object:
  void tree_print_short(const google::protobuf::Message & msg_,
                        std::ostream & out_ = std::clog,
                        const std::string & title_ = "",
                        const std::string & indent_ = "");

  //! Check if a message descriptor has a field with given name
  bool has_field(const google::protobuf::Descriptor & desc_,
                 const std::string & name_);

  // //! Check if a message descriptor has a oneof with given name
  // bool has_oneof(const google::protobuf::Descriptor & desc_,
  //                const std::string & name_);

  // //! Check if a message descriptor has an enum type with given name
  // bool has_enum_type(const google::protobuf::Descriptor & desc_,
  //                    const std::string & name_);

  bool        cpp_type_match_base_protobuf_type(const std::string cpp_type_id_);
  std::string cpp_integral_type_as_protobuf_type(const std::string cpp_type_id_);
  std::string cpp_type_as_protobuf_type(const std::string cpp_type_id_);

  namespace ext {
    template <typename T>
    struct binded_protobuf_guid_impl {
      static inline const char * call() {
        return nullptr;
      }
    };
  }

  /// Default implementation of the GUID fetch function
  template<class T>
  inline const char * binded_protobuf_guid() {
    return ext::binded_protobuf_guid_impl<T>::call();
  }

  template<>
  inline const char * binded_protobuf_guid<bool>(){
    return "bool";
  }

  template<>
  inline const char * binded_protobuf_guid<int8_t>(){
    return "int8";
  }

  template<>
  inline const char * binded_protobuf_guid<uint8_t>(){
    return "uint8";
  }

  template<>
  inline const char * binded_protobuf_guid<int16_t>(){
    return "int16";
  }

  template<>
  inline const char * binded_protobuf_guid<uint16_t>(){
    return "uint16";
  }

  template<>
  inline const char * binded_protobuf_guid<int32_t>(){
    return "int32";
  }

  template<>
  inline const char * binded_protobuf_guid<uint32_t>(){
    return "uint32";
  }

  template<>
  inline const char * binded_protobuf_guid<int64_t>(){
    return "int64";
  }

  template<>
  inline const char * binded_protobuf_guid<uint64_t>(){
    return "uint64";
  }

  template<>
  inline const char * binded_protobuf_guid<float>(){
    return "float";
  }

  template<>
  inline const char * binded_protobuf_guid<double>(){
    return "double";
  }

  template<>
  inline const char * binded_protobuf_guid<std::string>(){
    return "string";
  }

} // end of namespace protobuftools

#define BXPROTOBUFTOOLS_TYPE_BIND_TO_REGISTERED_PROTOBUF(T, K)  \
  namespace protobuftools {                                     \
    template<>                                                  \
    inline const char * binded_protobuf_guid< T >(){            \
      return K;                                                 \
    }                                                           \
  } /* protobuftools */                                         \
  /**/

#define BXPROTOBUFTOOLS_CLASS_BIND_TO_REGISTERED_PROTOBUF(T, K) \
  BXPROTOBUFTOOLS_TYPE_BIND_TO_REGISTERED_PROTOBUF(T,K)         \
  /**/

#define BXPROTOBUFTOOLS_ENUM_BIND_TO_REGISTERED_PROTOBUF(T, K) \
  BXPROTOBUFTOOLS_TYPE_BIND_TO_REGISTERED_PROTOBUF(T,K)        \
  /**/

#endif // BXPROTOBUFTOOLS_PROTOBUF_UTILS_H
