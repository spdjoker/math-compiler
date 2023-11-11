# Setup a clean workdir for building and running the binary
from docker.io/archlinux

run pacman --noconfirm -Sy
run pacman --noconfirm -S fish git
env DEBUGINFOD_URLS "https://debuginfod.archlinux.org"

run pacman --noconfirm -S make gcc valgrind gdb cmake

workdir /build

entrypoint ["bash", "-c", "fish"]
