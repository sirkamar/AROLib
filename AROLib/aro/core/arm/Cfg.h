#ifndef ARM_CFG_H
#define ARM_CFG_H

#pragma warning(disable: 4244)
#pragma warning(disable: 4250)
#pragma warning(disable: 4251)
#pragma warning(disable: 4715)

/* Target Version(s) */
// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

/* Standard Header Files */
#define WIN32_LEAN_AND_MEAN         // Exclude rarely-used stuff from Windows headers

#include <windows.h>                // Windows Header Files

/* Declare the library's interface specifier */
#if !defined(interface)
#define ARO_INTERFACE struct
#define interface ARO_INTERFACE
#endif

/* Include necessary standard headers */
#include <condition_variable>
#include <initializer_list>
#include <functional>
#include <sstream>
#include <thread>
#include <vector>
#include <mutex>

#endif /* ARM_CFG_H */
