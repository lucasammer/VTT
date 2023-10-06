#!/bin/bash

current_directory=$(pwd)

echo "Starting building in $current_directory..."

if which g++ >/dev/null; then
  g++ main.cpp -o itt -I $current_directory -lX11
  echo "Finished building!"
  echo "to run use './itt'"
else
  echo "g++ is not installed."
fi