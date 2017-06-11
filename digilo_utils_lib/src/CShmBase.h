#ifndef DIGILO_UTILS_CSHMBASE_H
#define DIGILO_UTILS_CSHMBASE_H

#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <string>

#define SHM_LOCATION "/dev/shm/"

class CShmBase {
    uint8_t *data;
    size_t size;
    int fd;
    ino_t inode;
    std::string name;
public:
    CShmBase();
    bool Open(const char *name, size_t size, bool resize = false);

    void Close();

    size_t GetSize() const { return size; };
    uint8_t* GetData() const { return data; };
    bool IsDeleted() const;
private:
    void clear();
};


#endif //DIGILO_UTILS_CSHMBASE_H
