#include "GeneralFunctions.hpp"
#include <gl/Glew.h>
std::ostream & operator << (std::ostream & out, const glm::vec3 & vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

std::ostream & operator << (std::ostream & out, const glm::mat4 & m ){
    for(int i = 0; i < 4; ++i){
        out << "(";
        for(int j = 0; j < 4; ++j){
            out << m[i][j] << ",  \t";
        }
        out << ")" << std::endl;
    }
    return out;
}
std::ostream & operator << (std::ostream & out, const glm::vec2 & vec){
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}
std::ostream & operator << (std::ostream & out, const glm::vec4 & vec){
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", "<< vec.w << ")";
	return out;
}
std::ostream & operator << (std::ostream & out, const glm::vec4 * vec){
	out << "(" << vec->x << ", " << vec->y << ", " << vec->z << ", "<< vec->w << ")";
	return out;
}

std::ostream & operator << (std::ostream & out, const Ray & ray){
    out<<"ray(" << ray.origin << "," << ray.direction << ")";
    return out;
}
std::ostream & operator << (std::ostream & out, const Ray * ray){
    out<<"ray(" << ray->origin << "," << ray->direction << ")";
    return out;
}

std::ostream & operator << (std::ostream & out, const Cell & cell){
	out<<cell.getString();
	return out;
}
std::ostream & operator << (std::ostream & out, const Cell * cell){
	out<<cell->getString();
	return out;
}
void drawRay(const Ray & ray, float distance){
	//std::cout << "drawing lines " << std::endl;
	return;//disabled temp
	glBegin(GL_LINES);
		//origin
		glVertex3f(ray.origin.x, ray.origin.y, ray.origin.z);
		//far point
		glm::vec3 far =  ray.direction * distance + ray.origin;
		glVertex3f(far.x, far.y, far.z);
	glEnd();
}
