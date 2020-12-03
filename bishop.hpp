#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "chess_piece.hpp"

namespace chess
{
    
    class bishop : public chess_piece
    {
    public:

        bishop(color c, const position_type& pos);
        virtual ~bishop() = default;
        
        bool can_move(const position_type& new_pos,
                      const has_piece_callback& cb) const override;
        void print(std::ostream& out) const override;
    };
}

#endif

