#include <iostream>
#include <vector>
#include <utility>

#include "tests.h"

#define DEBUG

using std::vector;
using std::pair;

int main() {
#ifdef DEBUG
    Tests().run();
#endif
    return 0;
}
