# Travellers Tales PSX Collision & GFX viewer

Travellers Tales videogame company realeased 7 PSX videogames that uses the same 3D engine adding some engine changes/improvements until TS2:

- **Rascal**: This is the first PSX title developed by Travellers Tales. It is said to be the worst PSX game ever made. This was due to the use of rotational control, and TT team beeing focused on the development of Sonic R.
- **Bugs Life**: Videogame based on the same title Pixar movie. It (finally) uses directional controls.
- **Toy Story 2**: Videogame based on the same title Pixar movie. It is the best of the 5 PSX videogames with lots of games sold and a rating of 9.1/10 (Metacritic)
- **Toy Story Racer & Muppet Race Mania**: Two nearly identical racing games with multiplayer support.
- **Weakest Link**: Simple QA videogame based on the same name TV show.
- **Buzz Lightyear of Star Command** (BLSC): This game is based on the animated series of the same name. This game was probably made due to the success of the TS2 game.

## How to use
You can try the online version of the tool [here](https://priceless-pike-6c8ff8.netlify.com/ "here").
The collision & GFX viewer reads the collision and GFX data from PSX savestates from an emulator (PSXE). These savestates must be uncompressed, and you must uncompress them first by renaming it's extension to **.GZ** and using your favorite tool like 7Zip / WinRAR to uncompress it.
Anyway, some example savestates are provided.

The controls are the following:
- **WASD**: move
- **QE**: rotate
- **Mouse move**: look arround
- **Mouse click**: select/deselect object

# Travellers Tales PSX Collision viewer

The collision viewer core is in *viewer.html*  and you should pass it a *file* parameter with the name of the file inside the *SSTATES* folder and a *game* parameter with the game wich correspond the savestate. You have links with this parameters in *index.html*, no need to type them manually.
When you open the viewer (assuming correct parameters) you will see a black screen, that will change when the file loads. Camera will spawn at [0,0,0] coordinates, so if you don't know where you are, look arround and move. **TSR/MRM** are not present in collision viewer since they aparently use a diferent collision system due to racing nature, and **Weakest Link** just doesn't have collision data.

## Color guide
Floor meshes are walkable, but they also act like walls
The colors used for the category of object collision meshes are the following:

### Toy Story 2 (final and prototype)
| wall|floor|   |
| :------------ | :------------ | :------------ |
|![ffffff](http://singlecolorimage.com/get/ffffff/40x40)|![c0c0c0](http://singlecolorimage.com/get/c0c0c0/40x40)|normal|
|![ccffcc](http://singlecolorimage.com/get/ccffcc/40x40)|![007700](http://singlecolorimage.com/get/007700/40x40)|green toxic|
|![aa00ff](http://singlecolorimage.com/get/aa00ff/40x40)|![7700aa](http://singlecolorimage.com/get/7700aa/40x40)|toxic 2|
|![ff00aa](http://singlecolorimage.com/get/ff00aa/40x40)|![aa0077](http://singlecolorimage.com/get/aa0077/40x40)|toxic 3|
|![7777ff](http://singlecolorimage.com/get/7777ff/40x40)|![0000aa](http://singlecolorimage.com/get/0000aa/40x40)|wet|
|![2222aa](http://singlecolorimage.com/get/2222aa/40x40)|![000066](http://singlecolorimage.com/get/000066/40x40)|dirty wet|
|![ffffaa](http://singlecolorimage.com/get/ffffaa/40x40)|![777755](http://singlecolorimage.com/get/777755/40x40)|slipery 1|
|![ffff77](http://singlecolorimage.com/get/ffff77/40x40)|![777733](http://singlecolorimage.com/get/777733/40x40)|slipery 2|

### BLSC
| wall|floor|   |
| :------------ | :------------ | :------------ |
|![ffffff](http://singlecolorimage.com/get/ffffff/40x40)|![c0c0c0](http://singlecolorimage.com/get/c0c0c0/40x40)|normal|
|![ccffcc](http://singlecolorimage.com/get/ccffcc/40x40)|![007700](http://singlecolorimage.com/get/007700/40x40)|toxic|
|![aa00ff](http://singlecolorimage.com/get/aa00ff/40x40)|![7700aa](http://singlecolorimage.com/get/7700aa/40x40)|toxic with high jump|
|![ff00aa](http://singlecolorimage.com/get/ff00aa/40x40)|![aa0077](http://singlecolorimage.com/get/aa0077/40x40)|toxic with waves|
|![7777ff](http://singlecolorimage.com/get/7777ff/40x40)|![0000aa](http://singlecolorimage.com/get/0000aa/40x40)|???|
|![2222aa](http://singlecolorimage.com/get/2222aa/40x40)|![000066](http://singlecolorimage.com/get/000066/40x40)|slipery wet|
|![ffffaa](http://singlecolorimage.com/get/ffffaa/40x40)|![777755](http://singlecolorimage.com/get/777755/40x40)|slipery 1|
|![ffff77](http://singlecolorimage.com/get/ffff77/40x40)|![777733](http://singlecolorimage.com/get/777733/40x40)|slipery 2|
|![ffff00](http://singlecolorimage.com/get/ffff00/40x40)|![777700](http://singlecolorimage.com/get/777700/40x40)|slipery 3|


## Bugs Life
| mesh|   |
| :------------ |:------------ |
|![ccffcc](http://singlecolorimage.com/get/ccffcc/40x40)|normal|
|![aa00ff](http://singlecolorimage.com/get/aa00ff/40x40)|instant death|
|![ff00aa](http://singlecolorimage.com/get/ff00aa/40x40)|level finish 1|
|![7777ff](http://singlecolorimage.com/get/7777ff/40x40)|level finish 2|
|![2222aa](http://singlecolorimage.com/get/2222aa/40x40)|toxic|

### Rascal
They are all **white**

## The collision engine
The 3D engine designed by Dave Deus has a lot of things in common for collision of the 4 games:
- it uses diferent collision "objects" that can be placed at a world position. These objects can be repeated at diferent positions, but they can't be rotated.
- The world collision data is an array of a fixed size structure with the object data, including position, category, and a pointer to it's collision meshes.
- Colision polygons are single sided, and you'll see them filled only if you are looking to the colision side, otherwise, you will only see the wireframe.
- The collision meshes are made of a 0x0100 int16 value followed by the number of polygons

The engine sufered several changes between Rascal and TS2, but Rascal, the first of the games, has the most different collision system in comparison to Bugs Life and TS2/BLSC.
TS2 and BLSC engines doesn't have appreciable diferences, and the code to render both collisions is the same.

- Some collision meshes in Rascal, referenced by object pointers, seems to be uninitialized/unused, wasting data memory and not containing anything. All the collision meshes pointed by objects in Bugs and TS2/BLSC are valid.
- The collision coordinates from the meshes are 32bit integer absolute positions in Rascal, but 16bit integer relative (to first point) positions in Bugs and TS2/BLSC.
- After reading the N number of poligons indicated in the second int16 of a collision mesh, Bugs and TS2/BLSC looks at the ending position for another 0x0100 value indicating aditional collision meshes for the same object. Rascal only reads up to one collision mesh, and seems to ignore these 0x0100 values.
- Polygons in Rascal and Bugs are single triangles, while in TS2/BLSC they can be either single, or double triangles, using a 4th coordinate. These double triangles share 2 of the 4 coordinates.
- A lot of code of this tool was reused with Bugs and TS2/BLSC due to the similarity of the engines and collision data. Since Rascal engine is the most diferent, a lot of custom functions were made for this game. Rascal is also the worst of the games (yeah, Rascal is not really a classic unforgettable game), that's the reason I didn't expent so much time reversing the engine. As result, it doesn't show object categories, and maybe it could fail with some savestates.
- There are minor engine diferences between the TS2 demo and TS2 final release, like the size of the object structure increased in 4 bytes.
- If you look for example at the bed object from Rascal save room, you will see that it's ceiling is very low, and doesn't correspond to what you see ingame. WTF?? This is because Rascal collision uses a single coordinate point for the player.

## FAQS
- **Why do I see different category planes/objects , usually out of bounds in TS2, BLSC, and Bugs Life that doesn't exist ingame?**
These collision objects seems to have be used for testing during the development of the games, and left disabled in the collision data.  Aren't they beautiful?

- **There are walls missing, as I see, I could go out of bounds. Fix it!**
Collision shown in this viewer doesn't include dynamic object like enemies, and also doesn't include "limit walls". With "limit walls" I mean, walls that has X,Z coordinates, but has infinite height. Do you imagine seeing a wall going to the infinite space in this editor? It won't be very beautiful.

# Travellers Tales PSX GFX viewer
To complement the collision viewer, a (still) more ambitious project has been made... With Travellers Tales GFX viewer you are able to see all level scenario models including the items. Travellers Tales GFX viewer works with all Traveller's Tales GFX games excepting Rascal.

Things you can see:
* Level scenario meshes
* Level items (ex: extra life, battery, powerups)
* Sprites (Like stair bars at AH. Sprites are not 3d models, they are just plain 2d graphics placed at a 3D position)
* Hidden items (with scale set to 0, like tokens, or first view buzz model in TS2)

Things you can't see:
* Enemies and characters (They are not present in level scene data, and are rendered out of this processed data)
* Coins (An extension of the GFX viewer to show coins was planned at a point, but I finally thinked that it wasn't necesary. Coins and items data array in TS2 final/proto is placed at a fixed memory region for all levels just before collision data, very easy to find. Coins have id=0x10)

Things Rendered:
* Textured (pal4/pal8) and untextured meshes with alpha channel.
* Vertex colors (used for lightning and untextured meshes colors)
* PSX color space (not linear)
* Translucid materials (3 types: additive blending, substractive blending, and both=translucid)
* Level background

Thing not rendered:
* Special (reflecting?) material objects. They have a negative vertex count. Currently rendered with normal materials.

## The technical datails you always love <3

Scenario data is made of an array of different size scenario items (24/32 bytes). There's a different starting address for each level, that is passed as URL parameter. A LOD scenario follows the normal one in TS2 and BL.
Both size scenario items start with 32bit xyz positions followed by 16bit xyz rotation, and ends with 32bit 3D/sprites object pointer.
32 bit scenario elements has 16bit xyz scale components following the rotation. **This scenario data structure is identical for all games**.

3D objects starts with a 32bit vertex element count (that is negative for special material).
- **TS2/TSR/MRM/WL/BLSC**: The following vertex array elements are made of 16bit xyz positions and a 16bit rgb15 vertex color (8byte).
- **BL**: The following vertex array elements are made of 16bit xyz positions and a 4th padding 16 bit value with no use, followed by 3 bytes for 24bit rgb24 vertex color and a last byte for... flags or internal engine use (12 byte).

Following the vertex array, there's a faces flag, palette & vram page & pal type byte, and faces count. At the end of the faces array you can find another faces flag, Palette & vram page & pal type, and count, or just 0xFFFF meaning no more faces. There are lot of 1bit flags like translucency, doublesided, textured, quads,... the faces array items are made of a 4 item list of 8bit vertex index (only 3 used for triangles). For textured elements is followed by a list of 4 8bit xy positions of face vertex UVs. *Note: if face is a triangle, in TS2 and later games you still have 4 positions and 4UVs beeing 1 unused. In BL, you have instead 3 positions and 3UV, meaning a smaller face data size*.

Engine has support for using PAL8 textures, but it's not used on all games (ex: TS2).

## Engine diferences
- MRM/TSR racing games have a diferent collision engine
- Color LUT and VRAM page combinations are in the same data structure for TS2/TSR/MRM/WL/BLSC, while BL has 2 diferent data structures, one for VRAM pages, and color LUTs.
- Face data uses 8byte vertex numbers for TS2/TSR/MRM/WL/BLSC while it uses 16byte vertex pointers in BL.
- Despite diferences in vertex and face data, BL and TS2/TSR/MRM/WL/BLSC engines still has lots of thing in common like the face flags, which are the same, Palette & vram page & pal type also works the same way, special material using negative vertex count,... More surprisingly, sprite data structure is equal, and continues using 24bit vertex color data in TS2/TSR/MRM/WL/BLSC.
- Background size for TS2 is always the same. In BLSC background height is variable, and for BL both height and width are variable. TSR, MRM, and WL doesn't have textured backgrounds.


## GFX viewer URL Parameters
- **ds**: if set to **y**es, it forces all meshes to be double-sided, for better visibility of some levels.
- **mult**: an optional parameter to set the size multiplier.

- **game**: Game the savestate belongs to.
- **gfxpointer**: A pointer to the scene element array to be rendered (EPSXE emulator address).
- **gfxcount**: number of scene elements to be rendered.
- **bkgx**: background vertical size for BL
- **bkgy**: background vertical size for BL and BLSC
- **th**: number of texture pages containing thumbs (not always needed)

# Files in TT PSX games
Game ISOs from Travellers Tales games contains the following file formats:

* **DAT**: Contains coin/object positions, model object and scene data (just models, no textures). It's the same model data that GFX viewer reads directly from savestates
* **ALL**: Contains collision object and scene data. Scene collision data is processed at level loading, while object collision is the same data that collision viewer reads directly from savestates
* **RAW**: This is a packed and compressed file using *RNC PRO-PACK* compression. Contains many level data, including level textures. It also seems to contains a compressed exact copy of ALL file in TS2 (WTF??)
