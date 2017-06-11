#define __STDC_FORMAT_MACROS
#include "CShmBase.h"
#include "log.h"
#include "common_utils.h"
#include <sys/mman.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>
#include <inttypes.h>

CShmBase::CShmBase() {
    clear();
}

bool CShmBase::Open(const char *name, size_t size, bool resize) {
    struct stat file_stat;

    if (fd > 0) {
        log_critical("Shm [%s] already opened", name);
        return false;
    }
    clear();
    this->name = name;
    fd = -1;
    if (size == 0) {
        fd = shm_open(name, O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
        if (fd < 0) {
            log_write(LOG_ERR | LOG_ERRNO, "shm_open(%s) failed", name);
            return false;
        }
    }
    if (fd < 0) {
        fd = shm_open(name, (O_CREAT | O_RDWR), (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
        if (fd < 0) {
            log_write(LOG_ERR | LOG_ERRNO, "shm_open(O_CREAT, %s) failed", name);
            return false;
        }
    }
    fchmod(fd, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));

    if (fstat(fd, &file_stat)) {
        log_write(LOG_ERR | LOG_ERRNO, "fstat(%s) failed", name);
        Close();
        return false;
    }
    if (size == 0) {
        size = file_stat.st_size;
    } else {
        if (!resize) {
            size_t realsize = file_stat.st_size;
            if (realsize && size != realsize) {
                log_write(LOG_ERR, "Invalid shm [%s] size=%zu instead of %zu", name, realsize, size);
                Close();
                return false;
            }
        }
        if (ftruncate(fd, size) < 0) {
            log_write(LOG_ERR | LOG_ERRNO, "ftruncate(%s, %zu) failed.", name, size);
            Close();
            return false;
        }
    }
    this->size = size;

    data = (uint8_t *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        log_write(LOG_ERR | LOG_ERRNO, "mmap(%s) failed. size=%zu", name, size);
        Close();
        return false;
    }
    if (mlock(data, size) != 0) {
        log_write(LOG_ERR | LOG_ERRNO, "mlock(%s) failed. size=%zu", name, size);
        Close();
        return false;
    }
    inode = file_stat.st_ino;
    log_write(LOG_NOTICE, "Open Shm [%s]. Inode=%" PRIu64 ", size=%zu", name, inode, size);
    return true;
}

void CShmBase::Close() {
    if (data && data != MAP_FAILED) {
        if (munlock(data, size) != 0) {
            log_write(LOG_ERR | LOG_ERRNO, "munlock(%s) failed", name.c_str());
        }
        munmap(data, size);
        close(fd);
    }
    clear();
}

void CShmBase::clear() {
    data = NULL;
    size = 0;
    fd = 0;
    inode = 0;
    name.clear();
}