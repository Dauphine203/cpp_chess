#include "queen.hpp"

namespace chess
{
    queen::queen(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool queen::can_move(const position_type& new_pos,
                         const has_piece_callback& cb) const
    {
        bool valid = check_col_move(new_pos, cb)
                    || check_row_move(new_pos, cb)
                    || check_diag_move(new_pos, cb);
        valid &= !cb(new_pos, get_color());
        return valid;
    }

    void queen::print(std::ostream& out) const
    {
        out << "P" << get_color();
    }
}

