#include <iostream>
#include "../include/maze.h"
#include "../include/trust.h"

extern "C" {
    int move(int direction);
    const char* getMazeState();
    const char* getTrustState();
}

void playerTurn(Maze& maze, int& x, int& y, const std::string& playerName, TrustSystem& trust) {
    system("cls"); // On Linux/Mac, use system("clear");
    maze.display(x, y);

    if (maze.isExit(x, y)) {
        std::cout << "🎉 " << playerName << " found the exit! Game Over.\n";
        exit(0);
    }

    char move;
    std::cout << "\n" << playerName << ", move (W/A/S/D): ";
    std::cin >> move;

    int newX = x, newY = y;
    if (move == 'w') newY--;
    else if (move == 's') newY++;
    else if (move == 'a') newX--;
    else if (move == 'd') newX++;

    if (newX < 0 || newY < 0 || newX >= 5 || newY >= 5) {
        std::cout << "🚫 Invalid move (out of bounds). Skipping turn.\n";
    } else if (maze.isWall(newX, newY)) {
        std::cout << "🚫 You hit a wall. Skipping turn.\n";
    } else {
        maze.clearPlayer(x, y);
        x = newX;
        y = newY;
        maze.setPlayer(x, y);
        maze.updateVisibility(x, y, playerName);
    }

    if (maze.isTrap(x, y)) {
        std::cout << "💥 You stepped on a trap! Lose 10 trust points.\n";
        trust.modifyTrust(playerName, -10);
    }

    if (maze.isClue(x, y)) {
        std::string direction;
        if (x < 4) direction = "east";
        else if (x > 4) direction = "west";
        else if (y < 4) direction = "south";
        else direction = "north";

        std::cout << "🧩 You found a clue! Exit is likely towards the " << direction << ".\n";
    }

    std::cin.ignore(); // clear leftover newline
    std::string message;
    char lieChoice;

    std::cout << "\nSend a message to the other player: ";
    std::getline(std::cin, message);

    bool isLie = false;
    while (true) {
        std::cout << "Is this message a lie? (y/n): ";
        std::cin >> lieChoice;
        if (lieChoice == 'y' || lieChoice == 'n') {
            isLie = (lieChoice == 'y');
            break;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }

    trust.sendMessage(playerName, message, isLie);

    char accuseChoice;
    while (true) {
        std::cout << "\nDo you want to accuse the last message of being a lie? (y/n): ";
        std::cin >> accuseChoice;
        if (accuseChoice == 'y') {
            trust.accuse(playerName);
            break;
        } else if (accuseChoice == 'n') {
            break;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    }

    std::cout << "\n🤝 Trust Levels:\n";
    std::cout << "Player 1: " << trust.getTrust("Player 1") << "\n";
    std::cout << "Player 2: " << trust.getTrust("Player 2") << "\n";

    std::cout << "\nPress Enter to end turn...";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    Maze maze(5, 5);
    TrustSystem trust;

    int p1x = 0, p1y = 0;
    int p2x = 4, p2y = 4;

    maze.setPlayer(p1x, p1y);
    maze.updateVisibility(p1x, p1y, "Player 1");

    maze.setPlayer(p2x, p2y);
    maze.updateVisibility(p2x, p2y, "Player 2");

    bool player1Turn = true;

    while (true) {
        if (player1Turn)
            playerTurn(maze, p1x, p1y, "Player 1", trust);
        else
            playerTurn(maze, p2x, p2y, "Player 2", trust);

        player1Turn = !player1Turn;
    }

    return 0;
}
