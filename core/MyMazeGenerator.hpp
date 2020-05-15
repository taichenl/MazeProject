//My MazeGenerator.hpp

#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"


class MyMazeGenerator: public MazeGenerator{
public:
  MyMazeGenerator();
  void generateMaze(Maze& maze) override;
};

#endif