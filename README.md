# MY Quake4 Mod

Hello. This is for my IT266 class. I may move this to another Github account for school, but I could use this for my portfolio too.

I have created some scripts to build, deploy, and run the mod. I also created a mod folder which will contain all assets (and def files) that will be pasted into the mod folder. I love bash.

## rocket_mod branch

Quick word on some things. I spent a lot of time yesterday debugging an issue with the `god` command failing in singleplayer. I also spent a lot of time trying to trace the code that is responsible for applying forces from explosions, and got super lost. It turns out that the code is already written, it just had to be enabled (I found this out from one of the former students on their github [here](https://github.com/98jfiore/Quake4RocketMod/commit/60d3a38023f8fdaae5cb0ce7a3fc733827475339#diff-1b7b75626355255c405efe9171da4d4457bcd215d41fd3af73e27424fd86bf85R10173)). I would've had no idea where to look. (I DID NOT STEAL THIS CODE!!! Please check commit history to see what I've done)


> [!WARNING]
This project is a Linux project. The CMakes provided has only been tested on Linux, as well as the shell scripts. Also note that the shell scripts are catered towards the tools I have (notably libzip). To whom it may concern, I have HANDWRITTEN these scripts and know what they do. I'm not sure how hard it will be to grade since I am on a different operating system, but please take my word that the work I show is honest. I can elaborate on anything with enthusiasm.
