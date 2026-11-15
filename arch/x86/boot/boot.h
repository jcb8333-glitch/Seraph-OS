/*
 * Header file for handling boot services once called by loader.
 * Specific services are defined in their own file.
 */
#ifndef _BOOT_H
#define _BOOT_H

#define STACK_SIZE 1024

#include <stdlib.h>
#include <os/efi.h>

// memory.c
// void detectMemory(void);

#endif // _BOOT_H