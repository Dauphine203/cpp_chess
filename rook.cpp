#include "rook.hpp"

namespace chess
{
    rook::rook(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool rook::can_move(const position_type& new_pos) const
    {
        // Let's return false for now, we'll implement
        // it later
        return false;
    }
}

