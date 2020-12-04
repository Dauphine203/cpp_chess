#include "knight.hpp"

namespace chess
{
    knight::knight(color c, const position_type& pos)
        : chess_piece(c, pos)
    {
    }

    bool knight::can_move(const position_type& new_pos,
                          const has_piece_callback& cb) const
    {
        const position_type& current_pos = get_position();

        bool previous_col = new_pos.first + 1 == current_pos.first;
        bool next_col = new_pos.first == current_pos.first + 1;
        bool previous_line = new_pos.second + 1 == current_pos.second;
        bool next_line = new_pos.second == current_pos.second + 1;

        bool previous_col2 = new_pos.first + 2 == current_pos.first;
        bool next_col2 = new_pos.first == current_pos.first + 2;
        bool previous_line2 = new_pos.second + 2 == current_pos.second;
        bool next_line2 = new_pos.second == current_pos.second + 2;

        bool previous_col_move = previous_col && (previous_line2 || next_line2);
        bool next_col_move = next_col && (previous_line2 || next_line2);
        bool previous_line_move = previous_line && (previous_col2 || next_col2);
        bool next_line_move = next_line && (previous_col2 || next_col2);

        bool valid = previous_col_move || next_col_move || previous_line_move || next_line_move;
        if (valid)
        {
            char col_min = std::min(current_pos.first, new_pos.first);
            char col_max = std::max(current_pos.first, new_pos.first);
            size_t row_min = std::min(current_pos.second, new_pos.second);
            size_t row_max = std::max(current_pos.second, new_pos.second);

            // The knight has two ways to reach a position:
            // 1] moves along its column, and then along its line
            // 2] moves along its line, and then along its column
            bool first_path_valid = check_path(current_pos,
                                               new_pos,
                                               position_type(current_pos.first, new_pos.second),
                                               cb);
            // If the first path is not valid, we need to check the second one
            if (!first_path_valid)
            {
                valid = check_path(current_pos,
                                   new_pos,
                                   position_type(new_pos.first, current_pos.second),
                                   cb);
            }
        }
        valid &= !cb(new_pos, get_color());
        return valid;
    }

    bool knight::check_path(const position_type& current_pos,
                            const position_type& new_pos,
                            const position_type& path_order,
                            const has_piece_callback& cb) const
    {
        bool jumped = false;
        bool valid = true;
        char col_min = std::min(current_pos.first, new_pos.first);
        char col_max = std::max(current_pos.first, new_pos.first);
        size_t row_min = std::min(current_pos.second, new_pos.second);
        size_t row_max = std::max(current_pos.second, new_pos.second);
        for (size_t i = row_min; i <= row_max; ++i)
        {
            position_type pos(path_order.first, i);
            bool has_piece = pos != current_pos && pos != new_pos && cb(pos, 'a');
            valid &= !has_piece || (has_piece && !jumped);
            jumped |= has_piece;
        }
        for (char i = col_min; i <= col_max; ++i)
        {
            position_type pos(i, new_pos.second);
            bool has_piece = pos != current_pos && pos != new_pos && cb(pos, 'a');
            valid &= !has_piece || (has_piece && !jumped);
            jumped |= has_piece;
        }
        return valid;
    }

    void knight::print(std::ostream& out) const
    {
        out << "N" << get_color();
    }
}

