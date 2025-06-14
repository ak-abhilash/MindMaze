#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <utility>

class Maze {
private:
    int width, height;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<bool>> visibilityP1;
    std::vector<std::vector<bool>> visibilityP2;
    std::vector<std::pair<int, int>> traps;
    std::vector<std::pair<int, int>> clues;

public:
    void updateVisibility(int x, int y, const std::string& player);
    Maze(int w, int h);
    void display(int px, int py);
    bool isWall(int x, int y);
    bool isExit(int x, int y);
    void setPlayer(int x, int y);
    void clearPlayer(int x, int y);
    void placeTraps(int count);
    void placeClues(int count);
    bool isTrap(int x, int y);
    bool isClue(int x, int y);
};

#endif
