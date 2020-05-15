// expmain.cpp
//
// ICS 46 Spring 2020
// Project #1: Dark at the End of the Tunnel
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the darkmaze library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.
#include <memory>
#include "Maze.hpp"
#include "MazeFactory.hpp"
#include "MyMazeGenerator.hpp"
#include "MySolver.hpp"

int main()
{

    std::unique_ptr<Maze> maze = MazeFactory{}.createMaze(5, 9);

    MyMazeGenerator generator;
    generator.generateMaze(*maze);
    return 0;
}

