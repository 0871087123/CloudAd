if [ $CXX != "g++" ];then
	export CXX=g++
	export CC=gcc
	echo "当前为标准C编译器"
else
	export PATH=$PATH:/home/kent/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
	export TOOLCHAIN=/home/kent/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian
	export TB_CC_PREFIX=arm-linux-
	export PKG_CONFIG_PREFIX=$TOOLCHAIN/arm-linux
	alias arm-linux-gcc=arm-linux-gnueabihf-gcc
	alias arm-linux-g++=arm-linux-gnueabihf-g++
	export CXX=arm-linux-gnueabihf-g++
	export CC=arm-linux-gnueabihf-gcc
	echo "当前为ARM-C编译器"
fi
