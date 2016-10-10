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

TODO


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
