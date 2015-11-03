#!/bin/bash

# Script that loads a progam directly into the mbed microcontroller's flash memory and launches it

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SCRIPT_NAME=`basename "$0"`
PRGM_SCRIPT="$SCRIPT_DIR/mbed-prgm.py"

# sets up the environment for shell colors
source $SCRIPT_DIR/colors

# check to make sure we were passed at least one file
USAGE="Usage: $SCRIPT_NAME <files-to-transfer>..."
if [ "$#" == "0" ]; then
    echo "$USAGE"
    exit 1
fi

# check for every file that was passed and make sure it exists
for i in "$@"; do
    if [ ! -e "$i" ]; then
        echo "${RED}${WHITEBG}${INVT}File $(basename $1) not found...${R}"
        exit 2
    fi
done

# become root if all the syntax is good and the files exist
if [ $UID -ne 0 ]; then
    echo "--  Becoming root"
    exec sudo $0 $@
fi

# get the mbed's serial path and exit if not found
MBED_SER_PATH=$(python $PRGM_SCRIPT --get-path 2>&1)
if [ -z "$MBED_SER_PATH" ]; then
    msg="No mbed device detected!"
    printf "$WHITE $REDBG $PUTLN \n"
    printf "%*s${FINLN}\n" $(((${#msg}+$(tput cols))/2)) "$msg"     # center align the message
    printf "$PUTLN$R\n"
    exit 2
else
    msg="mbed found at $MBED_SER_PATH"
    printf "$WHITE $BLUEBG $PUTLN \n"
    printf "%*s${FINLN}\n" $(((${#msg}+$(tput cols))/2)) "$msg"     # center align the message
    printf "$PUTLN$R\n"
fi

# exit if anything fails from here on out
set -e

MBED_DEV=$(sudo blkid -L MBED)

# get the mount point for the flash storage
IFS=' ' read -a dev_fields <<< $(mount | grep $MBED_DEV)
MNT_DIR=$(echo "${dev_fields[2]}")

if [ -z "${MNT_DIR}" ]; then
    msg="mbed has no mount point!"
    printf "$WHITE$REDBG$PUTLN\n"
    printf "%*s${FINLN}\n" $(((${#msg}+$(tput cols))/2)) "$msg"     # center align the message
    printf "$PUTLN$R\n"
    exit 3
fi

# loop through all the passed file and send them to the mbed
for i in "$@"; do
    # send the file with the python script
    python $PRGM_SCRIPT --no-fat-write --load-memory --wait --file=$i --destination=$MNT_DIR

    if [ $? -eq 0 ]; then
        # Yay, we made it!
        msg="Program load SUCCESS!"
        printf "$WHITE$GREENBG$PUTLN\n"
        printf "${BOLD}%*s${AOFF}${WHITE}${GREENBG}${FINLN}\n" $(((${#msg}+$(tput cols))/2)) "$msg"   # center align the message    
        printf "$PUTLN$R\n"
    else
        # something went wrong
        msg="Program load FAILED!"
        printf "$REDBG$PUTLN\n"
        printf "${BOLD}%*s${AOFF}${WHITE}${REDBG}${FINLN}\n" $(((${#msg}+$(tput cols))/2)) "$msg"   # center align the message
        printf "$PUTLN$R\n"
    fi
done


# Script that loads a progam directly into the mbed microcontroller's flash memory and launches its execution
# SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
# source $SCRIPT_DIR/colors

# # Become root
# if [ $UID -ne 0 ]; then
#     echo "--  Becoming root"
#     exec sudo $0 $@
# fi

# MBED_DEV=$(sudo blkid -L MBED)
# MBED_DEVICES_PATH="$(ls /dev/disk/by-id/ | grep -i mbed | sed 's\.*\/dev/disk/by-id/&\g')"

# if [ -z "$MBED_DEV" ]; then
#     echo "--  No mbed device(s) found"
#     exit 0
# else
#     echo "--  device found at $MBED_DEV"

#     IFS=' ' read -a dev_fields <<< $(mount | grep $MBED_DEV)
#     MNT_DIR=$(echo "${dev_fields[2]}")

#     if [ -z "$MBED_DEV" ];then
#         if [ -z "${MNT_DIR#/}" ]; then
#             echo "--  mbed is not mounted"
#             exit 0
#         fi
#     else
#         PRGM_SCRIPT="$SCRIPT_DIR/mbed-prgm.py"
#     fi
# fi
