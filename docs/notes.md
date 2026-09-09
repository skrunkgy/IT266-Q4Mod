# Notes

Here are some notes about getting this project to work at all.

## The original Quake 4 Linux binaries

As mentioned, id used to provide these binaries in the form of a "makeself" file on their ftp servers. This ftp server has since been vaporized or something, but mirror sites provided them thankfully.

I restructured the files to get rid of some junk, as well as adding some QoL stuff. This is all packaged into a tarball I store in my home server, where a script can later grab it and do some stuff to create a complete copy.

## Research

The Linux binaries initially look in the `$HOME/.quake4` as its "fs_savepath" (or "fs_basepath"). These variables are where the binary looks for the CD key, the configs, and where they write saves to. However, for tidiness we run the binary with the option to look inside its own directory instead. If the game is still asking for a CD key, check your original copy and look for `.../q4base/quake4key` and copy it into the `q4base` folder inside the Linux copy. If you can't find this file, ~~you are comitting theft~~ run the game once and it should be generated.

The binary also did not ship with default search paths for libraries, so we also manually pass this. This may be a source of failure, since I set it to look inside the current directory, `/usr/lib` and `/usr/lib32`. I have no idea where libraries are stored on other distros, as I use CachyOS (Arch based).

## The tarball

Currently, the tarball I made is hosted my own machine. You have every right to be sketchy about this, and I have no way to convince you that this isn't malware. However, I provide a checksum in the script as a layer of protection in the case aliens zap my server or something.

## Libraries

This is probably where most of the troubleshooting will come from. I have no idea what libraries are needed. The tarball comes with some dynamic libs that gets searched for.

For example, the `libSDL-1.2.so.0` library is needed for the `quake4.x86` binary and was pulled from my system, which is pretty up to date (since 2024). However, that comes from the `lib32-sdl12-compat` package, which needs SDL2, which I will not supply (sorry). For `quake4smp.x86`, it links against their own version of the library called `libSDL-1.2.id.so.0`, which id provides. For now, we will use the regular `quake4.x86` binary. I provide my own copy of the library, but it needs an SDL2 backend, which is noted in the dependencies.

## Other notes

I think the game runs a bit more choppy, and I have no idea why. I think it is the SDL backend to blame, since its a compatability layer basically. Sigh.

## Other projects

Before jumping through all these hopes, I was initially eyeing a project that aimed to be a modern port of Quake 4 along with its source code entirely open. However, the project relies heavily on AI generated code, and I don't trust code written by either robots or people who rely on robots.

For any issues, please contact me on:
- Discord: @skrunkgy
- Matrix: @skrunkgy:gurtgames.com
