// -*- mode: c++; -*-

#ifndef BXPROTOBUFTOOLS_BOOST_DATETIME_CONVERTERS_H
#define BXPROTOBUFTOOLS_BOOST_DATETIME_CONVERTERS_H

// Standard library:
#include <ctime>

// Third party:
// - Boost/date_time:
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/conversion.hpp>
// - Protobuf:
#include <google/protobuf/timestamp.pb.h>

// This project:
#include <protobuftools/core.h>
#include <protobuftools/node.h>
#include <protobuftools/exception.h>
#include <protobuftools/TimePeriod.pb.h>

namespace protobuftools {

  template<>
  class converter<boost::posix_time::ptime>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, boost::posix_time::ptime & t_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(node_.get_message().GetDescriptor()->full_name() != "google.protobuf.Timestamp",
                                   message_exception,
                                   node_.get_message(), "Not a 'google.protobuf.Timestamp' descriptor!");
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "'");
      std::string t_iso_repr = boost::posix_time::to_iso_string(t_);
      google::protobuf::Timestamp & ts = dynamic_cast<google::protobuf::Timestamp&>(node_.grab_message());
      ts.clear_seconds();
      ts.clear_nanos();
      if (!t_.is_special()) {
        std::time_t the_time = boost::posix_time::to_time_t(t_);
        static boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
        boost::posix_time::time_duration elapsed(t_ - epoch);
        long tick_per_sec = elapsed.ticks_per_second();
        //BX_LOG_DEBUG(node_.get_logging(), "=========== ticks/s    = " << tick_per_sec);
        static long nanos_per_sec = 1000000000;
        long nb_seconds = elapsed.total_seconds();
        long nb_nanos   = elapsed.total_nanoseconds() - nb_seconds * nanos_per_sec;
        //BX_LOG_DEBUG(node_.get_logging(), "=========== ISO        = " << t_iso_repr);
        //BX_LOG_DEBUG(node_.get_logging(), "=========== nb_seconds = " << nb_seconds);
        //BX_LOG_DEBUG(node_.get_logging(), "=========== nb_nanos   = " << nb_nanos);
        ::google::protobuf::int64 seconds = nb_seconds;
        ::google::protobuf::int32 nanos = nb_nanos;
        ts.set_seconds(seconds);
        ts.set_nanos(nanos);
      } else if (t_.is_neg_infinity()) {
        ts.set_seconds(std::numeric_limits<::google::protobuf::int64>::min());
        ts.set_nanos(-1);
      } else if (t_.is_pos_infinity()) {
        ts.set_seconds(std::numeric_limits<::google::protobuf::int64>::max());
        ts.set_nanos(-1);
      } else if (t_.is_not_a_date_time()) {
        ts.set_seconds(0);
        ts.set_nanos(-2);
      }
      return;
    }

    static void deprotobufize(::protobuftools::message_node & node_, boost::posix_time::ptime & t_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(node_.get_message().GetDescriptor()->full_name() != "google.protobuf.Timestamp",
                                   message_exception,
                                   node_.get_message(), "Not a 'google.protobuf.Timestamp' descriptor!");
      BX_LOG_DEBUG(node_.get_logging(),
                   "Message node of type '"
                   << node_.get_message().GetDescriptor()->full_name()
                   << "'");
      const google::protobuf::Timestamp & ts =
        dynamic_cast<const google::protobuf::Timestamp&>(node_.get_message());
      ::google::protobuf::int64 nb_seconds = ts.seconds();
      ::google::protobuf::int32 nb_nanos = ts.nanos();
      // Default:
      t_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
      if (nb_seconds == 0 && nb_nanos == -2) {
        t_ = boost::posix_time::ptime(boost::posix_time::not_a_date_time);
      } else if (nb_seconds == std::numeric_limits<::google::protobuf::int64>::min() &&
                 nb_nanos == -1) {
        t_ = boost::posix_time::ptime(boost::posix_time::neg_infin);
      } else if (nb_seconds == std::numeric_limits<::google::protobuf::int64>::max() &&
                 nb_nanos == -1) {
        t_ = boost::posix_time::ptime(boost::posix_time::pos_infin);
      } else {
        static boost::gregorian::date epoch(1970, 1, 1);
        boost::posix_time::time_duration elapsed(boost::posix_time::seconds(nb_seconds)  +
                                                 boost::posix_time::microseconds(nb_nanos / 1000));
        t_ = boost::posix_time::ptime(epoch , elapsed);
      }
      return;
    }

  };

  template<>
  class converter<boost::posix_time::time_period>
  {
  public:

    static void protobufize(::protobuftools::message_node & node_, boost::posix_time::time_period & p_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(node_.get_message().GetDescriptor()->full_name() != "protobuftools.TimePeriod",
                                   message_exception,
                                   node_.get_message(), "Not a 'protobuftools.TimePeriod' descriptor!");
      protobuftools::TimePeriod & tp =
        dynamic_cast<protobuftools::TimePeriod&>(node_.grab_message());
      tp.clear_begin();
      tp.clear_end();
      boost::posix_time::ptime tp_begin = p_.begin();
      boost::posix_time::ptime tp_end = p_.end();
      node_["begin"] % tp_begin;
      node_["end"]   % tp_end;
      return;
    }

    static void deprotobufize(::protobuftools::message_node & node_, boost::posix_time::time_period & p_)
    {
      BX_PROTOBUF_MESSAGE_THROW_IF(node_.get_message().GetDescriptor()->full_name() != "protobuftools.TimePeriod",
                                   message_exception,
                                   node_.get_message(), "Not a 'protobuftools.TimePeriod' descriptor!");
      const protobuftools::TimePeriod & tp =
        dynamic_cast<const protobuftools::TimePeriod&>(node_.get_message());
      boost::posix_time::ptime tp_begin;
      boost::posix_time::ptime tp_end;
      node_["begin"] % tp_begin;
      node_["end"]   % tp_end;
      p_ = boost::posix_time::time_period(tp_begin, tp_end);
      return;
    }

  };

}

#endif // BXPROTOBUFTOOLS_BOOST_DATETIME_CONVERTERS_H
