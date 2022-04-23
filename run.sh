#!/bin/bash


opt=$@

[ ! -d build ] 				&& mkdir -pv build
[ ! -d build/default ] 		&& mkdir -pv build/default
[ ! -d build/bin/lua ] 		&& mkdir -pv build/bin/lua

pushd build &> /dev/null

	#rm -r bin/
	# [ ! -d bin ] && mkdir bin
	
	echo " * Configure CMAKE files"
	#cmake -B Debug -DCMAKE_BUILD_TYPE=Debug ..
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	#cmake --config Debug ..
	echo " * Build project in $PWD"
	make -j8
	pushd bin &> /dev/null
	
		mv ../llbuilder .
		cp -r ../../lua .
		catchsegv ./llbuilder $opt	
	
	popd &> /dev/null

popd &> /dev/null

