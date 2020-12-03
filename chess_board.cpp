#include <algorithm>
#include "chess_board.hpp"
#include "piece_factory.hpp"

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

    void chess_board::print_separator(std::ostream& out) const
    {
        out << "+----+----+----+----+----+----+----+----+----+ " << std::endl;
    }
}

