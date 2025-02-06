#!/bin/bash
fswatch -0 -o ./src ./tests.cc ./include CMakeLists.txt | ./compile.sh