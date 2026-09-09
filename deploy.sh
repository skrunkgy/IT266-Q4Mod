#!/usr/bin/sh

# Simple script to copy compiled project into my game.

QUAKE_DIR="$HOME/Games/Quake\ 4"
cp -T build/gamex86.so $QUAKE_DIR/q4base/gamex86.so
