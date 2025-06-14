#include "../include/maze.h"
#include "../include/trust.h"
#include <string>

Maze maze(5, 5);
TrustSystem trust;
int px = 0, py = 0;
bool player1Turn = true;

extern "C" {
    void move(int dx, int dy) {
        int newX = px + dx;
        int newY = py + dy;
        if (newX >= 0 && newY >= 0 && newX < 5 && newY < 5 && !maze.isWall(newX, newY)) {
            px = newX;
            py = newY;
        }
    }

    const char* getMazeState() {
        static std::string view;
        view = maze.renderJSON(px, py);
        return view.c_str();
    }

    const char* getGameStateJSON() {
        static std::string state;
        state = trust.getStateJSON();
        return state.c_str();
    }

    void sendMessage(const char* msg, bool isLie) {
        std::string sender = player1Turn ? "Player 1" : "Player 2";
        trust.sendMessage(sender, msg, isLie);
    }

    void accuse() {
        std::string accuser = player1Turn ? "Player 1" : "Player 2";
        trust.accuse(accuser);
    }

    void resetGame() {
        px = 0;
        py = 0;
        player1Turn = true;
        trust.reset();
    }
}