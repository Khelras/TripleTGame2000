#include "cAudioManager.h"

cAudioManager::cAudioManager()
{
	m_Sounds.push_back(new PlayableSound(ESoundType::GravitySwap, "Sounds/turnStep.wav"));
}

cAudioManager::~cAudioManager()
{
	for (int i = std::size(m_Sounds) - 1; i >= 0; i--)
	{
		delete m_Sounds[i];
	}
	m_Sounds.clear();
}

void cAudioManager::PlaySound(ESoundType _type)
{
	for (int i = 0; i < std::size(m_Sounds); i++)
	{
		if (_type == m_Sounds[i]->m_Type)
		{
			m_Sounds[i]->m_Sound->play();
		}
	}
}
