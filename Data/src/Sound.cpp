#include <Sound.hpp>
#include <Config.hpp>

Sound::Sound():asset("assets\\"),wave(".wav")
{
    static bool initialized = false;

    if(!initialized){
    	std::cout << "----------------creating SOUND-----------------"<<std::endl;
    	Config::instance().getSetting("soundVolume", volume);
        //background
        addSound("backgroundWav");

        //laserSound
        addSound("laserPulseLightWav");

        addSound("laserPulseMediumWav");


        //heavyLaserSound
        addSound("laserPulseHeavyWav");


        //robotWireCutterAttackSound
        addSound("robotWireCutterAttackSound");


        //robotExplosiveAttackSound
        addSound("robotExplosiveAttackSound");

        //robotLaserTurretAttackSound
        addSound("robotLaserTurretAttackSound");

        std::cout << " initialized sound buffers "  << std::endl;
        addSound("HARPSHIT.wav");
        playOnce("HARPSHIT.wav");
    }
    initialized = true;
}

Sound::~Sound()
{
	for(int i = sounds.size() -1; i >= 0; i--){
		if(sounds[i]){
			delete sounds[i];
			sounds[i] = NULL;
		}

	}
	sounds.clear();
}

void Sound::update()
{

}
void Sound::addSound(const std::string & soundName){
	std::string fileAdress = "";
	Config::instance().getSetting(soundName, fileAdress);
	sf::SoundBuffer * buffer= new sf::SoundBuffer();
	if(!buffer->loadFromFile(fileAdress)){
	    std::cout << fileAdress << "failed to load " << std::endl;
        return;
	}
	else{
        buffers.insert(std::pair<std::string, sf::SoundBuffer*>(soundName, buffer));
	}

}

void Sound::playOnce(std::string fileName)
{
       // sf::Music music;
    /*std::string file = asset + filename + type;
    if (!music.openFromFile(file))
        std::cout <<  "music init fail" << std::endl; // error
        music.play();
    sounds.push_back(&music);
    */

    std::cout << "PLAYING SOUND "  << fileName << std::endl;
    sf::Sound * sound=  new sf::Sound();
    std::map<std::string, sf::SoundBuffer*>::iterator it = buffers.find(fileName);
    if(it != buffers.end()){
        sound->setBuffer(*it->second);
        sound->play();
        sound->setVolume(volume);
        sounds.push_back(sound);
    }
    else{
        std::cout << " no sound with the name " << fileName << " found " << std::endl;
    }
    cleanSounds();
}
void Sound::cleanSounds(){
    for(int i = sounds.size() -1 ; i>= 0; i--){
        std::vector<sf::Sound*>::iterator it = sounds.begin()+ i;
        sf::Sound * snd = *it;
        if(snd->getStatus())continue;
        else{
        	delete *it;
        	*it = NULL;
            sounds.erase(it);
        }
    }
}
std::map<std::string, sf::SoundBuffer*> Sound::buffers;
float Sound::volume;
