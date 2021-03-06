/*
** NetXMS - Network Management System
** Copyright (C) 2003-2014 Victor Kirhenshtein
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** File: nms_common.h
**
**/

#ifndef _nms_common_h_
#define _nms_common_h_

#ifdef WIN32
#ifndef _WIN32
#define _WIN32
#endif
#endif

#ifdef __SYMBIAN32__

// Symbian compiler defines _WIN32 in builds for emulator.
#undef _WIN32

#else

#if !defined(_WIN32) && !defined(UNDER_CE)

#ifdef _NETWARE
#include <config-netware.h>
#else
#include <config.h>
#ifdef WITH_OPENSSL
#define _WITH_ENCRYPTION   1
#endif
#endif

#else    /* _WIN32 */

#ifndef UNDER_CE
#define _WITH_ENCRYPTION   1
#define WITH_LDAP          1
#if !defined(WINDOWS_ONLY) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE
#endif
#endif

#endif

#endif	/* __SYMBIAN32__ */

#if HAVE_JEMALLOC_JEMALLOC_H
#include <jemalloc/jemalloc.h>
#endif

#ifdef HAVE_STDARG_H
#include <stdarg.h>
#endif

#include <unicode.h>

#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <netxms-version.h>

#if HAVE_WIDEC_H
#include <widec.h>
#endif // HAVE_WIDEC

/**
 * Define __64BIT__ if compiling for 64bit platform with Visual C++
 */
#if defined(_M_X64) || defined(_M_IA64) || defined(__LP64__) || defined(__PPC64__) || defined(__x86_64__)
#ifndef __64BIT__
#define __64BIT__
#endif
#endif

/**
 * Wrappers for 64-bit integer constants
 */
#if defined(__GNUC__) || defined(__HP_aCC) || defined(__IBMC__) || defined(__IBMCPP__) || defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define _LL(x) (x ## LL)
#define _ULL(x) (x ## ULL)
#elif defined(_MSC_VER)
#define _LL(x) (x ## i64)
#define _ULL(x) (x ## ui64)
#else
#define _LL(x) (x)
#define _ULL(x) (x)
#endif

/**
 * Common constants
 */
#define MAX_SECRET_LENGTH        64
#define MAX_DB_STRING            256
#define MAX_PARAM_NAME           256
#define MAX_CONFIG_VALUE         2000
#define MAX_COLUMN_NAME          64
#define MAX_DNS_NAME             256
#define MAX_HELPDESK_REF_LEN     64
#define MAX_PASSWORD             48
#define GROUP_FLAG               ((UINT32)0x80000000)
#define MAX_LVM_NAME_LEN 			128

#define NETXMS_MAX_CIPHERS       6
#define NETXMS_RSA_KEYLEN        2048

#ifndef LLONG_MAX
#define LLONG_MAX    _LL(9223372036854775807)
#endif

#ifndef LLONG_MIN
#define LLONG_MIN    (-LLONG_MAX - 1)
#endif

#ifndef ULLONG_MAX
#define ULLONG_MAX   _ULL(18446744073709551615)
#endif

#ifndef EVENTLOG_DEBUG_TYPE
#define EVENTLOG_DEBUG_TYPE		0x0080
#endif

#define INVALID_INDEX         0xFFFFFFFF
#define MD5_DIGEST_SIZE       16
#define SHA1_DIGEST_SIZE      20
#define SHA256_DIGEST_SIZE    32

#define FILE_BUFFER_SIZE      32768

/**
 * Compatibility defines for C sources
 */
#if !defined(__cplusplus) && !defined(CORTEX)
typedef int bool;
#endif

/**
 * Oracle Pro*C compatibility
 */
#ifdef ORA_PROC
#undef BYTE
#undef DWORD
#endif


/***** Platform dependent includes and defines *****/

#if defined(_WIN32) || defined(UNDER_CE)

/********** WINDOWS ********************/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT		0x0501
#endif

#define WITH_IPV6               1

#define USE_BUNDLED_LIBTRE      1
#define USE_BUNDLED_GETOPT      1

#define SAFE_FGETWS_WITH_POPEN  1

#define FS_PATH_SEPARATOR       _T("\\")
#define FS_PATH_SEPARATOR_A     "\\"
#define FS_PATH_SEPARATOR_W     L"\\"
#define FS_PATH_SEPARATOR_CHAR  _T('\\')

#define WEXITSTATUS(x)          (x)

#if _MSC_VER > 1300
#define HAVE_SCPRINTF           1
#define HAVE_VSCPRINTF          1
#define HAVE_SCWPRINTF          1
#define HAVE_VSCWPRINTF         1
#endif

#define HAVE_SNPRINTF           1
#define HAVE_VSNPRINTF          1

#define HAVE_GETADDRINFO        1

#define HAVE_STDARG_H           1

#define HAVE_ALLOCA             1

#ifndef va_copy
#define va_copy(x,y)            (x = y)
#endif
#define HAVE_DECL_VA_COPY       1

#define HAVE_LIBCURL            1

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef UNDER_CE
#include <sys/stat.h>
#include <process.h>
#include <io.h>
#include <fcntl.h>
#include <direct.h>
#endif

