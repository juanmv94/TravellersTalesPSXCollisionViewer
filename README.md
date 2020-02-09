# Travellers Tales PSX Collision viewer

Travellers Tales videogame company realeased 3 PSX videogames that uses the same 3D engine with minor improvements on each title:

- **Rascal**: This is the first PSX title developed by Travellers Tales. It is said to be the worst PSX game ever made. This was due to the use of rotational control, and TT team beeing focused on the development of Sonic R.
- **Bugs Life**: Videogame based on the same title Pixar movie. It (finally) uses directional controls.
- **Toy Story 2**: Videogame based on the same title Pixar movie. It is the best of the 3 PSX videogames with lots of games sold and a rating of 9.1/10 (Metacritic)

## How to use
You can try the online version of the tool [here](https://priceless-pike-6c8ff8.netlify.com/ "here").
The collision viewer reads the collision data from PSX savestates from an emulator (PSXE). These savestates must be uncompressed, so if they are, you must uncompress them first (you can use [offzip](https://aluigi.altervista.org/mytoolz/offzip.zip "offzip") for example).
Anyway, some example savestates are provided.
The viewer core is in *viewer.html*  and you should pass it a *file* parameter with the name of the file inside the *SSTATES* folder and a *game* parameter with the game wich correspond the savestate. You have links with this parameters in *index.html*, no need to type them manually.
When you open the viewer (assuming correct parameters) you will see a black screen, that will change when the file loads. Camera will spawn at [0,0,0] coordinates, so if you don't know where you are, look arround and move.
The controls are the following:
- **WASD**: move
- **QE**: rotate
- **Mouse move**: look arround
- **Mouse click**: select/deselect object

## Color guide
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

Floor meshes are walkable, but they also act like walls

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
The 3D engine designed by Dave Deus has a lot of things in common for collision of the 3 games:
- it uses diferent collision "objects" that can be placed at a world position. These objects can be repeated at diferent positions, but they can't be rotated.
- The world collision data is an array of a fixed size structure with the object data, including position, category, and a pointer to it's collision meshes.
- The collision meshes are made of a 0x0100 int16 value followed by the number of polygons

The engine sufered several changes, but Rascal, the first of the games, has the most different collision system in comparison to Bugs Life and TS2

- Some collision meshes in Rascal, referenced by object pointers, seems to be uninitialized/unused, wasting data memory and not containing anything. All the collision meshes pointed by objects in Bugs and TS2 are valid.
- The collision coordinates from the meshes are 32bit integer absolute positions in Rascal, but 16bit integer relative (to first point) positions in Bugs and TS2.
- After reading the N number of poligons indicated in the second int16 of a collision mesh, Bugs and TS2 looks at the ending position for another 0x0100 value indicating aditional collision meshes for the same object. Rascal only reads up to one collision mesh, and seems to ignore these 0x0100 values.
- Polygons in Rascal and Bugs are single triangles, while in TS2 they can be either single, or double triangles, using a 4th coordinate. These double triangles share 2 of the 4 coordinates.
- A lot of code of this tool was reused with Bugs and TS2 due to the similarity of the engines and collision data. Since Rascal engine is the most diferent, a lot of custom functions were made for this game. Rascal is also the worst of the games (yeah, Rascal is not really a classic unforgettable game), that's the reason I didn't expent so much time reversing the engine. As result, it doesn't show object categories, and maybe it could fail with some savestates.
- There are minor engine diferences between the TS2 demo and TS2 final release, like the size of the object structure increased in 4 bytes.
- If you look for example at the bed object from Rascal save room, you will see that it's ceiling is very low, and doesn't correspond to what you see ingame. WTF?? This is because Rascal collision uses a single coordinate point for the player.
