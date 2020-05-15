//MySolver.cpp
//Jason Li, ID 11014426
//This Cpp file is designed to define functions in the header files

#include "MySolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include <vector>
using namespace std;


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MySolver, "Backtracking Solver (Required)");


//default Constructor
MySolver::MySolver(){};


//Return a vector of Directions for prorgam to choose 
vector<Direction> possible_path(int x, int y, const Maze& maze, int * visited){
  vector<Direction> ListofDirections;
  if (!maze.wallExists(x, y, Direction::left) and x > 0 and visited[((x-1)*int(maze.getHeight()))+y] == 0){
    ListofDirections.push_back(Direction::left);
  }
  if (!maze.wallExists(x, y, Direction::right) and x < maze.getWidth()-1 and visited[((x+1)*int(maze.getHeight()))+y] == 0){
    ListofDirections.push_back(Direction::right);
  }
  if (!maze.wallExists(x, y, Direction::up) and y > 0 and visited[int(x*maze.getHeight()+y-1)] == 0){
    ListofDirections.push_back(Direction::up);
  }
  if (!maze.wallExists(x, y, Direction::down) and y < maze.getHeight() -1 and visited[int(x*maze.getHeight()+y+1)] == 0){
    ListofDirections.push_back(Direction::down);
  }
  return ListofDirections;
}


//recursive function using backtracing algorithem
//Examples like leaf and tree 
bool solve(int x, int y, int *truth, const Maze& maze, MazeSolution& mazeSolution){
  //base case for the recursive function
  if (x == mazeSolution.getEndingCell().first 
  and y == mazeSolution.getEndingCell().second 
  and mazeSolution.isComplete()){
    //terminate when the end point is reached
    return true;
  }


  //loop through the entire possible path
  //path that end without getting the endpoint will return a false
  for (Direction i :possible_path(x, y, maze, truth)){
    if (i == Direction::right){
      mazeSolution.extend(Direction::right);
      truth[(x+1)*int(mazeSolution.getHeight()) + y] = 1;
      if (solve(x+1, y, truth, maze, mazeSolution)){
        return true;
      }
      mazeSolution.backUp();
    }
    if (i == Direction::left){
      mazeSolution.extend(Direction::left);
      truth[(x-1)*int(mazeSolution.getHeight()) + y] = 1;
      if (solve(x-1, y, truth, maze, mazeSolution)){
        return true;
      }
      mazeSolution.backUp();
    }
    if (i == Direction::up){
      mazeSolution.extend(Direction::up);
      truth[x*int(mazeSolution.getHeight()) + y-1] = 1;
      if (solve(x, y-1, truth, maze, mazeSolution)){
        return true;
      }
      mazeSolution.backUp();
    }
    if (i == Direction::down){
      mazeSolution.extend(Direction::down);
      truth[x*int(mazeSolution.getHeight()) + y+1] = 1;
      if (solve(x, y+1, truth, maze, mazeSolution)){
        return true;
      }
      mazeSolution.backUp();
    }
  }
  //If all the path in this function has been denied, the result of 
  //this function will return false.
  return false;
}


//Solve the maze by using functions that is included iun maze and maze solutions
void MySolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
  int totalnumber = mazeSolution.getWidth()*mazeSolution.getHeight();
  //Calculate product of the entire list for later use of initilize a single int array

  int * truthArry = new int[totalnumber];
  //truth array consist of binary numbers that 0 is represented as visited
  //and 1 is represented as not visited

  for (int i = 0; i < totalnumber; i++) truthArry[i] = 0;  
  //initilize the entire array to 0 because the default is not visited

  ++truthArry[0];
  //We have already went through the first one 

  bool result = solve(mazeSolution.getStartingCell().first, 
  mazeSolution.getStartingCell().second, truthArry, maze, mazeSolution);
  //call recursive function

  result = true;
  delete[] truthArry;
  //delete the dynamic allocated array to free up space
}

