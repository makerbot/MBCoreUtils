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
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <locale>
#include <algorithm>
#include <sstream>
#include <string>
#include <list>
#include <chrono>
#include <iomanip>
#include <ctime>

#pragma GCC diagnostic pop

// We require a logging context string to be defined in order to use logging.
// The context string is supposed to identify the firmware component generating
// the log message, so it should either be a single short static string or a
// short static string with an index appended (via <<) when we have two or more
// components sharing the same code.
#ifndef LOGGING_CONTEXT
#error Logging context must be defined to use logging
#endif

// The main API entry point for standard logging
#define LOG(level) \
    BOOST_LOG_SEV(Logging::general::get(), boost::log::trivial::level) << "["\
    << LOGGING_CONTEXT << "] [" << Logging::getFilename(__FILE__) << ":"\
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

    // Typedefs for logging sinks
    typedef boost::log::sinks::synchronous_sink
        <boost::log::sinks::text_file_backend> backend;
    typedef boost::shared_ptr<backend> backend_ptr;

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

    // Custom collector class to get around two problems:
    //  - We want to collect general and telemetry logs independently
    //  - We want to remove the oldest log by number, not timestamp
    class Collector : public boost::log::sinks::file::collector {
      public:
        Collector(const std::string & target_dir,
                const std::string & file_name, int size_mb)
              : logs_dir_(target_dir),
                prefix_(file_name + "_"),
                total_size_(0),
                max_size_(size_mb * 1024 * 1024) {
            boost::filesystem::create_directories(logs_dir_);
        }

        void store_file(boost::filesystem::path const & src_path) override {
            std::string name(src_path.filename().string());
            int64_t lognum = parse_filename(name);
            if (lognum < 0) {
                // We generated a filename which we can't parse, so there is
                // a programming error somewhere if we get here.
                LOG(error) << "Can't parse log number from " << name;
                return;
            }
            int64_t size = boost::filesystem::file_size(src_path);
            auto it(files_.begin());
            while (it != files_.end() && total_size_ + size > max_size_) {
                auto filename(prefix_ + std::to_string(it->num) + ".log");
                auto path(logs_dir_ / filename);
                if (boost::filesystem::is_regular_file(path)) {
                    boost::system::error_code ec;
                    boost::filesystem::remove(path, ec);
                }
                total_size_ -= it->size;
                files_.erase(it++);
            }
            total_size_ += size;
            files_.push_back({lognum, size});
        }

        uintmax_t scan_for_files(boost::log::sinks::file::scan_method method,
                boost::filesystem::path const & pattern,
                unsigned int * counter) override {
            if (method == boost::log::sinks::file::no_scan) return 0;
            if (!boost::filesystem::is_directory(logs_dir_)) return 0;
            for (auto const & entry : boost::make_iterator_range(
                    boost::filesystem::directory_iterator(logs_dir_), {})) {
                if (entry.status().type() != boost::filesystem::regular_file)
                    continue;
                std::string name(entry.path().filename().string());
                int64_t lognum = parse_filename(name);
                if (lognum < 0) continue;
                int64_t size = boost::filesystem::file_size(entry.path());
                total_size_ += size;
                files_.push_back({lognum, size});
            }
            files_.sort([](const fileinfo & a, const fileinfo & b) {
                return a.num < b.num;
            });
            if (counter && !files_.empty()) {
                *counter = files_.back().num + 1;
            }
            return files_.size();
        }

      private:
        boost::filesystem::path logs_dir_;
        std::string prefix_;
        struct fileinfo {
            int64_t num;
            int64_t size;
        };
        std::list<fileinfo> files_;
        uint64_t total_size_, max_size_;

        // If name is a log filename that we would generate (format is
        // prefix_X.logs where X is a non-negative integer that is not
        // ridiculously large or contain extra leading zeros), return
        // the number of that log.  Otherwise return -1.
        int64_t parse_filename(const std::string & name) {
            auto pSize(prefix_.size());
            if (name.size() < pSize + 5) return -1;
            if (name.substr(0, pSize) != prefix_) return -1;
            if (name.substr(name.size() - 4) != ".log") return -1;
            auto x = name.substr(pSize, name.size() - 4 - pSize);
            if (x.size() > 18 || x.size() > 1 && x[0] == '0') return -1;
            int64_t lognum = 0;
            for (auto & c : x) {
                if (c < '0' || c > '9') return -1;
                lognum = lognum * 10 + c - '0';
            }
            return lognum;
        }
    };

    template<typename FmtT>
    backend_ptr MakeBackend(const std::string& folder_name,
            int size_mb, const std::string& file_name, FmtT format) {
        std::string target = std::string("/home/logs/") + folder_name;
        std::string path = target + "/" + file_name + "_%N.log";
        backend_ptr backend(boost::make_shared<backend>(
            boost::log::keywords::file_name = path.c_str(),
            boost::log::keywords::open_mode = std::ios::out | std::ios::app,
            boost::log::keywords::rotation_size = 1024 * 1024,
            boost::log::keywords::auto_flush = true));
        backend->locked_backend()->set_file_collector(
            boost::make_shared<Collector>(target, file_name, size_mb));
        backend->locked_backend()->scan_for_files();
        backend->set_formatter(format);
        boost::log::core::get()->add_sink(backend);
        return backend;
    }

    // A class to retrieve the current time with the local timezone and
    // monotonic time since boot -- this is attached as an attribute to
    // every log record we produce.
    struct Time {
        uint64_t monotonic_us;
        uint32_t local_us;
        std::tm localtime;
        Time() {
            using namespace std::chrono;  // NOLINT
            auto mnow = steady_clock::now().time_since_epoch();
            auto now = system_clock::now();
            monotonic_us = duration_cast<microseconds>(mnow).count();
            auto usTotal = duration_cast<microseconds>(now.time_since_epoch());
            local_us = (usTotal % 1000000).count();
            auto time = system_clock::to_time_t(now);
            localtime = *std::localtime(&time);  // NOLINT
        }
    };
}

