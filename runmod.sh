#!/usr/bin/sh

# Script to launch the modded version of our game

QUAKE_DIR="$HOME/Games/Quake 4"
MOD_NAME="mod_name"

"$QUAKE_DIR"/quake4 +set fs_game $MOD_NAME
