#include "file.h"

namespace mylib {

Board emptyBoard() {
    Board b;
    b.fill(Player::None);
    return b;
}

bool isValidMove(const Board& b, int pos) {
    return pos >= 0 && pos < 9 && b[pos] == Player::None;
}

bool applyMove(Board& b, int pos, Player p) {
    if (!isValidMove(b, pos) || p == Player::None) {
        return false;
    }
    b[pos] = p;
    return true;
}

namespace {
bool checkLine(const Board& b, int a, int c, int d) {
    return b[a] != Player::None && b[a] == b[c] && b[c] == b[d];
}
} // namespace

Outcome evaluate(const Board& b) {
    static const int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // строки
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // столбцы
        {0, 4, 8}, {2, 4, 6}             // диагонали
    };

    for (const auto& l : lines) {
        if (checkLine(b, l[0], l[1], l[2])) {
            return b[l[0]] == Player::X ? Outcome::XWins : Outcome::OWins;
        }
    }

    for (Player c : b) {
        if (c == Player::None) {
            return Outcome::InProgress;
        }
    }
    return Outcome::Draw;
}

} // namespace mylib