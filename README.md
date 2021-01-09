# bxprotobuftools

bxprotobuftools - Tools for *Protobuf* based serialization (C++ library)

The   ``bxprotobuftools``   library   (also   ``BxProtobuftools``   or
``Bayeux/Protobuftools``)  consists  in  a  set  of  C++  classes  and
utilities for serialization  based on the Google  Protocol Buffers API
(*protobuf*).

bxprotobuftools serialization is available for standard I/O streams.

This is a very preliminary work that needs more development, tests
and documentation.

bxprotobuftools  aims  to be  integrated  as  a  companion module  of  the
https://github.com/BxCppDev/Bayeux and Vire C++ libraries.

bxprotobuftools  has been  initiated  in the  framework  of the  SuperNEMO
physics experiment software.


## History

* Version 1.0.0 : first production release

## Dependencies and inspiration

bxprotobuftools depends on the Google Protocol Buffers library:

* the    Google    Protocol     Buffers    library    (version >= 3.0.0)
  (https://developers.google.com/protocol-buffers/)

  **Note:**  bxprotobuftools provides  its own  ``FindProtobuf.cmake``
  CMake script  (``find_package`` module) because the  one provided by
  CMake 3.5 (``/usr/share/cmake-3.5/Modules/FindProtobuf.cmake``) does
  not suit bxprotobuftools' needs.

  On Ubuntu 18.04/20.04 LTS : 
  
  ```
  $ sudo apt-get install protobuf-compiler libprotobuf-dev libprotobuf-c-dev
  ```

* the Boost C++ library (version >= 1.58, but former version may work) (http://www.boost.org/)

  - On Ubuntu 18.04LTS : Boost 1.65.1
  - On Ubuntu 20.04LTS : Boost 1.71
  
  ```
  $ sudo apt-get install libboost-all-dev
  ```

It is inspired by a former related work:
* ``Bayeux/Jsontools`` (https://github.com/BxCppDev/bxjsontools)

Needed tools and software (tested on Ubuntu 16.04/18.04/20.04 LTS):
* You  need  [CMake](https://cmake.org/)   version  >=  3.5.1  (former
  version may work)
* You need gcc version >= 5.4.0 (former version may work)

## License:

See the ``LICENSE.txt`` file.


## Build and install:

The  following  instructions  illustrate  how  to  build  and  install
bxprotobuftools on  a Linux system (Ubuntu  16.04/18.04/20.04 LTS). It
should be easy to adapt for a MacOS X system.

CMake options:

* ``BXPROTOBUFTOOLS_ENABLE_TESTING``  (default: ``ON``)  : builds  the
  test program(s).

### Note on Boost:

bxprotobuftools  implements   some  specific   Protobuf  serialization
support  for a  few Boost  classes of  interest (implies  Boost >=1.58
dependency):

In  principle  bxprotobuftools can  build  both  with a  system  Boost
installation (version  1.58 on Ubuntu  16.04 resolved by  the standard
``FindBoost.cmake`` script  using the ``find_package``  *MODULE* mode)
or with a  Boost installation provided  by   the  user  (example:
[Linuxbrew](http://linuxbrew.sh/)).

### Download the source code from GitHub:

In the following  we use ``/tmp`` as the base  working directory. Feel
free to change it to somewhere else (``${HOME}``, ``/opt``...).

```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_source.d/
$ cd /tmp/${USER}/bxprotobuftools/_source.d/
$ git clone https://github.com/BxCppDev/bxprotobuftools.git
```

### Install dependencies:

* Installation of system packages:

On Ubuntu 20.04 LTS, we suggest to install the following packages:
```sh
$ sudo apt-get install cmake
$ sudo apt-get install g++
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install protobuf-compiler libprotobuf-dev libprotobuf-c-dev
```

* Installation of system packages:

The  Google   Protocol  Buffers  library  can   be  installed  through
Linuxbrew/Homebrew.   The   ``https://github.com/BxCppDev/homebrew-bxtap``  tap
provides a  formula to install a  recent version of ``protobuf``  in a
way that makes it usable by bxprotobuftools.

Suggestion from a Linuxbrew setup:
```sh
$ brew tap bxcppdev/homebrew-bxtap
$ brew install bxcppdev/bxtap/protobuf@3.3.0
```

Also make  sure you have  a proper  installation of the  Boost library
(>=1.58) on your system. Boost may also be installed from brew:
```sh
$ brew install bxcppdev/bxtap/boost --c++11
```

The following command will then print the base path of both Linuxbrew's
protobuf and Boost installation:
```sh
$ brew --prefix
```


### Build the library from a dedicated directory:

Make sure you have a proper installation of the Google Protocol Buffer
(C++)  library version  3.0.0 and  companion tools  (``protoc``).  You
must also have an installation of the Boost library (>=1.58).

Instructions to build bxprotobuftools from a working build directory:
```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_build.d/
$ cd  /tmp/${USER}/bxprotobuftools/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=/tmp/${USER}/bxprotobuftools/_install.d \
    -DPROTOBUF_ROOT:PATH="installation/path/of/protobuf/version/3.0 \
    /tmp/${USER}/bxprotobuftools/_source.d/bxprotobuftools
$ make
$ make test
$ make install
```

Note the use  of the ``PROTOBUF_ROOT`` variable to help  CMake to find
the Protobuf dependee libraries.

On Ubuntu 20.04, system Boost  1.71 is available from ``/usr/include``
and ``/usr/lib`` and should be found automatically by CMake.
If you want to use a specific version of Boost (for
example one provided  by Linuxbrew), you must specify  the proper path
to help CMake to locate Boost files:

```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_build.d/
$ cd  /tmp/${USER}/bxprotobuftools/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=/tmp/${USER}/bxprotobuftools/_install.d \
    -DPROTOBUF_ROOT:PATH="/path/to/protobuf/version/3.0/installation/base/dir \
    -DBOOST_ROOT=/path/to/linuxbrew/installation/base/dir \
    /tmp/${USER}/bxprotobuftools/_source.d/bxprotobuftools
$ make
$ make test
$ make install
```

Should both protobuf and Boost be managed through Linuxbrew, you can use:
```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_build.d/
$ cd  /tmp/${USER}/bxprotobuftools/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=/tmp/${USER}/bxprotobuftools/_install.d \
    -DPROTOBUF_ROOT:PATH=$(brew --prefix) \
    -DBOOST_ROOT=$(brew --prefix) \
    /tmp/${USER}/bxprotobuftools/_source.d/bxprotobuftools
$ make
$ make test
$ make install
```

## Using bxprotobuftools:

* The   ``bxprotobuftools-query``   utility   allows  you   to   fetch
  informations about  your BxProtobuftools  installation. You  may add
  the following typical line in your ``~/.bashrc`` profile:

```sh
export PATH="/tmp/${USER}/bxprotobuftools/_install.d/bin:${PATH}"
```

This   will  give   you   access   to  the   ``bxprotobuftools-query``
command-line utility:

```sh
$ bxprotobuftools-query --help
```

* CMake  configuration  scripts (i.e.  ``BxProtobuftoolsConfig.cmake``
  and ``BxProtobuftoolsConfigVersion.cmake``) are  provided for client
  software.   The    CMake   ``find_package(BxProtobuftools   REQUIRED
  CONFIG)`` command  can be given  the following variable to  find the
  BxProtobuftools installation on your system:

```sh
$ cmake ... -DBxProtobuftools_DIR="$(bxprotobuftools-query --cmakedir)" ...
```

* There is  a simple example  ``ex01`` that illustrates a  very simple
  usecase.

## To do:

* Add  ``converter`` template  class for  ``std::map`` container  at least with
  simple types as the key (``int``, ``std::string``...).
