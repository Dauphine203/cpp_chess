#include "king.hpp"

namespace chess
{
    king::king(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool king::can_move(const position_type& new_pos,
                        const has_piece_callback& cb) const
    {
        const position_type& current_pos = get_position();
        bool col_valid = new_pos.first == current_pos.first
            || new_pos.first + 1 == current_pos.first
            || new_pos.first == current_pos.first + 1;
        bool row_valid = new_pos.second == current_pos.second
            || new_pos.second + 1 == current_pos.second
            || new_pos.second == current_pos.second + 1;
        bool valid = row_valid && col_valid && new_pos != current_pos;
        valid &= !cb(new_pos, get_color());
        // We should also check that this move does not put the
        // king in check. However, this requires knowing the position
        // of all opposite pieces, so this check will be delegated to
        // the chess_board class.
        return valid;
    }

    void king::print(std::ostream& out) const
    {
        out << "K" << get_color();
    }
}

