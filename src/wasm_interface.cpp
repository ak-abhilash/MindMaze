#include "../include/maze.h"
#include "../include/trust.h"

static Maze maze(5, 5);
static TrustSystem trust;
static int px = 0, py = 0;

extern "C" {

void move(int dx, int dy) {
    int newX = px + dx;
    int newY = py + dy;

    if (!maze.isWall(newX, newY)) {
        maze.clearPlayer(px, py);
        px = newX;
        py = newY;
        maze.setPlayer(px, py);
        maze.updateVisibility(px, py, "Player");
    }
}

const char* getMazeState() {
    static std::string output;
    output.clear();
    // For simplicity, we just show coordinates
    output = "Player is at (" + std::to_string(px) + ", " + std::to_string(py) + ")";
    return output.c_str();
}

int getTrustState() {
    return trust.getTrust("Player");
}

}