buildType="Release"

# for arg in "$@"; do
#   if [ "$arg" == "--release" ]; then
#     buildType="Release"
#   fi
# done

cd ../Binaries/$buildType
./Connector "$@"
