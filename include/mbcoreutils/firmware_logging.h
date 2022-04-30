// Copyright MakerBot, Inc. 2022

// This file provides wrappers around boost logging that provide the format
// and structure of logs that we use for all firmware logging from C++
// libraries.
#ifndef INCLUDE_MBCOREUTILS_FIRMWARE_LOGGING_H_
#define INCLUDE_MBCOREUTILS_FIRMWARE_LOGGING_H_

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/log/core.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup.hpp>

#include <locale>
#include <algorithm>
#include <sstream>
#include <string>

#pragma GCC diagnostic pop

// We require a logging channel name to be defined in order to use logging.
// It is generally recommended to pass this in from the build system to create
// one channel name per library.  Note that we don't actually use this as the
// logging channel, but we just manually include this in the log message.
#ifndef __LOGGING_CHANNEL__
#error Logging channel must be defined to use logging
#else
#endif

// The main API entry point for standard logging.  This includes file and line
// number information, so to wrap this call, either another macro should be
// used to directly call this, or the TODO function below should be called
// with this information passed in from the original source of the logging
// statement.
#define LOG(level) \
    BOOST_LOG_SEV(Logging::general::get(), boost::log::trivial::level) << "["\
    << __LOGGING_CHANNEL__ << "] [" << Logging::getFilename(__FILE__) << ":"\
    << __LINE__ << ":" << __func__ << "] "

// The main API entry point for telemetry logging
#define TELEM(level) \
    BOOST_LOG_SEV(Logging::telemetry::get(), boost::log::trivial::level)

namespace Logging {
    // Initialize the logging backends.  No logs will be written to disk before
    // this happens so this should be called as early as possible.  The folder
    // to write all logs into, the base name for each log, and the size cap for
    // each log are specified here.  The general log level will be set to info
    // and the telemetry log will be off -- these should be changed as soon as
    // possible to the configured level via the Change*Level functions, but we
    // want to make sure that we log any errors that happen before we load these
    // configurations.
    //
    // TODO(chris): The size caps for each individual log are not being honored,
    //   instead the smallest value passed will be used a a size cap for both
    //   logs combined.
    inline void Initialize(const std::string& folder_name,
        int general_size_mb, const std::string& general_file_name,
        int telemetry_size_mb, const std::string& telemetry_file_name);

    // Set the log level for each of the log backends.  We accept the strings
    // "debug", "info", "warning", "error", "off" (case insensitive).
    inline void ChangeGeneralLevel(const std::string& sev);
    inline void ChangeTelemetryLevel(const std::string& sev);

    // Implemenation
    //
    // The general configuration of boost logging is that you can make as many
    // sources and as many sinks as you want, and through some boost singleton
    // magic these will automatically all be connected up so that every source
    // writes to every sink.  We want a general log that writes to one log file
    // and a telemetry log that writes to a telemetry file, so we create two
    // log sources with different channel names, and then two log sinks that
    // always filter only the channel names that we want to log.

    // C++11 constexpr function to reduce a full file path to a filename.
    constexpr size_t getAfterSlashIdx(
            const char * file, size_t idx, size_t res) {
        return file[idx] ? getAfterSlashIdx(file, idx + 1,
            file[idx] == '/' ? idx + 1 : res) : res;
    }
    constexpr const char * getFilename(const char * file) {
        return file + getAfterSlashIdx(file, 0, 0);
    }

    // Typedef for logging sources
    typedef boost::log::sources::severity_channel_logger
        <boost::log::trivial::severity_level, std::string> log_class;

    // Typedef for logging sinks
    typedef boost::shared_ptr<boost::log::sinks::synchronous_sink  // NOLINT
        <boost::log::sinks::text_file_backend > > backend_ptr;

    // Use local statics to ensure that only one instance of each pointer is
    // ever created by the linker.
    inline backend_ptr & general_backend() {
        static backend_ptr backend;
        return backend;
    }
    inline backend_ptr & telemetry_backend() {
        static backend_ptr backend;
        return backend;
    }

