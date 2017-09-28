#pragma once
#include "Serializable.h"
#include "Rigidbody.h"
#include "Spacecraft.h"
#include <string>
#include <vector>
#include "network\net_shared.h"

class Participant :
    public Serializable
{
public:
    enum Type {
        Gamemaster = 0,
        Player = 1,
        Observer = 2
    };
private:
    TCPsocket socket;
    std::string name;
    Type type;
    std::vector<Rigidbody*> rigidbodies;

    unsigned int score;
    float scoreTimeCounter = 0;
public:
    Spacecraft* spacecraft;
    Participant(std::string name = "Participant", Type type = Type::Observer);
    ~Participant();

    void Serialize(std::ostream& stream) override;
    void Deserialize(std::istream& stream) override;

    Type GetType() { return type; }
    std::string GetName() { return name; }
    unsigned int GetScore() { return score; }
    void AddScore(unsigned int s) { score += s; }

    void AddRigidbody(Projectile* rigidbody) {
        rigidbodies.push_back(rigidbody);
    }
    void RemoveRigidbody(Rigidbody* ridgidbody);

    void Update(double deltaTime);

    bool IsAlive();
    void SetSocket(TCPsocket newSocket) { socket = newSocket; }
    TCPsocket GetSocket() { return socket; }
};