#ifndef S_IRUSR
# define S_IRUSR      0400
#endif
#ifndef S_IWUSR
# define S_IWUSR      0200
#endif

#define snprintf     _snprintf
#define vsnprintf    _vsnprintf
#define snwprintf    _snwprintf
#define vsnwprintf   _vsnwprintf
#define scprintf     _scprintf
#define vscprintf    _vscprintf
#define scwprintf    _scwprintf
#define vscwprintf   _vscwprintf
#define popen        _popen
#define pclose       _pclose
#define stricmp      _stricmp
#define strnicmp     _strnicmp
#define strupr(s)    _strupr(s)
#define getpid       _getpid
#define fileno(f)    _fileno(f)
#define chdir(p)     _chdir(p)
#define mkdir(p,m)   _mkdir(p,m)
#define lseek(f,o,w) _lseek(f,o,w)
#define unlink(x)    _unlink(x)

typedef UINT64 QWORD;   // for compatibility
typedef int socklen_t;
typedef long pid_t;
typedef LONG ssize_t;

typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#define INT64_FMT			_T("%I64d")
#define INT64_FMTA		"%I64d"
#define INT64_FMTW		L"%I64d"
#define UINT64_FMT		_T("%I64u")
#define UINT64_FMTA		"%I64u"
#define UINT64_FMTW		L"%I64u"
#define UINT64X_FMT(m)  _T("%") m _T("I64X")
#if defined(__64BIT__) || (_MSC_VER > 1300)
#define TIME_T_FMT      _T("%I64u")
#define TIME_T_FCAST(x) ((UINT64)(x))
#else
#define TIME_T_FMT      _T("%u")
#define TIME_T_FCAST(x) ((UINT32)(x))
#endif

// Socket compatibility
#define SHUT_RD      0
#define SHUT_WR      1
#define SHUT_RDWR    2

#define SetSocketReuseFlag(s) { \
	BOOL val = TRUE; \
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(BOOL)); \
}
#define SetSocketExclusiveAddrUse(s) { \
	BOOL val = TRUE; \
	setsockopt(s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *)&val, sizeof(BOOL)); \
}
#define SELECT_NFDS(x)  ((int)(x))
#define SetSocketNonBlocking(s) { \
	u_long one = 1; \
	ioctlsocket(s, FIONBIO, &one); \
}
#define SetSocketBlocking(s) { \
	u_long zero = 0; \
	ioctlsocket(s, FIONBIO, &zero); \
}
#define SetSocketNoDelay(s) { \
	BOOL val = TRUE; \
	setsockopt(s,  IPPROTO_TCP, TCP_NODELAY, (char *)&val, sizeof(BOOL)); \
}
#define SetSocketBroadcast(s) { \
	BOOL val = TRUE; \
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *)&val, sizeof(BOOL)); \
}

#ifdef UNDER_CE
#define O_RDONLY     0x0004
#define O_WRONLY     0x0001
#define O_RDWR       0x0002
#define O_CREAT      0x0100
#define O_EXCL       0x0200
#define O_TRUNC      0x0800
#endif

#if !defined(UNDER_CE)
#define HAVE_LIBEXPAT  1
#endif

#define XMPP_SUPPORTED 1

#define HAVE_LOCALE_H  1
#define HAVE_SETLOCALE 1

// Use Win32 API instead of msvcrt for memory allocation
#ifdef USE_WIN32_HEAP

#define malloc(n)       HeapAlloc(GetProcessHeap(), 0, n)
#define realloc(p, n)   (((p) == NULL) ? HeapAlloc(GetProcessHeap(), 0, n) : HeapReAlloc(GetProcessHeap(), 0, p, n))
#define free(p)         HeapFree(GetProcessHeap(), 0, p)
#define _tcsdup(s)      nx__tcsdup(s)
#define wcsdup(s)       nx_wcsdup(s)

#undef _tcsdup
#ifdef UNICODE
#define _tcsdup         nx_wcsdup
#else
#define _tcsdup         nx_strdup
#endif

#else

#define strdup       _strdup
#define wcsdup       _wcsdup

#endif

#elif defined(_NETWARE)

/********** NETWARE ********************/

#define FS_PATH_SEPARATOR       _T("/")
#define FS_PATH_SEPARATOR_A     "/"
#define FS_PATH_SEPARATOR_W     L"/"
#define FS_PATH_SEPARATOR_CHAR  _T('/')

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <wchar.h>
#include <netdb.h>

typedef int BOOL;
#if (SIZEOF_LONG == 4)
typedef long INT32;
#else
typedef int INT32;
#endif
#if (SIZEOF_LONG == 4)
typedef unsigned long UINT32;
#else
typedef unsigned int UINT32;
#endif
typedef INT32 LONG;
typedef UINT32 DWORD;
typedef unsigned short UINT16;
typedef UINT16 WORD;
typedef unsigned char BYTE;
typedef void * HANDLE;
typedef void * HMODULE;

