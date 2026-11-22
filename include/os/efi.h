#ifndef _EFI_H
#define _EFI_H

#include <stdint.h>

#if defined(__x86_64__) && !defined(_WIN32)
#define EFIAPI __attribute__((ms_abi))
#else
#define EFIAPI
#endif

/* Basic types */
typedef void VOID;
typedef uintptr_t   UINTN;
typedef uint8_t     UINT8;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;
typedef uint8_t     BOOLEAN;
typedef uint16_t    CHAR16;
typedef uint64_t    EFI_PHYSICAL_ADDRESS;
typedef uint64_t    EFI_VIRTUAL_ADDRESS;
typedef uint64_t    EFI_STATUS;
typedef void* EFI_HANDLE;

#define EFI_ERR_BIT ((UINTN)1 << 63)

/* Status codes */
#define EFI_SUCCESS 0
#define EFI_LOAD_ERROR          (1 | EFI_ERR_BIT)
#define EFI_INVALID_PARAMETER   (2 | EFI_ERR_BIT)
#define EFI_UNSUPPORTED         (3 | EFI_ERR_BIT)
#define EFI_BAD_BUFFER_SIZE     (4 | EFI_ERR_BIT)
#define EFI_BUFFER_TOO_SMALL    (5 | EFI_ERR_BIT)
#define EFI_NOT_READY           (6 | EFI_ERR_BIT)
#define EFI_DEVICE_ERROR        (7 | EFI_ERR_BIT)
#define EFI_WRITE_PROTECTED     (8 | EFI_ERR_BIT)
#define EFI_OUT_OF_RESOURCES    (9 | EFI_ERR_BIT)
#define EFI_NOT_FOUND           (14 | EFI_ERR_BIT)
#define EFI_ACCESS_DENIED       (15 | EFI_ERR_BIT)
#define EFI_SECURITY_VIOLATION  (16 | EFI_ERR_BIT)
#define EFI_TIMEOUT             (18 | EFI_ERR_BIT)
#define EFI_ABORTED             (21 | EFI_ERR_BIT)

/* GUID */
typedef struct {
    UINT32  data1;
    UINT16  data2;
    UINT16  data3;
    UINT8   data4[8];
} EFI_GUID;

#define EFI_ACPI_20_TABLE_GUID \
    {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}}

typedef struct {
    UINT64 signature;
    UINT32 revision;
    UINT32 headerSize;
    UINT32 CRC32;
    UINT32 reserved;
} EFI_TABLE_HEADER;

/* Simple Text Output */
struct EFI_TEXT_OUT_PROTO;
typedef EFI_STATUS (EFIAPI* EFI_TEXT_RESET)(
    struct EFI_TEXT_OUT_PROTO* This, 
    BOOLEAN extendedVerification
);
typedef EFI_STATUS (EFIAPI*  EFI_TEXT_STRING)(
    EFI_TEXT_OUT_PROTO* This, 
    CHAR16* String
);
typedef EFI_STATUS (EFIAPI* EFI_TEXT_CLEAR_SCREEN)(
    EFI_TEXT_OUT_PROTO* This
);

typedef struct {
    EFI_TEXT_RESET          reset;
    EFI_TEXT_STRING         outStr;
    VOID*                   testStr;
    VOID*                   queryMode;
    VOID*                   setMode;
    VOID*                   setAttribute;
    EFI_TEXT_CLEAR_SCREEN   clearScreen;
    VOID*                   setCursorPos;
    VOID*                   enableCursor;
    VOID*                   mode;  
} EFI_TEXT_OUT_PROTO;

/* e820 memory codes (May not use) */
typedef enum {
    efiReservedMemoryType,
    efiLoaderCode,
    efiLoaderData,
    efiBootServicesCode,
    efiBootServicesData,
    efiRuntimeServicesCode,
    efiRuntimeServicesData,
    efiConventionalMemory,
    efiUnusableMemory,
    efiACPIReclaimMemory,
    efiACPIMemoryNVS,
    efiMemoryMappedIO,
    efiMemoryMappedIOPortSpace,
    efiPalCode,
    efiPersistentMemory,
    efiMaxMemory,
    efiUnacceptedMemoryType
} EFI_MEMORY_TYPE;

typedef enum {
    allocateAnyPages,
    allocateMaxAddress,
    allocateAddress,
    maxAllocateType
} EFI_ALLOCATE_TYPE;

typedef struct {
    UINT32                  type;
    UINT32                  pad;
    EFI_PHYSICAL_ADDRESS    physicalStart;
    EFI_VIRTUAL_ADDRESS     virtualStart;
    UINT64                  numPages;
    UINT64                  attribute;
} EFI_MEMORY_DESCRIPTOR;

