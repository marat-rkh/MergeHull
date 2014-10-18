MergeHull
=========

Convex hull algorithm implementation using divide and conquer with no space separation


Dependencies: Qt, Boost, "gcc --version >= 4.6".


To build on linux: execute build.sh (with 'bash build.sh')

On other platforms, please, build manually with:

cd visualization

qmake &&
make &&
cd .. &&
qmake &&
make


Now, to run: ./merge-hull