#include "Slideshow.hpp"
#include "Config.hpp"
#include <iostream>
#include <assert.h>

Slideshow::Slideshow(sf::RenderWindow & window_):window(window_)
{
    //ctor
    displayingComics = true;
    currentSet = 0;
    currentSlide = 0;

    std::cout << "----------------creating Slideshow-----------"<< std::endl;
    Config & config = Config::instance();
    int count = config.getComicCount();
    for(int i = 0; i < count; i++){
        addComic(config.getComicAdress(i));
    }



    /*	print all comic sets and what they include.
    count = config.getComicSetCount();
    for(int i = 0; i < count; i++){
		std::vector<int> & set = config.getComicSet(i);
		std::cout << "set " <<  i << " = ";
		for(int j = 0; j < set.size(); j++){
			std::cout << set[j] << ",";
		}
		std::cout << std::endl;
    }
    */
}
Slideshow::~Slideshow()
{
    //dtor
}

void Slideshow::addComic(const std::string & texAdress){
    sf::Texture * tex = new sf::Texture;
    tex->loadFromFile(texAdress);

    sf::Sprite * sprite = new sf::Sprite();
    sprite->setTexture(*tex);

    float scaleX = (window.getSize().x / ((float) tex->getSize().x));
    float scaleY = (window.getSize().y / ((float) tex->getSize().y));
    if(scaleX < scaleY) sprite->setScale(scaleX,scaleX);
    else sprite->setScale(scaleY,scaleY);

    glm::vec2 pos = glm::vec2((float)window.getSize().x, (float)window.getSize().y);
    pos /= 2.0f;
    pos.y = 0;
    pos.x -= sprite->getGlobalBounds().width/2.0f;

    sprite->setPosition(pos.x, pos.y);

    textures.push_back(tex);
    comics.push_back(sprite);
    std::cout << texAdress << " added to comics" << std::endl;
}
void Slideshow::update(){
    if(displayingComics){
        std::vector<int> & toDisplay = Config::instance().getComicSet(currentSet);
        window.draw(*(comics[toDisplay[currentSlide]]));
    }
}
void Slideshow::onClick(){
    currentSlide += 1;
    if(currentSlide ==Config::instance().getComicSet(currentSet).size()){
        displayingComics = false;
        currentSlide = 0;
    }
}
void Slideshow::startSet(int setNumber){
	assert(setNumber >= 0 && setNumber < Config::instance().getComicSetCount());
	currentSet = setNumber;
	currentSlide = 0;
	displayingComics = true;
}
bool Slideshow::isInSlideShow(){
	return displayingComics;
}
