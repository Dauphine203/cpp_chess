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
        color c = get_color();
        const position_type& current_pos = get_position();
        bool valid = false;
        bool same_column = new_pos.first == current_pos.first;
        bool adv1_w = (new_pos.second == current_pos.second + 1) && (c == 'w');
        bool adv2_w = (new_pos.second == current_pos.second + 2) && (c == 'w');
        bool adv1_b = (new_pos.second + 1 == current_pos.second) && (c == 'b');
        bool adv2_b = (new_pos.second + 2 == current_pos.second) && (c == 'b');
        bool adv_1 = same_column && (adv1_w || adv1_b);
        bool adv_2 = same_column && (adv2_w || adv2_b);
        bool diag_w = (new_pos.first == current_pos.first + 1 || new_pos.first + 1 == current_pos.first)
            && (new_pos.second == current_pos.second + 1u);
        bool diag_b = (new_pos.first + 1 == current_pos.first || new_pos.first == current_pos.first + 1)
            && (new_pos.second == current_pos.second + 1u);
        
        if (diag_w || diag_b)
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
            if (c == 'w')
            {
                valid &= !cb(position_type(current_pos.first, current_pos.second + 1), 'a');
            }
            else
            {
                valid &= !cb(position_type(current_pos.first, new_pos.second + 1), 'a');
            }
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

