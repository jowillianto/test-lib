FROM jowillianto/cpp-module-toolchain:noble-cmake3.31-ninja1.11-llvm17
WORKDIR /app
COPY . .
RUN cmake -GNinja -DCMAKE_BUILD_TYPE=Release -B build .
WORKDIR /app/build
RUN ninja test