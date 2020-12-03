#include "pawn.hpp"

namespace chess
{
    pawn::pawn(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool pawn::can_move(const position_type& new_pos) const
    {
        // Let's return false for now, we'll implement
        // it later
        return false;
    }

    void pawn::print(std::ostream& out) const
    {
        out << "P" << get_color();
    }
}

