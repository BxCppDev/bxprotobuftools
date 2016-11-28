//! \file    bxprotobuftools/logger.h
//! \brief   Utilities for logging information
//! \details Logging information from the progress of an application
//!          often requires finer granularity than offered by the
//!          standard library streams. Log messages should also
//!          record where they came from.
//!
//!          To help developers log messages, bxprotobuftools supplies a
//!          very basic priority based logging system. This uses the
//!          standard iostreams under the hood, but messages are logged
//!          at one of 8 priority levels from most to least critical.
//!          A minimum priority may be set, with only messages at that
//!          priority or higher logged to the relevant iostream.
//!
//!          This minimum priority can be stored in a variable, allowing
//!          logging priority to be adjusted on an instance-by-instance
//!          basis as well as at global or class scope.
//!
//!          Helper macros are provided to provide logging at each
//!          level if a provided priority meets the minimum level.
//!          For example, to log an informational message, you could use:
//!
//!          @code
//!          protobuftools::logger::priority prio_;
//!          ...
//!          BX_LOG_INFORMATION(prio_, "Information message");
//!          @endcode
//!
//!          Provided the variable prio_ meets the minimum priority for
//!          information messages to be logged, the message will be
//!          streamed to the relevant iostream. As can be seen, the
//!          prio_ variable supplied to the logging macro could come
//!          from any relevant source (global, function argument, class
//!          variable, instance variable and so on).
//!
//!          Adapted from the Bayeux/datatools library.
//
// Copyright (c) 2016 by Ben Morgan <bmorgan.warwick@gmail.com>
// Copyright (c) 2016 by The University of Warwick
//
// This file is part of bxprotobuftools.
//
// bxprotobuftools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// bxprotobuftools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with bxprotobuftools.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BXPROTOBUFTOOLS_LOGGER_H
#define BXPROTOBUFTOOLS_LOGGER_H

// Standard Library:
#include <iostream>

// Third Party:
// - Boost:
#include <boost/current_function.hpp>

/// \brief Top-level namespace of the Bayeux/protobuftools module library
namespace protobuftools {

  //! Organise logging functionality under one roof
  struct logger {

    //! Priority levels for logging from most to least critical
    enum priority {
      PRIO_ALWAYS   = -1, //!< Always print the message
      PRIO_UNDEFINED = 0, //!< Undefined/invalid priority
      PRIO_FATAL,         //!< A fatal error. The application will most likely terminate. This is the highest priority.
      PRIO_CRITICAL,      //!< A critical error. The application might not be able to continue running successfully.
      PRIO_ERROR,         //!< An error. An operation did not complete successfully, but the application as a whole is not affected.
      PRIO_WARNING,       //!< A warning. An operation completed with an unexpected result.
      PRIO_NOTICE,        //!< A notice, which is an information with just a higher priority.
      PRIO_INFORMATION,   //!< An informational message, usually denoting the successful completion of an operation.
      PRIO_DEBUG,         //!< A debugging message.
      PRIO_TRACE          //!< A tracing message. This is the lowest priority.
    };

    //! return priority enumeration value from string
    //! The string can take three forms for matching, e.g. the PRIO_FATAL
    //! priority would be returned from input strings "PRIO_FATAL", "FATAL"
    //! or "fatal".
    //! @param name priority name
    //! @returns the matching priority enumeration or the PRIO_UNDEFINED
    //!          if the name is not valid
    static priority get_priority(const std::string& name);

    //! return priority label from the priority enumeration value
    //! @param p priority enumeration
    //! @returns the matching priority label or the empty string if the priority
    //!          is not valid
    static std::string get_priority_label(priority p);

    //! check if priority satisfy the fatal level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the fatal level
    static bool is_fatal(priority p);

    //! check if priority satisfy the critical level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the critical level
    static bool is_critical(priority p);

    //! check if priority satisfy the error level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the error level
    static bool is_error(priority p);

    //! check if priority satisfy the warning level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the warning level
    static bool is_warning(priority p);

    //! check if priority satisfy the notice level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the notice level
    static bool is_notice(priority p);

    //! check if priority satisfy the information level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the information level
    static bool is_information(priority p);

    //! check if priority satisfy the debug level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the debug level
    static bool is_debug(priority p);

    //! check if priority satisfy the trace level
    //! @param p priority enumeration
    //! @returns true if the priority is at least at the trace level
    static bool is_trace(priority p);

  };

} // namespace protobuftools

#include <protobuftools/logger_macros.h>

#endif // BXPROTOBUFTOOLS_LOGGER_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
