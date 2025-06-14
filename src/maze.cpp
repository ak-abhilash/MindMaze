#include "../include/maze.h"
#include <sstream>

Maze::Maze(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<char>(width, '.'));
    grid[1][1] = '#';
    grid[2][3] = '#';
    grid[3][1] = '#';
    grid[4][2] = 'E';
}

bool Maze::isWall(int x, int y) {
    return grid[y][x] == '#';
}

bool Maze::isExit(int x, int y) {
    return grid[y][x] == 'E';
}

std::string Maze::renderJSON(int px, int py) {
    std::ostringstream oss;
    oss << "{\"grid\":[";
    for (int y = 0; y < height; ++y) {
        oss << "[";
        for (int x = 0; x < width; ++x) {
            std::string val;
            if (x == px && y == py) val = "P";
            else if (grid[y][x] == '#') val = "W";
            else if (grid[y][x] == 'E') val = "E";
            else val = ".";
            oss << '\"' << val << '\"';
            if (x < width - 1) oss << ",";
        }
        oss << "]";
        if (y < height - 1) oss << ",";
    }
    oss << "],\"player\":{\"x\":" << px << ",\"y\":" << py << "}}";
    return oss.str();
}