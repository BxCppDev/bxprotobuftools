// Ourselves:
#include "foo.h"

// Bayeux/protobuftools:
#include <bayeux/protobuftools/protobuf_factory.h>
#include <bayeux/protobuftools/base_type_converters.h>
#include <bayeux/protobuftools/boost_converters.h>

foo::foo(const int16_t ival_)
  : _ival_(ival_)
{
  _timestamp_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

foo::foo(const int16_t ival_, const double dval_)
  : _ival_(ival_)
  , _dopt_(dval_)
{
  _timestamp_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

foo::foo(const int16_t ival_, const double dval_, const bar & bval_)
  : _ival_(ival_)
  , _dopt_(dval_)
  , _bopt_(bval_)
{
  _timestamp_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

foo::foo(const int16_t ival_, const double dval_, const bar & bval_,
         const boost::posix_time::ptime & t_)
  : _ival_(ival_)
  , _dopt_(dval_)
  , _bopt_(bval_)
  , _timestamp_(t_)
{
}

foo::~foo()
{
}

void foo::protobufize(protobuftools::message_node & node_,
                      const unsigned long int /* version_ */)
{
  node_["ival"] % _ival_;
  node_["dopt"] % _dopt_;
  node_["bopt"] % _bopt_;
  node_["timestamp"] % _timestamp_;
}

std::ostream & operator<<(std::ostream & out_, const foo & f_)
{
  out_ << "foo{ival=" << f_._ival_;
  if (f_._dopt_) {
    out_ << ";dval=" << f_._dopt_.get();
  }
  if (f_._bopt_) {
    out_ << ";bval=" << f_._bopt_.get();
  }
  out_ << ";timestamp='" << boost::posix_time::to_iso_string(f_._timestamp_)
       << "'";
  out_ << '}';
  return out_;
}
