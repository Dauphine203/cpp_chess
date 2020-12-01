#include "knight.hpp"

namespace chess
{
    knight::knight(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool knight::can_move(const position_type& new_pos) const
    {
        // Let's return false for now, we'll implement
        // it later
        return false;
    }
}

