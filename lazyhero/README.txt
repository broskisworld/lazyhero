The project lazyhero is a game/game engine. It was originally written for the 2018 HackUSU competition, and is owned solely by Josh Bosley and TJ Luebke.

directory tree + description
----------------------------
lazyhero
+-assets    sprites and images used by the game, automatically found by Cinder
|
+-blocks
| +-Box2D
|   +-src    parent include directory for Box2D includes
|
+-include    contains Resources.h (for Cinder's use?) - may be deleted later so do not place include files here
|
+-resources    same thing as "assets" folder? contains current cinder icon
|
+-src    DEPRECATED! old source files for lazyhero. no longer used, place source files in vc2013 directory
|
+-vc2013 PLACE SOURCE FILES IN HERE!!! (.cpp and .h)
| +-.vs    (hidden) for VS use
| |
| +-build
| | +-$(PlatformTarget)    currently "Win32"
| |   +-$(Configuration)    currently "Debug"
| |     +-intermediate    VS compile time stuff?
| |     |
| |     | lazyhero.exe    project executable
| |
| | *.cpp    source files
| | *.h    (header) source files
| | lazyhero.sln    project solution - open this file in visual studio NOT THE WHOLE REPO OR WILL NOT COMPILE
|
+-cinder
| +-include    parent include directory for Cinder includes
| |
| +-lib
|   +-$(PlatformTarget)    one of the library dependancy parent directories for Cinder libraries
|     +-$(Configuration)
|       +-$(PlatformToolset)    another necessary library dependancy parent directory
|
| README.txt    this file

source file descriptions
------------------------
TODO: finish README.txt XD