#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <string>
#include <filesystem>
#include <iostream>
#include <chrono>
#include "point.h"

using namespace std;

vector<Point> generateUniformPoints(int n, double xmin = 0, double xmax = 16, double ymin = 0, double ymax = 16);
vector<Point> generateCirclePoints(int n, double cx = 8.0, double cy = 8.0, double radius = 6.0);

void clearPlots();

void createGif();

void createVideo();