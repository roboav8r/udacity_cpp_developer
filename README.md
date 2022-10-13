# udacity_cpp_developer
C++ developer nanodegree program on Udacity

# Prerequisites - Linux
```
sudo apt update
sudo apt install build-essential
sudo apt install gdb
```

I also recommend using VSCode with the "C/C++" and "Clang-Format" extensions.

# Installation
In your home directory:
```
cd ~
git clone --recursive https://github.com/roboav8r/udacity_cpp_developer.git
```

# Projects
## System Monitor
This project parses the different files in the Linux file system and displays relevant information about the running processes and system usage.

### Usage
To build and run the system monitor, execute the following commands:
```
cd ~/udacity_cpp_developer/CppND-System-Monitor-Project-Updated
make build
./build/monitor
```

# Potential improvements
## System Monitor
- Use stringstream in `format.cpp`
- Move type declarations from `format.cpp` to `format.h` 