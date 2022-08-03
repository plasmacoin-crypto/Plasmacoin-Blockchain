//
// FILENAME: version-info.h | Plasmacoin Cryptocurrency
// DESCRIPTION: A central place to store version information
// CREATED: 2021-08-02 @ 8:22 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SOFTWARE_INFO_HPP
#define SOFTWARE_INFO_HPP

//
// Alllow stringifying integers
//

#define STRINGIFY(arg)     	  	  #arg
#define TO_STRING(arg)			  STRINGIFY(arg)

// Punctuation/delimiters
#define POINT 					  "."
#define DASH					  "-"

#define PLASMACOIN_VERSION_MINOR  1
#define PLASMACOIN_VERSION_MAJOR  0
#define PLASMACOIN_VERSION_PATCH  0

//
// Set these macros to 1 (true) if the release is a pre-release version.
//
// Only one should be set at a time. In the event that multiple are set,
// the first set macro is used.
//
// If none of the following macros are set, a stable (production) release
// is assumed.
//

#define ALPHA					  0
#define BETA 					  1
#define RC		  				  0

// Determine the pre-release type
#if ALPHA
	#define PRE_RELEASE_TYPE 	  "alpha"
#elif BETA
	#define PRE_RELEASE_TYPE	  "beta"
#elif RC
	#define PRE_RELEASE_TYPE 	  "rc"
#endif

#define PRE_RELEASE_VERSION		  1
#define BUILD_METADATA			  20220802
#define RELEASE_DATE_TIME 		  __DATE__ __TIME__
#define INITIAL_RELEASE_YEAR	  2022

//
// Version macros
//

#define PLASMACOIN_VERSION		  TO_STRING(PLASMACOIN_VERSION_MAJOR) POINT TO_STRING(PLASMACOIN_VERSION_MINOR) POINT TO_STRING(PLASMACOIN_VERSION_PATCH)
#define VERSION_METADATA		  PRE_RELEASE_TYPE TO_STRING(PRE_RELEASE_VERSION) DASH TO_STRING(BUILD_METADATA)
#define PLASMACOIN_FULL_VERSION	  PLASMACOIN_VERSION DASH VERSION_METADATA

#endif // SOFTWARE_INFO_HPP