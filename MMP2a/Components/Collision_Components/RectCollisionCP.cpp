//MultiMediaTechnology FHS
//MultiMediaProjekt 2a
//Kevin Raffetseder, Julian Resch, Jennifer Strohmer
#include "stdafx.h"
#include "../Graphics_Components/AnimatedGraphicsCP.h"
#include "../Transformation_Components/TransformationCP.h"
#include "RectCollisionCP.h"

void RectCollisionCP::update(float deltaTime)
{
    if (!m_gameObject.expired())
    {
        std::shared_ptr<GameObject> go = m_gameObject.lock();
        updateCollider(go);

        std::shared_ptr<TransformationCP> transf = go->getComponentsOfType<TransformationCP>().at(0);

        std::shared_ptr<GraphicsCP> ani;

        if (go->getComponentsOfType<GraphicsCP>().size() != 0)
        {
                ani = go->getComponentsOfType<GraphicsCP>().at(0);
                collisionRect = sf::FloatRect(
                    transf->getPosition().x,
                    transf->getPosition().y,
                    ani->getSprite().getGlobalBounds().width * scale,
                    ani->getSprite().getGlobalBounds().height * scale
                );
        }
        else
        {
            collisionRect = sf::FloatRect(
                transf->getPosition().x,
                transf->getPosition().y,
                colliderSize.x * scale,
                colliderSize.y * scale
            );
        }
    }
}

void RectCollisionCP::init()
{
    if (!m_gameObject.expired())
    {
        std::shared_ptr<GameObject> go = m_gameObject.lock();
        updateCollider(go);
    }
}

void RectCollisionCP::updateCollider(std::shared_ptr<GameObject> go)
{
    std::shared_ptr<TransformationCP> col = go->getComponentsOfType<TransformationCP>().at(0);

    if (go->getComponentsOfType<GraphicsCP>().size() == 0)
    {
        collisionRect = sf::FloatRect(
            col->getPosition().x - colliderSize.x / 2,
            col->getPosition().y - colliderSize.y / 2,
            colliderSize.x,
            colliderSize.y
        );
    }
    else
    {
        std::shared_ptr<GraphicsCP> ani = go->getComponentsOfType<GraphicsCP>().at(0);
        collisionRect = sf::FloatRect(
            col->getPosition().x - colliderSize.x / 2,
            col->getPosition().y - colliderSize.y / 2,
            ani->getSprite().getGlobalBounds().width,
            ani->getSprite().getGlobalBounds().height
        );
    }
}