#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <cstddef>
#include <ostream>
#include <utility>

namespace chess
{
    // We encode color with a simple char which can be 'w' or 'b'
    using color = char;
    using position_type = std::pair<char, std::size_t>;

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
        virtual bool can_move(const position_type& new_pos) const = 0;
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

