#!/bin/bash

cd "build/"

#conan install

#cmake "../" -G"Visual Studio 14 2015 Win64"

declare projectFileRegex='^\.\/(source\/(.*)?)?(\w|-)*?(.sln|.vcxproj(.filters)?)$'
declare -a targets=( $( find . | grep -E $projectFileRegex ) )

printf "Copying build files..\n"
for f in "${targets[@]}"
do
  :
  printf "Copying %s to %s\n" "$f" ".$f"
  cp $f ".$f"
done



#declare -a projectFiles= {
#  "Amber-Sun.sln"
#  "Amber-Sun.vcxproj"
#  "Amber-Sun.vcxproj.filters"
#
#  "ALL_BUILD.vcxproj"
#  "ALL_BUILD.vcxproj.filters"
#
#  "ZERO_CHECK"
#}
