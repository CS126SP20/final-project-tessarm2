# Development

4/23/20
---
Forget to fill this out for  a week. At this point in the project I have made 
the headers and class files I thought I might need. I played around with the 
cinder textbox class to try and make a name input screen. After much trial and error
with the print function, this was completed. I added block2D but realized I was not really
using the physics functions and switched to using Cinder-poSpritesheet to animate
the player. 
- Need to do: Make it so the player can control the sprite with the arrow-keys

4/24/20
---
After the above, I got used to using poSpritesheet and managed to get the 
chicken animation to play. However, it would only play in the top right corner. I considered
editing the library, but realized if I changed the matrices of opengl, I could
draw the player wherever I needed. On top of that, I realized
I could use the matrices to draw the background so that it scrolls
when the player reaches the edge.
- Need to do: Implement objects, NPCs, a border, and the fight mechanic

4/28/20
---
I worked on implementing game objects and NPCs. Ran into some issues with cinder lib
being outside of my_app, so I reformatted the game_object to load
the textures in my_app and have them passed in. Next, I tried to make it
so that if the player was going to collide with an object, they could not move.
This was difficult, because using the debugger I discovered Cinder considers the location the top-left corner, so
the player could walk into an object's sprite. Fixed this, but I am not 100% satisfied due to some
remaining overlap. I also added a function to print a textbox
of an object's description when a player interacts with it.
- Need to do: Add NPCs and make it so talking to them triggers a fight
- The code is starting to get a bit messy, should keep an eye on later clean-up

4/30/20
---
Added NPC class and animations. Refactored code a bit and removed repition when checking for object collision vs
checking for interaction with NPCs. Caused some issues with the game object vectors, 
but fixed them. Deleted classes and headers I am not using and began outlining
how the fight system is going to work.
- Still need to make fight engine and UI
- Considering adding a seperate Player class
- the text_input class is messy, lots of things are public that shouldn't be
- items???????? if I have time
- the setup() for my_app is cluttered, because each texture needs to be initalized
for the sprite animations and objects, thinking about how to fix this

5/1/20
---
Created a Player class rather than keeping track of player stats in my_app. Made an outline
for how items could work with enums and stat changes for if I decide to use them. Made it so
talking to a hostile NPC triggers a fight, but I am still working
on the UI and turn sequences. Also changed some long if statements to switch cases.
- Need to write fight UI and turns

5/4/20
---
Decided to delete item use in favor of a simple healing mechanic during battle. Working
on setting up battle UI and getting a three option menu to open and close
depending on if it is the player's turn. Made it so background shifts between red, black, and purple
during the battle.
- Need to make it so player can deal damage/take damage
  and set up turn based combat. 

5/5/20
---
Finished fight system (took a while, oof). Had an issue that the player and enemy health would reset after
the battle and the enemy would still be drawn on the map. Changed fight engine to take pointers, because it
was copying the given Objects, so the health was ultimately not changed. Decided to add an element
of randomness to damage and healing to spice things up a bit. Fixed bug where player could access fight menu after being killed.
- Need to finish drawing assets
- Clean up code and add comments

5/6/20
---
