#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using std::vector;
using std::cout;


enum class State {kEmpty, kObstacle};

std::string CellString(State cell)
{
    switch(cell)
    {
    case State::kObstacle:
        return "🗿   "; break;
    case State::kEmpty:
        return "0   "; break;
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



int main()
{
    vector<vector<State>> board = ReadBoardFile(std::string("1.board"));
    PrintBoard(board);
}