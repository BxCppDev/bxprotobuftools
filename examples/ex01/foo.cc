// Ourselves:
#include "foo.h"

// Bayeux/protobuftools:
#include <bayeux/protobuftools/protobuf_factory.h>
#include <bayeux/protobuftools/base_type_converters.h>
#include <bayeux/protobuftools/boost_optional_converter.h>
#include <bayeux/protobuftools/protobufable_converter.h>

foo::foo(const int16_t ival_)
  : _ival_(ival_)
{
}

foo::foo(const int16_t ival_, const double dval_)
  : _ival_(ival_)
  , _dopt_(dval_)
{
}

foo::foo(const int16_t ival_, const double dval_, const bar & bval_)
  : _ival_(ival_)
  , _dopt_(dval_)
  , _bopt_(bval_)
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
  out_ << '}';
  return out_;
}
