# bxprotobuftools

bxprotobuftools - Tools for *Protobuf* based serialization (C++ library)

The   ``bxprotobuftools``   library   (also   ``BxProtobuftools``   or
``Bayeux/Protobuftools``)  consists  in  a  set  of  C++  classes  and
utilities for serialization based on  the Google Protocol Buffers API.
It  aims to  be integrated  as a  companion module  of the  Bayeux C++
library (the foundation library  of the SuperNEMO physics experiment's
software).


This is a very preliminary work, not ready for production yet...
Some documentation and examples are still needed too.

For SuperNEMO users only:

Protobuf based serialization will be used  by the Vire C++ library for
communication between C++ implemented services, Java based Control and
Monitoring  System  (CMS)  servers  and  external  services  (RabbitMQ
server) for the SuperNEMO experiment.


## Dependencies and inspiration

bxprotobuftools depends on the Google Protocol Buffers library:
* the Google Protocol Buffers library (https://developers.google.com/protocol-buffers/)
* the Boost C++ library (http://www.boost.org/)

It is inspired by a former related work:
* ``Bayeux/Jsontools`` (https://github.com/fmauger/bxjsontools)

Needed tools and software (tested on Ubuntu 16.04 LTS):
* You need CMake version >= 2.8 (former version may work)
* You need gcc version >= 4.8.4 (former version may work)
* By default, some bxprotobuftools' parts depends on Boost 1.60 (former version may work).

## License:

See the ``LICENSE.txt`` file.


## Build and install:

The  following  instructions  illustrate  how  to  build  and  install
bxprotobuftools on a Linux system (Ubuntu  16.04 LTS). It should be easy
to adapt for a MacOS X system.

CMake options:

* ``BXPROTOBUFTOOLS_ENABLE_TESTING`` (default: ``ON``) : builds the test program(s).



### Download the source code from GitHub:
```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_source.d/
$ cd /tmp/${USER}/bxprotobuftools/_source.d/
$ git clone https://github.com/fmauger/bxprotobuftools.git
```
### Build the library from a dedicated directory:

For  SuperNEMO users  only:

The SuperNEMO experiment data  processing and simulation software uses
Cadfaelbrew    (https://github.com/SuperNEMO-DBD/cadfaelbrew)    which
provides some core software tools  and libraries (C++ compiler, Boost, GSL,
ROOT libraries...).  Before to build and install BxProtobuftools, you must
switch to a brew shell before:
```sh
$ brew sh
```

Then:
```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools/_build.d/
$ cd  /tmp/${USER}/bxprotobuftools/_build.d/
$ cmake \
  -DCMAKE_INSTALL_PREFIX=${HOME}/sw/bxprotobuftools/install-0.1.0 \
  /tmp/${USER}/bxprotobuftools/_source.d/bxprotobuftools/
$ make
$ make test
$ make install
```

### Enjoy bxprotobuftools from its installation directory:
```sh
$ LANG="C" tree ${HOME}/sw/bxprotobuftools/install-0.1.0
/home/{userlogin}/sw/bxprotobuftools/install-0.1.0
|-- bin
|   `-- bxprotobuftools-query
|-- include
|   `-- bayeux
|       `-- protobuftools
|           |-- base_type_converters.h
|           |-- bool_converter.h
|           |-- config.h
|           |-- core.h
|           |-- double_converter.h
|           |-- enum_converter.h
|           |-- exception.h
|           |-- float_converter.h
|           |-- i_protobufable.h
|           |-- int16_converter.h
|           |-- int32_converter.h
|           |-- int64_converter.h
|           |-- int8_converter.h
|           |-- io-inl.h
|           |-- io.h
|           |-- iofile-inl.h
|           |-- iofile.h
|           |-- logger.h
|           |-- logger_macros.h
|           |-- node-inl.h
|           |-- node.h
|           |-- protobuf_factory.h
|           |-- protobuf_utils.h
|           |-- protobufable_converter.h
|           |-- protobuftools.h
|           |-- std_array_converter.h
|           |-- std_list_converter.h
|           |-- std_set_converter.h
|           |-- std_string_converter.h
|           |-- std_type_converters.h
|           |-- std_vector_converter.h
|           |-- uint16_converter.h
|           |-- uint32_converter.h
|           |-- uint64_converter.h
|           |-- uint8_converter.h
|           `-- version.h
|-- lib
|   |-- cmake
|   |   `-- BxProtobuftools-0.1.0
|   |       |-- BxProtobuftoolsConfig.cmake
|   |       |-- BxProtobuftoolsConfigVersion.cmake
|   |       |-- BxProtobuftoolsTargets-noconfig.cmake
|   |       `-- BxProtobuftoolsTargets.cmake
|   `-- libBayeux_protobuftools.so
`-- share
    `-- BxProtobuftools-0.1.0
        |-- LICENSE.txt
        `-- examples
            `-- ex01
                `-- README.md
```

## Using bxprotobuftools:

* The ``bxprotobuftools-query`` utility allows you to fetch informations about your
  BxProtobuftools installation. You may add the following typical line in your
``~/.bashrc`` profile:
```sh
export PATH="${HOME}/sw/bxprotobuftools/install-0.1.0/bin:${PATH}"
```
  This will give you access to the ``bxprotobuftools-query`` command-line utility:
```sh
$ bxprotobuftools-query --help
```
* CMake  configuration  scripts (i.e. ``BxProtobuftoolsConfig.cmake`` and ``BxProtobuftoolsConfigVersion.cmake``) are provided for client
  software. The CMake ``find_package(BxProtobuftools REQUIRED CONFIG)`` command can be given
  the following variable to find the BxProtobuftools installation on your system:
```sh
$ cmake ... -DBxProtobuftools_DIR="$(bxprotobuftools-query --cmakedir)" ...
```
* There is  a simple example  ``ex01`` that illustrates a  very simple usecase.
