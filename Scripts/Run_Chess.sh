buildType="Debug"

for arg in "$@"; do
  if [ "$arg" == "--release" ]; then
    buildType="Release"
  fi
done

cd ../Binaries/linux-x86_64/$buildType/Chess-App
./Chess-App