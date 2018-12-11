#
# This scripts install alls what needed on osx
#

if [ $(uname -s) != "Darwin" ]; then
  echo "Available only on OSX"
  exit
fi

# Check if brew exists
if [ -z $(command -v brew) ]; then
  echo "Unable to find brew, please install or it's folder to \$PATH environment variable"
  exit
fi

brew install glew
