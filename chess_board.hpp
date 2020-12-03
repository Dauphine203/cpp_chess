#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <ostream>

#include "chess_array.hpp"
#include "chess_piece.hpp"

namespace chess
{

    class chess_board
    {
    public:

        chess_board();
        // chess_board is not supposed to be inherited,
        // the destructor is not virtual.
        ~chess_board();

        // Even if chess_board implements value semantic,
        // we're not supposed to have more than one instance
        // of chess board in the program. Let's ensure this by
        // deleting the copy and move constructors and operators.
        // Notice that this may change later, when we implement
        // the undo / redo mechanism.
        chess_board(const chess_board& rhs) = delete;
        chess_board& operator=(const chess_board& rhs) = delete;
        chess_board(chess_board&& rhs) = delete;
        chess_board& operator=(chess_board&& rhs) = delete;

        bool can_move(const position_type& from, const position_type& to) const;
        void move(const position_type& from, const position_type& to);

        void print(std::ostream& out) const;

    private:

        using piece_ptr = chess_piece*;

        // Yes, reference on pointer ;). This allows assigning the pointer
        // a different address, making it point to another memory location.
        piece_ptr& piece(const position_type& pos);
        const piece_ptr& piece(const position_type& pos) const;

        void print_separator(std::ostream& out) const;

        chess_array<std::array<chess_piece*, 8>> m_board;
    };
}

#endif

