#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=gcc --file=Build-Lichess.lua gmake2
popd

buildType="release"

# for arg in "$@"; do
#   if [ "$arg" == "--release" ]; then
#     buildType="release"
#   fi
# done


cd ../Core
make config=$buildType
cd ../UCI-connector
make config=$buildType