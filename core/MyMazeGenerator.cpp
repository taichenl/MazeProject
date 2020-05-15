//MyMazeGenerator.cpp
//This cpp file is designed to define all the functions 

#include "MyMazeGenerator.hpp"
#include "Direction.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Maze.hpp"
#include <random>
#include <vector>
using namespace std;


ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,
                               MyMazeGenerator,
                               "Random MazeGenerator (Required)");


//Default Constructor
MyMazeGenerator::MyMazeGenerator(){};

//Return a vector of directions that is possible
//Use pointer to the truth array to update
vector<Direction> possible_path(int x, int y, Maze& maze, int *truth){
  vector <Direction> path;
  if (x > 0 and truth[((x-1)*int(maze.getHeight()))+y] == 0){
    path.push_back(Direction::left);
  }
  if (x < maze.getWidth()-1 and truth[int((x+1)*maze.getHeight())+y] == 0){
    path.push_back(Direction::right);
  }
  if (y > 0 and truth[int(x*maze.getHeight()+y-1)] == 0){
    path.push_back(Direction::up);
  }
  if (y < maze.getHeight()-1 and truth[(x*int(maze.getHeight()))+y+1] == 0){
    path.push_back(Direction::down);
  }
  return path;
}


//chooseDirection takes a vector of directions and return a random element from it
Direction chooseDirection(vector <Direction> path){
  random_device device;
  default_random_engine engine{device()};
  // initilize the random number generator
  uniform_int_distribution<int> distribution{0, int(path.size()-1)};
  return path[distribution(engine)];
}


//recursive function that update the maze and truth table
void move(int row, int col, int *truth, Maze& maze){
  vector<Direction> ListofDirections = possible_path(row, col, maze, truth);
  while (ListofDirections.size()>0){
    Direction direct = chooseDirection(ListofDirections);

    if (direct ==Direction::left){
      maze.removeWall(row, col, Direction::left);
      row = row -1;
      truth[row*maze.getHeight() + col] = 1;
      //update the truth table
      move(row, col, truth,maze);
    }

    if (direct == Direction::right){
      maze.removeWall(row, col, Direction::right);
      row = row +1;
      truth[row*maze.getHeight() + col] = 1;
      move(row, col, truth,maze);
    }

    if (direct ==Direction::down){
      maze.removeWall(row, col, Direction::down);
      col = col+1;
      truth[row*maze.getHeight() + col] = 1;
      move(row, col, truth,maze);
    }

    if (direct ==Direction::up){
      maze.removeWall(row, col, Direction::up);
      col = col-1;
      truth[row*maze.getHeight() + col] = 1;
      move(row, col, truth,maze);
    }

    //Since x, y, and truth table has been updated 
    //Update the vector for the while loop
    ListofDirections = possible_path(row, col, maze, truth);
  }
}

  
void MyMazeGenerator::generateMaze(Maze& maze){
  //Add all the walls to the maze
  maze.addAllWalls();

  //Product of the width and length is the length of entire array
  int total = maze.getWidth()*maze.getHeight();

  //Dynamically allocate the truth table with the product
  int * truth = new int[total];

  //initialize the truth table to be zero.  
  for (int i = 0; i < total; i++) truth[i] = 0;

  //The first location has been used
  truth[0] = 1;;
  
  //call then recursive function to change the maze
  move(0, 0, truth, maze);

  //Free up the space
  delete[] truth;
}
