// Ourselves:
#include <protobuftools/protobuf_factory.h>

namespace protobuftools {

  protobuf_factory::protobuf_factory()
  {
    return;
  }

  protobuf_factory::~protobuf_factory()
  {
    return;
  }

  bool protobuf_factory::has_factory_function(const std::string & name_) const
  {
    return _factory_function_registry_.count(name_) == 1;
  }

  void protobuf_factory::register_factory_function(const std::string & name_,
                                                   message_factory_type msg_factory_function_)
  {
    _factory_function_registry_[name_] = msg_factory_function_;
    return;
  }

  void protobuf_factory::unregister_factory_function(const std::string & name_)
  {
    _factory_function_registry_.erase(name_);
    return;
  }

  std::shared_ptr<protobuf_factory::message_type>
  protobuf_factory::create_message_instance(const std::string & name_)
  {
    google::protobuf::Message * instance = nullptr;
    auto it = _factory_function_registry_.find(name_);
    if (it != _factory_function_registry_.end()) {
      instance = it->second();
    }
    if (instance != nullptr) {
      return std::shared_ptr<message_type>(instance);
    }
    return nullptr;
  }

  // static
  protobuf_factory & protobuf_factory::system_factory()
  {
    static protobuf_factory _f;
    return _f;
  }

  void protobuf_factory::print(std::ostream & out_, const std::string & title_) const
  {
    if (!title_.empty()) {
      out_ << title_ << ' ' << std::endl;
    }
    out_ << "|-- Number of registered message factories: "
         << _factory_function_registry_.size() << std::endl;
    std::size_t count = 0;
    for (const auto f : _factory_function_registry_) {
      if (++count != _factory_function_registry_.size()) {
        out_ << "|-- ";
      } else {
        out_ << "`-- ";
      }
      out_ << "Name = '" << f.first << "'" << std::endl;
    }
  }

  base_protobuf_factory_registrar::base_protobuf_factory_registrar(const std::string & classname_)
  {
    _classname_ = classname_;
    // _registrars_[classname_] = this;
    return;
  }

  base_protobuf_factory_registrar::~base_protobuf_factory_registrar()
  {
    // _registrars_.erase(*this);
    return;
  }

  const std::string & base_protobuf_factory_registrar::get_classname() const
  {
    return _classname_;
  }

  // const std::map<std::string, base_protobuf_factory_registrar *> &
  // base_protobuf_factory_registrar::registrars()
  // {
  //   return _registrars_;
  // }

  // void print_registrars(std::ostream & out_)
  // {
  //   for (const auto reg : base_protobuf_factory_registrar::registrars()) {
  //      out_ << reg.first << std::endl;
  //   }
  // }

} // end of namespace protobuftools