#ifdef X_INT64_X
typedef X_INT64_X INT64;
#else
#error Target system does not have signed 64bit integer type
#endif

#ifdef X_UINT64_X
typedef X_UINT64_X UINT64;
typedef UINT64 QWORD;
#else
#error Target system does not have unsigned 64bit integer type
#endif

#define INT64_FMT			_T("%lld")
#define INT64_FMTW		L"%lld"
#define INT64_FMTA		"%lld"
#define UINT64_FMT		_T("%llu")
#define UINT64_FMTW		L"%llu"
#define UINT64_FMTA		"%llu"
#define UINT64X_FMT(m)  _T("%") m _T("llX")
#define TIME_T_FMT		_T("%u")
#define TIME_T_FCAST(x) ((UINT32)(x))

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

// Socket compatibility
typedef int SOCKET;

#define closesocket(x) close(x)
#define WSAGetLastError() (errno)

#define WSAEINTR        EINTR
#define WSAEWOULDBLOCK  EWOULDBLOCK
#define WSAEINPROGRESS  EINPROGRESS
#define WSAESHUTDOWN    ESHUTDOWN
#define INVALID_SOCKET  (-1)

#define SetSocketReuseFlag(sd) { \
	int nVal = 1; \
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const void *)&nVal,  \
			(socklen_t)sizeof(nVal)); \
}

#define SetSocketExclusiveAddrUse(s)

#define SetSocketNonBlocking(s) { \
   int f = fcntl(s, F_GETFL); \
   if (f != -1) fcntl(s, F_SETFL, f | O_NONBLOCK); \
}

#define SetSocketNoDelay(s) { \
	int val = 1; \
	setsockopt(s,  IPPROTO_TCP, TCP_NODELAY, (char *)&val, sizeof(int)); \
}

#define SetSocketBroadcast(s) { \
	int val = 1; \
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *)&val, sizeof(int)); \
}

#define SELECT_NFDS(x)  (x)

#else    /* not _WIN32 or _NETWARE */

/*********** UNIX *********************/

#ifndef PREFIX
#ifdef UNICODE
#define PREFIX    L"/usr/local"
#else
#define PREFIX		"/usr/local"
#endif
#warning Installation prefix not defined, defaulting to /usr/local
#endif

#if HAVE_ALLOCA_H
#include <alloca.h>
#endif

#if HAVE_WCHAR_H
#include <wchar.h>
#endif

#if HAVE_WCTYPE_H
#include <wctype.h>
#endif

#include <errno.h>

#define FS_PATH_SEPARATOR       _T("/")
#define FS_PATH_SEPARATOR_A     "/"
#define FS_PATH_SEPARATOR_W     L"/"
#define FS_PATH_SEPARATOR_CHAR  _T('/')

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif

#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#if HAVE_SYS_INT_TYPES_H
#include <sys/int_types.h>
#endif

#if HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if HAVE_NETINET_TCP_H
#include <netinet/tcp.h>
#endif

#if HAVE_NET_NH_H
#include <net/nh.h>
#endif

#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#if HAVE_NETDB_H
#include <netdb.h>
#endif

#if HAVE_FCNTL_H
#include <fcntl.h>
#endif

#include <dirent.h>

#if _USE_GNU_PTH
#include <pth.h>
#endif

#ifdef __sun
#include <sys/atomic.h>
#endif

#if defined(__HP_aCC) && HAVE_ATOMIC_H
#include <atomic.h>
#endif

#ifdef __IBMCPP__
#include <builtins.h>
#endif

#ifdef __minix
#undef HAVE_ITOA  /* Minix has non-compatible itoa() */
#undef HAVE_GETHOSTBYNAME2_R
#endif

#include <sys/socket.h>
#include <sys/un.h>

typedef int BOOL;
#if (SIZEOF_LONG == 4)
#if (SIZEOF_INT == 4)
typedef int INT32;
typedef unsigned int UINT32;
#else
typedef long INT32;
typedef unsigned long UINT32;
#endif
#undef __64BIT__
#else
typedef int INT32;
typedef unsigned int UINT32;
#ifndef __64BIT__
#define __64BIT__
#endif
#endif
typedef unsigned short UINT16;
typedef short INT16;
typedef unsigned char BYTE;
typedef INT32 LONG;  // for compatibility
typedef UINT32 DWORD;  // for compatibility
typedef UINT16 WORD;  // for compatibility
typedef void * HANDLE;
typedef void * HMODULE;

#if !HAVE_MODE_T
typedef int mode_t;
#endif

// We have to use long as INT64 on HP-UX - otherwise
// there will be compilation errors because of type redefinition in
// system includes
#ifdef _HPUX

#ifdef __LP64__
typedef long INT64;
typedef unsigned long UINT64;
#else
typedef long long INT64;
typedef unsigned long long UINT64;
#endif

#else    /* _HPUX */

#if HAVE_LONG_LONG && (SIZEOF_LONG_LONG == 8)
typedef long long INT64;
#elif HAVE_INT64_T
typedef int64_t INT64;
#elif SIZEOF_LONG == 8
typedef long INT64;
#else
#error Target system does not have signed 64bit integer type
#endif

