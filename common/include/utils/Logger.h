#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Constants.h"

namespace hyperion_proxy::common::utils {

    class Logger {
        public:
            enum class LogLevel { INFO, WARNING, ERROR, DEBUG };

            static void log(const std::string &message, LogLevel level = LogLevel::INFO) { log(message, level, LOG_DEFAULT_DATE_FORMAT); }

            static void log(const std::string &message, LogLevel level, const std::string &dateFormat) {
                const char *colorCode;
                const char *levelStr;

                switch (level) {
                    case LogLevel::INFO:
                        colorCode = LOG_COLOR_INFO;
                        levelStr = "INFO";
                        break;
                    case LogLevel::WARNING:
                        colorCode = LOG_COLOR_WARNING;
                        levelStr = "WARNING";
                        break;
                    case LogLevel::ERROR:
                        colorCode = LOG_COLOR_ERROR;
                        levelStr = "ERROR";
                        break;
                    case LogLevel::DEBUG:
                        colorCode = LOG_COLOR_DEBUG;
                        levelStr = "DEBUG";
                        break;
                    default:
                        colorCode = LOG_COLOR_DEFAULT;
                        levelStr = "LOG";
                }

                std::ostream &out = (level == LogLevel::ERROR) ? std::cerr : std::cout;

                // Get current time
                auto now = std::chrono::system_clock::now();
                std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

                // Format time
                std::tm buf{};
#if defined(_WIN32)
                localtime_s(&buf, &nowTime);
#else
                localtime_r(&nowTime, &buf);
#endif
                std::ostringstream timeStream;
                timeStream << std::put_time(&buf, dateFormat.c_str());

                // Log message
                out << "[" << timeStream.str() << "] " << colorCode << "[" << levelStr << "] " << LOG_COLOR_RESET << message << std::endl;
            }
    };

}  // namespace hyperion_proxy::common::utils