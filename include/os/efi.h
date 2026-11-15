#ifndef _EFI_H
#define _EFI_H

#include <stdint.h>

#if defined(__x86_64__) && !defined(_WIN32)
#define EFIAPI __attribute__((ms_abi))
#else
#define EFIAPI
#endif

#define EFI_ERR

/* Basic types */
typedef uint8_t BOOLEAN;
typedef uint16_t CHAR16;
typedef uintptr_t UINTN;
typedef uint64_t EFI_STATUS;
typedef void* EFI_HANDLE;


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

/* GUID */
typedef struct {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
} EFI_GUID;

#define EFI_ACPI_20_TABLE_GUID \
    {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}}

typedef struct {
    uint64_t signature;
    uint32_t revision;
    uint32_t headerSize;
    uint32_t CRC32;
    uint32_t reserved;
} EFI_TABLE_HEADER;

/* Simple Text Output */
struct EFI_TEXT_OUT_PROTO;
typedef EFI_STATUS (EFIAPI* EFI_TEXT_RESET)(
    struct EFI_TEXT_OUT_PROTO* This, BOOLEAN extendedVerification
);
typedef EFI_STATUS (EFIAPI*  EFI_TEXT_STRING)(
    struct EFI_TEXT_OUT_PROTO* This, CHAR16* String
);
typedef EFI_STATUS (EFIAPI* EFI_TEXT_CLEAR_SCREEN)(
    struct EFI_TEXT_OUT_PROTO* This
);

typedef struct EFI_TEXT_OUT_PROTO {
    EFI_TEXT_RESET reset;
    EFI_TEXT_STRING outStr;
    void* testStr;
    void* queryMode;
    void* setMode;
    void* setAttribute;
    EFI_TEXT_CLEAR_SCREEN clearScreen;
    void* setCursorPos;
    void* enableCursor;
    void* mode;  
};

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

typedef enum {
    allocateAnyPAges,
    allocateMaxAddress,
    allocateAddress,
    maxAllocateType
} EFI_ALLOCATE_TYPE;

typedef struct {
    uint32_t                type;
    uint32_t                pad;
    EFI_PHYSICAL_ADDRESS    physicalStart;
    EFI_VIRTUAL_ADDRESS     virtualStart;
    uint64_t                numPages;
    uint64_t                attribute;
} EFI_MEMORY_DESCRIPTOR;

/* Boot Services */
typedef EFI_STATUS (EFIAPI* EFI_ALLOCATE_PAGES)(
    EFI_ALLOCATE_TYPE type, EFI_MEMORY_TYPE memoryType, EFI_PHYSICAL_ADDRESS* memory
);
typedef EFI_STATUS (EFIAPI* EFI_FREE_PAGES)(
    EFI_PHYSICAL_ADDRESS memory, UINTN pages
);
typedef EFI_STATUS (EFIAPI* EFI_GET_MEMORY_MAP)(
    UINTN* memMapSize, EFI_MEMORY_DESCRIPTOR* memMap, UINTN* mapKey, UINTN* descSize, uint32_t descVer
);
typedef EFI_STATUS (EFIAPI* EFI_ALLOCATE_POOL)(
    EFI_MEMORY_TYPE poolType, UINTN size, void** buffer
);
typedef EFI_STATUS (EFIAPI* EFI_FREE_POOL)(
    void* buffer
);
typedef EFI_STATUS(EFIAPI* EFI_EXIT_BOOT_SERVICES)(
    EFI_HANDLE imageHandle, UINTN mapKey
);
typedef EFI_STATUS(EFIAPI* EFI_SET_WATCHDOG_TIMER)(
    UINTN timeout, uint64_t watchdogCode, UINTN dataSize, CHAR16* watchdogData
);
typedef EFI_STATUS (EFIAPI* EFI_LOCATE_PROTOCOL)(
    EFI_GUID* protocol, void* registration, void** interface
);
typedef EFI_STATUS (EFIAPI* EFI_HANDLE_PROTOCOL)(
    EFI_HANDLE handle, EFI_GUID* protocol, void **interface
);

typedef struct {
    EFI_TABLE_HEADER Header;
    // Task priority
    void* RaiseTPL;
    void* RestoreTPL;
    // Memory
    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP getMemoryMap;
    EFI_ALLOCATE_POOL AllocatePool;
    EFI_FREE_POOL FreePool;
    // Events
    void* CreateEvent;
    void* SetTimer;
    void* WaitForEvent;
    void* SignalEvent;
    void* CloseEvent;
    void* CheckEvent;
    // Protocol Handlers
    void* InstallProtocolInterface;
    void* ReinstallProtocolInterface;
    void* UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL HandleProtocol;
    void* Reserved;
    void* RegisterProtocolNotify;
    void* Locatehandle;
    void* LocateDevicePath;
    void* InstallConfigurationTable;
    // Image Services
    void* LoadImage;
    void* StartImage;
    void* Exit;
    void* UnloadImage;
    EFI_EXIT_BOOT_SERVICES ExitBootServices;
    // misc
    void* GetNextMonotonicCount;
    void* Stall;
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;
    // Driver Support
    void* ConnectController;
    void* DisconnectController;
    // Open/Close Protocol
    void* OpenProtocol;
    void* CloseProtocol;
    void* OpenProtocolInformation;
    // Library
    void* ProtocolsPerHandle;
    void* LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL LocateProtocol;
    void* InstallMultipleProtocolInterfaces;
    void* UninstallMultipleProtocolInterfaces;
    // CRC / Memory Utils
    void* CalculatorCrc32;
    void* CopyMem;
    void* SetMem;
    void* CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct {
    EFI_GUID    vendorGUID;
    void*       vendorTable;
} EFI_CONFIG_TABLE;

typedef struct {
    EFI_TABLE_HEADER    header;
    CHAR16*             firmwareVendor;
    uint32_t            firmwareRevision;
    EFI_HANDLE          consoleInHandle;
    void*               conIn;
    EFI_HANDLE          consoleOutHandle;
    // efi_simple_text_output_proto *conout
    EFI_HANDLE          stdErrHandle;
    // efi_simple_text_output_proto *stderr
    void*               runtimeServices;
    //efi_boot_services* bootServices
    UINTN               numTableEntries;
    EFI_CONFIG_TABLE*   configTable;
} EFI_SYSTEM_TABLE;

#endif // _EFI_H