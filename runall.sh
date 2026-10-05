#!/usr/bin/sh

MOD="zombies"

./build.sh
./deploy.sh $MOD
./runmod.sh $MOD
