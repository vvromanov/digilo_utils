#include <cstring>
#include <algorithm>
#include "CShmDictionary.h"

typedef struct {
    const CShmDictionary &dict;
    const char *name;
} search_rec_t;

static bool compare(const CShmDictionary::name_rec_t &r, const search_rec_t &t) {
    return strcmp(t.dict.Lookup(r.id), t.name) < 0;
}

void CShmDictionary::Clear() {
    count = 0;
    names_used = 0;
}

CShmDictionary::index_t CShmDictionary::Add(const char *name) {
    int len = strlen(name);
    if (names_used + len + 1 > DICTIONARY_NAMES_STORAGE_SIZE) {
        return DICTIONARY_INVALID_INDEX;
    }
    if (count >= DICTIONARY_SIZE) {
        return DICTIONARY_INVALID_INDEX;
    }
    search_rec_t r = {*this, name};
    name_rec_t *p = std::lower_bound(index, index + count, r, compare);
    if (p != (index + count)) {
        if (strcmp(names_storage + p->name_offset, name) == 0) {
            return p->id;
        }
        memmove(p + 1, p, ((index + count) - p) * sizeof(*p));
    }
    p->id = count;
    p->name_offset = str_index[count] = names_used;
    count++;
    memcpy(names_storage + names_used, name, len + 1);
    names_used += len + 1;
    return p->id;
}

CShmDictionary::index_t CShmDictionary::Lookup(const char *name) const {
    search_rec_t r = {*this, name};
    const name_rec_t *p = std::lower_bound(index, index + count, r, compare);
    if (p != (index + count) && strcmp(names_storage + p->name_offset, name) == 0) {
        return p->id;
    } else {
        return DICTIONARY_INVALID_INDEX;
    }
}

const char *CShmDictionary::Lookup(CShmDictionary::index_t index) const {
    if (index < 0 || index >= count) {
        return NULL;
    }
    return names_storage + str_index[index];
}
