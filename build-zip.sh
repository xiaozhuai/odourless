#!/usr/bin/env bash

PROJECT_ROOT="$1"
SRC_APP="$2"
VERSION="$3"
DIST="$4"
ARCH="$5"

echo "Clear dist"
rm -rf "${DIST}"
mkdir -p "${DIST}"

echo "Copy app to dist"
cp -r "${SRC_APP}" "${DIST}/"

echo "Create zip"
cd "${DIST}" || exit
zip "Odourless-${ARCH}-${VERSION}.zip" -r "Odourless.app" > /dev/null
cd - || exit
