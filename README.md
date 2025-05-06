# Computer club

#### Build

From the root directory:

```bash
git submodule update --init --recursive # clones test framework

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

#### Usage

```bash
./build/comp_club <input-file>
```

#### Testing

Testing framework [gtest](https://github.com/google/googletest)

```bash
./build/test_comp_club # runs tests
```
