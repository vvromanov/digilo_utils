#include <cstdio>
#include <cerrno>
#include <cstring>
#include "log.h"
#include "common_utils.h"

bool log_to_syslog = false;
bool log_to_console = true;

const char* level_to_name(int32_t level) {
    switch (level & LOG_PRIMASK) {
        case LOG_EMERG:
            return "EMERG";
        case LOG_ALERT:
            return "ALERT";
        case LOG_CRIT:
            return "CRIT";
        case LOG_ERR:
            return "ERR";
        case LOG_WARNING:
            return "WARN";
        case LOG_NOTICE:
            return "NOTI";
        case LOG_INFO:
            return "INFO";
        case LOG_DEBUG:
            return "DEBG";
        default:
            return "???";
    }
}
void log_writev(int level, const char *format, va_list ap) {
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
        fprintf(stderr, "%s | ", level_to_name(level));
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
