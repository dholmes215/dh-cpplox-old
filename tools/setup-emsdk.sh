#!/bin/bash

# This script installs the Emscripten SDK according to the instructions at:
# https://emscripten.org/docs/getting_started/downloads.html

REPO_ROOT=`git rev-parse --show-toplevel`
TOOLS_ROOT=$REPO_ROOT/tools

RUNNING_SCRIPT=$(realpath "$0")
EXPECTED_SCRIPT=$(realpath $TOOLS_ROOT/setup-emsdk.sh)

if [ "$RUNNING_SCRIPT" != "$EXPECTED_SCRIPT" ]; then
    echo "setup_emsdk.sh must be run from within the project git repository"
    exit 1
fi

cd $TOOLS_ROOT

# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk

# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh

echo "Emscripten environment variables have been set and paths have been added to your PATH for the current shell only.  To make this persistent, you can run:"
echo "    echo 'source \"/home/david/git/cpp-template-2/tools/emsdk/emsdk_env.sh\"' >> $HOME/.bash_profile"
echo "This script did not do that for you."
