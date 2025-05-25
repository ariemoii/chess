#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=gcc --file=Build-Testing.lua gmake2
popd

buildType="debug"

for arg in "$@"; do
  if [ "$arg" == "--release" ]; then
    buildType="release"
  fi
done

echo "here"


cd ../Core
make config=$buildType
cd ../Testing
make config=$buildType