//! \file  protobuftools/logger_macros.h
//! \brief Macros associated to logging utilities
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

#ifndef PROTOBUFTOOLS_LOGGER_MACROS_H
#define PROTOBUFTOOLS_LOGGER_MACROS_H

// Standard Library:
#include <iostream>

// Third Party:
// - Boost:
#include <boost/current_function.hpp>

// This project:
#include <protobuftools/logger.h>

//! Log Message if Priority is greater or equal to PRIO_FATAL
#define BX_LOG_FATAL(Priority, Message)                                 \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_FATAL) { \
      std::cerr << "[fatal:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_CRITICAL
#define BX_LOG_CRITICAL(Priority, Message)                              \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_CRITICAL) { \
      std::cerr << "[critical:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_ERROR
#define BX_LOG_ERROR(Priority, Message)                                 \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p  >= ::protobuftools::logger::PRIO_ERROR) { \
      std::cerr << "[error:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_WARNING
#define BX_LOG_WARNING(Priority, Message)                               \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_WARNING) { \
      std::cerr << "[warning:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_NOTICE
#define BX_LOG_NOTICE(Priority, Message)                                \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_NOTICE) { \
      std::clog << "[notice:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_INFORMATION
#define BX_LOG_INFORMATION(Priority, Message)                           \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_INFORMATION) { \
      std::clog << "[information:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_DEBUG
#define BX_LOG_DEBUG(Priority, Message)                                 \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_DEBUG) { \
      std::clog << "[debug:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log Message if Priority is greater or equal to PRIO_TRACE
#define BX_LOG_TRACE(Priority, Message)                                 \
  {                                                                     \
    ::protobuftools::logger::priority _bx_xxx_p = Priority;		\
    if (_bx_xxx_p == ::protobuftools::logger::PRIO_ALWAYS || _bx_xxx_p >= ::protobuftools::logger::PRIO_TRACE) { \
      std::cerr << "[trace:" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] " << Message << std::endl; \
    }                                                                   \
  }

//! Log an entering message if Priority is greater or equal to PRIO_TRACE
#define BX_LOG_TRACE_ENTERING(Priority)         \
  {                                             \
    BX_LOG_TRACE(Priority, "Entering...");      \
  }

//! Log an exiting message if Priority is greater or equal to PRIO_TRACE
#define BX_LOG_TRACE_EXITING(Priority)          \
  {                                             \
    BX_LOG_TRACE(Priority, "Exiting.");         \
  }

#endif // PROTOBUFTOOLS_LOGGER_MACROS_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
