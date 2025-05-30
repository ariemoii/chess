./Setup-Linux.sh

buildType="debug"

for arg in "$@"; do
  if [ "$arg" == "--release" ]; then
    buildType="release"
  fi
done

cd ../Core
make config=$buildType
cd ../Chess-App
make config=$buildType