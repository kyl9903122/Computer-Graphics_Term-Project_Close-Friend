#pragma once

#include <map>
#include "./Dependencies/IrrKlang.h"
#pragma comment(lib, "./Dependencies/irrKlang.lib") 

using namespace irrklang;

class Sound
{
public:
	Sound();
	~Sound();

	int CreateSound(const char* filePath);
	void DeleteSound(int index);
	void PlaySound(int index, bool bLoop, float volume);


private:
	ISoundEngine* m_engine = NULL;

	std::map<int, ISoundSource*> m_soundList;
};

