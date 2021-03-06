#include <algorithm>
#include "chess_board.hpp"
#include "piece_factory.hpp"

// This is required to use the _1, and _2 placeholders
using namespace std::placeholders;

namespace chess
{
    chess_board::chess_board()
    {
        for(char i = 'a'; i != 'i'; ++i)
        {
            for (size_t j = 0; j < 8; ++j)
            {
                m_board[i][j] = nullptr;
            }
        }

        m_board['a'][0] = make_rook('w', {'a', 0});
        m_board['b'][0] = make_knight('w', {'b', 0});
        m_board['c'][0] = make_bishop('w', {'c', 0});
        m_board['d'][0] = make_queen('w', {'d', 0});
        m_board['e'][0] = make_king('w', {'e', 0});
        m_board['f'][0] = make_bishop('w', {'f', 0});
        m_board['g'][0] = make_knight('w', {'g', 0});
        m_board['h'][0] = make_rook('w', {'h', 0});

        m_board['a'][1] = make_pawn('w', {'a', 1});
        m_board['b'][1] = make_pawn('w', {'b', 1});
        m_board['c'][1] = make_pawn('w', {'c', 1});
        m_board['d'][1] = make_pawn('w', {'d', 1});
        m_board['e'][1] = make_pawn('w', {'e', 1});
        m_board['f'][1] = make_pawn('w', {'f', 1});
        m_board['g'][1] = make_pawn('w', {'g', 1});
        m_board['h'][1] = make_pawn('w', {'h', 1});

        m_board['a'][6] = make_pawn('b', {'a', 6});
        m_board['b'][6] = make_pawn('b', {'b', 6});
        m_board['c'][6] = make_pawn('b', {'c', 6});
        m_board['d'][6] = make_pawn('b', {'d', 6});
        m_board['e'][6] = make_pawn('b', {'e', 6});
        m_board['f'][6] = make_pawn('b', {'f', 6});
        m_board['g'][6] = make_pawn('b', {'g', 6});
        m_board['h'][6] = make_pawn('b', {'h', 6});

        m_board['a'][7] = make_rook('b', {'a', 7});
        m_board['b'][7] = make_knight('b', {'b', 7});
        m_board['c'][7] = make_bishop('b', {'c', 7});
        m_board['d'][7] = make_queen('b', {'d', 7});
        m_board['e'][7] = make_king('b', {'e', 7});
        m_board['f'][7] = make_bishop('b', {'f', 7});
        m_board['g'][7] = make_knight('b', {'g', 7});
        m_board['h'][7] = make_rook('b', {'h', 7});

        // std::function constructor accepts function objects,
        // that is, functions and classes defining operator().
        // has_piece is not a function but a method, it can
        // not be invoked this way: has_piece(pos, c), but
        // has to be called on an object: my_chess_board.has_piece(pos, c);
        // Therefore, we need to "bind" the method to the current instance
        // of chess_board (that is, this).
        // We take the address of a method M of a class C with the syntax
        // &M::C
        // We use placeholders _1 and _2 to tall the compiler that we
        // don't bind values to arguments of the function.
        // More on bind can be found at https://en.cppreference.com/w/cpp/utility/functional/bind
        m_callback = std::bind(&chess_board::has_piece, this, _1, _2);

        // Initializes the white and black pieces lists
        auto white_it = m_white_pieces.begin();
        auto black_it = m_black_pieces.begin();
        for (const auto& c: m_board)
        {
            *white_it++ = c[0];
            *white_it++ = c[1];
            *black_it++ = c[6];
            *black_it++ = c[7];
        }

        // Initiliazes the king's "trackers"
        p_white_king = m_board['e'][0];
        p_black_king = m_board['e'][7];

        m_current_color = 'w';
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
            bool valid = check_bounds(from) && check_bounds(to);
            // Checks that the user doe snot try to move an opponent piece
            valid &= pce->get_color() == m_current_color;
            valid &= pce->can_move(to, m_callback);
            valid &= check_in_check(pce, to);
            return valid;
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
            color c = must_die->get_color();
            if (c == 'b')
            {
                auto it = std::find(m_black_pieces.begin(), m_black_pieces.end(), must_die);
                *it = nullptr;
            }
            else
            {
                auto it = std::find(m_white_pieces.begin(), m_white_pieces.end(), must_die);
                *it = nullptr;
            }
            delete must_die;
        }
        piece(to) = pce;
        piece(from) = nullptr;
        pce->notify_move();
        m_current_color = pce->get_opposite_color();
    }

    void chess_board::print(std::ostream& out) const
    {
        print_separator(out);
        for (size_t i = 0; i < 8; ++i)
        {
            out << "|  " << 8 - i << " |";
            for (char j = 'a'; j != 'i'; ++j)
            {
                chess_piece* pce = m_board[j][7 - i];
                if (pce != nullptr)
                {
                    out << " " << (*pce) << " |";
                }
                else
                {
                    out << "    |";
                }
            }
            out << std::endl;
            print_separator(out);
        }
        out << "|    |  a |  b |  c |  d |  e |  f |  g |  h | " << std::endl;
        print_separator(out);
    }

    chess_board::piece_ptr& chess_board::piece(const position_type& pos)
    {
        return m_board[pos.first][pos.second];
    }

    const chess_board::piece_ptr& chess_board::piece(const position_type& pos) const
    {
        return m_board[pos.first][pos.second];
    }

    bool chess_board::has_piece(const position_type& pos, color c) const
    {
        piece_ptr pce = piece(pos);
        return pce && (c == 'a' || pce->get_color() == c);
    }

    bool chess_board::check_bounds(const position_type& pos) const
    {
        return pos.first >= 'a' && pos.first <= 'h' && pos.second < 8u;
    }

    bool chess_board::check_in_check(piece_ptr piece, const position_type& new_pos) const
    {
        bool valid = true;
        color c = piece->get_opposite_color();
        // Let's emulate a move of piece to new_pos and check whether the king of opposite
        // color is in check. To do so, we temporarily set the position of piece to new_pos,
        // perform the check, and reset back piece to its original position
        // Takes a copy, since we're going to alter the internal position of piece after
        position_type current_pos = piece->get_position();
        piece->move(new_pos);
        if (c == 'b')
        {
            valid = check_in_check(m_white_pieces, p_black_king);
        }
        else
        {
            valid = check_in_check(m_black_pieces, p_white_king);
        }
        piece->move(current_pos);
        return valid;
    }

    bool chess_board::check_in_check(const piece_list& l, piece_ptr king) const
    {
        bool valid = true;
        for (auto p: l)
        {
            if (p != nullptr)
            {
                valid &= !p->can_move(king->get_position(), m_callback);
            }
        }
        return valid;
    }

    void chess_board::print_separator(std::ostream& out) const
    {
        out << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
    }
}

