#!/usr/bin/env bash

src_dir=$(pwd)
build_dir=$(pwd)/_build.d

if [ -d "${build_dir}" ]; then
    rm -fr ${build_dir}
fi
mkdir -p ${build_dir}

which bxprotobuftools-query
if [ $? -ne 0 ]; then
    echo >2 "error: BxProtobuftools seems not installed!"
    cd ${src_dir}
    exit 1
fi

cd ${build_dir}
echo >2 "notice: Configuring ex01..."
cmake \
    -DBxProtobuftools_DIR="$(bxprotobuftools-query --cmakedir)" \
    ${src_dir}
if [ $? -ne 0 ]; then
    echo >2 "error: Configuration failed!"
    cd ${src_dir}
    exit 1
fi
echo >2 "notice: Compiling ex01..."
make -j4
if [ $? -ne 0 ]; then
    echo >2 "error: Compilation failed!"
    cd ${src_dir}
    exit 1
fi

echo >2 "notice: Running ex01..."
./ex01
if [ $? -ne 0 ]; then
    echo >2 "error: Execution failed!"
    cd ${src_dir}
    exit 1
fi

cd ${src_dir}
rm -fr ${build_dir}
exit 0

# end
