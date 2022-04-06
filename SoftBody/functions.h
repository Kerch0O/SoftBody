#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>
#include <unordered_map>
#include <tuple>
#include "spring.h"
#include "massPoint.h"
#include "Obstacle.h"

sf::Vector2f operator*(sf::Vector2f v, sf::Vector2f k);

void vCout(sf::Vector2f v, std::string s);
float pythag(sf::Vector2f v);
void convAngle360(sf::Vector2f d, float& theta);
void step(std::vector<spring> &s, std::vector<std::vector<massPoint>> &m, std::vector<Obstacle> &obstacles, float dt);
void rectStep(std::vector<spring> &s, std::vector<std::vector<massPoint>> &m);
void physicsStep(std::vector<spring> &s, std::vector<std::vector<massPoint>> &m, float dt);
void collisionStep(std::vector<std::vector<massPoint>>& m, std::vector<Obstacle> &obstacles);
void initialiseSprings(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, float d, float k, float a);
void createPartition(std::vector<std::vector<massPoint>>& m, std::vector<spring>& s, int i, int j, float d, float k, float a);
bool circleCollision(sf::Vector2f p1, sf::Vector2f p2, float r);
bool obstaclePointIntersect(Obstacle& o, massPoint& m, sf::Vector2f &closest);
void pushNormalR(massPoint& m1, massPoint& m2, std::vector<std::tuple<massPoint*, sf::Vector2f, sf::Vector2f>> &reflections);
void boundaryPush(massPoint &m1, std::vector<Obstacle> &obstacles);
float dot(sf::Vector2f v1, sf::Vector2f v2);
bool bounds(int i, int N);
float MAX(float a, float b);
float MIN(float a, float b);
sf::Vector2f calcCorner(sf::Vector2f s, sf::Vector2f p, float r, int n);
bool rectCollision(sf::Vector2f p, sf::RectangleShape s);

