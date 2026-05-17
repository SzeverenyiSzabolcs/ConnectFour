#pragma once
#include <string>
#include <vector>

class CWidget;
class CBoardWidget;
class CButton;
class CStatusWidget;
class CNextPlayerWidget;

class CGameMaster
{
public:
    static const int COLS = 7;
    static const int ROWS = 6;

private:
    std::vector<std::vector<int>> board;
    int current_player;
    int winner;
    bool draw;
    int selected_column;

    std::vector<CWidget*> widgets;

public:
    CGameMaster();
    ~CGameMaster();

    void Run();
    void NewGame();
    bool DropInColumn(int column);
    void SetSelectedColumn(int column);

    int GetCell(int row, int column) const;
    int GetCurrentPlayer() const;
    int GetWinner() const;
    bool IsDraw() const;
    bool IsFinished() const;
    int GetSelectedColumn() const;
    std::string StatusText() const;

private:
    void DrawAll() const;
    bool ColumnFull(int column) const;
    bool BoardFull() const;
    bool CheckWinner(int row, int column, int player) const;
    int CountDirection(int row, int column, int dr, int dc, int player) const;
};