/* Boot Services */
typedef EFI_STATUS (EFIAPI* EFI_ALLOCATE_PAGES)(
    EFI_ALLOCATE_TYPE type, 
    EFI_MEMORY_TYPE memoryType,
    UINTN pages,
    EFI_PHYSICAL_ADDRESS* memory
);
typedef EFI_STATUS (EFIAPI* EFI_FREE_PAGES)(
    EFI_PHYSICAL_ADDRESS memory, 
    UINTN pages
);
typedef EFI_STATUS (EFIAPI* EFI_GET_MEMORY_MAP)(
    UINTN* memMapSize, 
    EFI_MEMORY_DESCRIPTOR* memMap, 
    UINTN* mapKey, 
    UINTN* descSize, 
    UINT32* descVer
);
typedef EFI_STATUS (EFIAPI* EFI_ALLOCATE_POOL)(
    EFI_MEMORY_TYPE poolType, 
    UINTN size, 
    VOID** buffer
);
typedef EFI_STATUS (EFIAPI* EFI_FREE_POOL)(
    VOID* buffer
);
typedef EFI_STATUS(EFIAPI* EFI_EXIT_BOOT_SERVICES)(
    EFI_HANDLE imageHandle, 
    UINTN mapKey
);
typedef EFI_STATUS(EFIAPI* EFI_SET_WATCHDOG_TIMER)(
    UINTN timeout, 
    UINT64 watchdogCode, 
    UINTN dataSize, 
    CHAR16* watchdogData
);
typedef EFI_STATUS (EFIAPI* EFI_LOCATE_PROTOCOL)(
    EFI_GUID* protocol, 
    VOID* registration, 
    VOID** interface
);
typedef EFI_STATUS (EFIAPI* EFI_HANDLE_PROTOCOL)(
    EFI_HANDLE handle, 
    EFI_GUID* protocol, 
    VOID** interface
);

typedef struct {
    EFI_TABLE_HEADER Header;
    // Task priority
    VOID* RaiseTPL;
    VOID* RestoreTPL;
    // Memory
    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP getMemoryMap;
    EFI_ALLOCATE_POOL AllocatePool;
    EFI_FREE_POOL FreePool;
    // Events
    VOID* CreateEvent;
    VOID* SetTimer;
    VOID* WaitForEvent;
    VOID* SignalEvent;
    VOID* CloseEvent;
    VOID* CheckEvent;
    // Protocol Handlers
    VOID* InstallProtocolInterface;
    VOID* ReinstallProtocolInterface;
    VOID* UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL HandleProtocol;
    VOID* Reserved;
    VOID* RegisterProtocolNotify;
    VOID* Locatehandle;
    VOID* LocateDevicePath;
    VOID* InstallConfigurationTable;
    // Image Services
    VOID* LoadImage;
    VOID* StartImage;
    VOID* Exit;
    VOID* UnloadImage;
    EFI_EXIT_BOOT_SERVICES ExitBootServices;
    // misc
    VOID* GetNextMonotonicCount;
    VOID* Stall;
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;
    // Driver Support
    VOID* ConnectController;
    VOID* DisconnectController;
    // Open/Close Protocol
    VOID* OpenProtocol;
    VOID* CloseProtocol;
    VOID* OpenProtocolInformation;
    // Library
    VOID* ProtocolsPerHandle;
    VOID* LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL LocateProtocol;
    VOID* InstallMultipleProtocolInterfaces;
    VOID* UninstallMultipleProtocolInterfaces;
    // CRC / Memory Utils
    VOID* CalculatorCrc32;
    VOID* CopyMem;
    VOID* SetMem;
    VOID* CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct {
    EFI_GUID    vendorGUID;
    VOID*       vendorTable;
} EFI_CONFIG_TABLE;

typedef struct {
    EFI_TABLE_HEADER    header;
    CHAR16*             firmwareVendor;
    UINT32              firmwareRevision;
    EFI_HANDLE          consoleInHandle;
    VOID*               conIn;
    EFI_HANDLE          consoleOutHandle;
    EFI_TEXT_OUT_PROTO* conOut;
    EFI_HANDLE          stdErrHandle;
    EFI_TEXT_OUT_PROTO* stdErr;
    VOID*               runtimeServices;
    EFI_BOOT_SERVICES*  bootServices;
    UINTN               numTableEntries;
    EFI_CONFIG_TABLE*   configTable;
} EFI_SYSTEM_TABLE;

/* Entry point signature */
typedef EFI_STATUS (EFIAPI* EFI_IMAGE_ENTRY_POINT)(
    EFI_HANDLE imageHandle, 
    EFI_SYSTEM_TABLE* systemTable
);

#endif // _EFI_H