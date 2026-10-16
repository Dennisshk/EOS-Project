#!/bin/bash
# see https://wiki.osdev.org/GCC_Cross-Compiler

# Switch to directory of script
script_path=$(dirname "$(realpath "${BASH_SOURCE[0]}")")
cd "$script_path"

# Install dependencies
sudo apt install -y \
       	build-essential \
       	bison \
       	flex \
       	libgmp3-dev \
       	libmpc-dev \
       	libmpfr-dev \
       	texinfo \
       	libisl-dev \
       	libncurses5-dev \
       	libpython3-dev

# Set configuration
export PREFIX="$script_path/compiler"
export TARGET=aarch64-none-elf
export PATH="$PREFIX/bin:$PATH"

# Download needed packages
mkdir -p compiler/src
cd compiler/src

curl https://ftp.gnu.org/gnu/binutils/binutils-2.46.0.tar.gz | tar -xz
curl https://ftp.gnu.org/gnu/gdb/gdb-17.1.tar.gz | tar -xz
curl https://ftp.gnu.org/gnu/gcc/gcc-12.5.0/gcc-12.5.0.tar.gz | tar -xz

# --- Build and install Binutils ---
mkdir build-binutils
cd build-binutils
../binutils-2.46.0/configure \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --with-sysroot \
    --disable-nls \
    --disable-werror \
    --with-python=$(which python3) \
    --with-tui \
    --with-curses
make -j 9
make install -j 9

# --- Build and install GDB ---
cd ..
mkdir build-gdb
cd build-gdb
../gdb-17.1/configure --target=$TARGET --prefix="$PREFIX" --disable-werror
make all-gdb -j 9
make install-gdb -j 9

# --- Build and install GCC --
cd ..
which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
../gcc-12.5.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc -j 9
make all-target-libgcc -j 9
make all-target-libstdc++-v3 -j 9
make install-gcc -j 9
make install-target-libgcc -j 9
make install-target-libstdc++-v3 -j 9
