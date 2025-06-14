#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
private:
    int width, height;
    std::vector<std::vector<char>> grid;
public:
    Maze(int w, int h);
    bool isWall(int x, int y);
    bool isExit(int x, int y);
    std::string renderJSON(int px, int py);
};

#endif