# Rocket Research

This section of the documentation is for the `rocket_mod` branch. I will list research and whatever changes here. I want to make rocket jumping.

## God mode not working

God mode on singleplayer wasn't working. Turns out this SDK omitted the `isMultiplayer` check in the `idGameLocal::CheatsOk()` function. Glad I was able to debug this.
