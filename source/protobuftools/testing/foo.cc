#include "foo.h"

// Third party:
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
// - Boost/date_time:
#include <boost/date_time/posix_time/time_formatters.hpp>
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

// This project:
#include <protobuftools/base_type_converters.h>
#include <protobuftools/enum_converter.h>
#include <protobuftools/std_type_converters.h>
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
#include <protobuftools/boost_datetime_converters.h>
#include <protobuftools/boost_optional_converter.h>
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

namespace protobuftools {

  namespace testing {

    void zoo::print(std::ostream & out_,
                    const std::string & title_,
                    const std::string & indent_) const
    {
      if (!title_.empty()) {
        out_ << indent_ << title_ << ' ' << std::endl;
      }
      out_ << indent_ << "|-- open   = " << open << std::endl;
      out_ << indent_ << "|-- number = " << number << std::endl;
      out_ << indent_ << "`-- price  = " << price << std::endl;
      return;
    }

    std::ostream & operator<<(std::ostream & out_, const zoo & z_)
    {
      out_ << "zoo{open=" << z_.open << ";number=" << z_.number << ";price="
           << z_.price << '}';
      return out_;
    }

    void zoo::protobufize(protobuftools::message_node & node_,
                          const unsigned long int version_)
    {
      node_["open"] % open;
      node_["number"] % number;
      node_["price"] % price;
      return;
    }

    bool zoo::operator<(const zoo & z_) const
    {
      if (open < z_.open) return true;
      if (open > z_.open) return false;
      if (number < z_.number) return true;
      if (number > z_.number) return false;
      if (price < z_.price) return true;
      return false;
    }

    bool zoo::operator==(const zoo & z_) const
    {
      if (open != z_.open) return true;
      if (number != z_.number) return true;
      if (price != z_.price) return false;
      return true;
    }

    void foo::bar::print(std::ostream & out_,
                         const std::string & title_,
                         const std::string & indent_) const
    {
      if (!title_.empty()) {
        out_ << indent_ << title_ << ' ' << std::endl;
      }
      out_ << indent_ << "|-- name  = '" << name << "'" << std::endl;
      out_ << indent_ << "|-- value = " << value << std::endl;
      out_ << indent_ << "`-- z :" << std::endl;
      z.print(out_, "", indent_ + "    ");
       return;
    }

    void foo::bar::protobufize(protobuftools::message_node & node_,
                               const unsigned long int version_)
    {
      node_["name"] % name;
      node_["value"] % value;
      node_["z"] % z;
      return;
    }

