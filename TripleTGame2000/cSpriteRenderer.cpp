#include "cSpriteRenderer.h"
#include "cTextureManager.h"

cSpriteRenderer::cSpriteRenderer()
{
    cTextureManager& TextureManager = cTextureManager::GetInstance();

    // Default Sprite is the Cube Texture
    m_Texture = std::make_shared<sf::Texture>(*TextureManager.m_CubeTex);
    m_Sprite = std::make_shared<sf::Sprite>(*m_Texture);

    m_AnimInfo.m_DoesAnimationLoop = true;
}

cSpriteRenderer::~cSpriteRenderer()
{
}

void cSpriteRenderer::InitializeSprite(std::shared_ptr<sf::Texture> _Texture)
{
    m_Texture = _Texture;

    m_Sprite = std::make_shared<sf::Sprite>(*m_Texture);
    m_Sprite->setOrigin(sf::Vector2f(m_Texture->getSize().x / 2.0f, m_Texture->getSize().y / 2.0f));
}

void cSpriteRenderer::InitializeSprite(std::shared_ptr<sf::Texture> _Texture, int _FrameWidth, int _FrameHeight)
{
    m_FrameSize = sf::Vector2i(_FrameWidth, _FrameHeight);
    m_Texture = _Texture;

    sf::IntRect FrameRect = sf::IntRect(sf::Vector2i(0, 0), m_FrameSize);
    m_Sprite = std::make_shared<sf::Sprite>(*m_Texture, FrameRect);
    m_Sprite->setOrigin(sf::Vector2f(m_FrameSize.x / 2.0f, m_FrameSize.y / 2.0f));
}

void cSpriteRenderer::SetFlipH(bool _FlipX)
{
    float X = m_Sprite->getScale().x;
    m_Sprite->setScale(sf::Vector2f(_FlipX ? -X : X, 1));
}

void cSpriteRenderer::SetFlipY(bool _FlipY)
{
    float Y = m_Sprite->getScale().y;
    m_Sprite->setScale(sf::Vector2f(1, _FlipY ? -Y : Y));
}

void cSpriteRenderer::UpdateSprite(float _DeltaTime)
{
    // If sprite isnt animating return
    if (!m_AnimInfo.m_IsAnimating)
    {
        return;
    }

    m_AnimInfo.m_AnimTimer += m_AnimInfo.m_AnimSpeed * _DeltaTime;

    if (m_AnimInfo.m_AnimTimer > 1.0f)
    {
        m_AnimInfo.m_AnimTimer -= 1.0f;
        m_AnimInfo.m_AnimXCurrent++;

        // Go to start of X row when it goes over the X length of the animation
        if (m_AnimInfo.m_AnimXCurrent > m_AnimInfo.m_AnimXEnd)
        {
            m_AnimInfo.m_AnimXCurrent = m_AnimInfo.m_AnimXStart;
            m_AnimInfo.m_AnimYCurrent++;

            // Go to start of Y collumn when it goes over the Y length of the animation
            if (m_AnimInfo.m_AnimYCurrent > m_AnimInfo.m_AnimYEnd)
            {
                // If the animation loops, continue animating
                if (m_AnimInfo.m_LoopAmount > 0) m_AnimInfo.m_LoopAmount--;
                if (m_AnimInfo.m_LoopAmount == 0) m_AnimInfo.m_IsAnimating = false;
                if (!m_AnimInfo.m_IsAnimating)
                {
                    return;
                }

                m_AnimInfo.m_AnimYCurrent = m_AnimInfo.m_AnimYStart;
            }
        }

        // Set frame to new animation frame
        SetSpriteFrame(m_AnimInfo.m_AnimXCurrent, m_AnimInfo.m_AnimYCurrent, false);
    }
}

void cSpriteRenderer::SetSpriteAnimation(sAnimationInfo _AnimInfo)
{
    // If you try to set the animation to the current animation return
    if (m_AnimInfo.m_IsAnimating &&
        _AnimInfo.m_AnimXStart == m_AnimInfo.m_AnimXStart &&
        _AnimInfo.m_AnimYStart == m_AnimInfo.m_AnimYStart &&
        _AnimInfo.m_AnimXEnd == m_AnimInfo.m_AnimXEnd &&
        _AnimInfo.m_AnimYEnd == m_AnimInfo.m_AnimYEnd)
    {
        m_AnimInfo.m_LoopAmount = _AnimInfo.m_LoopAmount;
        return;
    }

    m_AnimInfo.m_IsAnimating = true;
    m_AnimInfo.m_LoopAmount = _AnimInfo.m_LoopAmount;

    // Reset Animation Info to sync animation back up when it starts
    m_AnimInfo = _AnimInfo;
    m_AnimInfo.m_AnimXCurrent = m_AnimInfo.m_AnimXStart;
    m_AnimInfo.m_AnimYCurrent = m_AnimInfo.m_AnimYStart;

    // By default start the animation at the start
    SetSpriteFrame(m_AnimInfo.m_AnimXCurrent, m_AnimInfo.m_AnimYCurrent, false);
}

void cSpriteRenderer::SetSpriteFrame(int _XFrame, int _YFrame, bool _DisableAnimation)
{
	if (_DisableAnimation)
	{
		m_AnimInfo.m_IsAnimating = false;
	}

	// Set Texture Rect for Animation Frame
	sf::Vector2i Origin = sf::Vector2i(_XFrame * m_FrameSize.x, _YFrame * m_FrameSize.y);
	sf::IntRect FrameRect = sf::IntRect(Origin, m_FrameSize);
	m_Sprite->setTextureRect(FrameRect);
}

void cSpriteRenderer::SetAnimationSpeed(float _Speed)
{
	m_AnimInfo.m_AnimSpeed = _Speed;
}

void cSpriteRenderer::SetDoesnAnimLoop(bool _DoesAnimLoop)
{
	m_AnimInfo.m_DoesAnimationLoop = _DoesAnimLoop;
}


std::shared_ptr<sf::Sprite> cSpriteRenderer::GetSprite()
{
	return m_Sprite;
}

std::shared_ptr<sf::Texture> cSpriteRenderer::GetTexture()
{
	return m_Texture;
}

sAnimationInfo cSpriteRenderer::GetAnimInfo()
{
	return m_AnimInfo;
}
