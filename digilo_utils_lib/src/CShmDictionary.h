#ifndef DIGILO_UTILS_CSHMDICTIONARY_H
#define DIGILO_UTILS_CSHMDICTIONARY_H

#include <stdint.h>

#define DICTIONARY_NAMES_STORAGE_SIZE  64000
#define DICTIONARY_SIZE 500
#define DICTIONARY_INVALID_INDEX -1
#define DICTIONARY_NAME_MAX_LEN  128

class CShmDictionary {
public:
    typedef int32_t index_t;
    typedef struct {
        index_t id;
        uint32_t name_offset;
    } name_rec_t;

    typedef struct {
        index_t count;
        name_rec_t index[DICTIONARY_SIZE];
    } index_info_t;

    void Clear();
    index_t Add(const char *name);
    index_t Lookup(const char *name) const;
    const char *Lookup(index_t index) const;
    void GetIndex(index_info_t& index) const;
    void GetCategory(const char* prefix, index_info_t& index) const;

private:
    index_info_t index_info;
    uint32_t names_used; //Использованое хранилище имен
    char names_storage[DICTIONARY_NAMES_STORAGE_SIZE];
    uint32_t str_index[DICTIONARY_SIZE];
};

#endif //DIGILO_UTILS_CSHMDICTIONARY_H
