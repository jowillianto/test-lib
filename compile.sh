#!/bin/bash
while read -d "" event; do
  clear;
  cd build;
  cmake .;
  ninja;
  cd ..;
done