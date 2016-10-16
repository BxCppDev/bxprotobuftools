// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_TESTING_FOO_H
#define BXPROTOBUFTOOLS_TESTING_FOO_H

// Standard library:
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <array>

// Third party:
// - Boost/date_time:
#include <boost/date_time/posix_time/posix_time_types.hpp>

// This project
#include <protobuftools/i_protobufable.h>

namespace protobuftools {

  namespace testing {

    /// \brief A simple enumeration
    enum code_type {
      CODE_ZERO  = 0,
      CODE_ONE   = 1,
      CODE_TWO   = 2,
      CODE_THREE = 3,
      CODE_FOUR  = 4,
      CODE_MANY  = 100
    };

    /// \brief A zoo class
    struct zoo : public protobuftools::i_protobufable
    {

      void print(std::ostream & out_ = std::clog,
                 const std::string & title_ = "",
                 const std::string & indent_ = "") const;

      virtual void protobufize(protobuftools::message_node & node_,
                               unsigned long int version_ = 0);

      bool operator==(const zoo &) const;

      bool operator<(const zoo &) const;

      bool    open   = false;
      int32_t number = 7;
      float   price  = 5.50;

    };

    /// \brief A foo class
    struct foo : public protobuftools::i_protobufable
    {
      enum status_type {
        ERR_OK      = 0,
        ERR_GENERIC = 1,
        ERR_MORE    = 2
      };

      struct bar : public protobuftools::i_protobufable
      {

        void print(std::ostream & out_ = std::clog,
                   const std::string & title_ = "",
                   const std::string & indent_ = "") const;

        virtual void protobufize(protobuftools::message_node & node_,
                                 unsigned long int version_ = 0);

        std::string name = "World!";
        int32_t     value = 12;
        zoo         z;

      };

      void print(std::ostream & out_ = std::clog,
                 const std::string & title_ = "",
                 const std::string & indent_ = "") const;

      virtual void protobufize(protobuftools::message_node & node_,
                               unsigned long int version_ = 0);

      bool        flag = true;
      uint16_t    u16 = 12;
      int32_t     i32 = -42;
      float       f = 2.718F;
      double      d = 3.14519;
      status_type status = ERR_OK;
      code_type   code = CODE_ZERO;
      std::string word = "hello";
      std::vector<int32_t> vi32 = { 12, 42, 666};
      std::list<float>     lf = { 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F};
      std::set<int16_t>    si16 = { 2, 4, 6, 8};
      std::array<double,4> ad = {{ 10, 20, 30, 40}};
      bar                  dummy;
      std::vector<zoo>     vz;
      std::list<zoo>       lz;
      std::set<zoo>        sz;
      std::array<zoo,3>    az;
      boost::posix_time::ptime time;

    };

  } // namespace testing

} // namespace protobuftools

#endif // BXPROTOBUFTOOLS_TESTING_FOO_H
