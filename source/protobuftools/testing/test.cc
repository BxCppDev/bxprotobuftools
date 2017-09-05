// Ourselves:
#include <protobuftools/testing/test.h>

// Standard library:
#include <iostream>

// This project:
#include <protobuftools/config.h>
#include <protobuftools/core.h>
#include <protobuftools/node.h>
#include <protobuftools/base_type_converters.h>
#include <protobuftools/std_type_converters.h>
#include <protobuftools/serdes.h>
#include <protobuftools/io.h>
#include <protobuftools/iofile.h>

#define BXPROTOBUFTOOLS_WITH_BOOST 1

#if BXPROTOBUFTOOLS_WITH_BOOST == 1
// Boost:
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <protobuftools/boost_type_converters.h>
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

namespace bar {

  /// A foreign class with no embedded Protobuf-serialization method
  class Foreign
  {
  public:
    Foreign() : _x_(0.0), _y_(0.0) {}
    Foreign(double x_, double y_) : _x_(x_), _y_(y_) {}
    double get_x() const { return _x_; }
    double get_y() const { return _y_; }
    double & grab_x() { return _x_; }
    double & grab_y() { return _y_; }
    void zero() {
      _x_ = 0.0;
      _y_ = 0.0;
      return;
    }
    friend std::ostream & operator<<(std::ostream & out_, const Foreign & f_)
    {
      out_ << "{x=" << f_._x_<< ";y=" << f_._y_ << "}";
      return out_;
    }
  private:
    double _x_;
    double _y_;
  };

} // namespace bar

namespace protobuftools {

  /// A Protobuf converter dedicated to the foreign class
  template<>
  class converter<bar::Foreign>
  {
  public:

    static void protobufize(message_node & node_, bar::Foreign & f_)
    {
      node_.grab_value() = Json::objectValue;
      {
        google::protobuf::Message & xValue = node_.grab_value()["x"];
        node_value newNode(xValue, node_.is_serializing(), false);
        newNode % f_.grab_x();
      }
      {
        google::protobuf::Message & yValue = node_.grab_value()["y"];
        node_value newNode(yValue, node_.is_serializing(), false);
        newNode % f_.grab_y();
      }
      return;
    }

    static void deprotobufize(message_node & node_, bar::Foreign & f_)
    {
      if (not node_.get_value().isObject()) {
        throw wrong_type(node_.get_value(), "expected object!");
      }
      {
        google::protobuf::Message & xValue = node_.grab_value()["x"];
        node_value newNode(xValue, node_.is_serializing(), false);
        newNode % f_.grab_x();
      }
      {
        google::protobuf::Message & yValue = node_.grab_value()["y"];
        node_value newNode(yValue, node_.is_serializing(), false);
        newNode % f_.grab_y();
      }
      return;
    }

  };

} // namespace protobuftools

namespace protobuftools {

  namespace testing {

    class A
    {
    public:

      A()
      {
        _name_ = "foo";
        _x_ = 1234567;
        _values_ = {1.2, 3.4, 4.5};
        // _dict_["a"] = 4;
        // _dict_["b"] = 3;
        // _dict_["c"] = 2;
        // _dict_["d"] = 1;
        return;
      }

      void reset()
      {
        _name_.clear();
        _x_ = 0;
        _values_.clear();
        // _dict_.clear();
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
        _maybe_ = boost::none;
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
        return;
      }

#if BXPROTOBUFTOOLS_WITH_BOOST == 1
      void set_maybe(int mb_)
      {
        _maybe_ = mb_;
        return;
      }
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

      void print(std::ostream & out_) const
      {
        out_ << "Class A : " << std::endl;
        out_ << "|-- name : '" << _name_ << "'" << std::endl;
        out_ << "|-- x : '" << _x_ << "'" << std::endl;
        out_ << "|-- values : [" << _values_.size() << "]" << std::endl;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
        out_ << "|-- maybe : ";
        if (_maybe_) {
          out_ << _maybe_.get();
        } else {
          out_ << "<none>";
        }
        out_ << std::endl;
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
        // out_ << "`-- dict : [" << _dict_.size() << "]" << std::endl;
        out_ << "`-- End" << std::endl;
        return;
      }

      void protobufize(protobuftools::message_node & node_,
                       unsigned long int version_ = 0)
      {
        node_["name"]   % _name_;
        node_["x"]      % _x_;
        node_["values"] % _values_;
        // node_["dict"]   % _dict_;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
        node_["maybe"]  % _maybe_;
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
        return;
      }

    private:

      std::string _name_;
      uint32_t _x_;
      std::vector<double> _values_;
      // std::map<std::string, int> _dict_;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
      boost::optional<int32_t> _maybe_;
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

    };

    class B
    {
    public:

      B()
      {
        return;
      }

      void add(const A & a_)
      {
        _many_.push_back(a_);
        return;
      }

      void protobufize(protobuftools::node & node_, unsigned long int version_ = 0)
      {
        node_["many"] % _many_;
        return;
      }

      void print(std::ostream & out_) const
      {
        out_ << "Class B : " << std::endl;
        out_ << "`-- many : [" << _many_.size() << "]" << std::endl;
        for (auto a : _many_) {
          out_ << "   item : ";
          a.print(out_);
        }
        return;
      }

