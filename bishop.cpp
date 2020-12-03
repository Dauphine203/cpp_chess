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
        const position_type& current_pos = get_position();
        char col_min = std::min(current_pos.first, new_pos.first);
        char col_max = std::max(current_pos.first, new_pos.first);
        size_t row_min = std::min(current_pos.second, new_pos.second);
        size_t row_max = std::max(current_pos.second, new_pos.second);
        bool valid = (size_t(col_max - col_min) == row_max - row_min)
            && (new_pos.first != current_pos.first);
        if (valid)
        {
            size_t dist = row_max - row_min;
            for (size_t i = 1; valid && (i < dist - 1); ++i)
            {
                position_type pos(col_min + static_cast<char>(i),
                                  row_min + i);
                valid = !cb(pos, 'a');
            }
            valid &= !cb(new_pos, get_color());
        }
        return false;
    }

    void bishop::print(std::ostream& out) const
    {
        out << "B" << get_color();
    }
}

