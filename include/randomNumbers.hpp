#pragma once

#include <random>

namespace rnd {

std::mt19937& getGenerator();
int randomInt(int min, int max);

}
