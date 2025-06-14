#ifndef TRUST_H
#define TRUST_H

#include <string>

class TrustSystem {
private:
    int trustP1;
    int trustP2;
    std::string lastSender;
    bool lastLie;
    std::string lastMessage;
public:
    TrustSystem();
    void sendMessage(const std::string& sender, const std::string& message, bool isLie);
    void accuse(const std::string& accuser);
    int getTrust(const std::string& player);
    void reset();
    std::string getStateJSON();
};

#endif