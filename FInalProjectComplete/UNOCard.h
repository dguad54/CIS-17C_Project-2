#pragma once
#include <string>
using namespace std;

struct UNOCard {
    string color;
    int number;
    UNOCard(string c, int n) : color(c), number(n) { }
};
