#include "rook.hpp"

namespace chess
{
    rook::rook(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool rook::can_move(const position_type& new_pos,
                        const has_piece_callback& cb) const
    {
        bool valid = check_col_move(new_pos, cb) || check_row_move(new_pos, cb);
        valid &= !cb(new_pos, get_color());
        return valid;
    }

    void rook::print(std::ostream& out) const
    {
        out << "R" << get_color();
    }
}

