#ifndef _TERMINAL_CODES_H_
#define _TERMINAL_CODES_H_

#define VT_SETCOLOR_GREEN      "\x1B[1;32m"
#define VT_SETCOLOR_RED        "\x1B[1;31m"
#define VT_SETCOLOR_YELLOW     "\x1B[1;33m"
#define VT_SETCOLOR_NORMAL     "\x1B[0m"
#define VT_SETCOLOR_NOTICE     "\x1B[1;34m"
#define VT_SETCOLOR_BLUE_      "\x1B[1;36m"
#define VT_SETCOLOR_BLUE       "\x1B[0;36m"
#define VT_SETCOLOR_CRITICAL   "\x1B[1;33;41m\x1B[5;33;41m"
#define VT_SETCOLOR_PARANOID   "\x1B[1;30m"

#define VT_CLEAR_SCREEN   "\x1B[2J"
#define VT_CLEAR_LINE_END "\x1B[K"

#endif /* _TERMINAL_CODES_H_ */
