#include "cAudioManager.h"

cAudioManager::cAudioManager()
{
	m_Sounds.push_back(new PlayableSound(ESoundType::GravitySwap, "Sounds/turnStep.wav"));
}

cAudioManager::~cAudioManager()
{
	for (int i = m_Sounds.size() - 1; i >= 0; i--)
	{
		delete m_Sounds[i];
	}
	m_Sounds.clear();
}

void cAudioManager::PlaySound(ESoundType _type)
{
	for (int i = 0; i < m_Sounds.size(); i++)
	{
		if (_type == m_Sounds[i]->m_Type)
		{
			m_Sounds[i]->m_Sound->play();
		}
	}
}
