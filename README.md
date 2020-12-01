## Build instructions

These instructions require cmake.

Open a terminal or a git bash and clone the repo (or fork it and clone your fork if you
want to submit changes):

```bash
git clone https://github.com/Dauphine203/cpp_chess.git
cd cpp_chess
```

Create a `build` directory to avoid polluting the sources:

```bash
mkdir build
cd build
```

### Windows

Open a Native Tools for your compiler, cd to the `build` directory you've created before,
and run the following

```bash
cmake -G "NMake Makefiles" ..
nmake
```

Once this is done, you can run the program with

```bash
cpp_chess.exe
```

### Linux / OSX

Open a terminal, cd to the `build` directory you've created before, and run the following:

```bash
cmake ..
make
```

Once this is done, you can run the programm with

```bash
./cpp_chess
```
