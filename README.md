<img src="https://swift.org/assets/images/swift.svg" alt="Swift logo" height="70" >

# Swift Programming Language

## Welcome to Swift

Swift is a high-performance system programming language.  It has a clean
and modern syntax, offers seamless access to existing C and Objective-C code
and frameworks, and is memory safe by default.

Although inspired by Objective-C and many other languages, Swift is not itself a
C-derived language. As a complete and independent language, Swift packages core
features like flow control, data structures, and functions, with high-level
constructs like objects, protocols, closures, and generics. Swift embraces
modules, eliminating the need for headers and the code duplication they entail.

To learn more about the programming language, visit [swift.org](https://swift.org/documentation/).

## Swift + Vex

Vex has a history of convoluted and annoying programming languages. However, with the release of tools such as Vexcode and support for Python and Javascript, this is beginning to change. This project attempts to port high-level language Swift and its standard library to the Vex V5.

Initially, I attempted to keep support for other platforms intact so that this might be folded into the actual Swift repo. This proved to be quite difficult, so I have adopted a "scorched-earth" policy, where all platform-specific code for non-VexOS's is removed when it causes a problem.


## Getting Started

These instructions give the most direct path to a working Swift development
environment. To build from source you will need about 2 GB of disk space for the
source code and up to 70 GB of disk space for the build artifacts with full
debugging. Depending on your machine, a clean build can take a few minutes to
several hours. Naturally, incremental builds are much faster.


### System Requirements

macOS, Ubuntu Linux LTS, and the latest Ubuntu Linux release are the current
supported host development operating systems. However, compilation has only been tested on macOS.

Please make sure you use Python 2.x. Python 3.x is not supported currently.

#### macOS

To build for macOS, you need [Xcode 10.2 beta](https://developer.apple.com/xcode/downloads/).
The required version of Xcode changes frequently, and is often a beta release.
Check this document or the host information on <https://ci.swift.org> for the
current required version.

You will also need [CMake](https://cmake.org) and [Ninja](https://ninja-build.org),
which can be installed via a package manager:

**[Homebrew](https://brew.sh/)**

    brew install cmake ninja

**[MacPorts](https://macports.org)**

    sudo port install cmake ninja

Instructions for installing CMake and Ninja directly can be found [below](#build-dependencies).

#### Linux

For Ubuntu, you'll need the following development dependencies:

    sudo apt-get install git cmake ninja-build clang python uuid-dev libicu-dev icu-devtools libbsd-dev libedit-dev libxml2-dev libsqlite3-dev swig libpython-dev libncurses5-dev pkg-config libblocksruntime-dev libcurl4-openssl-dev systemtap-sdt-dev tzdata rsync

**Note:** LLDB currently requires at least `swig-1.3.40` but will successfully build
with version 2 shipped with Ubuntu.

Build instructions for Ubuntu 14.04 LTS can be found [here](docs/Ubuntu14.md).

### Getting Sources for Swift and Related Projects

First create a directory for all of the Swift sources:

    mkdir swift-source
    cd swift-source

**Note:** This is important since update-checkout (see below) checks out
repositories next to the Swift source directory. This means that if one clones
Swift and has other unrelated repositories, update-checkout may not clone those
repositories and will update them instead.

**Via HTTPS**  For those checking out sources as read-only, HTTPS works best:

    git clone https://github.com/apple/swift.git
    ./swift/utils/update-checkout --clone

**Via SSH**  For those who plan on regularly making direct commits,
cloning over SSH may provide a better experience (which requires
[uploading SSH keys to GitHub](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/)):

    git clone git@github.com:apple/swift.git
    ./swift/utils/update-checkout --clone-with-ssh

### Building Swift

The `build-script` is a high-level build automation script that supports basic
options such as building a Swift-compatible LLDB, building the Swift Package
Manager, building for various platforms, running tests after builds, and more.

To build for VexOS, run:

    ./utils/build-script -R --vexos --vex-sdk ~/sdk  --skip-build-osx --build-swift-dynamic-sdk-overlay=0 --no-swift-stdlib-assertions --build-swift-static-stdlib  --build-swift-dynamic-stdlib=0

#### Build Products

All of the build products are placed in `swift-source/build/${TOOL}-${MODE}/${PRODUCT}-${PLATFORM}/`.
If macOS Swift with Ninja in DebugAssert mode was built, all of the products
would be in `swift-source/build/Ninja-DebugAssert/swift-macosx-x86_64/`. It
helps to save this directory as an environment variable for future use.

    export SWIFT_BUILD_DIR="~/swift-source/build/Ninja-DebugAssert/swift-macosx-x86_64"

#### Ninja

Once the first build has completed, Ninja can perform fast incremental builds of
various products. These incremental builds are a big timesaver when developing
and debugging.

    cd ${SWIFT_BUILD_DIR}
    ninja swift

This will build the Swift compiler, but will not rebuild the standard library or
any other target. Building the `swift-stdlib` target as an additional layer of
testing from time to time is also a good idea. To build just the standard
library, run:

    ninja swift-stdlib

It is always a good idea to do a full build after using `update-checkout`.

### Swift Toolchains

#### Building

Swift toolchains are created using the script
[build-toolchain](https://github.com/apple/swift/blob/master/utils/build-toolchain). This
script is used by swift.org's CI to produce snapshots and can allow for one to
locally reproduce such builds for development or distribution purposes. E.x.:

```
  $ ./utils/build-toolchain $BUNDLE_PREFIX
```

where ``$BUNDLE_PREFIX`` is a string that will be prepended to the build
date to give the bundle identifier of the toolchain's ``Info.plist``. For
instance, if ``$BUNDLE_PREFIX`` was ``com.example``, the toolchain
produced will have the bundle identifier ``com.example.YYYYMMDD``. It
will be created in the directory you run the script with a filename
of the form: ``swift-LOCAL-YYYY-MM-DD-a-osx.tar.gz``.

Beyond building the toolchain, ``build-toolchain`` also supports the
following (non-exhaustive) set of useful options::

- ``--dry-run``: Perform a dry run build. This is off by default.
- ``--test``: Test the toolchain after it has been compiled. This is off by default.
- ``--distcc``: Use distcc to speed up the build by distributing the c++ part of
  the swift build. This is off by default.

More options may be added over time. Please pass ``--help`` to
``build-toolchain`` to see the full set of options.

## Testing Swift

See [docs/Testing.md](docs/Testing.md), in particular the section on [lit.py](docs/Testing.md#using-litpy).

## Learning More

Be sure to look through the [docs](https://github.com/apple/swift/tree/master/docs)
directory for more information about the compiler. In particular, the documents
titled [Debugging the Swift Compiler](docs/DebuggingTheCompiler.rst) and
[Continuous Integration for Swift](docs/ContinuousIntegration.md) are very
helpful to understand before submitting your first PR.

### Building Documentation

To read the compiler documentation, start by installing the
[Sphinx](http://sphinx-doc.org) documentation generator tool by running the
command:

    easy_install -U "Sphinx < 2.0"

Once complete, you can build the Swift documentation by changing directory into
[docs](https://github.com/apple/swift/tree/master/docs) and typing `make`. This
compiles the `.rst` files in the [docs](https://github.com/apple/swift/tree/master/docs)
directory into HTML in the `docs/_build/html` directory.

Many of the docs are out of date, but you can see some historical design
documents in the `docs` directory.

Another source of documentation is the standard library itself, located in
`stdlib`. Much of the language is actually implemented in the library
(including `Int`), and the standard library gives some examples of what can be
expressed today.

## Build Dependencies

### CMake
[CMake](https://cmake.org) is the core infrastructure used to configure builds of
Swift and its companion projects; at least version 3.4.3 is required.

On macOS, you can download the [CMake Binary Distribution](https://cmake.org/download),
bundled as an application, copy it to `/Applications`, and add the embedded
command line tools to your `PATH`:

    export PATH=/Applications/CMake.app/Contents/bin:$PATH

On Linux, if you have not already installed Swift's [development
dependencies](#linux), you can download and install the CMake
package separately using the following command:

    sudo apt-get install cmake


### Ninja
[Ninja](https://ninja-build.org) is the current recommended build system
for building Swift and is the default configuration generated by CMake. [Pre-built
packages](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages)
are available for macOS and Linux distributions. You can also clone Ninja
next to the other projects and it will be bootstrapped automatically:

**Via HTTPS**

    git clone https://github.com/ninja-build/ninja.git && cd ninja
    git checkout release
    cat README

**Via SSH**

    git clone git@github.com:ninja-build/ninja.git && cd ninja
    git checkout release
    cat README
