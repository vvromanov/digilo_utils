#ifndef DIGILO_UTILS_LOG_H_H
#define DIGILO_UTILS_LOG_H_H
#include <syslog.h>
#include <stdint.h>
#include <stdarg.h>

#define LOG_ERRNO 0x1000

void log_write(int32_t level, const char *format, ...) __attribute__((format(printf, 2, 3)));
void log_writev(int32_t level, const char *format, va_list ap);

#define log_critical(format, ...)  log_write(LOG_CRIT, format,  __VA_ARGS__);

#endif //DIGILO_UTILS_LOG_H_H
