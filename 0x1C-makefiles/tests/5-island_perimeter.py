#!/usr/bin/python3

def island_perimeter(grid):
    """
    Computes the perimeter of an island described in the given grid.
    Args:
        grid: A list of lists of int rep the island. 0 reps a water zone, 1 reps a land zone.
    Returns:
        An int reps the perimeter of the island.
    Raises:
        ValueError: If the grid is not rectangular, or if the island has lakes (water inside that isn't connected to the water around the island).
    """
    rows = len(grid)
    cols = len(grid[0])
    perimeter = 0

    for a in range(rows):
        for b in range(cols):
            if grid[a][b] == 1:
                # check left
                if b == 0 or grid[a][b-1] == 0:
                    perimeter += 1
                # check right
                if b == cols-1 or grid[a][b+1] == 0:
                    perimeter += 1
                # check top
                if a == 0 or grid[a-1][b] == 0:
                    perimeter += 1
                # check bottom
                if a == rows-1 or grid[a+1][b] == 0:
                    perimeter += 1

    # check for lakes
    for a in range(rows):
        for b in range(cols):
            if grid[a][b] == 1:
                if a > 0 and grid[a-1][b] == 0 and (b == 0 or grid[a][b-1] == 0) and (b == cols-1 or grid[a][b+1] == 0):
                    raise ValueError("Grid has a lake")
                if b > 0 and grid[a][b-1] == 0 and (a == 0 or grid[a-1][b] == 0) and (a == rows-1 or grid[a+1][b] == 0):
                    raise ValueError("Grid has a lake")

    return perimeter
