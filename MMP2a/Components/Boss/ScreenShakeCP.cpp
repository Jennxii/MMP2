#include "stdafx.h"
#include "ScreenShakeCP.h"

void ScreenShakeCP::init()
{
    timePassed = 0;
    m_intensity = 2.f;
    m_speed = 100.f;
    setScreenShake = false;
    m_originalView = m_window->getView();
}

void ScreenShakeCP::update(float deltaTime)
{
    if (m_bossGraphicsCP->getAnimationType() == Attack && m_bossGraphicsCP->getAnimationFrame() == ATTACK_FRAME)
    {
        setScreenShake = true;
        timePassed = 0;
    }

    if (setScreenShake)
    {
        auto shakenView = m_originalView;
        float shakeOffsetX = m_intensity * std::sin(m_speed * timePassed);
        float shakeOffsetY = m_intensity * std::cos(m_speed * timePassed);

        shakenView.move(shakeOffsetX, shakeOffsetY);

        m_window->setView(shakenView);

        if (timePassed >= SHAKE_DURATION_THRESHOLD)
        {
            setScreenShake = false;
            m_window->setView(m_originalView);
        }
    }
    timePassed += deltaTime;
}
