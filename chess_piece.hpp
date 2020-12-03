#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <cstddef>
#include <functional>
#include <ostream>
#include <utility>

namespace chess
{
    // We encode color with a simple char which can be 'w' or 'b'
    // We need a third value, 'a' for any, because the color might
    // not be important when checking for the validity of a move
    using color = char;
    using position_type = std::pair<char, std::size_t>;
    using has_piece_callback = std::function<bool (const position_type&, color)>;

    class chess_piece
    {
    public:

        // When the destructor is trivial (i.e. its implementation
        // does not do anything), you can declare it as default
        // and omit its implementation in the cpp. The same
        // apply for copy and move constructor, and assign
        // operators.
        virtual ~chess_piece() = default;

        // Entity semantic: we delete copy and move constructors
        // and assign operators
        chess_piece(const chess_piece&) = delete;
        chess_piece& operator=(const chess_piece&) = delete;
        chess_piece(chess_piece&&) = delete;
        chess_piece& operator=(chess_piece&&) = delete;

        color get_color() const;

        const position_type& get_position() const;
        void move(const position_type& new_pos);

        // This is specific to the type of piece
        // can move must performs two operations:
        // - check that the move current_pos -> new_pos is valid
        //   for this piece
        // - check whether every case of the path to new_pos is
        //   free or not. Since a path is specific to a piece,
        //   this cannot be delegated to the chess_board class.
        // We don't want chess_piece to depend on chess_board,
        // therefore we use the common callback pattern: the chess_board
        // will call can move with an additional argument, a function
        // that can be invoked by the piece and that will eventually
        // call a method of chess_board (thus the name 'callback')
        virtual bool can_move(const position_type& new_pos,
                              const has_piece_callback& cb) const = 0;
        virtual void print(std::ostream& out) const = 0;

    protected:

        // Let's emphasize the entity semantic by defining
        // the constructor as protected so it is clear we
        // don't want this class to be instantiated by clients
        chess_piece(color c, const position_type& pos);

    private:

        color m_color;
        position_type m_position;
    };

    std::ostream& operator<<(std::ostream& out, const chess_piece& pce);
}

#endif

