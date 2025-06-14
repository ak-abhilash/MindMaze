#include "maze.h"

Maze maze(5, 5);
int px = 0, py = 0;

extern "C" {

// Move the player by dx, dy
void move(int dx, int dy) {
    int newX = px + dx;
    int newY = py + dy;

    if (newX < 0 || newY < 0 || newX >= 5 || newY >= 5) return;
    if (maze.isWall(newX, newY)) return;

    px = newX;
    py = newY;
}

// Return the maze grid as a string
const char* getMazeState() {
    static std::string output;
    output.clear();

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (x == px && y == py)
                output += "P ";
            else if (maze.isWall(x, y))
                output += "# ";
            else if (maze.isExit(x, y))
                output += "E ";
            else
                output += ". ";
        }
        output += "\n";
    }

    return output.c_str();
}
}