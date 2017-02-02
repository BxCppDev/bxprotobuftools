#ifndef FOO_H
#define FOO_H

// Standard library:
#include <iostream>

// Boost:
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// Bayeux/protobuftools:
#include <bayeux/protobuftools/i_protobufable.h> // Main interface

// This project:
#include "bar.h"

class foo
  : public protobuftools::i_protobufable
{
public:
  foo(const int16_t ival_ = 0);
  foo(const int16_t ival_, const double dval_);
  foo(const int16_t ival_, const double dval_, const bar & bval_);
  foo(const int16_t ival_,
      const double dval_,
      const bar & bval_,
      const boost::posix_time::ptime & t_);
  virtual ~foo();
  virtual void protobufize(protobuftools::message_node & node_,
                           const unsigned long int version_);
  friend std::ostream & operator<<(std::ostream & out_, const foo & f_);
private:
  int16_t                 _ival_;
  boost::optional<double> _dopt_;
  boost::optional<bar>    _bopt_;
  boost::posix_time::ptime _timestamp_;
};

// Bind the C++ class to a specific protobuf message class
#include <bayeux/protobuftools/protobuf_utils.h>
BXPROTOBUFTOOLS_CLASS_BIND_TO_REGISTERED_PROTOBUF(foo, "ex01/foo")

#endif // FOO_H
