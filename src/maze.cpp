#include "../include/maze.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Maze::Maze(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<char>(width, '.'));

    // Add static walls
    grid[1][1] = '#';
    grid[2][3] = '#';
    grid[3][1] = '#';

    // Exit location
    grid[4][2] = 'E';

    // Initialize visibility
    visibilityP1.resize(height, std::vector<bool>(width, false));
    visibilityP2.resize(height, std::vector<bool>(width, false));

    // Random placements
    placeTraps(3);
    placeClues(3);
}

void Maze::display(int px, int py) {
    auto& vis = (px == 0 && py == 0) ? visibilityP1 : visibilityP2;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == px && y == py) std::cout << "P ";
            else if (!vis[y][x]) std::cout << "? ";
            else std::cout << grid[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

bool Maze::isWall(int x, int y) {
    return grid[y][x] == '#';
}

bool Maze::isExit(int x, int y) {
    return grid[y][x] == 'E';
}

bool Maze::isTrap(int x, int y) {
    for (auto& t : traps)
        if (t.first == x && t.second == y) return true;
    return false;
}

bool Maze::isClue(int x, int y) {
    for (auto& c : clues)
        if (c.first == x && c.second == y) return true;
    return false;
}

void Maze::setPlayer(int x, int y) {
    // Optional: visually mark on grid
}

void Maze::clearPlayer(int x, int y) {
    // Optional: visually unmark on grid
}

void Maze::placeTraps(int count) {
    srand(static_cast<unsigned>(time(0)));
    while (traps.size() < static_cast<size_t>(count)) {
        int tx = rand() % width;
        int ty = rand() % height;
        if (!isWall(tx, ty) && !isExit(tx, ty) && !(tx == 0 && ty == 0) && !(tx == 4 && ty == 4)) {
            traps.emplace_back(tx, ty);
        }
    }
}

void Maze::placeClues(int count) {
    while (clues.size() < static_cast<size_t>(count)) {
        int cx = rand() % width;
        int cy = rand() % height;
        if (!isWall(cx, cy) && !isExit(cx, cy) && !(cx == 0 && cy == 0) && !(cx == 4 && cy == 4)) {
            clues.emplace_back(cx, cy);
        }
    }
}

void Maze::updateVisibility(int x, int y, const std::string& player) {
    auto& vis = (player == "Player 1") ? visibilityP1 : visibilityP2;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                vis[ny][nx] = true;
            }
        }
    }
}