#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>
#include <unordered_map>
#include "spring.h"
#include "massPoint.h"


void vCout(sf::Vector2f v, std::string s);
float pythag(sf::Vector2f v);
void convAngle360(sf::Vector2f d, float& theta);
void step(std::vector<spring> &s, std::vector<std::vector<massPoint>> &m);
void rectStep(std::vector<spring> &s, std::vector<std::vector<massPoint>> &m);
void physicsStep(std::vector<spring> &s, std::vector<std::vector<massPoint>> &m);
float makeKey(float i, float j);
void initialiseSprings(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, float d, float k, float a);
void createPartition(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, int i, int j, float d, float k, float a);

