#!/bin/bash

if ! command -v qemu-system-aarch64 >/dev/null 2>&1; then
    echo "qemu-system-aarch64 missing"
    echo "You can install it using 'sudo apt-get install qemu-system' on debian based systems"
    exit 1
fi

file_name="eos-project"
qemu-system-aarch64 -M raspi3b -serial stdio -s -S -kernel "$(dirname "${BASH_SOURCE[0]}")/../cmake-build-debug/$file_name.img"
