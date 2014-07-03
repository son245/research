research
========
A research problem with Dr. Khang Tran - Truman State University
Problem: We are trying to find the locations of n points so that the product of all the gaps between each two points are maximum.
Approach: my approach is using genetic algorithm. First applying it to a linear but similar problem to analyze the efficiency of the problem. Then based on that, apply it to the square problem.
Scope: we want to be able to use the algorithm with all shapes in the future.

Code explaination:there are currently 2 main files, the testLine.cpp and the testSquare.cpp. They both use 2 classes: Point class and the 
Chromosome class. Evolution methods are defined in the main files.

Compilation: just simple compilation with g++ -std=c++0x testLine.cpp point.cpp chromosome.cpp if using linux.
