include(CheckSymbolExists)

# Append our own modules to the module path.
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(SEND_ERROR "SourceKit cannot be built standalone")
endif()

include(SwiftWindowsSupport)
swift_swap_compiler_if_needed("SourceKit")

if (DARWIN_TOOLCHAIN_VERSION)
  set(SOURCEKIT_VERSION_STRING "${DARWIN_TOOLCHAIN_VERSION}")
else()
  set(SOURCEKIT_VERSION_STRING "${SWIFT_COMPILER_VERSION}")
endif()

set(SOURCEKIT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCEKIT_BINARY_DIR ${SWIFT_BINARY_DIR})

set(SOURCEKIT_RUNTIME_OUTPUT_INTDIR "${SWIFT_RUNTIME_OUTPUT_INTDIR}")
set(SOURCEKIT_LIBRARY_OUTPUT_INTDIR "${SWIFT_LIBRARY_OUTPUT_INTDIR}")

check_symbol_exists(dispatch_block_create "dispatch/dispatch.h" HAVE_DISPATCH_BLOCK_CREATE)
configure_file(
  ${SOURCEKIT_SOURCE_DIR}/include/SourceKit/Config/config.h.cmake
  ${SOURCEKIT_BINARY_DIR}/include/SourceKit/Config/config.h)

set(SOURCEKIT_DEPLOYMENT_OS "${SWIFT_HOST_VARIANT}")
set(SOURCEKIT_DEPLOYMENT_TARGET "${SWIFT_SDK_${SWIFT_HOST_VARIANT_SDK}_DEPLOYMENT_VERSION}")

STRING(TOLOWER "${SWIFT_PRIMARY_VARIANT_SDK}" SOURCEKIT_PLATFORM_NAME)
# Remove '_simulator' from the name if it exists
STRING(REPLACE "_simulator" "" SOURCEKIT_PLATFORM_NAME "${SOURCEKIT_PLATFORM_NAME}")

set(SWIFT_SOURCEKIT_USE_INPROC_LIBRARY TRUE)

# Now include AddSwiftSourceKit
include(AddSwiftSourceKit)

include_directories(BEFORE
  ${SOURCEKIT_BINARY_DIR}/include
  ${SOURCEKIT_SOURCE_DIR}/include
  ${SOURCEKIT_BINARY_DIR}/tools/SourceKit/include
)

string(TOUPPER "${CMAKE_SYSTEM_NAME}" SOURCEKIT_DEFAULT_TARGET_SDK)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(tools)
