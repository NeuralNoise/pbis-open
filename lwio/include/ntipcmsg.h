/* Editor Settings: expandtabs and use 4 spaces for indentation
 * ex: set softtabstop=4 tabstop=8 expandtab shiftwidth=4: *
 * -*- mode: c, c-basic-offset: 4 -*- */

/*
 * Copyright Likewise Software
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the license, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.  You should have received a copy
 * of the GNU Lesser General Public License along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 *
 * LIKEWISE SOFTWARE MAKES THIS SOFTWARE AVAILABLE UNDER OTHER LICENSING
 * TERMS AS WELL.  IF YOU HAVE ENTERED INTO A SEPARATE LICENSE AGREEMENT
 * WITH LIKEWISE SOFTWARE, THEN YOU MAY ELECT TO USE THE SOFTWARE UNDER THE
 * TERMS OF THAT SOFTWARE LICENSE AGREEMENT INSTEAD OF THE TERMS OF THE GNU
 * LESSER GENERAL PUBLIC LICENSE, NOTWITHSTANDING THE ABOVE NOTICE.  IF YOU
 * HAVE QUESTIONS, OR WISH TO REQUEST A COPY OF THE ALTERNATE LICENSING
 * TERMS OFFERED BY LIKEWISE SOFTWARE, PLEASE CONTACT LIKEWISE SOFTWARE AT
 * license@likewisesoftware.com
 */

/*
 * Copyright (C) Likewise Software. All rights reserved.
 *
 * Module Name:
 *
 *        ntipcmsg.h
 *
 * Abstract:
 *
 *        NT lwmsg IPC
 *
 * Authors: Danilo Almeida (dalmeida@likewisesoftware.com)
 */

#ifndef __NT_IPC_MSG_H__
#define __NT_IPC_MSG_H__

#include <lwmsg/lwmsg.h>
#include "lwiodef.h"
#include "lwioipc.h"
#include <lwio/io-types.h>

// TODO-Add async completion support.

// TODO-Add check in lwmsg to check for protocol tags > 16 bits.
// Apparently, the server crashed if you do that.
#define _NT_IPC_MESSAGE_TYPE_BASE 20

//
// Protocol Message Types
//
// The message types map to message structures like this:
//
//   NT_IPC_MESSAGE_TYPE_<XXX> --> NT_IPC_MESSAGE_<XXX>
//
// Any exceptions have a comment with the corresponding structure type.
//

typedef enum _NT_IPC_MESSAGE_TYPE
{
    NT_IPC_MESSAGE_TYPE_CREATE_FILE = _NT_IPC_MESSAGE_TYPE_BASE,
    NT_IPC_MESSAGE_TYPE_CREATE_FILE_RESULT,
    NT_IPC_MESSAGE_TYPE_CLOSE_FILE,                     // NT_IPC_MESSAGE_GENERIC_FILE
    NT_IPC_MESSAGE_TYPE_CLOSE_FILE_RESULT,              // NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
    NT_IPC_MESSAGE_TYPE_READ_FILE,
    NT_IPC_MESSAGE_TYPE_READ_FILE_RESULT,               // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_WRITE_FILE,
    NT_IPC_MESSAGE_TYPE_WRITE_FILE_RESULT,              // NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
    NT_IPC_MESSAGE_TYPE_DEVICE_IO_CONTROL_FILE,         // NT_IPC_MESSAGE_GENERIC_CONTROL_FILE
    NT_IPC_MESSAGE_TYPE_DEVICE_IO_CONTROL_FILE_RESULT,  // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_FS_CONTROL_FILE,                // NT_IPC_MESSAGE_GENERIC_CONTROL_FILE
    NT_IPC_MESSAGE_TYPE_FS_CONTROL_FILE_RESULT,         // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_FLUSH_BUFFERS_FILE,             // NT_IPC_MESSAGE_GENERIC_FILE
    NT_IPC_MESSAGE_TYPE_FLUSH_BUFFERS_FILE_RESULT,      // NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
    NT_IPC_MESSAGE_TYPE_QUERY_INFORMATION_FILE,
    NT_IPC_MESSAGE_TYPE_QUERY_INFORMATION_FILE_RESULT,  // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_SET_INFORMATION_FILE,
    NT_IPC_MESSAGE_TYPE_SET_INFORMATION_FILE_RESULT,    // NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
    NT_IPC_MESSAGE_TYPE_QUERY_DIRECTORY_FILE,
    NT_IPC_MESSAGE_TYPE_QUERY_DIRECTORY_FILE_RESULT,     // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_READ_DIRECTORY_CHANGE_FILE,
    NT_IPC_MESSAGE_TYPE_READ_DIRECTORY_CHANGE_FILE_RESULT, // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_QUERY_FS_INFORMATION_FILE,
    NT_IPC_MESSAGE_TYPE_QUERY_FS_INFORMATION_FILE_RESULT, // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_QUERY_VOLUME_INFORMATION_FILE,
    NT_IPC_MESSAGE_TYPE_QUERY_VOLUME_INFORMATION_FILE_RESULT, // NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
    NT_IPC_MESSAGE_TYPE_LOCK_FILE,
    NT_IPC_MESSAGE_TYPE_LOCK_FILE_RESULT, 
    NT_IPC_MESSAGE_TYPE_UNLOCK_FILE,
    NT_IPC_MESSAGE_TYPE_UNLOCK_FILE_RESULT,
    NT_IPC_MESSAGE_TYPE_QUERY_SECURITY_FILE,
    NT_IPC_MESSAGE_TYPE_QUERY_SECURITY_FILE_RESULT,
    NT_IPC_MESSAGE_TYPE_SET_SECURITY_FILE,
    NT_IPC_MESSAGE_TYPE_SET_SECURITY_FILE_RESULT
} NT_IPC_MESSAGE_TYPE, *PNT_IPC_MESSAGE_TYPE;

