#include "CGameMaster.hpp"
#include "CWidget.hpp"
#include "CBoardWidget.hpp"
#include "CButton.hpp"
#include "CStatusWidget.hpp"
#include "graphics.hpp"
#include <algorithm>
#include "CNextPlayerWidget.hpp"

using namespace genv;

namespace
{
    const int WINDOW_W = 760;
    const int WINDOW_H = 640;
}

CGameMaster::CGameMaster()
    : board(ROWS, std::vector<int>(COLS, 0)),
      current_player(1),
      winner(0),
      draw(false),
      selected_column(3)
{
    widgets.push_back(new CBoardWidget(20, 20, this));
    widgets.push_back(new CStatusWidget(20, 545, 560+120, 75, this));
    widgets.push_back(new CButton(610, 40, 120, 45, "ÚJ játék", [this]() { NewGame(); }));
    widgets.push_back(new CNextPlayerWidget(610, 110, 120, 170, this));
}

CGameMaster::~CGameMaster()
{
    for (CWidget* widget : widgets)
    {
        delete widget;
    }
}

void CGameMaster::Run()
{
    gout.open(WINDOW_W, WINDOW_H);
    gout << font("LiberationSans-Regular.ttf", 22);

    DrawAll();

    event ev;
    while (gin >> ev)
    {
        if (ev.type == ev_key && ev.keycode == key_escape)
        {
            break;
        }

        if (ev.type == ev_key)
        {
            if (ev.keycode == key_left)
            {
                SetSelectedColumn(selected_column - 1);
            }
            else if (ev.keycode == key_right)
            {
                SetSelectedColumn(selected_column + 1);
            }
            else if (ev.keycode == key_down || ev.keycode == key_enter || ev.keycode == key_space)
            {
                DropInColumn(selected_column);
            }
            else if (ev.keycode >= '1' && ev.keycode <= '7')
            {
                int column = ev.keycode - '1';
                SetSelectedColumn(column);
                DropInColumn(column);
            }
            else if (ev.keycode == 'n' || ev.keycode == 'N')
            {
                NewGame();
            }
        }

        for (CWidget* widget : widgets)
        {
            widget->Handle(ev);
        }

        DrawAll();
    }
}

void CGameMaster::NewGame()
{
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            board[r][c] = 0;
        }
    }

    current_player = 1;
    winner = 0;
    draw = false;
    selected_column = 3;
}

bool CGameMaster::DropInColumn(int column)
{
    if (column < 0 || column >= COLS || IsFinished() || ColumnFull(column))
    {
        return false;
    }

    for (int row = ROWS - 1; row >= 0; --row)
    {
        if (board[row][column] == 0)
        {
            board[row][column] = current_player;
            selected_column = column;

            if (CheckWinner(row, column, current_player))
            {
                winner = current_player;
            }
            else if (BoardFull())
            {
                draw = true;
            }
            else
            {
                current_player = 3 - current_player;
            }
            return true;
        }
    }

    return false;
}

void CGameMaster::SetSelectedColumn(int column)
{
    selected_column = std::clamp(column, 0, COLS - 1);
}

int CGameMaster::GetCell(int row, int column) const
{
    if (row < 0 || row >= ROWS || column < 0 || column >= COLS)
    {
        return 0;
    }
    return board[row][column];
}

int CGameMaster::GetCurrentPlayer() const
{
    return current_player;
}

int CGameMaster::GetWinner() const
{
    return winner;
}

bool CGameMaster::IsDraw() const
{
    return draw;
}

bool CGameMaster::IsFinished() const
{
    return winner != 0 || draw;
}

int CGameMaster::GetSelectedColumn() const
{
    return selected_column;
}

std::string CGameMaster::StatusText() const
{
    if (winner == 1)
    {
        return "PIROS nyert! N gombbal kezhetsz új kört";
    }
    if (winner == 2)
    {
        return "SÁRGA nyert! N gombbal kezhetsz új kört";
    }
    if (draw)
    {
        return "DÖNTETLEN! N gombbal kezhetsz új kört";
    }

    if (current_player == 1)
    {
        return "PIROS jön. Egér, nyilak, és számok 1-től 7-ig is működnek";
    }

    return "SÁRGA jön. Egér, nyilak, és számok 1-től 7-ig is működnek";
}

void CGameMaster::DrawAll() const
{
    gout << color(245, 245, 245)
         << move_to(0, 0)
         << box(WINDOW_W, WINDOW_H);

    for (CWidget* widget : widgets)
    {
        widget->Draw();
    }

    gout << refresh;
}

bool CGameMaster::ColumnFull(int column) const
{
    return board[0][column] != 0;
}

bool CGameMaster::BoardFull() const
{
    for (int c = 0; c < COLS; ++c)
    {
        if (!ColumnFull(c))
        {
            return false;
        }
    }
    return true;
}

bool CGameMaster::CheckWinner(int row, int column, int player) const
{
    const int directions[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    for (const auto& direction : directions)
    {
        int total = 1;
        total += CountDirection(row, column, direction[0], direction[1], player);
        total += CountDirection(row, column, -direction[0], -direction[1], player);
        if (total >= 4)
        {
            return true;
        }
    }

    return false;
}

int CGameMaster::CountDirection(int row, int column, int dr, int dc, int player) const
{
    int count = 0;
    int r = row + dr;
    int c = column + dc;

    while (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player)
    {
        ++count;
        r += dr;
        c += dc;
    }

    return count;
}
