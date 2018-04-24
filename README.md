# Angry Birds

A non-physics recreation of the popular mobile game Angry Birds within ASGE.

irrKlang libraries are required to run the game - copy them to the exe folder from the prerequisites zip.

UML and pseudocode can be found within /Planning/.

## Additional Notes

LevelBuilder is available in the /Resources/LEVELS/ folder once the game is built - this is the tool I used to create levels for the game! 

Feel free to give it a go, you'll just have to rename the level file it outputs to an existing level filename (0,1,2,3). I've removed the dynamic menu I had since I now use premade images rather than text.

Enabling editor mode in LevelBuilder will enter you into the level editor when you next launch Angry Birds. Controls are on-screen.

Be careful not to exceed the "engine limits" for block counts when creating a level... these are specified in AngryGameVars.h.