    void foo::print(std::ostream & out_,
                    const std::string & title_,
                    const std::string & indent_) const
    {
      if (!title_.empty()) {
        out_ << indent_ << title_ << ' ' << std::endl;
      }
      out_ << indent_ << "|-- flag   = " << flag << std::endl;
      out_ << indent_ << "|-- u16    = " << u16 << std::endl;
      out_ << indent_ << "|-- i32    = " << i32 << std::endl;
      out_ << indent_ << "|-- f      = " << f << std::endl;
      out_ << indent_ << "|-- d      = " << d << std::endl;
      out_ << indent_ << "|-- status = " << status << std::endl;
      out_ << indent_ << "|-- code   = " << code << std::endl;
      out_ << indent_ << "|-- word   = '" << word << "'" << std::endl;
      out_ << indent_ << "|-- vi32[#" << vi32.size() << "]" << std::endl;
      for (std::size_t i = 0; i < vi32.size(); i++) {
        out_ << indent_ << "|   "
             << (i + 1 == vi32.size() ? "`-- " : "|-- ")
             << "vi32[" << i << "] = " << vi32[i]
             << std::endl;
      }
      out_ << indent_ << "|-- lf[#" << lf.size() << "]" << std::endl;
      {
        std::size_t count = 0;
        for (const auto & item : lf) {
          out_ << indent_ << "|   "
               << (count + 1 == lf.size() ? "`-- " : "|-- ")
               << "lf[" << count << "] = " << item
               << std::endl;
          count++;
        }
      }

      out_ << indent_ << "|-- si16[#" << si16.size() << "]" << std::endl;
      {
        std::size_t count = 0;
        for (const auto & item : si16) {
          out_ << indent_ << "|   "
               << (count + 1 == si16.size() ? "`-- " : "|-- ")
               << "si16[" << count << "] = " << item
               << std::endl;
          count++;
        }
      }

      out_ << indent_ << "|-- ad[#" << ad.size() << "]" << std::endl;
      {
        std::size_t count = 0;
        for (const auto & item : ad) {
          out_ << indent_ << "|   "
               << (count + 1 == ad.size() ? "`-- " : "|-- ")
               << "ad[" << count << "] = " << item
               << std::endl;
          count++;
        }
      }

      out_ << indent_ << "|-- dummy :" << std::endl;
      dummy.print(out_, "", indent_ + "|   ");

      out_ << indent_ << "|-- vz[#" << vz.size() << "]" << std::endl;
      for (std::size_t i = 0; i < vz.size(); i++) {
        std::string tag = (i + 1 == vz.size() ? "    " : "|   ");
        out_ << indent_ << "|   "
             << (i + 1 == vz.size() ? "`-- " : "|-- ")
             << "vz[" << i << "] : " << std::endl;
        vz[i].print(out_, "", indent_ + "|   " + tag);
      }

      out_ << indent_ << "|-- lz[#" << lz.size() << "]" << std::endl;
      {
        std::size_t count = 0;
        for (const auto & item : lz) {
          std::string tag = (count + 1 == lz.size() ? "    " : "|   ");
          out_ << indent_ << "|   "
               << (count + 1 == lz.size() ? "`-- " : "|-- ")
               << "lz[" << count << "] : " << std::endl;
          item.print(out_, "", indent_ + "|   " + tag);
          count++;
        }
      }

      out_ << indent_ << "|-- sz[#" << sz.size() << "]" << std::endl;
      {
        std::size_t count = 0;
        for (const auto & item : sz) {
          std::string tag = (count + 1 == sz.size() ? "    " : "|   ");
          out_ << indent_ << "|   "
               << (count + 1 == sz.size() ? "`-- " : "|-- ")
               << "sz[" << count << "] : " << std::endl;
          item.print(out_, "", indent_ + "|   " + tag);
          count++;
        }
      }

      out_ << indent_ << "|-- az[#" << sz.size() << "]" << std::endl;
      {
        std::size_t count = 0;
        for (const auto & item : az) {
          std::string tag = (count + 1 == az.size() ? "    " : "|   ");
          out_ << indent_ << "|   "
               << (count + 1 == az.size() ? "`-- " : "|-- ")
               << "az[" << count << "] : " << std::endl;
          item.print(out_, "", indent_ + "|   " + tag);
          count++;
        }
      }

#if BXPROTOBUFTOOLS_WITH_BOOST == 1
      out_ << indent_ << "|-- time   = [" << boost::posix_time::to_iso_string(time) << ']' << std::endl;

      out_ << indent_ << "|-- ou16   = ";
      if (ou16) {
        out_ << "[" << ou16.get() << ']';
      } else {
        out_ << "<none>";
      }
      out_ << std::endl;

      out_ << indent_ << "|-- oz     = ";
      if (oz) {
        out_ << "[" << oz.get() << ']';
      } else {
        out_ << "<none>";
      }
      out_ << std::endl;

      out_ << std::endl;


#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1

      out_ << indent_ << "`-- The end." << std::endl;

      return;
    }

    void foo::protobufize(protobuftools::message_node & node_,
                          const unsigned long int version_)
    {
      if (node_.is_debug()) {
        node_.print(std::cerr, "foo::protobufize: message node: ", "[debug] " );
      }
      node_["flag"]   % flag;
      node_["u16"]    % u16;
      node_["i32"]    % i32;
      node_["f"]      % f;
      node_["d"]      % d;
      node_["status"] % status;
      node_["code"]   % code;
      node_["word"]   % word;
      node_["vi32"]   % vi32;
      node_["lf"]     % lf;
      node_["si16"]   % si16;
      node_["ad"]     % ad;
      node_["dummy"]  % dummy;
      node_["vz"]     % vz;
      node_["lz"]     % lz;
      node_["sz"]     % sz;
      node_["az"]     % az;
#if BXPROTOBUFTOOLS_WITH_BOOST == 1
      node_["time"]   % time;
      node_["ou16"]   % ou16;
      node_["oz"]     % oz;
#endif // BXPROTOBUFTOOLS_WITH_BOOST == 1
      return;
    }

  } // namespace testing

} // namespace protobuftools
