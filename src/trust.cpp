#include "../include/trust.h"
#include <iostream>

TrustSystem::TrustSystem() : trustP1(100), trustP2(100), lastLie(false) {}

void TrustSystem::sendMessage(const std::string& sender, const std::string& message, bool isLie) {
    lastSender = sender;
    lastLie = isLie;
    std::cout << sender << " says: \"" << message << "\"\n";
}

void TrustSystem::accuse(const std::string& accuser) {
    if (accuser == lastSender) {
        std::cout << "⚠️ You can't accuse yourself. No trust change.\n";
        return;
    }

    if (lastLie) {
        std::cout << "✅ Correct accusation! " << accuser << " gains 5 trust.\n";
        modifyTrust(accuser, 5);
    } else {
        std::cout << "❌ Wrong accusation! " << accuser << " loses 5 trust.\n";
        modifyTrust(accuser, -5);
    }
}

int TrustSystem::getTrust(const std::string& player) {
    return (player == "Player 1") ? trustP1 : trustP2;
}

void TrustSystem::modifyTrust(const std::string& player, int amount) {
    if (player == "Player 1") trustP1 += amount;
    else if (player == "Player 2") trustP2 += amount;
}