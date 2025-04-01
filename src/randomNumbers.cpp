#include <randomNumbers.hpp>

namespace rnd {

std::mt19937& getGenerator() {
    static std::random_device rd {};
    static std::seed_seq ss { rd(), rd(), rd(), rd(), rd(), rd() };
    static std::mt19937 gen { ss };

    return gen;
}

int randomInt(int min, int max) {
    std::uniform_int_distribution dist { min, max };

    return dist(getGenerator());
}

}