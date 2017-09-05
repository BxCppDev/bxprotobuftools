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

function my_usage()
{
    cat<<EOF

Options:

   --help             : print help
   --boost-root path  : set the Boost installation base directory

EOF
    return
}


src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d
boost_root=
protobuf_prefix=
brew_it=0

devel=false

while [ -n "$1" ]; do
    opt="$1"
    if [ "${opt}" = "--protobuf-prefix" ]; then
	shift 1
	protobuf_prefix="$1"
    elif [ "${opt}" = "--boost-root" ]; then
	shift 1
	boost_root="$1"
    elif [ "${opt}" = "--brew" ]; then
	brew_it=1
    else
	echo >&2 "[error] Invalid command line switch '${opt}'!"
	exit 1
    fi
    shift 1
done

if [ ${brew_it} -ne 0 ]; then
    boost_root="$(brew --prefix)"
    protobuf_prefix="$(brew --prefix)"
fi

which protoc
if [ $? -ne 0 ]; then
    echo >&2 "[error] Protocol Buffers compiler is not installed! Abort!"
    my_exit 1
fi
pkg-config --exists protobuf
if [ $? -ne 0 ]; then
    echo >&2 "[error] No pkg-config support for Protocol Buffers! Abort!"
    my_exit 1
fi

pkg-config --atleast-version=3.0.0 protobuf
if [ $? -ne 0 ]; then
    echo >&2 "[error] Invalid version of Protocol Buffers! Abort!"
    my_exit 1
fi
protobuf_version=$(pkg-config --modversion protobuf)
protobuf_prefix=$(pkg-config --variable=prefix protobuf)
if [ "x${protobuf_prefix}" = "x" ]; then
    echo >&2 "[error] Missing Protocol Buffers installation path! Abort!"
    my_exit 1
else
    echo >&2 "[info] Found Protocol Buffer version ${protobuf_version} at ${protobuf_prefix}."
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
boost_option=
if [ -n "${boost_root}" ]; then
    boost_option="-DBOOST_ROOT:PATH=${boost_root}"
fi
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    ${boost_option} \
    -DPROTOBUF_ROOT:PATH="${protobuf_prefix}" \
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
echo >&2 "[info] Testing..."
make test
if [ $? -ne 0 ]; then
    echo >&2 "[error] Some tests failed! Abort!"
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
