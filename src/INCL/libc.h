#ifndef LIBC_H
#define LIBC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int printk(uint16_t log_level, const char *string);

// ------- STRING -------
size_t strlen(const char *str);
uint16_t strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *s1, const char *s2);

// -------- MEM --------
uint16_t memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);

#endif