#if HAVE_UNSIGNED_LONG_LONG && (SIZEOF_LONG_LONG == 8)
typedef unsigned long long UINT64;
#elif HAVE_UINT64_T
typedef uint64_t UINT64;
#elif HAVE_U_INT64_T
typedef u_int64_t UINT64;
#elif SIZEOF_LONG == 8
typedef unsigned long UINT64;
#else
#error Target system does not have unsigned 64bit integer type
#endif

#endif   /* _HPUX */

typedef UINT64 QWORD;   // for compatibility

#define INT64_FMT			_T("%lld")
#define INT64_FMTW		L"%lld"
#define INT64_FMTA		"%lld"
#define UINT64_FMT		_T("%llu")
#define UINT64_FMTW		L"%llu"
#define UINT64_FMTA		"%llu"
#define UINT64X_FMT(m)  _T("%") m _T("llX")
#ifdef __64BIT__
#define TIME_T_FMT		_T("%llu")
#define TIME_T_FCAST(x)         ((UINT64)(x))
#else
#define TIME_T_FMT		_T("%u")
#define TIME_T_FCAST(x)         ((UINT32)(x))
#endif

#ifndef TRUE
#define TRUE   1
#endif
#ifndef FALSE
#define FALSE  0
#endif

#ifndef MAX_PATH
#ifdef PATH_MAX
#define MAX_PATH PATH_MAX
#else
#define MAX_PATH 1024
#endif
#endif

// Socket compatibility
typedef int SOCKET;

#define closesocket(x) close(x)
#define WSAGetLastError() (errno)

#define WSAEINTR        EINTR
#define WSAEWOULDBLOCK  EWOULDBLOCK
#define WSAEINPROGRESS  EINPROGRESS
#define WSAESHUTDOWN    ESHUTDOWN
#define INVALID_SOCKET  (-1)

#define SetSocketReuseFlag(sd) { \
	int nVal = 1; \
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const void *)&nVal,  \
			(socklen_t)sizeof(nVal)); \
}

#define SetSocketExclusiveAddrUse(s)

#define SetSocketNonBlocking(s) { \
   int f = fcntl(s, F_GETFL); \
   if (f != -1) fcntl(s, F_SETFL, f | O_NONBLOCK); \
}

#define SetSocketNoDelay(s) { \
	int val = 1; \
	setsockopt(s,  IPPROTO_TCP, TCP_NODELAY, (const void *)&val, sizeof(int)); \
}

#define SetSocketBroadcast(s) { \
	int val = 1; \
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, (const void *)&val, sizeof(int)); \
}

#define SELECT_NFDS(x)  (x)

#if !(HAVE_SOCKLEN_T) && !defined(_USE_GNU_PTH)
typedef unsigned int socklen_t;
#endif

#ifndef SUN_LEN
#define SUN_LEN(su) (sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif

// Shared library suffix
#ifndef SHLIB_SUFFIX
#if defined(_HPUX) && !defined(__64BIT__)
#define SHLIB_SUFFIX	_T(".sl")
#else
#define SHLIB_SUFFIX	_T(".so")
#endif
#endif

typedef struct hostent HOSTENT;

#if HAVE_DECL___VA_COPY && !HAVE_DECL_VA_COPY
#define HAVE_DECL_VA_COPY 1
#define va_copy(d,s) __va_copy(d,s)
#endif

#endif   /* _WIN32 */

/**
 * Value used to indicate invalid pointer where NULL is not appropriate
 */
#ifdef __64BIT__
#define INVALID_POINTER_VALUE    ((void *)_ULL(0xFFFFFFFFFFFFFFFF))
#else
#define INVALID_POINTER_VALUE    ((void *)0xFFFFFFFF)
#endif

/**
 * Casting between pointer and 32-bit integer
 */
#ifdef __64BIT__
#define CAST_FROM_POINTER(p, t) ((t)((UINT64)(p)))
#define CAST_TO_POINTER(v, t) ((t)((UINT64)(v)))
#else
#define CAST_FROM_POINTER(p, t) ((t)(p))
#define CAST_TO_POINTER(v, t) ((t)(v))
#endif

/**
 * OpenSSL
 */
#if defined(_WITH_ENCRYPTION) && !defined(ORA_PROC)

#include <openssl/crypto.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/opensslv.h>
#include <openssl/err.h>

#ifdef NETXMS_NO_AES
#ifndef OPENSSL_NO_AES
#define OPENSSL_NO_AES
#endif
#endif

#ifdef NETXMS_NO_BF
#ifndef OPENSSL_NO_BF
#define OPENSSL_NO_BF
#endif
#endif

#ifdef NETXMS_NO_IDEA
#ifndef OPENSSL_NO_IDEA
#define OPENSSL_NO_IDEA
#endif
#endif

#ifdef NETXMS_NO_DES
#ifndef OPENSSL_NO_DES
#define OPENSSL_NO_DES
#endif
#endif

#if OPENSSL_VERSION_NUMBER >= 0x00907000
#define OPENSSL_CONST const
#else
#define OPENSSL_CONST
#endif

