#ifndef PAWN_HPP
#define PAWN_HPP

#include "chess_piece.hpp"

namespace chess
{
    
    class pawn : public chess_piece
    {
    public:

        pawn(color c, const position_type& pos);
        virtual ~pawn() = default;
        
        bool can_move(const position_type& new_pos,
                      const has_piece_callback& cb) const override;
        void print(std::ostream& out) const override;
    };
}

#endif

