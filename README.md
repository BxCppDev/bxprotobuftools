# bxprotobuftools

bxprotobuftools - Tools for *Protobuf* based serialization (C++ library)

The   ``bxprotobuftools``   library   (also   ``BxProtobuftools``   or
``Bayeux/Protobuftools``)  consists  in  a  set  of  C++  classes  and
utilities for serialization  based on the Google  Protocol Buffers API
(*protobuf*).  It is used by the Vire C++  library.

This is a very preliminary work, not ready for production yet...  Some
documentation and examples are still needed too.

**Note**:

bxprotobuftools has been  initiated in the framework  of the SuperNEMO
physics experiment software.

Protobuf  based serialization  is used  by  the Vire  C++ library  for
communication between services implemented in C++ and/or Java in the
framework of the Control and  Monitoring System (CMS) of the SuperNEMO experiment.


## Dependencies and inspiration

bxprotobuftools depends on the Google Protocol Buffers library:

* the    Google    Protocol     Buffers    library    (version >= 3.0.0)
  (https://developers.google.com/protocol-buffers/)

  **Note:**  bxprotobuftools provides  its own  ``FindProtobuf.cmake``
  CMake script  (``find_package`` module) because the  one provided by
  CMake 3.5 (``/usr/share/cmake-3.5/Modules/FindProtobuf.cmake``) does
  not suit our needs.

* the Boost C++ library (version >= 1.58) (http://www.boost.org/)

It is inspired by a former related work:
* ``Bayeux/Jsontools`` (https://github.com/BxCppDev/bxjsontools)

Needed tools and software (tested on Ubuntu 16.04 LTS):
* You need CMake version >= 3.3 (former version may work)
* You need gcc version >= 5.4.0 with C++11 support (former version may work)
* bxprotobuftools depends on Boost >= 1.58 (former version may work).

## License:

See the ``LICENSE.txt`` file.


## Build and install:

The  following  instructions  illustrate  how  to  build  and  install
bxprotobuftools on  a Linux  system (Ubuntu 16.04  LTS). It  should be
easy to adapt for a MacOS X system.

CMake options:

* ``BXPROTOBUFTOOLS_ENABLE_TESTING`` (default: ``ON``) : builds the test program(s).

### Note on Boost:

bxprotobuftools  implements   some  specific   Protobuf  serialization
support  for a  few  Boost  classes of  interest  (implies Boost  >=1.58
dependency):

In  principle  bxprotobuftools can  build  both  with a  system  Boost
installation (version  1.58 on Ubuntu  16.04 resolved by  the standard
``FindBoost.cmake`` script  using the ``find_package``  *MODULE* mode)
or with a  Boost installation provided by  Linuxbrew (version >=1.60).

### Download the source code from GitHub:

```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_source.d/
$ cd /tmp/${USER}/bxprotobuftools/_source.d/
$ git clone https://github.com/BxCppDev/bxprotobuftools.git
```

### Build the library from a dedicated directory:

Make sure you have a proper installation of the Google Protocol Buffer
(C++)  library version  3.0.0 and  companion tools  (``protoc``).  You
must also have an installation of the Boost library (>=1.58).


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

* Add  ``converter`` template  class for  ``std::map`` container  with
  simple types (ints, strings...).
* Add  ``converter`` template  class  for a  few  useful classes  from
   ``boost::date_time`` and mapped using the ``google.protobuf.Timestamp``
   message.
