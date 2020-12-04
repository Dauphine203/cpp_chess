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
        
        bool can_move(const position_type& new_pos,
                      const has_piece_callback& cb) const override;
        void print(std::ostream& out) const override;

    private:

        // Common code for checking two paths of a same move:
        // 1] along the column, then along the line:
        //    path_order must be initialized with (current_pos.first, new_pos.second)
        // 2] along the line, then along the column:
        //    path_order must be initialized with (new_pos.first, current_pos.second)
        bool check_path(const position_type& current_pos,
                        const position_type& new_pos,
                        const position_type& path_order,
                        const has_piece_callback& cb) const;
    };
}

#endif

