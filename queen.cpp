#include "queen.hpp"

namespace chess
{
    queen::queen(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool queen::can_move(const position_type& new_pos) const
    {
        // Let's return false for now, we'll implement
        // it later
        return false;
    }
}

