#!/usr/bin/env bash

PROJECT_ROOT="$1"
SRC_APP="$2"
VERSION="$3"
DIST="$4"

echo "Clear dist"
mkdir -p "${DIST}"
rm -rf "${DIST}/Odourless.app"
rm -f "${DIST}/Odourless_*.zip"

echo "Copy app to dist"
cp -r "${SRC_APP}" "${DIST}/"

echo "Copy dylibs"
mkdir -p "${DIST}/Odourless.app/Contents/Frameworks"
cp "${PROJECT_ROOT}/vendor/wxwidgets/lib/libwx_osx_cocoau-3.1.dylib" "${DIST}/Odourless.app/Contents/Frameworks/"
install_name_tool -change "@rpath/libwx_osx_cocoau-3.1.dylib" "@executable_path/../Frameworks/libwx_osx_cocoau-3.1.dylib" "${DIST}/Odourless.app/Contents/MacOS/odourless"

#otool -L "${DIST}/Odourless.app/Contents/MacOS/odourless"
#otool -L "${DIST}/Odourless.app/Contents/Frameworks/libwx_osx_cocoau-3.1.dylib"
#install_name_tool -id "xxx" xxx/dylib

echo "Create zip"
cd "${DIST}" || exit
zip "Odourless_${VERSION}.zip" -r "Odourless.app" > /dev/null
cd - || exit
