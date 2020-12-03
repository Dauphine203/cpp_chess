#include "chess_piece.hpp"

namespace chess
{
    color chess_piece::get_color() const
    {
        return m_color;
    }

    color chess_piece::get_opposite_color() const
    {
        return m_color == 'b' ? 'w' : 'b';
    }

    const position_type& chess_piece::get_position() const
    {
        return m_position;
    }

    void chess_piece::move(const position_type& new_pos)
    {
        m_position = new_pos;
    }

    // Default implementation does nothing
    void chess_piece::notify_move()
    {
    }

    chess_piece::chess_piece(color c, const position_type& pos)
        : m_color(c), m_position(pos)
    {
    }

    bool chess_piece::check_col_move(const position_type& new_pos,
                                     const has_piece_callback& cb) const
    {
        const position_type& current_pos = get_position();
        bool valid = new_pos.first == current_pos.first && new_pos.second != current_pos.second;
        if (valid)
        {
            size_t min_pos = std::min(current_pos.second, new_pos.second);
            size_t max_pos = std::max(current_pos.second, new_pos.second);
            for (size_t i = min_pos + 1; valid && (i < max_pos - 1); ++i)
            {
                valid = !cb(position_type(new_pos.first, i), 'a');
            }
        }
        return valid;
    }

    bool chess_piece::check_row_move(const position_type& new_pos,
                                     const has_piece_callback& cb) const
    {
        const position_type& current_pos = get_position();
        bool valid = new_pos.second == current_pos.second && new_pos.first != current_pos.first;
        if (valid)
        {
            char min_pos = std::min(current_pos.first, new_pos.first);
            char max_pos = std::max(current_pos.first, new_pos.first);
            for (char i = static_cast<char>(min_pos + 1); valid && (i < max_pos - 1); ++i)
            {
                valid = !cb(position_type(i, new_pos.second), 'a');
            }
        }
        return valid;
    }

    bool chess_piece::check_diag_move(const position_type& new_pos,
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
        }
        return valid;
    }

    std::ostream& operator<<(std::ostream& out, const chess_piece& pce)
    {
        pce.print(out);
        return out;
    }
}

