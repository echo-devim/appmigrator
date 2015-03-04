#!/bin/sh

cd ./AnjutaSource
./configure
make
cd ..
mkdir ./bin
mkdir ./bin/scripts
cp ./AnjutaSource/src/appmigrator.ui ./bin/appmigrator.ui
cp ./AnjutaSource/src/backupWindow.ui ./bin/backupWindow.ui
cp ./AnjutaSource/src/restoreWindow.ui ./bin/restoreWindow.ui
cp ./AnjutaSource/src/appmigrator ./bin/appmigrator
cp ./backend-scripts/* ./bin/scripts/

printf "Done! The program is in the bin folder (Press any key to exit)\n"

read