#else

// Prevent compilation errors on function prototypes
#define RSA void

#endif

/**
 * open() flags compatibility
 */
#ifndef O_BINARY
#define O_BINARY 0
#endif

/**
 * Windows-specific structures for non-Windows platforms
 */
#ifndef _WIN32

typedef struct tagPOINT
{
   int x;
   int y;
} POINT;

#endif

/**
 * Event log severity codes
 */
#ifndef _WIN32
#define EVENTLOG_SUCCESS                0x0000
#define EVENTLOG_ERROR_TYPE             0x0001
#define EVENTLOG_WARNING_TYPE           0x0002
#define EVENTLOG_INFORMATION_TYPE       0x0004
#define EVENTLOG_AUDIT_SUCCESS          0x0008
#define EVENTLOG_AUDIT_FAILURE          0x0010
#endif   /* _WIN32 */

#define NXLOG_DEBUG     EVENTLOG_DEBUG_TYPE
#define NXLOG_INFO      EVENTLOG_INFORMATION_TYPE
#define NXLOG_WARNING   EVENTLOG_WARNING_TYPE
#define NXLOG_ERROR     EVENTLOG_ERROR_TYPE

/**
 * Interface types
 */
#define IFTYPE_OTHER                      1
#define IFTYPE_REGULAR1822                2
#define IFTYPE_HDH1822                    3
#define IFTYPE_DDN_X25                    4
#define IFTYPE_RFC877_X25                 5
#define IFTYPE_ETHERNET_CSMACD            6
#define IFTYPE_ISO88023_CSMACD            7
#define IFTYPE_ISO88024_TOKENBUS          8
#define IFTYPE_ISO88025_TOKENRING         9
#define IFTYPE_ISO88026_MAN               10
#define IFTYPE_STARLAN                    11
#define IFTYPE_PROTEON_10MBIT             12
#define IFTYPE_PROTEON_80MBIT             13
#define IFTYPE_HYPERCHANNEL               14
#define IFTYPE_FDDI                       15
#define IFTYPE_LAPB                       16
#define IFTYPE_SDLC                       17
#define IFTYPE_DS1                        18
#define IFTYPE_E1                         19
#define IFTYPE_BASIC_ISDN                 20
#define IFTYPE_PRIMARY_ISDN               21
#define IFTYPE_PROP_PTP_SERIAL            22
#define IFTYPE_PPP                        23
#define IFTYPE_SOFTWARE_LOOPBACK          24
#define IFTYPE_EON                        25
#define IFTYPE_ETHERNET_3MBIT             26
#define IFTYPE_NSIP                       27
#define IFTYPE_SLIP                       28
#define IFTYPE_ULTRA                      29
#define IFTYPE_DS3                        30
#define IFTYPE_SMDS                       31
#define IFTYPE_FRAME_RELAY                32
#define IFTYPE_RS232                      33
#define IFTYPE_PARA                       34
#define IFTYPE_ARCNET                     35
#define IFTYPE_ARCNET_PLUS                36
#define IFTYPE_ATM                        37
#define IFTYPE_MIOX25                     38
#define IFTYPE_SONET                      39
#define IFTYPE_X25PLE                     40
#define IFTYPE_ISO88022LLC                41
#define IFTYPE_LOCALTALK                  42
#define IFTYPE_SMDS_DXI                   43
#define IFTYPE_FRAME_RELAY_SERVICE        44
#define IFTYPE_V35                        45
#define IFTYPE_HSSI                       46
#define IFTYPE_HIPPI                      47
#define IFTYPE_MODEM                      48
#define IFTYPE_AAL5                       49
#define IFTYPE_SONET_PATH                 50
#define IFTYPE_SONET_VT                   51
#define IFTYPE_SMDS_ICIP                  52
#define IFTYPE_PROP_VIRTUAL               53
#define IFTYPE_PROP_MULTIPLEXOR           54
#define IFTYPE_IEEE80212                  55
#define IFTYPE_FIBRECHANNEL               56
#define IFTYPE_HIPPIINTERFACE             57
#define IFTYPE_FRAME_RELAY_INTERCONNECT   58
#define IFTYPE_AFLANE8023                 59
#define IFTYPE_AFLANE8025                 60
#define IFTYPE_CCTEMUL                    61
#define IFTYPE_FAST_ETHERNET              62
#define IFTYPE_ISDN                       63
#define IFTYPE_V11                        64
#define IFTYPE_V36                        65
#define IFTYPE_G703_AT64K                 66
#define IFTYPE_G703_AT2MB                 67
#define IFTYPE_QLLC                       68
#define IFTYPE_FASTETHERFX                69
#define IFTYPE_CHANNEL                    70
#define IFTYPE_IEEE80211                  71
#define IFTYPE_IBM370_PARCHAN             72
#define IFTYPE_ESCON                      73
#define IFTYPE_DLSW                       74
#define IFTYPE_ISDNS                      75
#define IFTYPE_ISDNU                      76
#define IFTYPE_LAPD                       77
#define IFTYPE_IPSWITCH                   78
#define IFTYPE_RSRB                       79
#define IFTYPE_ATMLOGICAL                 80
#define IFTYPE_DS0                        81
#define IFTYPE_DS0_BUNDLE                 82
#define IFTYPE_BSC                        83
#define IFTYPE_ASYNC                      84
#define IFTYPE_CNR                        85
#define IFTYPE_ISO88025DTR                86
#define IFTYPE_EPLRS                      87
#define IFTYPE_ARAP                       88
#define IFTYPE_PROPCNLS                   89
#define IFTYPE_HOSTPAD                    90
#define IFTYPE_TERMPAD                    91
#define IFTYPE_FRAME_RELAY_MPI            92
#define IFTYPE_X213                       93
#define IFTYPE_ADSL                       94
#define IFTYPE_RADSL                      95
#define IFTYPE_SDSL                       96
#define IFTYPE_VDSL                       97
#define IFTYPE_ISO88025CRFPINT            98
#define IFTYPE_MYRINET                    99
#define IFTYPE_VOICEEM                    100
#define IFTYPE_VOICEFXO                   101
#define IFTYPE_VOICEFXS                   102
#define IFTYPE_VOICEENCAP                 103
#define IFTYPE_VOICEOVERIP                104
#define IFTYPE_ATMDXI                     105
#define IFTYPE_ATMFUNI                    106
#define IFTYPE_ATMIMA                     107
#define IFTYPE_PPPMULTILINKBUNDLE         108
#define IFTYPE_IPOVERCDLC                 109
#define IFTYPE_IPOVERCLAW                 110
#define IFTYPE_STACKTOSTACK               111
#define IFTYPE_VIRTUAL_IP_ADDRESS         112
#define IFTYPE_MPC                        113
#define IFTYPE_IPOVERATM                  114
#define IFTYPE_ISO88025FIBER              115
#define IFTYPE_TDLC                       116
#define IFTYPE_GIGABIT_ETHERNET           117
#define IFTYPE_HDLC                       118
#define IFTYPE_LAPF                       119
#define IFTYPE_V37                        120
#define IFTYPE_X25MLP                     121
#define IFTYPE_X25_HUNT_GROUP             122
#define IFTYPE_TRANSPHDLC                 123
#define IFTYPE_INTERLEAVE                 124
#define IFTYPE_FAST                       125
#define IFTYPE_IP                         126
#define IFTYPE_DOCSCABLE_MACLAYER         127
#define IFTYPE_DOCSCABLE_DOWNSTREAM       128
#define IFTYPE_DOCSCABLE_UPSTREAM         129
#define IFTYPE_A12MPPSWITCH               130
#define IFTYPE_TUNNEL                     131
#define IFTYPE_COFFEE                     132
#define IFTYPE_CES                        133
#define IFTYPE_ATM_SUBINTERFACE           134
#define IFTYPE_L2VLAN                     135
#define IFTYPE_L3IPVLAN                   136
#define IFTYPE_L3IPXVLAN                  137
#define IFTYPE_DIGITAL_POWERLINE          138
#define IFTYPE_MEDIAMAIL_OVER_IP          139
#define IFTYPE_DTM                        140
#define IFTYPE_DCN                        141
#define IFTYPE_IPFORWARD                  142
#define IFTYPE_MSDSL                      143
#define IFTYPE_IEEE1394                   144
#define IFTYPE_GSN                        145
#define IFTYPE_DVBRCC_MACLAYER            146
#define IFTYPE_DVBRCC_DOWNSTREAM          147
#define IFTYPE_DVBRCC_UPSTREAM            148
#define IFTYPE_ATM_VIRTUAL                149
#define IFTYPE_MPLS_TUNNEL                150
#define IFTYPE_SRP                        151
#define IFTYPE_VOICE_OVER_ATM             152
#define IFTYPE_VOICE_OVER_FRAME_RELAY     153
#define IFTYPE_IDSL                       154
#define IFTYPE_COMPOSITE_LINK             155
#define IFTYPE_SS7_SIGLINK                156
#define IFTYPE_PROPWIRELESSP2P            157
#define IFTYPE_FRFORWARD                  158
#define IFTYPE_RFC1483                    159
#define IFTYPE_USB                        160
#define IFTYPE_IEEE8023ADLAG              161
#define IFTYPE_BGP_POLICY_ACCOUNTING      162
#define IFTYPE_FRF16MFR_BUNDLE            163
#define IFTYPE_H323_GATEKEEPER            164
#define IFTYPE_H323_PROXY                 165
#define IFTYPE_MPLS                       166
#define IFTYPE_MFSIGLINK                  167
#define IFTYPE_HDSL2                      168
#define IFTYPE_SHDSL                      169
#define IFTYPE_DS1FDL                     170
#define IFTYPE_POS                        171
#define IFTYPE_DVBASI_IN                  172
#define IFTYPE_DVBASI_OUT                 173
#define IFTYPE_PLC                        174
#define IFTYPE_NFAS                       175
#define IFTYPE_TR008                      176
#define IFTYPE_GR303RDT                   177
#define IFTYPE_GR303IDT                   178
#define IFTYPE_ISUP                       179
#define IFTYPE_PROPDOCSWIRELESSMACLAYER   180
#define IFTYPE_PROPDOCSWIRELESSDOWNSTREAM 181
#define IFTYPE_PROPDOCSWIRELESSUPSTREAM   182
#define IFTYPE_HIPERLAN2                  183
#define IFTYPE_PROPBWAP2MP                184
#define IFTYPE_SONET_OVERHEAD_CHANNEL     185
#define IFTYPE_DW_OVERHEAD_CHANNEL        186
#define IFTYPE_AAL2                       187
#define IFTYPE_RADIOMAC                   188
#define IFTYPE_ATMRADIO                   189
#define IFTYPE_IMT                        190
#define IFTYPE_MVL                        191
#define IFTYPE_REACHDSL                   192
#define IFTYPE_FRDLCIENDPT                193
#define IFTYPE_ATMVCIENDPT                194
#define IFTYPE_OPTICAL_CHANNEL            195
#define IFTYPE_OPTICAL_TRANSPORT          196
#define IFTYPE_PROPATM                    197
#define IFTYPE_VOICE_OVER_CABLE           198
#define IFTYPE_INFINIBAND                 199
#define IFTYPE_TELINK                     200
#define IFTYPE_Q2931                      201
#define IFTYPE_VIRTUALTG                  202
#define IFTYPE_SIPTG                      203
#define IFTYPE_SIPSIG                     204
#define IFTYPE_DOCSCABLEUPSTREAMCHANNEL   205
#define IFTYPE_ECONET                     206
#define IFTYPE_PON155                     207
#define IFTYPE_PON622                     208
#define IFTYPE_BRIDGE                     209
#define IFTYPE_LINEGROUP                  210
#define IFTYPE_VOICEEMFGD                 211
#define IFTYPE_VOICEFGDEANA               212
#define IFTYPE_VOICEDID                   213
#define IFTYPE_MPEG_TRANSPORT             214
#define IFTYPE_SIXTOFOUR                  215
#define IFTYPE_GTP                        216
#define IFTYPE_PDNETHERLOOP1              217
#define IFTYPE_PDNETHERLOOP2              218
#define IFTYPE_OPTICAL_CHANNEL_GROUP      219
#define IFTYPE_HOMEPNA                    220
#define IFTYPE_GFP                        221
#define IFTYPE_CISCO_ISL_VLAN             222
#define IFTYPE_ACTELIS_METALOOP           223
#define IFTYPE_FCIPLINK                   224
#define IFTYPE_RPR                        225
#define IFTYPE_QAM                        226
#define IFTYPE_LMP                        227
#define IFTYPE_CBLVECTASTAR               228
#define IFTYPE_DOCSCABLEMCMTSDOWNSTREAM   229
#define IFTYPE_ADSL2                      230
#define IFTYPE_MACSECCONTROLLEDIF         231
#define IFTYPE_MACSECUNCONTROLLEDIF       232
#define IFTYPE_AVICIOPTICALETHER          233
#define IFTYPE_ATM_BOND                   234
#define IFTYPE_VOICEFGDOS                 235
#define IFTYPE_MOCA_VERSION1              236
#define IFTYPE_IEEE80216WMAN              237
#define IFTYPE_ADSL2PLUS                  238
#define IFTYPE_DVBRCSMACLAYER             239
#define IFTYPE_DVBTDM                     240
#define IFTYPE_DVBRCSTDMA                 241
#define IFTYPE_X86LAPS                    242
#define IFTYPE_WWANPP                     243
#define IFTYPE_WWANPP2                    244
#define IFTYPE_VOICEEBS                   245
#define IFTYPE_IFPWTYPE                   246
#define IFTYPE_ILAN                       247
#define IFTYPE_PIP                        248
#define IFTYPE_ALUELP                     249
#define IFTYPE_GPON                       250
#define IFTYPE_VDSL2                      251
#define IFTYPE_CAPWAP_DOT11_PROFILE       252
#define IFTYPE_CAPWAP_DOT11_BSS           253
#define IFTYPE_CAPWAP_WTP_VIRTUAL_RADIO   254
#define IFTYPE_BITS                       255
#define IFTYPE_DOCSCABLEUPSTREAMRFPORT    256
#define IFTYPE_CABLEDOWNSTREAMRFPORT      257
#define IFTYPE_VMWARE_VIRTUAL_NIC         258
#define IFTYPE_IEEE802154                 259
#define IFTYPE_OTNODU                     260
#define IFTYPE_OTNOTU                     261
#define IFTYPE_IFVFITYPE                  262
#define IFTYPE_G9981                      263
#define IFTYPE_G9982                      264
#define IFTYPE_G9983                      265
#define IFTYPE_ALUEPON                    266
#define IFTYPE_ALUEPONONU                 267
#define IFTYPE_ALUEPONPHYSICALUNI         268
#define IFTYPE_ALUEPONLOGICALLINK         269
#define IFTYPE_ALUGPONONU                 270
#define IFTYPE_ALUGPONPHYSICALUNI         271
#define IFTYPE_VMWARE_NIC_TEAM            272

