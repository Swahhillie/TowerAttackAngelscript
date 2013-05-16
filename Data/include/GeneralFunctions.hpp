#ifndef GENERALFUNCTIONS_HPP_INCLUDED
#define GENERALFUNCTIONS_HPP_INCLUDED

#include <iostream>
#include <glm/glm.hpp>
#include "Ray.hpp"
#include "Cell.hpp"
std::ostream & operator << (std::ostream & out, const glm::vec3 & vec);
std::ostream & operator << (std::ostream & out, const glm::mat4 & m);
std::ostream & operator << (std::ostream & out, const glm::vec2 & vec);
std::ostream & operator << (std::ostream & out, const glm::vec4 * vec);
std::ostream & operator << (std::ostream & out, const glm::vec4 & vec);
std::ostream & operator << (std::ostream & out, const Ray & ray);
std::ostream & operator << (std::ostream & out, const Ray * ray);
std::ostream & operator << (std::ostream & out, const Cell & cell);
std::ostream & operator << (std::ostream & out, const Cell * cell);

void drawRay(const Ray & ray, float distance);
#endif // GENERALFUNCTIONS_HPP_INCLUDED
