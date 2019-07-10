

set(SUPPORTED_OSX_ARCHS "x86_64")

is_sdk_requested(OSX swift_build_osx)
if(swift_build_osx)
  configure_sdk_darwin(
      OSX "OS X" "${SWIFT_DARWIN_DEPLOYMENT_VERSION_OSX}"
      macosx macosx macosx "${SUPPORTED_OSX_ARCHS}")
  configure_target_variant(OSX-DA "OS X Debug+Asserts"   OSX DA "Debug+Asserts")
  configure_target_variant(OSX-RA "OS X Release+Asserts" OSX RA "Release+Asserts")
  configure_target_variant(OSX-R  "OS X Release"         OSX R  "Release")
endif()
