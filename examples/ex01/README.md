# Example of Google Protocol Buffer based serialization

ex01 - Simple classes with Google Protocol Buffer based serialization interface

## Description:

There are two  simple C++ classes (``bar`` and ``foo``)  which use the
``protobuftools::i_protobufable`` interface and are associated to some
specific `proto`  messages (``BarMsg``  and ``FooMsg``).   The example
program illustrates how  to serialize and deserialize  objects of such
types within a buffer.

## Build the example:

```sh
$ mkdir -p _build.d
$ cd _build.d
$ cmake \
  -DBxProtobuftools_DIR="$(bxprotobuftools-query --cmakedir)" \
   ..
$ make
```

# Not needed : -DProtobuf_DIR="$(dirname `which protoc`)/../lib"

## Run the example:

```sh
$ ./_build.d
$ ./ex01
```
