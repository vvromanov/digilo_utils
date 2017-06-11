#ifndef DIGILO_UTILS_LOG_H_H
#define DIGILO_UTILS_LOG_H_H

#include <syslog.h>
#include <stdint.h>
#include <stdarg.h>

#define LOG_ERRNO 0x1000
#define LOG_MAX_LOG_LEVEL LOG_DEBUG
extern uint64_t log_lines_count[LOG_MAX_LOG_LEVEL + 1];

void log_write(int32_t level, const char *format, ...) __attribute__((format(printf, 2, 3)));

void log_writev(int32_t level, const char *format, va_list ap);

const char *log_level_to_name(int32_t level);

#endif //DIGILO_UTILS_LOG_H_H
