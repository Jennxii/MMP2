#pragma once
#include "Component.h"
class StatsCP : public Component
{
public:

    StatsCP(std::weak_ptr<GameObject> gameObject, std::string id, int hp, int dmg, std::string incObjType) : Component(gameObject, id), maxHealth(hp), gameObjectType(incObjType), originalDamage(dmg) {};

    void update(float deltaTime) override;

    std::string getComponentId() override
    {
        return this->componentId;
    }

    void setComponentId(std::string id) override
    {
        this->componentId = id;
    }

    void init() override;

    void subtracktHealth(int dmg) { health -= dmg; std::cout << health << std::endl; if (health <= 0) { isDead = true; } }
    void addHealth(int healing) { health += healing; }
    int getHealth() { return health; }
    void setHealth(int newHealth) { health = newHealth; }

    int getMaxHealth() { return maxHealth; }

    int getDamage() { return damage; }

    void toggleIFrames() { hasIFrames = hasIFrames ? false : true; }
    bool getIFrameState() { return hasIFrames; }
    bool hasDied() { return isDead; }

    std::string getObjectType() { return this->gameObjectType; }
private:
    int maxHealth;
    int health;
    int originalDamage;
    int damage;
    std::string gameObjectType;
    bool hasIFrames = false;
    bool isDead;
};