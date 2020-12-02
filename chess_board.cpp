#include <algorithm>
#include "chess_board.hpp"

namespace chess
{
    chess_board::chess_board()
    {
        // The constructor should instantiate the different
        // pieces and store them. However, this requires
        // including the headers of all the different pieces,
        // while we want chess_board to depend on the chess_piece
        // base class only. Let's be lazy and solve this problem
        // later.
    }

    chess_board::~chess_board()
    {
        // This assumes empty cases are initialized with nullptr
        std::for_each(m_board.begin(), m_board.end(), [](auto& row)
        {
            std::for_each(row.begin(), row.end(), [](auto* piece)
            {
                delete piece;
            });
        });
    }


    bool chess_board::can_move(const position_type& from, const position_type& to) const
    {
        chess_piece* pce = piece(from);
        if (pce)
        {
            return pce->can_move(to);
        }
        else
        {
            return false;
        }
    }

    void chess_board::move(const position_type& from, const position_type& to)
    {
        // Updates chess piece
        chess_piece* pce = piece(from);
        pce->move(to);
        // Updates chess board - first deletes piece at th destination
        // position if there is one (since the move is valid, it means
        // that the piece is taken by another one)
        chess_piece* must_die = piece(to);
        if (must_die != nullptr)
        {
            delete must_die;
        }
        piece(to) = pce;
        piece(from) = nullptr;

    }

    chess_board::piece_ptr& chess_board::piece(const position_type& pos)
    {
        return m_board[pos.first][pos.second];
    }

    const chess_board::piece_ptr& chess_board::piece(const position_type& pos) const
    {
        return m_board[pos.first][pos.second];
    }
}