    // Create boost singletons for the logging sources -- these declare the
    // identifiers general and telemetry which have a ::get() static method
    // to retrieve a singleton of type log_class.
    BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(general, log_class) {
        log_class lg(boost::log::keywords::channel = "general");
        return lg;
    }
    BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(telemetry, log_class) {
        log_class lg(boost::log::keywords::channel = "telemetry");
        return lg;
    }

    // Helper function for changing the log level -- we always need the filter
    // to both select the log level and only allow entries from one channel.
    template <int Level>
    void SetLevel(backend_ptr & backend, const char * channel) {
        backend->set_filter(boost::log::trivial::severity >= Level &&
            boost::log::expressions::attr<std::string>("Channel") == channel);
    }

    // Generic function to map string severities to boost severities
    inline void ChangeLevel(
        backend_ptr & backend, const char * channel, const std::string & sev) {
        if (backend) {
            backend->reset_filter();
            std::string lower(sev.size(), ' ');
            std::transform(sev.cbegin(), sev.cend(), lower.begin(),
                           [](char c) {return std::tolower(c, std::locale());});
            if (lower == "debug") {
                SetLevel<boost::log::trivial::debug>(backend, channel);
            } else if (lower == "info") {
                SetLevel<boost::log::trivial::info>(backend, channel);
            } else if (lower == "warning") {
                SetLevel<boost::log::trivial::warning>(backend, channel);
            } else if (lower == "error") {
                SetLevel<boost::log::trivial::error>(backend, channel);
            } else if (lower == "off") {
                SetLevel<boost::log::trivial::fatal>(backend, channel);
            } else {
                LOG(warning) << "Invalid log specifier: " << sev;
                SetLevel<boost::log::trivial::trace>(backend, channel);
            }
        }
    }

    inline void ChangeGeneralLevel(const std::string& sev) {
        ChangeLevel(general_backend(), "general", sev);
    }
    inline void ChangeTelemetryLevel(const std::string& sev) {
        ChangeLevel(telemetry_backend(), "telemetry", sev);
    }

    inline void Initialize(const std::string& folder_name,
            int general_size_mb, const std::string& general_file_name,
            int telemetry_size_mb, const std::string& telemetry_file_name) {
        std::string general_path = std::string("/home/logs/") + folder_name
            + "/" + general_file_name + "_%N.log";
        std::string target = std::string("/home/logs/") + folder_name;
        std::string telemetry_path = std::string("/home/logs/") + folder_name
            + "/" + telemetry_file_name + "_%N.log";
        if (!general_backend()) {
            general_backend() = boost::log::add_file_log(
                boost::log::keywords::file_name = general_path.c_str(),
                boost::log::keywords::open_mode = std::ios::out | std::ios::app,
                // rotate files every 1MB
                boost::log::keywords::rotation_size = 1024 * 1024,
                // flush logfile to disk on write
                boost::log::keywords::auto_flush = true,
                boost::log::keywords::target = target.c_str(),
                boost::log::keywords::max_size = general_size_mb * 1024*1024,
                boost::log::keywords::format = "[%TimeStamp%]: %Message%");
            ChangeGeneralLevel("info");
        }
        if (!telemetry_backend()) {
            telemetry_backend() = boost::log::add_file_log(
                boost::log::keywords::file_name = telemetry_path.c_str(),
                boost::log::keywords::open_mode = std::ios::out | std::ios::app,
                // rotate files every 1MB
                boost::log::keywords::rotation_size = 1024 * 1024,
                // flush logfile to disk on write
                boost::log::keywords::auto_flush = true,
                boost::log::keywords::target = target.c_str(),
                boost::log::keywords::max_size = telemetry_size_mb * 1024*1024,
                boost::log::keywords::format = "%TimeStamp%,%Message%");
            ChangeTelemetryLevel("off");
        }
        boost::log::add_common_attributes();
    }
}

#endif  // INCLUDE_MBCOREUTILS_FIRMWARE_LOGGING_H_
