// Ourselves:
#include "bar.h"

// Bayeux/protobuftools:
#include <bayeux/protobuftools/protobuf_factory.h>
#include <bayeux/protobuftools/base_type_converters.h>
#include <bayeux/protobuftools/std_type_converters.h>
#include <bayeux/protobuftools/protobufable_converter.h>

bar::bar(const bool bval_)
  : _bval_(bval_)
{
}

bar::bar(const bool bval_, const std::string & sval_)
  : _bval_(bval_)
  , _sval_(sval_)
{
}

bar::~bar()
{
}

void bar::protobufize(protobuftools::message_node & node_,
                      const unsigned long int /* version_ */)
{
  node_["bval"] % _bval_;
  node_["sval"] % _sval_;
}

std::ostream & operator<<(std::ostream & out_, const bar & b_)
{
  out_ << "bar{bval=" << b_._bval_;
  out_ << ";sval='" << b_._sval_ << '\'';
  out_ << '}';
  return out_;
}
