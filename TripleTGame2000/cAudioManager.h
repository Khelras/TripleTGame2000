#pragma once
#include "SFML/Audio.hpp"
#include <vector>
#include <string>

enum ESoundType
{
	GravitySwap,
};

struct PlayableSound
{
	ESoundType m_Type;

	std::string m_Path;

	sf::SoundBuffer m_Buffer;
	sf::Sound* m_Sound;

	PlayableSound(ESoundType _type, std::string _path)
	{
		m_Type = _type;
		m_Buffer = sf::SoundBuffer(_path);
		m_Sound = new sf::Sound(m_Buffer);
	}

	~PlayableSound()
	{
		delete m_Sound;
	}
};

class cAudioManager
{
public:
	cAudioManager();
	~cAudioManager();


	// PlaySound(ESoundType _type)
	// Purpose: Plays a sound of the specified type
	void PlaySound(ESoundType _type);

private:
	std::vector<PlayableSound*> m_Sounds;
};

