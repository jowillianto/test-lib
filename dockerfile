FROM jowillianto/cpp-module-toolchain:noble-cmake3.31-ninja1.11-llvm17
WORKDIR /app
COPY . .
RUN cmake \
  -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DMODERNA_TEST_LIB_BUILD_TESTS=ON \
  -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
  -Bbuild .
WORKDIR /app/build
RUN ninja 
RUN ASAN_OPTIONS=alloc_dealloc_mismatch=0 ninja test 