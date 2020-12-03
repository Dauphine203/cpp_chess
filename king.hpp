#ifndef KING_HPP
#define KING_HPP

#include "chess_piece.hpp"

namespace chess
{
    
    class king : public chess_piece
    {
    public:

        king(color c, const position_type& pos);
        virtual ~king() = default;
        
        bool can_move(const position_type& new_pos,
                      const has_piece_callback& cb) const override;
        void print(std::ostream& out) const override;
    };
}

#endif

