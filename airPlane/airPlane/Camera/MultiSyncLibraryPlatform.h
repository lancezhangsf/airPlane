//=============================================================================
// Copyright � 2011 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with Point Grey Research, Inc. (PGR).
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id:
//=============================================================================

#ifndef MULTISYNCLIBRARYPLATFORM_H
#define MULTISYNCLIBRARYPLATFORM_H

//=============================================================================
// Platform-specific header file for MultiSunc Library.
//
// All the platform-specific code that is required by individual compilers
// to produce the appropriate code for each platform.
//=============================================================================

#if defined(WIN32) || defined(WIN64)

// Windows 32-bit and 64-bit
#ifdef MULTISYNCLIBRARY_EXPORT
#define MULTISYNCLIBRARY_API __declspec( dllexport )
#elif defined(MULTISYNCLIBRARY_STATIC)
#define MULTISYNCLIBRARY_API
#else
#define MULTISYNCLIBRARY_API __declspec( dllimport )
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#elif defined(MAC_OSX)

// Mac OSX

#else
// Linux and all others

// Using GCC 4 where hiding attributes is possible
#define MULTISYNCLIBRARY_API __attribute__ ((visibility ("default")))
#define MULTISYNCLIBRARY_LOCAL  __attribute__ ((visibility ("hidden")))

#endif

#endif // MULTISYNCLIBRARYPLATFORM_H

