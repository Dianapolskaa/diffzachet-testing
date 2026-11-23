#include "file.h"
#include <QtTest/QtTest>
#include <string>

// Хелпер: создаёт поле из строки ('X', 'O', '.')
static mylib::Board fromString(const char* s) {
    mylib::Board b = mylib::emptyBoard();
    for (int i = 0; i < 9; ++i) {
        b[i] = (s[i] == 'X') ? mylib::Player::X :
                   (s[i] == 'O') ? mylib::Player::O : mylib::Player::None;
    }
    return b;
}

class TestTicTacToe : public QObject
{
    Q_OBJECT

private slots:
    // Позитивные: определение победителя
    void evaluate_emptyBoard_inProgress();
    void evaluate_winLines_data();
    void evaluate_winLines();
    void evaluate_draw_fullBoardNoWinner();
    void evaluate_inProgress_notFullBoardNoWinner();

    // Валидация хода
    void isValidMove_emptyCell_true();
    void isValidMove_occupiedCell_false();
    void isValidMove_outOfBounds_false();

    // Применение хода (транзакционность)
    void applyMove_valid_boardUpdated();
    void applyMove_invalid_outOfBounds_boardUnchanged();
    void applyMove_occupiedCell_notOverwritten();
    void applyMove_nonePlayer_rejected();

    // Сквозной сценарий
    void gameFlow_alternating_xWinsAtFifthMove();
    void gameFlow_allNineMoves_draw();

    // Негативные: смешанные состояния
    void evaluate_mixedBoard_oWins();
};

void TestTicTacToe::evaluate_emptyBoard_inProgress() {
    QCOMPARE(mylib::evaluate(mylib::emptyBoard()), mylib::Outcome::InProgress);
}

void TestTicTacToe::evaluate_winLines_data() {
    QTest::addColumn<std::string>("board");
    QTest::addColumn<mylib::Outcome>("expected");
    QTest::addColumn<QString>("title");

    // Строки
    QTest::newRow("top row")    << std::string("XXX.O.O..") << mylib::Outcome::XWins << "top";
    QTest::newRow("middle row") << std::string(".O.XXX.O.") << mylib::Outcome::XWins << "middle";
    QTest::newRow("bottom row") << std::string("O.O...XXX") << mylib::Outcome::XWins << "bottom";

    // Столбцы (ИСПРАВЛЕНЫ данные из методички!)
    QTest::newRow("left col")   << std::string("X.OX.OX..") << mylib::Outcome::XWins << "left";
    QTest::newRow("mid col")    << std::string(".X..X..X") << mylib::Outcome::XWins << "middle"; // ИСПРАВЛЕНО: было .X.X.X...
    QTest::newRow("right col")  << std::string("..X..X..X") << mylib::Outcome::XWins << "right";

    // Диагонали
    QTest::newRow("main diag")  << std::string("X...X...X") << mylib::Outcome::XWins << "main diag";
    QTest::newRow("anti diag")  << std::string("O.X.X.X..O") << mylib::Outcome::XWins << "anti diag";
}

void TestTicTacToe::evaluate_winLines() {
    QFETCH(std::string, board);
    QFETCH(mylib::Outcome, expected);
    QFETCH(QString, title);

    QCOMPARE(mylib::evaluate(fromString(board.c_str())), expected);
}

void TestTicTacToe::evaluate_draw_fullBoardNoWinner() {
    QCOMPARE(mylib::evaluate(fromString("XOXOXOOXO")), mylib::Outcome::Draw);
}

void TestTicTacToe::evaluate_inProgress_notFullBoardNoWinner() {
    QCOMPARE(mylib::evaluate(fromString("XO........")), mylib::Outcome::InProgress);
}

void TestTicTacToe::evaluate_mixedBoard_oWins() {
    // O выигрывает по анти-диагонали (2, 4, 6) — ИСПРАВЛЕНО: было X.O.O.XO.
    QCOMPARE(mylib::evaluate(fromString("X.O.O.OX..")), mylib::Outcome::OWins);
}

void TestTicTacToe::isValidMove_emptyCell_true() {
    QVERIFY(mylib::isValidMove(mylib::emptyBoard(), 4));
}

void TestTicTacToe::isValidMove_occupiedCell_false() {
    auto b = fromString("X.........");
    QVERIFY(!mylib::isValidMove(b, 0));
}

void TestTicTacToe::isValidMove_outOfBounds_false() {
    auto b = mylib::emptyBoard();
    QVERIFY(!mylib::isValidMove(b, 9));
    QVERIFY(!mylib::isValidMove(b, -1));
}

void TestTicTacToe::applyMove_valid_boardUpdated() {
    auto b = mylib::emptyBoard();
    QVERIFY(mylib::applyMove(b, 0, mylib::Player::X));
    QCOMPARE(b[0], mylib::Player::X);
}

void TestTicTacToe::applyMove_invalid_outOfBounds_boardUnchanged() {
    auto b = mylib::emptyBoard();
    QVERIFY(!mylib::applyMove(b, 9, mylib::Player::X));
    QCOMPARE(b[8], mylib::Player::None);
}

void TestTicTacToe::applyMove_occupiedCell_notOverwritten() {
    auto b = fromString("X.........");
    QVERIFY(!mylib::applyMove(b, 0, mylib::Player::O));
    QCOMPARE(b[0], mylib::Player::X);
}

void TestTicTacToe::applyMove_nonePlayer_rejected() {
    auto b = mylib::emptyBoard();
    QVERIFY(!mylib::applyMove(b, 4, mylib::Player::None));
    QCOMPARE(b[4], mylib::Player::None);
}

void TestTicTacToe::gameFlow_alternating_xWinsAtFifthMove() {
    auto b = mylib::emptyBoard();
    QVERIFY(mylib::applyMove(b, 0, mylib::Player::X));
    QVERIFY(mylib::applyMove(b, 3, mylib::Player::O));
    QVERIFY(mylib::applyMove(b, 1, mylib::Player::X));
    QVERIFY(mylib::applyMove(b, 4, mylib::Player::O));
    QVERIFY(mylib::applyMove(b, 2, mylib::Player::X));
    QCOMPARE(mylib::evaluate(b), mylib::Outcome::XWins);
}

void TestTicTacToe::gameFlow_allNineMoves_draw() {
    // ИСПРАВЛЕНО: последовательность {0, 2, 1, 3, 5, 4, 6, 7, 8} даёт ничью
    auto b = mylib::emptyBoard();
    mylib::Player p = mylib::Player::X;

    int moves[9] = {0, 2, 1, 3, 5, 4, 6, 7, 8};
    for (int i = 0; i < 9; ++i) {
        QVERIFY2(mylib::applyMove(b, moves[i], p),
                 QStringLiteral("ход %1 отклонён").arg(moves[i]).toUtf8().constData());
        p = (p == mylib::Player::X) ? mylib::Player::O : mylib::Player::X;
    }
    // Итоговое поле: X X O / O O X / X O X (нет трёх в ряд)
    QCOMPARE(mylib::evaluate(b), mylib::Outcome::Draw);
}

QTEST_MAIN(TestTicTacToe)
#include "test_file.moc"