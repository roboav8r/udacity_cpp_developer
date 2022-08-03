#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm> 

using std::vector;
using std::cout;

/*
TO DO:
- reorganize functions
- clean up the workspace - "using", etc
- add comments
- testing
- Check c++ dev guide, rename nodes appropriately
*/



enum class State {kEmpty, kObstacle, kSearched, kPath, kStart, kGoal};

std::string CellString(State cell)
{
    switch(cell)
    {
    case State::kObstacle:
        return "🗿   "; break;
    case State::kEmpty:
        return "0   "; break;
    case State::kPath:
        return "🛣️   "; break;
    case State::kSearched:
        return "🔎   "; break;
    case State::kStart:
        return "🟩   "; break;
    case State::kGoal:
        return "🚩   "; break;      
    default:
        return "0   "; break;
    }

}

void PrintBoard(vector<vector<State>> &board)
{
    for (vector<State> &row : board) {
        for (State &ii : row) {
            cout << CellString(ii);
        }
        cout << "\n";
    }
}

vector<State> ParseLine(std::string line)
{
    std::istringstream StreamLine(line);
    int ii;
    char cc;
    vector<State> vec;

    while (StreamLine >> ii >> cc )
    {
        switch (ii)
        {
            case 0: vec.push_back(State::kEmpty); break;
            case 1: vec.push_back(State::kObstacle); break; 
            default: vec.push_back(State::kEmpty); break;
        }
    }
    return vec;
}

vector<vector<State>> ReadBoardFile(std::string path)
{
    vector<vector<State>> board;
    std::ifstream boardfile(path);

    if (boardfile)
    {
        cout << "got board file, hooah" << "\n";
        std::string line;
        while(getline(boardfile, line))
        {
            board.push_back(ParseLine(line));
        }
    }
    return board;
}

int Heuristic(int x, int y, int xGoal, int yGoal) 
{
    return abs(xGoal-x) + abs(yGoal - y);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &OpenNodes, vector<vector<State>> &board)
{
    vector<int> node{x, y, g, h};
    OpenNodes.push_back(node);
    board[x][y] = State::kSearched;
}

bool Compare (vector<int> node1, vector<int> node2) 
{
    if ((node1[2]+node1[3]) > (node2[2]+node2[3])) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 * NOTE: Udacity provided this
 */
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

bool CheckValidCell (int x, int y, vector<vector<State>> &grid)
{
    // Is the node on the grid? ensure it isn't an obstacle and hasn't already been searched
    if (x >= 0 && x < grid.size() && y>=0 && y < grid[x].size()) {
        
        switch(grid[x][y])
        {
        case State::kObstacle:
            return false; break;
        case State::kEmpty:
            return true; break;
        case State::kPath:
            return false; break;
        case State::kSearched:
            return false; break;        
        case State::kStart:
            return false; break;   
        default:
            return "0   "; break;
        }

    } else { // The node is off the grid and not valid
        return false;
    }
}

void ExpandNeighbors(const vector<int> current, int goal[2], vector<vector<int>> &open, vector<vector<State>> &grid)
{
    // Iterate through potential neighbors
    vector<vector<int>> neighbors = {{current[0]-1,current[1]},{current[0]+1,current[1]},{current[0],current[1]-1},{current[0],current[1]+1}};

    for (vector<int> neighbor : neighbors)
    {
        // If neighbor is a valid cell, compute g/h and add it to vector of open nodes
        if (CheckValidCell(neighbor[0],neighbor[1], grid)) {
            AddToOpen(neighbor[0], neighbor[1], current[2]+1, Heuristic(neighbor[0],neighbor[1],goal[0],goal[1]), open, grid);
        }

    }
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2])
{
    vector<vector<int>> open; // Initialize open nodes vector

    // Initialize starting node and add to vector of open nodes
    vector<int> initNode{init[0], init[1], 0, Heuristic(init[0],init[1],goal[0],goal[1])};
    AddToOpen(initNode[0],initNode[1], initNode[2], initNode[3], open, grid);
    vector<int> current(4);

    // Search the grid
    while (open.empty() == false)
    {
        // Sort the open list using CellSort, and get the current node.
        CellSort(&open);
        current = open.back();
        open.pop_back();

        // Get the x and y values from the current node and set grid[x][y] to kPath.
        grid[current[0]][current[1]] = State::kPath;

        // Check if you've reached the goal. If so, return grid.
        if (current[0]==goal[0] && current[1]==goal[1])
        {
            grid[current[0]][current[1]] = State::kGoal;
            grid[init[0]][init[1]] = State::kStart;
            return grid;
        }
        
        // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
        ExpandNeighbors(current,goal,open,grid);
    }

    cout << "A* search placeholder" << "\n";
    return grid;
}

#include "test.cpp" // For testing solution - tests came from Udacity, not my own work

int main()
{
    // Testing - from Udacity's included test.cpp
    //TestParseLine();
    TestHeuristic();
    TestAddToOpen();
    TestCompare();
    TestExpandNeighbors();
    TestSearch();

    // Initialize starting and goal points
    int init[2] {0,0};
    int goal[2] {4,5};

    // Get the current map and find the path using A* search
    vector<vector<State>> board = ReadBoardFile(std::string("1.board"));
    vector<vector<State>> grid = Search(board, init, goal);

    PrintBoard(board);
    PrintBoard(grid);

}