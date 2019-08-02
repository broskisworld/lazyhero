# lazyhero

Basic platformer game engine with entities, collisions, animations, world building, and sample AI implementation. Originally based on a project by Josh Bosley (me) and Timothy Luebke (my roommate) from the 24-hour USU Hackathon coding competition.

## Basic Heirarchy

### Files

`lazyhero\assets` This folder contains all spritesheets + textures used by lazyhero. Any file inside of this folder will be automatically found by Cinder (the graphics engine) by calling the `loadAsset("example.png")` function

`lazyhero\vc2013` Here's where the bulk of the actual project files are, and is the project home directory for visual studio.

### Classes

`lazyheroApp` is the entry point from the graphics library to all top level functions of lazyhero. Game initialization starts here, graphics and physics updates are triggered by the `update()` and `draw()` functions, and user input data is received here.


`LazyWorld` is where the bulk of the game is built. Anything that relates to the gameplay itself is found here. Level building, list of game entities and physics objects, physics updates, and the camera object are all accessed via the `LazyWorld` class.
Important game vars:
- `vector<vector<Block>> worldData` is a 2d vector for holding all of the blocks in an associated level. When `createWorldFromList()` is called, a list of 2d vectors is generated representing the outline of the level. 
- `vector<Line2> blockOutlines` is that list of lines. Once loaded into Box2D as rigidbodies during the createWorldFromList(), this is simply a reference of lines to draw during the render phase. If textures are desired to be displayed as opposed to simply a world outline, this may be obsolete
- `vector<Entity *> worldEntities` is a list of all entities currently in the world. Everytime Cinder calls `update()`, each entity's `stepAI()` function is called, and everytime Cinder calls `draw()`, each entity's `draw()` function is called.
- `b2World * physWorld` is the Box2D world.
- `vector<b2Body *>` physicsBodies is a list of every physics body in the Box2D world.
- `Camera2D cam` is the class that handles OpenGL's drawing, and has the algorithm to loosely follow the hero's XY coordinates.

`InputManager` simple wrapper class to handle key presses and releases from Cinder and hold their values in public booleans.

`Block` simple class for static level blocks. Not affected by physics. Currently drawing has been disabled for blocks, replaced instead with the outline only.

`Camera2D` follows a fixed XY coordinate and can be configured to follow exactly, or more loosely (like how it currently is). `setFixPoint(x, y)` is called periodically from the hero to keep its fix point on the hero.

`Entity` defines anything that moves in the game. Whether it has an "active" ai or not, anything that obeys (at least some) laws of physics fits here. Anything that inherents from `Entity` has both an `stepAI()` and `draw()` function, though they can be overriden. Currently the default `draw()` function assumes that all entities have an associate animation. I plan to change this(?)

`Hero` Our lovely hero. Inherits from the `Entity` class and uses the default `draw()` function but has special ai functionality to follow key input from the user, wall-jump, and do pretty animations while he does so.

`ninja` Unimplemented enemy character I was in the middle of designing. Why did my naming scheme change around 4am? Not sure.


## Toolchain

### Cinder
lazyhero uses [Cinder](https://libcinder.org/) for graphics and audio (current version 0.9.1). Once you have downloaded it and extracted the files, you need to create an environment variable on your PC called CINDER_DIR, and set its value to the path where you extracted Cinder. If you don't create that variable, lazyhero will not be able to link correctly. However, we have been having issues with dependancies recently (hopefully fixed), so lmk if the project doesn't link automatically.

### Visual Studio
Cinder requires the C++ build tools from Visual Studio 2013. While you can still develop and compile on newer versions of visual studio (I've been using VS2017) you MUST have Visual Studio 2013 installed. Downloading the v120 build tools from Microsoft will not suffice as they don't include the C++ tools included. You may need a Microsoft account to download the older version of VS. I found it [here](https://visualstudio.microsoft.com/vs/older-downloads/). Sign in and download "Visual Studio Community 2013 with Update 5."

### Box2D/OpenGL
lazyhero also used Box2D for all physics interations, but should be included in the repo already. Cinder is OpenGL based, and I haven't had any issues with versions or hardware capability but lmk if you find something :)

## Gallery

![Sample Gameplay 1](/gallery/1.png)
![Sample Gameplay 2](/gallery/2.png)
![Sample Gameplay 3](/gallery/3.png)
