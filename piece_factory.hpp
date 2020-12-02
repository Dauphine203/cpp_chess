#ifndef PIECE_FACTORY_HPP
#define PIECE_FACTORY_HPP

#include "chess_piece.hpp"

namespace chess
{
    // The idea is to delegate the instantiation of chess pieces
    // to functions that will hide the real type of these pieces.
    // This way, the client only depends on the chess_piece class
    // and does not have to include all the headers defining the
    // different pieces.

    chess_piece* make_pawn(color c, const position_type& pos);
    chess_piece* make_rook(color c, const position_type& pos);
    chess_piece* make_knight(color c, const position_type& pos);
    chess_piece* make_bishop(color c, const position_type& pos);
    chess_piece* make_king(color c, const position_type& pos);
    chess_piece* make_queen(color c, const position_type& pos);
}

#endif

