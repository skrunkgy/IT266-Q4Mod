# Quake4SDK

SDK and tools to run Quake 4 on Linux, as well as develop mods for it. Uses CMake to build binaries, and focuses on the GCC/Make for building. Heavily modified from `Xanz/Quake4SDK` until I pulled the source coed from an id mirror archive and fixed the code myself!!

# Dependencies

For the SDK you must have:

- You must have CMake 3.13 or greater
- GCC compiler
- A VALID COPY OF QUAKE 4 SOMEWHERE!!!

# Setup

## Quake 4 on Linux

Quake 4 did not ship with any Linux binaries, but id software USED TO provide a binary to patch it. I have created a script to automate most of the setup.

```
./install.sh [-o OUTPUT_DIR] [-s QUAKE_DIR]

-o		Specifies where the new Linux version will live. Defaults to "~/Games/Quake 4"
-s		Specifies where the old Quake 4 lives. Defaults to "~/.local/share/Steam/steamapps/common/Quake 4"
```

Make sure curl is installed, or the script will complain and bail.

## Dependencies

### Arch / Arch based

For Arch, make sure you have `[multilib]` section enabled in `/etc/pacman.conf`. Then, run:
```$ sudo pacman -Sy```
and then make sure the following packages are installed:
- lib32-glibc
- lib32-libxext
- lib32-libx11
- lib32-zlib
- lib32-mesa
- lib32-sdl2

### Ubuntu

To enable multilib on Ubuntu, run:
```$ sudo dpkg --add-architecture i386```
and then refresh the repositories:
```$ sudo apt update```

Then, make sure the following packages are installed:
- gcc-multilib
- libx11-6:i386
- zlib1g:i386
- libxext6:i386
- libgl1:i386
- libsdl2-2.0-0

## Developing with the SDK

Simply use your favorite IDE to modify the source code. When you want to build it, simply run `build.sh`. This will provide a `gamex86.so` file in the `build` directory.

A `deploy.sh` script is provided to insert the binary into a .pk4 file inside the game installation directory. Please edit this script if the default Quake 4 path is not matched.

A `runmod.sh` script is provided to launch the game under the mod directly. Please change the mod name in this script (and install path of Quake 4) if they don't match.

For more inquiries, refer to [here](docs/notes.md)
