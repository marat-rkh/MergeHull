#include "stdafx.h"
#include "viewer.h"

#include "tests.h"

//#define DEBUG_

int main(int argc, char ** argv) {
#ifdef DEBUG_
    Tests().run();
#else
    QApplication app(argc, argv);
    convex_hull_viewer viewer;
    visualization::run_viewer(&viewer, "Convex Hull");
#endif
}
