#include <errno.h>
#include <sys/stat.h>
#include "log.h"
#include "file_utils.h"

bool is_file_exist(const char* name) {
    struct stat sts;
    if (stat(name, &sts) == -1) {
        return false;
    }
    return true;
}