/**
 * IP Header -- RFC 791
 */
typedef struct tagIPHDR
{
	BYTE m_cVIHL;	         // Version and IHL
	BYTE m_cTOS;			   // Type Of Service
	WORD m_wLen;			   // Total Length
	WORD m_wId;			      // Identification
	WORD m_wFlagOff;	      // Flags and Fragment Offset
	BYTE m_cTTL;			   // Time To Live
	BYTE m_cProtocol;	      // Protocol
	WORD m_wChecksum;	      // Checksum
	struct in_addr m_iaSrc;	// Internet Address - Source
	struct in_addr m_iaDst;	// Internet Address - Destination
} IPHDR;

/**
 * ICMP Header - RFC 792
 */
typedef struct tagICMPHDR
{
	BYTE m_cType;			// Type
	BYTE m_cCode;			// Code
	WORD m_wChecksum;		// Checksum
	WORD m_wId;				// Identification
	WORD m_wSeq;			// Sequence
} ICMPHDR;

/**
 * INADDR_NONE can be undefined on some systems
 */
#ifndef INADDR_NONE
#define INADDR_NONE	(0xFFFFFFFF)
#endif

/**
 * Check if given string is NULL and always return valid pointer
 */
#define CHECK_NULL(x)      ((x) == NULL ? _T("(null)") : (x))
#define CHECK_NULL_A(x)    ((x) == NULL ? "(null)" : (x))
#define CHECK_NULL_EX(x)   ((x) == NULL ? _T("") : (x))
#define CHECK_NULL_EX_A(x) ((x) == NULL ? "" : (x))

