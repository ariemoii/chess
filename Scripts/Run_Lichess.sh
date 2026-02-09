buildType="Release"

# for arg in "$@"; do
#   if [ "$arg" == "--release" ]; then
#     buildType="Release"
#   fi
# done

mv ../Binaries/Release/Connector ../../lichess-bot/engines/

cd ../../lichess-bot/


#from https://github.com/lichess-bot-devs/lichess-bot/wiki/How-to-Install
python3 -m venv venv # If this fails you probably need to add Python3 to your PATH.
virtualenv venv -p python3
source ./venv/bin/activate
python3 -m pip install -r requirements.txt

python3 lichess-bot.py