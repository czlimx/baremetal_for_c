#!/bin/bash
if [ $# != 2 ];then
    echo -e "\033[31m please select project::release.sh <am3358 am6254 am5718 stm32h750 h6> <freertos rt-thread threadx tryrtos>. \033[0m"
    exit 0
fi

case $1 in
    "am3358" | "am5718" )
            echo -e "\033[32m Start to compile the $1 board, please wait patiently. \033[0m"
            cmake -B build/$1 -DRTOS_KERNEL=$2 -DRTOS_BOARD=$1 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./cmake/$1.cmake -G "Unix Makefiles" -S .
            make -C build/$1 --no-print-directory
            ;;
    "h6" | "am6254" | "stm32h750" )
            echo -e "\033[31m The $1 boards will be supported in the future. \033[0m"
            ;;
    *)
            echo -e "\033[31m The $1 boards will be supported in the future. \033[0m"
            ;;
esac