/**
 * Free memory block if it isn't NULL
 */
#if FREE_IS_NULL_SAFE
#define safe_free(x) free(x);
#define safe_free_and_null(x) { free(x); x = NULL; }
#else
#define safe_free(x) { if ((x) != NULL) free(x); }
#define safe_free_and_null(x) { if ((x) != NULL) { free(x); x = NULL; } }
#endif

/**
 * free() wrapper if it isn't NULL safe
 */
#if defined(__cplusplus) && !FREE_IS_NULL_SAFE
inline void nx_free(void *p)
{
   if (p != NULL)
      free(p);
}
#define free nx_free
#endif

/**
 * delete object and nullify pointer
 */
#define delete_and_null(x) { delete x; x = NULL; }

/**
 * Convert half-byte's value to hex digit and vice versa
 */
#define bin2hex(x) ((x) < 10 ? ((x) + _T('0')) : ((x) + (_T('A') - 10)))
#ifdef UNICODE
#define hex2bin(x) ((((x) >= _T('0')) && ((x) <= _T('9'))) ? ((x) - _T('0')) : \
                    (((towupper(x) >= _T('A')) && (towupper(x) <= _T('F'))) ? (towupper(x) - _T('A') + 10) : 0))
#else
#define hex2bin(x) ((((x) >= '0') && ((x) <= '9')) ? ((x) - '0') : \
                    (((toupper(x) >= 'A') && (toupper(x) <= 'F')) ? (toupper(x) - 'A' + 10) : 0))
