#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#include <stdint.h>

/* memory cases */
void* memcpy(void* dst, const void* src, size_t len);
void* memmove(void* dst, const void* src, size_t len);
void* memset(void* dst, int data, size_t len);
int memcmp(void* seg1, void* seg2, size_t len);

/* string cases */
extern int strcmp(const char* str1, const char* str2);
extern size_t strlen(const char* str);

#endif // _STRING_H