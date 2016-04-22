if [ "$CPLUS_INCLUDE_PATH" ]
then
  export CPLUS_INCLUDE_PATH="$(dirname $(readlink -f -e "${BASH_SOURCE[0]}"))/cxx-prettyprint:$CPLUS_INCLUDE_PATH"
else
  export CPLUS_INCLUDE_PATH="$(dirname $(readlink -f -e "${BASH_SOURCE[0]}"))/cxx-prettyprint"
fi
export CPLUS_INCLUDE_PATH="$(dirname $(readlink -f -e "${BASH_SOURCE[0]}"))/gtest-1.7.0/include:$CPLUS_INCLUDE_PATH"

if [ "$LIBRARY_PATH" ]
then
  export LIBRARY_PATH="$(dirname $(readlink -f -e "${BASH_SOURCE[0]}"))/gtestbuild:$LIBRARY_PATH"
else
  export LIBRARY_PATH="$(dirname $(readlink -f -e "${BASH_SOURCE[0]}"))/gtestbuild"
fi
