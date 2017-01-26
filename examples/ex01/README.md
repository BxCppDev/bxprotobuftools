# Example of Google Protocol Buffer based serialization

ex01 - Simple classes with Google Protocol Buffer based serialization interface

## Description:

There are two  simple C++ classes (``bar`` and ``foo``)  which use the
``protobuftools::i_protobufable`` interface and are associated to some
specific `proto`  messages (``BarMsg``  and ``FooMsg``).   The example
program illustrates how  to serialize and deserialize  objects of such
types within a buffer, using the Protobuf format.

## Build the example:

```sh
$ mkdir -p /tmp/${USER}/bxprotobuftools_ex01/_source.d
$ cp -a $(bxprotobuftools-query --exampledir)/ex01 /tmp/${USER}/bxprotobuftools_ex01/_source.d
$ mkdir -p /tmp/${USER}/bxprotobuftools_ex01/_build.d
$ cd /tmp/${USER}/bxprotobuftools_ex01/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX="/tmp/${USER}/bxprotobuftools_ex01/_install.d" \
  -DBxProtobuftools_DIR="$(bxprotobuftools-query --cmakedir)" \
  /tmp/${USER}/bxprotobuftools_ex01/_source.d/ex01
$ make
$ make install
```

## Run the example:

```sh
$ ./_build.d
$ ./ex01
```