#endif

/**
 * Define min() and max() if needed
 */
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

/**
 * Define _tcsicmp() for non-windows
 */
#ifndef _WIN32
#define stricmp   strcasecmp
#define strnicmp  strncasecmp
#define wcsicmp   wcscasecmp
#define wcsnicmp  wcsncasecmp
#endif

/**
 * Compare two numbers and return -1, 0, or 1
 */
#define COMPARE_NUMBERS(n1,n2) (((n1) < (n2)) ? -1 : (((n1) > (n2)) ? 1 : 0))

/**
 * Increment pointer for given number of bytes
 */
#define inc_ptr(ptr, step, ptype) ptr = (ptype *)(((char *)ptr) + step)

/**
 * Validate numerical value
 */
#define VALIDATE_VALUE(var,x,y,z) { if ((var < x) || (var > y)) var = z; }

/**
 * DCI (data collection item) data types
 */
#define DCI_DT_INT         0
#define DCI_DT_UINT        1
#define DCI_DT_INT64       2
#define DCI_DT_UINT64      3
#define DCI_DT_STRING      4
#define DCI_DT_FLOAT       5
#define DCI_DT_NULL        6
#define DCI_DT_DEPRECATED  255	/* used internally by agent */

/**
 * Insert parameter as string
 */
#ifdef UNICODE
#define STRING(x)   L#x
#else
#define STRING(x)   #x
#endif

/**
 * Pipe handle
 */
#ifdef _WIN32
#define HPIPE HANDLE
#define INVALID_PIPE_HANDLE INVALID_HANDLE_VALUE
#else
#define HPIPE int
#define INVALID_PIPE_HANDLE (-1)
#endif

#ifdef __cplusplus

/**
 * Session enumeration callback return codes
 */
enum EnumerationCallbackResult
{
   _STOP = 0,
   _CONTINUE = 1
};

#endif

#endif   /* _nms_common_h_ */
