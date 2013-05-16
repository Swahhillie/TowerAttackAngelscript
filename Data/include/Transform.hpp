#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.hpp"
#include <vector>

class Transform : public Component
{
    public:
        Transform();
        virtual ~Transform();
        virtual void update();

		//const glm::vec3 UPVECTOR(0.0f,1.0f,0.0f);

        void setPosition(const glm::vec3 & newPos);


        void setParent(Transform * newParent);


        void addChild(Transform * child);
        void removeChild(Transform * child);
        glm::mat4 getTransformation()const;


        void translate(glm::vec3 translation);
		void rotate(float angle, glm::vec3 axis);
		void lookAt(const glm::vec3 & point, const glm::vec3 & up);
		void lookAt(const glm::vec3 & point);
		void scale(const glm::vec3 & scale);

        unsigned int getChildCount()const;
        unsigned int getChildCountTotal()const;
        Transform * getParent()const;
        Transform * getChild(int index);
        glm::vec3 getPosition()const;
        glm::vec3 getLocalPosition()const;

        const std::vector<Transform*> & getChildren()const{return children;}
        void setTransformation(const glm::mat4 & transf);

        virtual const std::string getName(){return "Transform";}


    protected:
    private:
		Transform & operator = (const Transform & other){/*disallow assignmentOperator */return *this;}
		Transform(const Transform & other){/*dissallow copy constructor */}

        std::vector<Transform*> children;
        Transform * parent;
        glm::mat4 transformation; // the objects transformation

};

#endif // TRANSFORM_H
