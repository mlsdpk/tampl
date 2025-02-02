#pragma once

#include <fmt/core.h>
#include <fmt/color.h>

namespace tampl {

enum class LogLevel { DEBUG, INFO, WARN, ERROR, FATAL };

#ifndef TAMPL_LOG_LEVEL
  #define TAMPL_LOG_LEVEL tampl::LogLevel::INFO
#endif

inline void vlog(LogLevel level, fmt::string_view fmt, fmt::format_args args)
{
  if (level < TAMPL_LOG_LEVEL) return;

  fmt::text_style style;
  const char* prefix = "";

  switch (level) {
    case LogLevel::DEBUG:
      style = fmt::fg(fmt::color::cyan);
      prefix = "[DEBUG] ";
      break;
    case LogLevel::INFO:
      style = fmt::fg(fmt::color::green);
      prefix = "[INFO]  ";
      break;
    case LogLevel::WARN:
      style = fmt::fg(fmt::color::yellow);
      prefix = "[WARN]  ";
      break;
    case LogLevel::ERROR:
      style = fmt::fg(fmt::color::red);
      prefix = "[ERROR] ";
      break;
    case LogLevel::FATAL:
      style = fmt::fg(fmt::color::red) | fmt::emphasis::bold;
      prefix = "[FATAL] ";
      break;
  }

  fmt::print(style, "{}{}\n", prefix, fmt::vformat(fmt, args));

  if (level == LogLevel::FATAL) {
    std::terminate();
  }
}

template <typename... T>
inline void log(LogLevel level, fmt::format_string<T...> fmt, T&&... args)
{
  tampl::vlog(level, fmt, fmt::make_format_args(args...));
}

#define TAMPL_LOG(level, fmt, ...) \
  tampl::log(level, fmt, ##__VA_ARGS__)

#define TAMPL_DEBUG(fmt, ...) TAMPL_LOG(tampl::LogLevel::DEBUG, fmt, ##__VA_ARGS__)
#define TAMPL_INFO(fmt, ...)  TAMPL_LOG(tampl::LogLevel::INFO, fmt, ##__VA_ARGS__)
#define TAMPL_WARN(fmt, ...)  TAMPL_LOG(tampl::LogLevel::WARN, fmt, ##__VA_ARGS__)
#define TAMPL_ERROR(fmt, ...) TAMPL_LOG(tampl::LogLevel::ERROR, fmt, ##__VA_ARGS__)
#define TAMPL_FATAL(fmt, ...) TAMPL_LOG(tampl::LogLevel::FATAL, fmt, ##__VA_ARGS__)

} // namespace tampl
