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
        // Let's return false for now, we'll implement
        // it later
        return false;
    }

    void king::print(std::ostream& out) const
    {
        out << "K" << get_color();
    }
}