//
// Protocol Helper Types
//

typedef struct _NT_IPC_HELPER_ECP {
    IN PCSTR pszType;
    IN PVOID pData;
    IN ULONG Size;
} NT_IPC_HELPER_ECP, *PNT_IPC_HELPER_ECP;

//
// Protocol Messages
//

typedef struct _NT_IPC_MESSAGE_GENERIC_FILE {
    IN IO_FILE_HANDLE FileHandle;
} NT_IPC_MESSAGE_GENERIC_FILE, *PNT_IPC_MESSAGE_GENERIC_FILE;

typedef struct _NT_IPC_MESSAGE_GENERIC_CONTROL_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN ULONG ControlCode;
    IN PVOID InputBuffer;
    IN ULONG InputBufferLength;
    IN ULONG OutputBufferLength;
} NT_IPC_MESSAGE_GENERIC_CONTROL_FILE, *PNT_IPC_MESSAGE_GENERIC_CONTROL_FILE;

typedef struct _NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT {
    // From IO_STATUS_BLOCK (which uses context-based union):
    OUT NTSTATUS Status;
    OUT ULONG BytesTransferred;
} NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT, *PNT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT;

typedef struct _NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT {
    // Break up IO_STATUS_BLOCK into Status and BytesTransferred so that the
    // IPC marshaling layer can use BytesTransferred for the length of Buffer.

    // From IO_STATUS_BLOCK (which uses context-based union):
    OUT NTSTATUS Status;
    OUT ULONG BytesTransferred;

    // Length is BytesTransferred.
    OUT PVOID Buffer;
} NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT, *PNT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT;

//
// NtCreateFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_CREATE_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_CREATE_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_CREATE_FILE
// OUT: NT_IPC_MESSAGE_CREATE_FILE_RESULT
//

typedef struct _NT_IPC_MESSAGE_CREATE_FILE {
    IN PIO_CREDS pSecurityToken;
    IN IO_FILE_NAME FileName;
    IN ACCESS_MASK DesiredAccess;
    IN OPTIONAL LONG64 AllocationSize;
    IN FILE_ATTRIBUTES FileAttributes;
    IN FILE_SHARE_FLAGS ShareAccess;
    IN FILE_CREATE_DISPOSITION CreateDisposition;
    IN FILE_CREATE_OPTIONS CreateOptions;
    IN OPTIONAL PVOID EaBuffer; // FILE_FULL_EA_INFORMATION
    IN ULONG EaLength;
    IN OPTIONAL PSECURITY_DESCRIPTOR_RELATIVE SecurityDescriptor;
    IN ULONG SecDescLength;
#if 0
    // TODO -- Add stuff for QOS.
    IN OPTIONAL PVOID SecurityQualityOfService; // TBD
#endif
    IN OPTIONAL PNT_IPC_HELPER_ECP EcpList;
    IN ULONG EcpCount;
} NT_IPC_MESSAGE_CREATE_FILE, *PNT_IPC_MESSAGE_CREATE_FILE;

