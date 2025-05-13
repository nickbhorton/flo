#pragma once

#include <ctime>
#include <format>
#include <iostream>
#include <string_view>

namespace flo::log
{
#define LOG_NAME "flo"
#define TERM_GREEN "\u001b[32m"
#define TERM_YELLOW "\u001b[33m"
#define TERM_RED "\u001b[31m"
#define TERM_CLEAR "\u001b[0m"

template <typename... Args> void debug(std::string_view fmt_sv, Args&&... args)
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    static char log_time[256];
    strftime(log_time, 256, "[%H:%M:%S]", &datetime);
    std::cout << log_time << " " << LOG_NAME << ": " << std::vformat(fmt_sv, std::make_format_args(args...))
              << std::endl;
}

template <typename... Args> void info(std::string_view fmt_sv, Args&&... args)
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    static char log_time[256];
    strftime(log_time, 256, "[%H:%M:%S]", &datetime);
    std::cout << TERM_GREEN << log_time << " " << LOG_NAME << ": "
              << std::vformat(fmt_sv, std::make_format_args(args...)) << TERM_CLEAR << std::endl;
}

template <typename... Args> void warn(std::string_view fmt_sv, Args&&... args)
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    static char log_time[256];
    strftime(log_time, 256, "[%H:%M:%S]", &datetime);
    std::cout << TERM_YELLOW << log_time << " " << LOG_NAME << ": "
              << std::vformat(fmt_sv, std::make_format_args(args...)) << TERM_CLEAR << std::endl;
}

template <typename... Args> void error(std::string_view fmt_sv, Args&&... args)
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    static char log_time[256];
    strftime(log_time, 256, "[%H:%M:%S]", &datetime);
    std::cout << TERM_RED << log_time << " " << LOG_NAME << ": " << std::vformat(fmt_sv, std::make_format_args(args...))
              << TERM_CLEAR << std::endl;
}
}; // namespace flo::log
