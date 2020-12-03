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
        const position_type& current_pos = get_position();
        bool same_col = new_pos.first == current_pos.first;
        bool same_row = new_pos.second == current_pos.second;
        bool valid = same_col ^ same_row;
        if (valid)
        {
            if (same_col)
            {
                size_t min_pos = std::min(current_pos.second, new_pos.second);
                size_t max_pos = std::max(current_pos.second, new_pos.second);
                for (size_t i = min_pos + 1; valid && (i < max_pos - 1); ++i)
                {
                    valid = !cb(position_type(new_pos.first, i), 'a');
                }
            }
            else
            {
                char min_pos = std::min(current_pos.first, new_pos.first);
                char max_pos = std::max(current_pos.first, new_pos.first);
                for (char i = static_cast<char>(min_pos + 1); valid && (i < max_pos - 1); ++i)
                {
                    valid = !cb(position_type(i, new_pos.second), 'a');
                }
            }
            valid &= !cb(new_pos, get_color());
        }
        return valid;
    }

    void rook::print(std::ostream& out) const
    {
        out << "R" << get_color();
    }
}

