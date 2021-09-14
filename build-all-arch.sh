#!/usr/bin/env bash

build_arch() {
  ARCH="$1"
  cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="${ARCH}" -B "build-${ARCH}" .
  cmake --build "build-${ARCH}" -- install -j8
}

build_arch x86_64
build_arch arm64
build_arch arm64e