    private:

      std::vector<A> _many_;

    };

    // static
    void test::run_test_0()
    {
      std::clog << "\ntest::run_test_0: \n" ;
      A a1;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
      a1.set_maybe(666);
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
      std::clog << "a1 = \n";
      a1.print(std::clog);
      protobuftools::store("test-protobuftools-file_0.json", a1);

      std::ostringstream buffer_out;
      protobuftools::store(buffer_out,a1);
      std::string buffer = buffer_out.str();
      std::clog << "JSON buffer: [" << buffer << "]" << std::endl;
      std::istringstream buffer_in(buffer);
      A a1_bis;
      protobuftools::load(buffer_in,a1_bis);
      std::clog << "Deserialized a1 = \n";
      a1_bis.print(std::clog);
      std::clog << "\n";

      A a2;
      a2.reset();
      std::clog << "a2 = \n";
      a2.print(std::clog);
      protobuftools::load("test-protobuftools-file_0.json", a2);
      std::clog << "a2 = \n";
      a2.print(std::clog);

      return;
    }

    // static
    void test::run_test_1()
    {
      std::clog << "\ntest::run_test_1: \n" ;
      B b1;
      for (int i = 0; i < 4; i++) {
        A a1;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
        if (i % 2) {
          a1.set_maybe(333 - i);
        }
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
        b1.add(a1);
      }
      std::clog << "b1 = \n";
      b1.print(std::clog);
      protobuftools::store("test-protobuftools-file_1.json", b1);

      B b2;
      protobuftools::load("test-protobuftools-file_1.json", b2);
      std::clog << "b2 = \n";
      b2.print(std::clog);

      return;
    }

    // static
    void test::run_test_2()
    {
      std::clog << "\ntest::run_test_2: \n" ;
      std::map<std::string, B> bees;

      B b1;
      for (int i = 0; i < 4; i++) {
        A a1;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
        if (i % 2) {
          a1.set_maybe(666 - i);
        }
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
        b1.add(a1);
      }
      bees["riri"] = b1;
      bees["fifi"] = b1;
      bees["loulou"] = b1;
      protobuftools::store("test-protobuftools-file_2.json", bees);

      bees.clear();
      protobuftools::load("test-protobuftools-file_2.json", bees);

      return;
    }

    // static
    void test::run_test_3()
    {
      std::clog << "\ntest::run_test_3: \n" ;
      std::map<std::string, bar::Foreign> fees;
      fees["f0"] = bar::Foreign(+1.0, -2.0);
      fees["f1"] = bar::Foreign(-3.0, +0.5);
      fees["f2"] = bar::Foreign(+2.0, -1.0);
      std::clog << "fees = \n";
      for (auto f : fees) {
        std::clog << f.first << " : " << f.second << std::endl;
      }
      protobuftools::store("test-protobuftools-file_3.json", fees);

      fees.clear();
      protobuftools::load("test-protobuftools-file_3.json", fees);
      std::clog << "fees = \n";
      for (auto f : fees) {
        std::clog << f.first << " : " << f.second << std::endl;
      }

      return;
    }

    // static
    void test::run_test_4()
    {
      std::clog << "\ntest::run_test_4: \n" ;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
      std::map<std::string, boost::posix_time::ptime> times;
      for (int i = 0; i < (int) 7; i++) {
        boost::posix_time::ptime t(boost::posix_time::microsec_clock::local_time());
        if (i == 3) {
          t = boost::posix_time::ptime(boost::posix_time::neg_infin);
        } else if (i == 4) {
          t = boost::posix_time::ptime(boost::posix_time::pos_infin);
        } else if (i == 5) {
          t = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
        }
        times["t" + boost::lexical_cast<std::string>(i)] = t;
      }
      std::clog << "times = \n";
      for (auto t : times) {
        std::clog << t.first << " : " << boost::posix_time::to_simple_string(t.second) << std::endl;
      }
      protobuftools::store("test-protobuftools-file_4.json", times);

      times.clear();
      protobuftools::load("test-protobuftools-file_4.json", times);
      std::clog << "times = \n";
      for (auto t : times) {
        std::clog << t.first << " : " << boost::posix_time::to_simple_string(t.second) << std::endl;
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() +
                                          boost::posix_time::seconds(10));
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
        protobuftools::store("test-protobuftools-file_4bis.json", tp);
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() -
                                          boost::posix_time::seconds(1));
        protobuftools::load("test-protobuftools-file_4bis.json", tp);
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() -
                                          boost::posix_time::seconds(1));
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
        protobuftools::store("test-protobuftools-file_4ter.json", tp);
      }

      {
        boost::posix_time::time_period tp(boost::posix_time::microsec_clock::local_time(),
                                          boost::posix_time::microsec_clock::local_time() +
                                          boost::posix_time::seconds(1));
        protobuftools::load("test-protobuftools-file_4ter.json", tp);
        std::clog << "tp : " << boost::posix_time::to_simple_string(tp) << std::endl;
      }

#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

      return;
    }

  } // end of namespace testing

} // end of namespace protobuftools
