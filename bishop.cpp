#include "bishop.hpp"

namespace chess
{
    bishop::bishop(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool bishop::can_move(const position_type& new_pos,
                          const has_piece_callback& cb) const
    {
        // Let's return false for now, we'll implement
        // it later
        return false;
    }

    void bishop::print(std::ostream& out) const
    {
        out << "B" << get_color();
    }
}

