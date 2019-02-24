# Scop

3D object renderer from object files
Work only on OSX >= ElCaptain and Windows 10

# Build

## Windows

Installing [Visual Studio 15 2017](https://visualstudio.microsoft.com/fr/vs/features/cplusplus/) will provide you all the build tools necessary to compile a program on Windows ...
In our case, we will ue [cmake](https://cmake.com).

```ps
# Make sure the path to cmake in your environment Path variable with the following command in Powershell
# $env:Path = "path/to/cmake";
git submodule init
cmake .
cmake --build  .
```

## OSX
```bash
git submodule init
make
```
