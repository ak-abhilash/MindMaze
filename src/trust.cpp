#include "../include/trust.h"
#include <sstream>

TrustSystem::TrustSystem() : trustP1(100), trustP2(100), lastLie(false), lastMessage("") {}

void TrustSystem::sendMessage(const std::string& sender, const std::string& message, bool isLie) {
    lastSender = sender;
    lastLie = isLie;
    lastMessage = message;
}

void TrustSystem::accuse(const std::string& accuser) {
    if (accuser != lastSender && lastLie) {
        if (accuser == "Player 1") trustP1 += 5;
        else trustP2 += 5;
    } else {
        if (accuser == "Player 1") trustP1 -= 5;
        else trustP2 -= 5;
    }
}

int TrustSystem::getTrust(const std::string& player) {
    return player == "Player 1" ? trustP1 : trustP2;
}

void TrustSystem::reset() {
    trustP1 = 100;
    trustP2 = 100;
    lastMessage = "";
}

std::string TrustSystem::getStateJSON() {
    std::ostringstream oss;
    oss << "{\"Player 1\":" << trustP1 << ",\"Player 2\":" << trustP2 << ",\"lastMessage\":\"" << lastMessage << "\"}";
    return oss.str();
}
