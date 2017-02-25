#!/bin/bash

cd "build/"

# Conan setup
conan install

# CMake setup
cmake "../" -G"Visual Studio 14 2015 Win64"

# Get Visual Studio files
declare projectFileRegex='^\.\/(source\/(.*)?)?(\w|-)*?(.sln|.vcxproj(.filters)?)$'
declare -a targets=( $( find . | grep -E $projectFileRegex ) )

# Move project files (targets) one folder down
printf "Copying build files..\n"
for f in "${targets[@]}"
do
  :
  printf "Copying %s to %s\n" "$f" ".$f"
  cp $f ".$f"
done