// We provide an overload of the std::ostream << operator so that Boost logging
// will automatically know how to format our timestamps.  The format is a ISO
// 8601 timestamp with microseconds, then a single space, then a decimal number
// number of seconds since boot with microsecond accuracy.
//
// Host compiled versions of firmware that are build on older platforms do not
// implement the c++11 feature std::put_time.  We don't really need this feature
// for unit tests so we just output nothing in this case.
namespace std {
    inline ostream & operator<<(ostream & os, const Logging::Time & t) {
#if !defined(__GNUC__) || (__GNUC__ >= 5)
        os << std::put_time(&t.localtime, "%FT%T.");
        os << std::setfill('0') << std::setw(6) << t.local_us << std::setw(0);
        os << std::put_time(&t.localtime, "%z ") << t.monotonic_us / 1000000;
        os << "." << std::setw(6) << t.monotonic_us % 1000000 << std::setw(0);
#endif
        return os;
    }
}

namespace Logging {
    // Implement an attribute for a timestamp with timezone
    class timestamp_impl : public boost::log::attribute::impl {
      public:
        boost::log::attribute_value get_value() {
            return boost::log::attributes::make_attribute_value(Time());
        }
    };
    class timestamp : public boost::log::attribute {
      public:
        timestamp() : boost::log::attribute(new timestamp_impl()) {}
        explicit timestamp(boost::log::attributes::cast_source const& source)
          : boost::log::attribute(source.as< timestamp_impl >()) {}
    };

    inline void Initialize(const std::string& folder_name,
            int general_size_mb, const std::string& general_file_name,
            int telemetry_size_mb, const std::string& telemetry_file_name) {
        if (!general_backend()) {
            general_backend() = MakeBackend(
                folder_name, general_size_mb, general_file_name,
                boost::log::expressions::stream << "[" <<
                boost::log::expressions::attr<Time>("TimeStamp") <<
                "]: " << boost::log::expressions::smessage);
            ChangeGeneralLevel("info");
        }
        if (!telemetry_backend()) {
            telemetry_backend() = MakeBackend(
                folder_name, telemetry_size_mb, telemetry_file_name,
                boost::log::expressions::stream <<
                boost::log::expressions::attr<Time>("TimeStamp") <<
                "," << boost::log::expressions::smessage);
            ChangeTelemetryLevel("off");
        }
        boost::log::core::get()->add_global_attribute("TimeStamp", timestamp());
    }
}

#endif  // INCLUDE_MBCOREUTILS_FIRMWARE_LOGGING_H_
