#!/bin/bash
fswatch -0 -o ./src ./tests ./include CMakeLists.txt | ./compile.sh