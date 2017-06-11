#include <cstdio>
#include <cerrno>
#include <cstring>
#include "log.h"
#include "common_utils.h"

bool log_to_syslog = true;
bool log_to_console = true;
uint64_t log_lines_count[LOG_MAX_LOG_LEVEL + 1];

const char* log_level_to_name(int32_t level) {
    switch (level & LOG_PRIMASK) {
        case LOG_EMERG:
            return "EMRG";
        case LOG_ALERT:
            return "ALRT";
        case LOG_CRIT:
            return "CRIT";
        case LOG_ERR:
            return "ERRR";
        case LOG_WARNING:
            return "WARN";
        case LOG_NOTICE:
            return "NOTI";
        case LOG_INFO:
            return "INFO";
        case LOG_DEBUG:
            return "DEBG";
        default:
            __builtin_unreachable ();
            return "???";
    }
}

void log_writev(int level, const char *format, va_list ap) {
    log_lines_count[level & LOG_PRIMASK]++;
    if (log_to_syslog) {
        if ((level & LOG_ERRNO)==LOG_ERRNO) {
            char tmp[1024];
            STRNCPY(tmp, format);
            STRNCAT(tmp," | %m");
            vsyslog(level & LOG_PRIMASK, tmp, ap);
        } else {
            vsyslog(level & LOG_PRIMASK, format, ap);
        }
    }
    if (log_to_console) {
        fprintf(stderr, "%s | ", log_level_to_name(level));
        vfprintf(stderr,format, ap);
        if ((level & LOG_ERRNO)==LOG_ERRNO) {
            fprintf(stderr, " | E%d - %s\n", errno, strerror(errno));
        } else {
            fputs("\n", stderr);
        }
    }
}

void log_write(int32_t level, const char *format, ...) {
    va_list va;
    va_start(va, format);
    log_writev(level, format, va);
    va_end(va);
}
