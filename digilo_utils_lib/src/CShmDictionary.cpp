#include <cstring>
#include <algorithm>
#include "CShmDictionary.h"
#include "common_utils.h"

typedef struct {
    const CShmDictionary &dict;
    const char *name;
} search_rec_t;

static bool compare(const CShmDictionary::name_rec_t &r, const search_rec_t &t) {
    return strcmp(t.dict.Lookup(r.id), t.name) < 0;
}

void CShmDictionary::Clear() {
    index_info.count = 0;
    names_used = 0;
}

CShmDictionary::index_t CShmDictionary::Add(const char *name) {
    int len = strlen(name);
    if (names_used + len + 1 > DICTIONARY_NAMES_STORAGE_SIZE) {
        return DICTIONARY_INVALID_INDEX;
    }
    if (index_info.count >= DICTIONARY_SIZE) {
        return DICTIONARY_INVALID_INDEX;
    }
    search_rec_t r = {*this, name};
    name_rec_t *p = std::lower_bound(index_info.index, index_info.index + index_info.count, r, compare);
    if (p != (index_info.index + index_info.count)) {
        if (strcmp(names_storage + p->name_offset, name) == 0) {
            return p->id;
        }
        memmove(p + 1, p, ((index_info.index + index_info.count) - p) * sizeof(*p));
    }
    p->id = index_info.count;
    p->name_offset = str_index[index_info.count] = names_used;
    index_info.count++;
    memcpy(names_storage + names_used, name, len + 1);
    names_used += len + 1;
    return p->id;
}

CShmDictionary::index_t CShmDictionary::Lookup(const char *name) const {
    search_rec_t r = {*this, name};
    const name_rec_t *p = std::lower_bound(index_info.index, index_info.index + index_info.count, r, compare);
    if (p != (index_info.index + index_info.count) && strcmp(names_storage + p->name_offset, name) == 0) {
        return p->id;
    } else {
        return DICTIONARY_INVALID_INDEX;
    }
}

const char *CShmDictionary::Lookup(CShmDictionary::index_t index) const {
    if (index < 0 || index >= index_info.count) {
        return NULL;
    }
    return names_storage + str_index[index];
}

void CShmDictionary::GetIndex(CShmDictionary::index_info_t &index_) const {
    index_.count = this->index_info.count;
    memcpy(index_.index, this->index_info.index, sizeof(index_.index[0]) * index_.count);
}

void CShmDictionary::GetCategory(const char *prefix, CShmDictionary::index_info_t &index_) const {
    if (prefix == NULL || prefix[0] == 0) {
        GetIndex(index_);
    } else {
        char prefix_[DICTIONARY_NAME_MAX_LEN + 1];
        STRNCPY(prefix_, prefix);
        search_rec_t r = {*this, prefix_};
        const name_rec_t *p1 = std::lower_bound(index_info.index, index_info.index + index_info.count, r, compare);
//        if (strcmp(names_storage + p1->name_offset, prefix_) != 0) {
//            p1++;
//        }
        STRNCAT(prefix_, "\xFF");
        const name_rec_t *p2 = std::lower_bound(index_info.index, index_info.index + index_info.count, r, compare);
//        if (strcmp(names_storage + p2->name_offset, prefix_) != 0) {
//            p2++;
//        }
        index_.count = p2 - p1;
        memmove(index_.index, p1, index_.count * sizeof(index_.index[0]));
    }
}
