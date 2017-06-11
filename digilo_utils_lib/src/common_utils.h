#ifndef DIGILO_UTILS_COMMON_UTILS_H_H
#define DIGILO_UTILS_COMMON_UTILS_H_H

#include <string.h>

#define BZERO_S(some_struct) memset(&(some_struct), 0, sizeof(some_struct))
#define STRNCPY(destination, source) do { strncpy((destination), (source), sizeof(destination)); destination[sizeof(destination)-1]=0;} while (0)
#define STRNCAT(destination, source) do { strncat((destination), (source), sizeof(destination) - strlen(destination) - 1); destination[sizeof(destination)-1]=0;} while (0)

#endif //DIGILO_UTILS_COMMON_UTILS_H_H
