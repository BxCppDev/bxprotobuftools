// logger.cc - Implementation of protobuftools logger
//
// Copyright (c) 2016 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2016 by The University of Warwick
//
// This file is part of protobuftools.
//
// protobuftools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// protobuftools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with protobuftools.  If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <protobuftools/logger.h>

// Standard Library:

// Third Party:
// - Boost:
#include <boost/assign.hpp>
#include <boost/algorithm/string.hpp>
// Clang doesn't like bimap's use of BOOST_PP...
#if defined (__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wredeclared-class-member"
#endif

#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

#if defined (__clang__)
#pragma clang diagnostic pop
#endif

namespace {
  //! Hide awkward boost bimap declaration in a typedef
  struct PriorityLookup {
    typedef boost::bimap<
      boost::bimaps::set_of<std::string>,
      boost::bimaps::multiset_of<protobuftools::logger::priority>
      > LookupTable;
  };

  //! Construct the lookup table.
  PriorityLookup::LookupTable ConstructLookupTable() {
    PriorityLookup::LookupTable a;
    boost::assign::insert(a)
      ("PRIO_FATAL", protobuftools::logger::PRIO_FATAL)
      ("FATAL", protobuftools::logger::PRIO_FATAL)
      ("fatal", protobuftools::logger::PRIO_FATAL)
      ("PRIO_CRITICAL", protobuftools::logger::PRIO_CRITICAL)
      ("CRITICAL", protobuftools::logger::PRIO_CRITICAL)
      ("critical", protobuftools::logger::PRIO_CRITICAL)
      ("PRIO_ERROR", protobuftools::logger::PRIO_ERROR)
      ("ERROR", protobuftools::logger::PRIO_ERROR)
      ("error", protobuftools::logger::PRIO_ERROR)
      ("PRIO_WARNING", protobuftools::logger::PRIO_WARNING)
      ("WARNING", protobuftools::logger::PRIO_WARNING)
      ("warning", protobuftools::logger::PRIO_WARNING)
      ("PRIO_NOTICE", protobuftools::logger::PRIO_NOTICE)
      ("NOTICE", protobuftools::logger::PRIO_NOTICE)
      ("notice", protobuftools::logger::PRIO_NOTICE)
      ("PRIO_INFORMATION", protobuftools::logger::PRIO_INFORMATION)
      ("INFORMATION", protobuftools::logger::PRIO_INFORMATION)
      ("information", protobuftools::logger::PRIO_INFORMATION)
      ("PRIO_DEBUG", protobuftools::logger::PRIO_DEBUG)
      ("DEBUG", protobuftools::logger::PRIO_DEBUG)
      ("debug", protobuftools::logger::PRIO_DEBUG)
      ("PRIO_TRACE", protobuftools::logger::PRIO_TRACE)
      ("TRACE", protobuftools::logger::PRIO_TRACE)
      ("trace", protobuftools::logger::PRIO_TRACE);

    return a;
  }

  //! Return priority label stripped of "PRIO_" prefix and lowercased
  std::string GetCanonicalLabel(const std::string& raw) {
    return boost::to_lower_copy(boost::ireplace_first_copy(raw, "PRIO_", ""));
  }

} // namespace

namespace protobuftools {

  logger::priority logger::get_priority(const std::string& name) {
    static PriorityLookup::LookupTable a;
    if (a.empty()) a = ConstructLookupTable();

    PriorityLookup::LookupTable::left_const_iterator p = a.left.find(name);
    return p != a.left.end() ? p->second : PRIO_UNDEFINED;
  }

  std::string logger::get_priority_label(logger::priority p)
  {
    static PriorityLookup::LookupTable a;
    if (a.empty()) a = ConstructLookupTable();

    PriorityLookup::LookupTable::right_const_iterator n = a.right.find(p);
    return n != a.right.end() ? GetCanonicalLabel(n->second) : "";
  }

  bool logger::is_fatal(priority p)
  {
    return p >= PRIO_FATAL;
  }

  bool logger::is_critical(priority p)
  {
    return p >= PRIO_CRITICAL;
  }

  bool logger::is_error(priority p)
  {
    return p >= PRIO_ERROR;
  }

  bool logger::is_warning(priority p)
  {
    return p >= PRIO_WARNING;
  }

  bool logger::is_notice(priority p)
  {
    return p >= PRIO_NOTICE;
  }

  bool logger::is_information(priority p)
  {
    return p >= PRIO_INFORMATION;
  }

  bool logger::is_debug(priority p)
  {
    return p >= PRIO_DEBUG;
  }

  bool logger::is_trace(priority p)
  {
    return p >= PRIO_TRACE;
  }

} // namespace protobuftools
