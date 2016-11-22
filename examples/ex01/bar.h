#ifndef BAR_H
#define BAR_H

// Standard library:
#include <iostream>

// Bayeux/protobuftools:
#include <bayeux/protobuftools/i_protobufable.h> // Main interface

class bar
  : public protobuftools::i_protobufable
{
public:
  bar(const bool bval_ = false);
  bar(const bool bval_, const std::string & sval_);
  virtual ~bar();
  virtual void protobufize(protobuftools::message_node & node_,
                           const unsigned long int version_);
  friend std::ostream & operator<<(std::ostream & out_, const bar & b_);
private:
  bool        _bval_;
  std::string _sval_;
};

// Bind the C++ class to a specific protobuf message class
#include <bayeux/protobuftools/protobuf_utils.h>
BXPROTOBUFTOOLS_CLASS_BIND_TO_REGISTERED_PROTOBUF(bar, "ex01/bar")

#endif // BAR_H
