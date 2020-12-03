#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "chess_piece.hpp"

namespace chess
{
    
    class queen : public chess_piece
    {
    public:

        queen(color c, const position_type& pos);
        virtual ~queen() = default;
        
        bool can_move(const position_type& new_pos,
                      const has_piece_callback& cb) const override;
        void print(std::ostream& out) const override;
    };
}

#endif

