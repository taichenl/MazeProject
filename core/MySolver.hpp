//MySolver.hpp

#ifndef MYSOLVER_HPP
#define MYSOLVER_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"


class MySolver: public MazeSolver{
public:
    MySolver();
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
};

#endif //MYSOLVER_HPP
