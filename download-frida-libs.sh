#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${DIR}"

VERSION="15.1.25"

rm -rf vendor/frida-core
rm -rf vendor/frida-gum

download_frida_core() {
  ARCH="$1"
  FRIDA_CORE_TAR="frida-core-devkit-${VERSION}-macos-${ARCH}.tar.xz"

  echo "- Download frida-core (${ARCH})"
  cd "${DIR}"
  rm -rf "vendor/frida-core/${ARCH}"
  mkdir -p "vendor/frida-core/${ARCH}"
  cd "vendor/frida-core/${ARCH}"
  wget "https://github.com/frida/frida/releases/download/${VERSION}/${FRIDA_CORE_TAR}"

  echo "- Extract frida-core (${ARCH})"
  tar -xJf "${FRIDA_CORE_TAR}"
  rm "${FRIDA_CORE_TAR}"
  cd "${DIR}"
}

download_frida_gum() {
  ARCH="$1"
  FRIDA_GUM_TAR="frida-gum-devkit-${VERSION}-macos-${ARCH}.tar.xz"

  echo "- Download frida-gum (${ARCH})"
  cd "${DIR}"
  rm -rf "vendor/frida-gum/${ARCH}"
  mkdir -p "vendor/frida-gum/${ARCH}"
  cd "vendor/frida-gum/${ARCH}"
  wget "https://github.com/frida/frida/releases/download/${VERSION}/${FRIDA_GUM_TAR}"

  echo "- Extract frida-gum (${ARCH})"
  tar -xJf "${FRIDA_GUM_TAR}"
  rm "${FRIDA_GUM_TAR}"
  cd "${DIR}"
}

download_frida_core x86_64
download_frida_gum x86_64

download_frida_core arm64
download_frida_gum arm64

download_frida_core arm64e
download_frida_gum arm64e

echo "- Done!"
