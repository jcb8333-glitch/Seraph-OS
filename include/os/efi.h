#ifndef _EFI_H
#define _EFI_H

#include <stdint.h>

#define EFI_ERR

/* Status codes */
#define EFI_SUCCESS 0
#define EFI_LOAD_ERROR          (1 | EFI_ERR)
#define EFI_DEVICE_ERROR        (2 | EFI_ERR)
#define EFI_INVALID_PARAMETER   (3 | EFI_ERR)
#define EFI_UNSUPPORTED         (4 | EFI_ERR)
#define EFI_BAD_BUFFER_SIZE     (5 | EFI_ERR)
#define EFI_BUFFER_TOO_SMALL    (6 | EFI_ERR)
#define EFI_NOT_READY           (7 | EFI_ERR)
#define EFI_NOT_FOUND           (8 | EFI_ERR)
#define EFI_OUT_OF_RESOURCES    (9 | EFI_ERR)
#define EFI_ACCESS_DENIED       (10 | EFI_ERR)
#define EFI_TIMEOUT             (11 | EFI_ERR)
#define EFI_ABORTED             (12 | EFI_ERR)
#define EFI_SECURITY_VIOLATION  (13 | EFI_ERR)
#define EFI_SECURITY_VIOLATION  (14 | EFI_ERR)

typedef uint64_t EFI_STATUS;
typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

/* e820 memory codes (May not use) */
typedef enum {
    efiReservedMemoryType,
    efiLoaderCode,
    efiLoaderData,
    efiBootServicesCode,
    efiBootServicesData,
    efiRuntimeServicesCode,
    efiRuntimeServicesDate,
    efiConventionalMemory,
    efiUnusableMemory,
    efiACPIReclaimMemory,
    efiACPIMemoryNVS,
    efiMemoryMappedIO,
    efiMemoryMappedIOPortSpace,
    efiPalCode,
    efiPersistentMemory,
    efiMaxMemory,
} EFI_MEMORY_TYPE;

typedef struct {
    uint32_t type;
    uint32_t pad;
    EFI_PHYSICAL_ADDRESS physicalStart;
    EFI_VIRTUAL_ADDRESS virtualStart;
    uint64_t numPages;
    uint64_t attribute;
} EFI_MEMORY_DESCRIPTOR;

#endif // _EFI_H