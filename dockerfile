FROM ubuntu:24.04

RUN apt update && apt install -y \
  cmake \
  clang-18 \
  clang-tools-18 \
  ninja-build

WORKDIR /app
COPY . .
RUN CXX=clang++-18 cmake -GNinja -DCMAKE_BUILD_TYPE=Release -B build .
WORKDIR /app/build
RUN ninja test_lib_example_linked_list test_lib_example_many_file test_lib_example_multithread_cache
RUN ./test_lib_example_linked_list 1000
RUN ./test_lib_example_many_file
RUN ./test_lib_example_multithread_cache