//===--- Platform.h - Helpers related to target platforms -------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_BASIC_PLATFORM_H
#define SWIFT_BASIC_PLATFORM_H

#include "swift/Basic/LLVM.h"
#include "swift/Config.h"
#include "llvm/ADT/StringRef.h"

namespace llvm {
  class Triple;
}

namespace swift {

  enum class DarwinPlatformKind : unsigned {
    MacOS
  };

  /// Returns the platform name for a given target triple.
  ///
  /// For example, the iOS simulator has the name "iphonesimulator", while real
  /// iOS uses "iphoneos". OS X is "macosx". (These names are intended to be
  /// compatible with Xcode's SDKs.)
  ///
  /// If the triple does not correspond to a known platform, the empty string is
  /// returned.
  StringRef getPlatformNameForTriple(const llvm::Triple &triple);

  /// Returns the platform Kind for Darwin triples.
  DarwinPlatformKind getDarwinPlatformKind(const llvm::Triple &triple);

  /// Maps an arbitrary platform to its non-simulator equivalent.
  ///
  /// If \p platform is not a simulator platform, it will be returned as is.
  DarwinPlatformKind getNonSimulatorPlatform(DarwinPlatformKind platform);

  /// Returns the architecture component of the path for a given target triple.
  ///
  /// Typically this is used for mapping the architecture component of the
  /// path.
  ///
  /// For example, on Linux "armv6l" and "armv7l" are mapped to "armv6" and
  /// "armv7", respectively, within LLVM. Therefore the component path for the
  /// architecture specific objects will be found in their "mapped" paths.
  ///
  /// This is a stop-gap until full Triple support (ala Clang) exists within swiftc.
  StringRef getMajorArchitectureName(const llvm::Triple &triple);

  /// Computes the normalized target triple used as the most preferred name for
  /// module loading.
  ///
  /// For platforms with fat binaries, this canonicalizes architecture,
  /// vendor, and OS names, strips OS versions, and makes inferred environments
  /// explicit. For other platforms, it returns the unmodified triple.
  ///
  /// The input triple should already be "normalized" in the sense that
  /// llvm::Triple::normalize() would not affect it.
  llvm::Triple getTargetSpecificModuleTriple(const llvm::Triple &triple);
} // end namespace swift

#endif // SWIFT_BASIC_PLATFORM_H
