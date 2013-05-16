#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
//#include "Object.hpp"
#include "Component.hpp"
#include <vector>
#include <map>
//namespace std


class Sound : public Component
{
    public:
        Sound();
        virtual ~Sound();
        virtual void update();
        void playOnce(std::string Filename);
        virtual const std::string getName(){return "Sound";}
    protected:
    private:
		Sound(const Sound& other){/*nothing*/ }
		Sound& operator = (const Sound& other) {/*nothing*/return *this;}
		void addSound(const std::string & name);
        std::string asset;
        std::string wave;
        static std::map<std::string, sf::SoundBuffer*> buffers;
        std::vector<sf::Sound*> sounds;
        sf::Music music;
        void cleanSounds();
        static float volume;

};

#endif // SOUND_H
