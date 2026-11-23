#pragma once
#include <array>

namespace mylib {

enum class Player { None, X, O };
enum class Outcome { InProgress, XWins, OWins, Draw };

// Поле 3x3, индексы 0..8:
// 0 1 2
// 3 4 5
// 6 7 8
using Board = std::array<Player, 9>;

// Возвращает пустое поле.
Board emptyBoard();

// Ход валиден, если индекс в диапазоне [0, 8] и клетка пуста.
bool isValidMove(const Board& b, int pos);

// Применяет ход. Возвращает false, если ход невалиден (поле при этом НЕ меняется).
bool applyMove(Board& b, int pos, Player p);

// Оценивает состояние: победа X/O, ничья (все клетки заняты) или игра продолжается.
Outcome evaluate(const Board& b);

} // namespace mylib