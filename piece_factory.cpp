#include "piece_factory.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"

namespace chess
{
    chess_piece* make_pawn(color c, const position_type& pos)
    {
        return new pawn(c, pos);
    }

    chess_piece* make_rook(color c, const position_type& pos)
    {
        return new rook(c, pos);
    }

    chess_piece* make_knight(color c, const position_type& pos)
    {
        return new knight(c, pos);
    }

    chess_piece* make_bishop(color c, const position_type& pos)
    {
        return new bishop(c, pos);
    }

    chess_piece* make_king(color c, const position_type& pos)
    {
        return new king(c, pos);
    }

    chess_piece* make_queen(color c, const position_type& pos)
    {
        return new queen(c, pos);
    }
}

