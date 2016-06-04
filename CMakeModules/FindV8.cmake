# Locate V8
# This module defines
# V8_LIBRARY
# V8_FOUND, if false, do not try to link to V8
# V8_INCLUDE_DIR, where to find the headers

FIND_PATH(V8_INCLUDE_DIR NAMES "include/v8.h"
    PATHS
    ${V8_DIR}/
    )

IF(WIN32)
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
	
	FIND_LIBRARY(V8_BASE_0 
	NAMES v8_base_0
	PATHS
	${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
	)
	FIND_LIBRARY(V8_BASE_1 
	NAMES v8_base_1
	PATHS
	${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
	)
	FIND_LIBRARY(V8_BASE_2 
	NAMES v8_base_2
	PATHS
	${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
	)
	FIND_LIBRARY(V8_BASE_3 
	NAMES v8_base_3
	PATHS
	${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
	)

	FIND_LIBRARY(V8_SNAPSHOT_LIBRARY
    NAMES v8_nosnapshot libv8_external_snapshot
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
    )
	SET(V8_BASE_LIBRARY ${V8_BASE_0} ${V8_BASE_1} ${V8_BASE_2} ${V8_BASE_3})
	MESSAGE(STATUS "windows")
	
	FIND_LIBRARY(V8_ICUUC_LIBRARY
    NAMES icuuc libicuuc
    PATHS
	${V8_DIR}/
    ${V8_DIR}/icu
	${V8_DIR}/lib
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    )
	FIND_LIBRARY(V8_ICUI18N_LIBRARY
    NAMES icui18n libicui18n
    PATHS
	${V8_DIR}/
    ${V8_DIR}/icu
	${V8_DIR}/lib
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    )
	FIND_LIBRARY(V8_ICUDATA_LIBRARY
    NAMES icudt
    PATHS
	${V8_DIR}/
    ${V8_DIR}/icu
	${V8_DIR}/lib
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    )

ELSE (WIN32)

MESSAGE(STATUS "NOT on windows")
FIND_LIBRARY(V8_BASE_LIBRARY
    NAMES v8_base libv8_base
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
    ${V8_DIR}/out/x64.release/obj.target/src/
    )
	
FIND_LIBRARY(V8_SNAPSHOT_LIBRARY
    #NAMES v8_external_snapshot libv8_external_snapshot
    NAMES v8_nosnapshot libv8_nosnapshot
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
    ${V8_DIR}/out/x64.release/obj.target/src/
    )
FIND_LIBRARY(V8_ICUUC_LIBRARY
    NAMES icuuc libicuuc
    PATHS
    ${V8_DIR}/icu
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    ${V8_DIR}/out/x64.release/obj.target/src/
    )

FIND_LIBRARY(V8_ICUI18N_LIBRARY
    NAMES icui18n libicui18n
    PATHS
    ${V8_DIR}/icu
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    ${V8_DIR}/out/x64.release/obj.target/src/
    )
FIND_LIBRARY(V8_ICUDATA_LIBRARY
    NAMES icudata libicudata
    PATHS
    ${V8_DIR}/icu
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    ${V8_DIR}/out/x64.release/obj.target/src/
    )

FIND_LIBRARY(V8_SAMPLER_LIBRARY
    NAMES v8_libsampler libv8_libsampler
    PATHS
    ${V8_DIR}/icu
    ${V8_DIR}/lib/icu
    ${V8_DIR}/out/x64.release/obj.target/third_party/icu/    
    ${V8_DIR}/out/x64.release/obj.target/src/
    )
	
ENDIF (WIN32)

FIND_LIBRARY(V8_LIBBASE_LIBRARY
    NAMES v8_libbase libv8_libbase
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
    ${V8_DIR}/out/x64.release/obj.target/src/
    )

FIND_LIBRARY(V8_PLATFORM_LIBRARY
    NAMES v8_libplatform libv8_libplatform
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/lib
    ${V8_DIR}/out/x64.release/obj.target/tools/gyp/
    ${V8_DIR}/out/x64.release/obj.target/src/
    )

FIND_FILE(V8_NATIVE_BLOB
    NAMES natives_blob.bin
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/out/x64.release/
    ${V8_DIR}/out/x64.release/obj.target/src/
    )

FIND_FILE(V8_SNAPSHOT_BLOB
    NAMES snapshot_blob.bin
    PATHS
    ${V8_DIR}/
    ${V8_DIR}/out/x64.release/
    ${V8_DIR}/out/x64.release/obj.target/src/
    )

SET(V8_BLOB ${V8_SNAPSHOT_BLOB} ${V8_NATIVE_BLOB})

SET(V8_FOUND 0)
IF(V8_BASE_LIBRARY AND V8_SNAPSHOT_LIBRARY AND V8_PLATFORM_LIBRARY AND V8_LIBBASE_LIBRARY)
    SET(V8_LIBRARY ${V8_BASE_LIBRARY} ${V8_LIBBASE_LIBRARY} ${V8_SNAPSHOT_LIBRARY} ${V8_PLATFORM_LIBRARY} ${V8_SAMPLER_LIBRARY})

    IF(V8_ICUUC_LIBRARY AND V8_ICUI18N_LIBRARY AND V8_ICUDATA_LIBRARY)
        SET(V8_FOUND 1)
        SET(V8_LIBRARY ${V8_LIBRARY} ${V8_ICUUC_LIBRARY} ${V8_ICUI18N_LIBRARY})
		IF (!WIN32)
		 SET(V8_LIBRARY ${V8_LIBRARY})
		ENDIF (!WIN32)
        SET(V8_INCLUDE_DIR ${V8_INCLUDE_DIR} ${V8_DIR})
    ENDIF(V8_ICUUC_LIBRARY AND V8_ICUI18N_LIBRARY AND V8_ICUDATA_LIBRARY)

ELSE(V8_BASE_LIBRARY AND V8_SNAPSHOT_LIBRARY AND V8_PLATFORM_LIBRARY AND V8_LIBBASE_LIBRARY)
    MESSAGE(STATUS "V8 base library not found")
ENDIF(V8_BASE_LIBRARY AND V8_SNAPSHOT_LIBRARY AND V8_PLATFORM_LIBRARY AND V8_LIBBASE_LIBRARY)
