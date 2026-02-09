#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=gcc --file=Build-Testing.lua gmake2
popd
cd ../Core
make configrelease
cd ../Testing
make config=release