## PainPlatformer
Powered by the "PainNSuffering" engine

Which is written in C++ and SDL2

### Building
To build, simply run the script relevant to your platform

#### Windows

```
powershell ./build-deps.ps1
```

#### Linux (Debian/Ubuntu based)
```
./build-deps-deb.sh
```

#### Linux (Arch/Manjaro based)
```
./build-deps-arch.sh
```

Then, enter the build folder and run
```
cmake --build .
```