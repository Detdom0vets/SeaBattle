#include "utilities.h"

utilities::utilities()
{

}

int generateRandomNumber(int from, int to)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> uid(from, to);
    return uid(gen);
}

