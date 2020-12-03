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
        // Let's return false for now, we'll implement
        // it later
        return false;
    }

    void queen::print(std::ostream& out) const
    {
        out << "P" << get_color();
    }
}