typedef struct _NT_IPC_MESSAGE_CREATE_FILE_RESULT {
    OUT IO_FILE_HANDLE FileHandle;

    // From IO_STATUS_BLOCK (which uses context-based union):
    OUT NTSTATUS Status;
    OUT FILE_CREATE_RESULT CreateResult;
} NT_IPC_MESSAGE_CREATE_FILE_RESULT, *PNT_IPC_MESSAGE_CREATE_FILE_RESULT;

//
// NtCloseFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_CLOSE_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_CLOSE_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_GENERIC_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
//

//
// NtReadFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_READ_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_READ_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_READ_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

typedef struct _NT_IPC_MESSAGE_READ_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN ULONG Length;
    IN OPTIONAL PLONG64 ByteOffset;
    IN OPTIONAL PULONG Key;
} NT_IPC_MESSAGE_READ_FILE, *PNT_IPC_MESSAGE_READ_FILE;

//
// NtWriteFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_WRITE_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_WRITE_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_READ_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
//

typedef struct _NT_IPC_MESSAGE_WRITE_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN PVOID Buffer;
    IN ULONG Length;
    IN OPTIONAL PLONG64 ByteOffset;
    IN OPTIONAL PULONG Key;
} NT_IPC_MESSAGE_WRITE_FILE, *PNT_IPC_MESSAGE_WRITE_FILE;

//
// NtDeviceIoControlFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_DEVICE_IO_CONTROL_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_DEVICE_IO_CONTROL_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_GENERIC_CONTROL_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

//
// NtFsControlFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_FS_CONTROL_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_FS_CONTROL_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_GENERIC_CONTROL_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

//
// NtFlushBuffersFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_FLUSH_BUFFERS_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_FLUSH_BUFFERS_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_GENERIC_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
//

//
// NtQueryInformationFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_QUERY_INFORMATION_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_QUERY_INFORMATION_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_QUERY_INFORMATION_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

typedef struct _NT_IPC_MESSAGE_QUERY_INFORMATION_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN ULONG Length;
    IN FILE_INFORMATION_CLASS FileInformationClass;
} NT_IPC_MESSAGE_QUERY_INFORMATION_FILE, *PNT_IPC_MESSAGE_QUERY_INFORMATION_FILE;

//
// NtSetInformationFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_SET_INFORMATION_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_SET_INFORMATION_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_SET_INFORMATION_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
//

typedef struct _NT_IPC_MESSAGE_SET_INFORMATION_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN PVOID FileInformation;
    IN ULONG Length;
    IN FILE_INFORMATION_CLASS FileInformationClass;
} NT_IPC_MESSAGE_SET_INFORMATION_FILE, *PNT_IPC_MESSAGE_SET_INFORMATION_FILE;

//
// NtQueryDirectoryFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_QUERY_DIRECTORY_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_QUERY_DIRECTORY_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_QUERY_DIRECTORY_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

typedef struct _NT_IPC_MESSAGE_QUERY_DIRECTORY_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN ULONG Length;
    IN FILE_INFORMATION_CLASS FileInformationClass;
    IN BOOLEAN ReturnSingleEntry;
    IN OPTIONAL PIO_MATCH_FILE_SPEC FileSpec;
    IN BOOLEAN RestartScan;
} NT_IPC_MESSAGE_QUERY_DIRECTORY_FILE, *PNT_IPC_MESSAGE_QUERY_DIRECTORY_FILE;

//
// NtReadDirectoryChangeFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_READ_DIRECTORY_CHANGE_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_READ_DIRECTORY_CHANGE_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_READ_DIRECTORY_CHANGE_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

