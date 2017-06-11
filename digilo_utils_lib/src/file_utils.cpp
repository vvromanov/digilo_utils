#include <errno.h>
#include <sys/stat.h>
#include "log.h"
#include "file_utils.h"

bool is_file_exist(const char* name) {
    struct stat sts;
    if (stat(name, &sts) == -1) {
        if (errno != ENOENT) {
            log_write(LOG_ERR | LOG_ERRNO, "stat(%s) error", name);
        }
        return false;
    }
    return true;
}
