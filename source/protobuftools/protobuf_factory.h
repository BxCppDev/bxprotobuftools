// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_PROTOBUF_FACTORY_H
#define BXPROTOBUFTOOLS_PROTOBUF_FACTORY_H

// Standard library:
#include <string>
#include <iostream>
#include <memory>
#include <map>

// Third party:
// - Boost:
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
// - Protocol Buffers:
#include <google/protobuf/message.h>

namespace protobuftools {

  //! \brief Factory of protobuf message instances
  //! From http://www.jsolutions.co.uk/C++/objectfactory.html
  //! Author: John Cumming
  //! http://stackoverflow.com/questions/5120768/how-to-implement-the-factory-method-pattern-in-c-correctly
  class protobuf_factory
  {
  public:
    typedef google::protobuf::Message        message_type;
    typedef boost::function<message_type*()> message_factory_type;

    //! Default constructor
    protobuf_factory();

    //! Destructor
    ~protobuf_factory();

    //! Check if a factory function exists in the registry
    bool has_factory_function(const std::string & name_) const;

    //! Add a factory function to the registry
    void register_factory_function(const std::string & name_,
                                   message_factory_type msg_factory_function_);

    //! Remove a factory function from the registry
    void unregister_factory_function(const std::string & name_);

    //! Creation of instance
    std::shared_ptr<message_type> create_message_instance(const std::string & name_);

    //! Smart print
    void print(std::ostream & out_ = std::clog, const std::string & title_ = "") const;

    //! Return the global factory of 'google::protobuf::Message' classes
    static protobuf_factory & system_factory();

  private:

    std::map<std::string, message_factory_type> _factory_function_registry_; ///< The registry of factory function

  };

  //! \brief Base class for protobuf message factory registrars
  class base_protobuf_factory_registrar
  {

  public:

    //! Constructor
    base_protobuf_factory_registrar(const std::string & classname_);

    //! Destructor
    virtual ~base_protobuf_factory_registrar();

    //! Return the registered class name
    const std::string & get_classname() const;

    // const std::map<std::string, base_protobuf_factory_registrar *> & registrars();

   private:

    std::string _classname_; //!< The registration type unique identifier of the auto-registered class

    // static std::map<std::string, base_protobuf_factory_registrar *> _registrars_;

  };

  template<class T>
  class protobuf_factory_registrar : public base_protobuf_factory_registrar
  {
  public:

    //! Constructor
    protobuf_factory_registrar(const std::string & classname_) : base_protobuf_factory_registrar(classname_)
    {
      // Register the class factory function:
      protobuf_factory::system_factory().register_factory_function(classname_, boost::factory<T*>());
      return;
    }

    //! Destructor
    virtual ~protobuf_factory_registrar()
    {
      // Unregister the class factory function:
      protobuf_factory::system_factory().unregister_factory_function(get_classname());
      return;
    }

  };

  // void print_registrars(std::ostream & out_ = std::clog);

} // end of namespace protobuftools

#define BXPROTOBUFTOOLS_REGISTER_CLASS(Name, Type)                      \
  namespace {                                                           \
    static ::protobuftools::protobuf_factory_registrar<Type> _protobuf_message_registrar(Name); \
  }                                                                     \
  /**/

#define BXPROTOBUFTOOLS_REGISTER_CLASS_LABELED(Name, Type, Id)         \
  namespace {                                                          \
    static ::protobuftools::protobuf_factory_registrar<Type> _ ## Id ## __protobuf_message_registrar(Name); \
  }                                                                    \
/**/

#endif // BXPROTOBUFTOOLS_PROTOBUF_FACTORY_H
