#!/usr/bin/sh

# Script that puts our binary into the pak file in our mod folder (or creates pak file then does it)

QUAKE_DIR="$HOME/Games/Quake 4"
MOD_NAME="rocket_mod"

# Check if we have ziptool. Not really needed.
which ziptool 1>/dev/null 2>/dev/null
if [ $? -ne 0 ]; then
	echo "Bro get libzip. Aborting"
fi

# Make the directory, and ignore the warning if it doesn't exist
mkdir -p "$QUAKE_DIR/$MOD_NAME" 2>/dev/null

# Check for the game100.pk4, and copy it from /q4base if it doesn't exist
ls "$QUAKE_DIR/$MOD_NAME/game100.pk4" 1>/dev/null 2>/dev/null
if [ $? -ne 0 ]; then
	cp "$QUAKE_DIR/q4base/game100.pk4" "$QUAKE_DIR/$MOD_NAME/"
fi

# Copy content of our mod folder into the deployed mod's directory
cp -r mod/* "$QUAKE_DIR/$MOD_NAME/"

# I am so sorry if this looks like crap, this library is so ass
TARGET_PK4="$QUAKE_DIR/$MOD_NAME/game100.pk4"
INDEX=$(ziptool "$TARGET_PK4" name_locate gamex86.so 0 | awk '{print $9}')
BIN_SIZE=$(ls -l build/gamex86.so | awk '{print $5}')

# Delete the binary and add the new one
ziptool "$TARGET_PK4" delete $INDEX
ziptool "$TARGET_PK4" add_file gamex86.so build/gamex86.so 0 $BIN_SIZE
