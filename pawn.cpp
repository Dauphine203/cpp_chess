#include "pawn.hpp"

namespace chess
{
    pawn::pawn(color c, const position_type& pos)
        : chess_piece(c, pos)
        , m_has_moved(false)
    {
    }

    bool pawn::can_move(const position_type& new_pos,
                        const has_piece_callback& cb) const
    {
        const position_type& current_pos = get_position();
        bool valid = false;
        bool same_column = new_pos.first == current_pos.first;
        bool adv_1 = same_column && new_pos.second == current_pos.second + 1;
        bool adv_2 = same_column && new_pos.second == current_pos.second + 2;
        bool diag = (new_pos.first == current_pos.first + 1 || new_pos.first + 1 == current_pos.first)
            && (new_pos.second == current_pos.second + 1u);
        
        if (diag)
        {
            valid = cb(new_pos, get_opposite_color());
        }
        else if(adv_1)
        {
            valid = !cb(new_pos, 'a');
        }
        else if(adv_2)
        {
            valid = !m_has_moved;
            valid &= !cb(position_type(current_pos.first, current_pos.second + 1), 'a');
            valid &= !cb(new_pos, 'a');
        }
        return valid;
    }

    void pawn::print(std::ostream& out) const
    {
        out << "P" << get_color();
    }

    void pawn::notify_move()
    {
        m_has_moved = true;
    }
}

