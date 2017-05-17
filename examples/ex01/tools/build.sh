#!/usr/bin/env bash

# A Bash script to build and install BxProtobuftools ex01 example on Ubuntu (16.04).

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

devel=false
bxprotobuftools_install_dir=

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

while [ -n "$1" ]; do
    opt="$1"
    if [ "${opt}" = "--bxprotobufinstall-prefix" ]; then
	shift 1
	bxprotobuftools_install_dir="$1"
    elif [ "${opt}" = "--devel" ]; then
	devel=true
    fi
    shift 1
done

if [ "x${bxprotobuftools_install_dir}" = "x" ]; then
    if [ ${devel} = true ]; then
	bxprotobuftools_install_dir="../../_install.d"
    else
	echo >&2 "[error] Missing BxProtobuftools installation path! Abort!"
	my_exit 1
    fi
fi
if [ ! -d ${bxprotobuftools_install_dir} ]; then
    echo >&2 "[error] No BxProtobuftools installation! Abort!"
    my_exit 1
else
    cd ${bxprotobuftools_install_dir}
    bxprotobuftools_install_dir=$(pwd)
    echo >&2 "[info] BxProtobuftools install dir = '${bxprotobuftools_install_dir}'"
    cd ${opwd}
    export PATH="${bxprotobuftools_install_dir}/bin:${PATH}"
fi

which bxprotobuftools-query > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo >&2 "[error] BxProtobuftools is not installed! Abort!"
    my_exit 1
fi

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

mkdir -p ${build_dir}

echo >&2 ""
echo >&2 "[info] Configuring..."
cd ${build_dir}
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DBxProtobuftools_DIR="$(bxprotobuftools-query --cmakedir)" \
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

echo >&2 "[info] Build dir:"
tree ${build_dir}
echo >&2 ""

echo >&2 ""
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

echo >&2 "[info] Installation dir:"
tree ${install_dir}
echo >&2 ""

my_exit 0

# end
