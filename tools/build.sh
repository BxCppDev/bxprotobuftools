#!/usr/bin/env bash

# A Bash script to build and install devel BxPrototools on Ubuntu (16.04).

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

devel=false
pb_prefix=

while [ -n "$1" ]; do
    opt="$1"
    # echo >&2 "[debug] opt='${opt}'"
    if [ "${opt}" = "--protobuf-prefix" ]; then
	shift 1
	pb_prefix="$1"
    elif [ "${opt}" = "--devel" ]; then
	devel=true
    fi
    shift 1
done

if [ "x${pb_prefix}" = "x" ]; then
    if [ ${devel} = true ]; then
	pb_prefix="/opt/sw/GoogleProtocolBuffers/install-3.0.0"
    else
	echo >&2 "[error] Missing Protobuf installation path! Abort!"
	my_exit 1
    fi
fi

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

mkdir -p ${build_dir}

cd ${build_dir}
echo >&2 ""
echo >&2 "[info] Configuring..."
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DPROTOBUF_ROOT:PATH="${pb_prefix}" \
    ${src_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] CMake failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Building..."
make -j4
if [ $? -ne 0 ]; then
    echo >&2 "[error] Build failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

# tree ${install_dir}

my_exit 0

# end
