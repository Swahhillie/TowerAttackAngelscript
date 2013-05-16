#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <sfml/graphics.hpp>
#include <string>
#include <vector>

class Slideshow
{
    public:
        Slideshow(sf::RenderWindow & window);
        virtual ~Slideshow();

        bool displayingComics;

		void startSet(int setNumber);
		bool isInSlideShow();

        void onClick();
        void update();
    protected:
    private:
        int currentSet;
        unsigned int currentSlide;


        void addComic(const std::string & texAdress);
        std::vector<sf::Texture *> textures;
        std::vector<sf::Sprite *> comics;

        sf::RenderWindow & window;
};

#endif // SLIDESHOW_H
