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
        bool valid = check_diag_move(new_pos, cb);
        valid &= !cb(new_pos, get_color());
        return valid;
    }

    void bishop::print(std::ostream& out) const
    {
        out << "B" << get_color();
    }
}