typedef struct _NT_IPC_MESSAGE_READ_DIRECTORY_CHANGE_FILE {
    IN IO_FILE_HANDLE FileHandle;
    OUT PVOID Buffer;
    IN ULONG Length;
    IN BOOLEAN WatchTree;
    IN ULONG NotifyFilter;
    IN OPTIONAL PULONG MaxBufferSize;
} NT_IPC_MESSAGE_READ_DIRECTORY_CHANGE_FILE, *PNT_IPC_MESSAGE_READ_DIRECTORY_CHANGE_FILE;

//
// NtQueryVolumeInformation
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_QUERY_VOLUME_INFORMATION_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_QUERY_VOLUME_INFORMATION_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_QUERY_VOLUME_INFORMATION_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_BUFFER_RESULT
//

typedef struct _NT_IPC_MESSAGE_QUERY_VOLUME_INFORMATION_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN ULONG Length;
    IN FILE_INFORMATION_CLASS FsInformationClass;
} NT_IPC_MESSAGE_QUERY_VOLUME_INFORMATION_FILE, *PNT_IPC_MESSAGE_QUERY_VOLUME_INFORMATION_FILE;

//
// NtLockFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_LOCK_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_LOCK_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_LOCK_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
//

typedef struct _NT_IPC_MESSAGE_LOCK_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN LONG64 ByteOffset;
    IN LONG64 Length;
    IN ULONG Key;
    BOOLEAN FailImmediately;
    BOOLEAN ExclusiveLock;	
} NT_IPC_MESSAGE_LOCK_FILE, *PNT_IPC_MESSAGE_LOCK_FILE;

//
// NtUnlockFile
//
// IN TAG:  NT_IPC_MESSAGE_TYPE_UNLOCK_FILE
// OUT TAG: NT_IPC_MESSAGE_TYPE_UNLOCK_FILE_RESULT
//
// IN:  NT_IPC_MESSAGE_UNLOCK_FILE
// OUT: NT_IPC_MESSAGE_GENERIC_FILE_IO_RESULT
//

typedef struct _NT_IPC_MESSAGE_UNLOCK_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN LONG64 ByteOffset;
    IN LONG64 Length;
    IN ULONG Key;
} NT_IPC_MESSAGE_UNLOCK_FILE, *PNT_IPC_MESSAGE_UNLOCK_FILE;

typedef struct _NT_IPC_MESSAGE_QUERY_SECURITY_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN SECURITY_INFORMATION SecurityInformation;
    IN ULONG Length;
} NT_IPC_MESSAGE_QUERY_SECURITY_FILE, *PNT_IPC_MESSAGE_QUERY_SECURITY_FILE;

typedef struct _NT_IPC_MESSAGE_SET_SECURITY_FILE {
    IN IO_FILE_HANDLE FileHandle;
    IN SECURITY_INFORMATION SecurityInformation;
    IN PSECURITY_DESCRIPTOR_RELATIVE SecurityDescriptor;
    IN ULONG Length;
} NT_IPC_MESSAGE_SET_SECURITY_FILE, *PNT_IPC_MESSAGE_SET_SECURITY_FILE;

//
// Functions
//

NTSTATUS
NtIpcLWMsgStatusToNtStatus(
    IN LWMsgStatus LwMsgStatus
    );

LWMsgStatus
NtIpcNtStatusToLWMsgStatus(
    IN NTSTATUS Status
    );

NTSTATUS
NtIpcAddProtocolSpec(
    IN OUT LWMsgProtocol* pProtocol
    );

NTSTATUS
NtIpcAddProtocolSpecEx(
    IN OUT LWMsgProtocol* pProtocol,
    OUT OPTIONAL PCSTR* ppszError
    );

NTSTATUS
NtIpcUnregisterFileHandle(
    IN LWMsgCall* pCall,
    IN IO_FILE_HANDLE FileHandle
    );

NTSTATUS
NtIpcReleaseFileHandle(
    IN LWMsgCall* pCall,
    IN IO_FILE_HANDLE FileHandle
    );

#endif /* __NT_IPC_MSG_H__ */


 
/*
local variables:
mode: c
c-basic-offset: 4
indent-tabs-mode: nil
tab-width: 4
end:
*/
 
