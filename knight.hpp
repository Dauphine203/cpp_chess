#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "chess_piece.hpp"

namespace chess
{
    
    class knight : public chess_piece
    {
    public:

        knight(color c, const position_type& pos);
        virtual ~knight() = default;
        
        bool can_move(const position_type& new_pos) const override;
        void print(std::ostream& out) const override;
    };
}

#endif

