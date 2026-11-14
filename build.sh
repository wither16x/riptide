#!/bin/bash

# Workaround for https://github.com/Gag91/HelpMake/issues/3

cd riptide/client || exit

if [[ "$1" == "--clean" ]]; then
    hm --clean
    exit
fi

hm -b --json
cd ..