#!/bin/bash
fswatch -0 -o ./src ./tests.cc  CMakeLists.txt | ./compile.sh