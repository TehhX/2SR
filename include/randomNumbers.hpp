#pragma once

#include <random>

namespace rnd {

// Retrieve reference to random generator
std::mt19937& generator();

// Generate random integer between min and max, inclusive
int integer(int min, int max);

// Generate random bool, either true or false
bool boolean();

}
