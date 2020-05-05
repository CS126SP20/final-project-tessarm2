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
