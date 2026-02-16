# PEXESOLVER

This program lets you find an arrangement of user-defined black and white tiles, such that every shared edge matches color.

<br>
<img width="876" height="400" alt="pexesok_transparent" src="https://github.com/user-attachments/assets/5f9ce02a-6d56-4780-b213-a91730ad0d1e" />
<br> <br>

You can also define the desired superstructure - for the example of 24 different tiles, you can specify whether the resulting arrangement will be a 4x6, 3x8 or 2x12.

For a set of tiles where this solution does not exist, you can also toggle an option to show partial solutions (with only one or two tiles missing)

The name is a play on words pexeso (the Czech name for the memory game, the original idea behind this project), and solver, since it finds an arrangement fulfilling the defined ruleset.

## How the algorithm works

The algorithm is recursive in its nature. It mimics an algorithm used to efficiently and quickly solve sudokus. Since the tiles are black and white, the program can be made extremely efficient using bitmaps and bitshifts, only working with boolean values. 

In every recursion step, the program tries to place a tile at the next available spot and checks if its edges match with its neighbors. If not, it rotates the tile by 90° and checks again. If the tile does not match at all, it tries the next from the que. When it exhausts all options, the recursion branch ends and reverts to a previous position, making a similar choice, until it either finds a solution or checks every option. 
