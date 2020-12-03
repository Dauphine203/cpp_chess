#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

#include "chess_board.hpp"

// WINDOWS
// mkdir build
// cd build
// cmake -G "NMake Makefiles" ..
// nmake

// LINUX // MACOS
// mkdir build
// cd build
// cmake ..
// make

namespace chess
{
    void print_chess()
    {
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  8 | Rb | Nb | Bb | Qb | Kb | Bb | Nb | Rb |" << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  7 | Pb | Pb | Pb | Pb | Pb | Pb | Pb | Pb | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  6 |    |    |    |    |    |    |    |    | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  5 |    |    |    |    |    |    |    |    | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  4 |    |    |    |    |    |    |    |    | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  3 |    |    |    |    |    |    |    |    | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  2 | Pw | Pw | Pw | Pw | Pw | Pw | Pw | Pw | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|  1 | Rw | Nw | Bw | Qw | Kw | Bw | Nw | Rw | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
        std::cout << "|    |  a |  b |  c |  d |  e |  f |  g |  h | " << std::endl;
        std::cout << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
    }

    using move_type = std::pair<position_type, position_type>;

    void get_move(std::string input, move_type& pos)
    {
        std::array<std::string, 4> tmp;

        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
        input[input.find('-')] = ',';
        std::size_t i = 0;
        std::string token;
        std::istringstream iss(input);
        while(std::getline(iss, token, ','))
        {
            tmp[i++] = token;
        }
        if(i<4)
        {
            throw std::runtime_error("too few position arguments");
        }

        pos.first.first = tmp[0][0];
        // Users enter position starting at 1 while C++ arrays start at 0
        pos.first.second = stoul(tmp[1]) - 1;
        pos.second.first = tmp[2][0];
        pos.second.second = stoul(tmp[3]) - 1;
    }
}

int main(int /*argc*/, char** /*argv*/)
{
    chess::chess_board board;
    board.print(std::cout);
    std::string input;
    std::cout << "Enter your move: ro,co - rd,cd" << std::endl;
    std::getline(std::cin, input);
    chess::move_type pos;
    try
    {
        chess::get_move(input, pos);
        std::cout << "Legal move: " << board.can_move(pos.first, pos.second) << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

