#ifndef NODE_NODE_H
#define NODE_NODE_H

#include <vector>
#include <utility>
using namespace std;

int whiteRings = 5;
int blackRings = 5;   // Number of Black rows
const int Rows = 19;  // Number of rows on board
const int Cols = 11;  // Number of columns on board

// Structure for string point
struct Point{
  int x;
  int y;
};

// The symbols for valid, invalid and representing markers and rings
enum Symbols{
  I, V, Black_Ring, Black_Marker, White_Ring, White_Marker
};

class Board{
public:
  vector<vector<Element>> board_state = {
    {I, I, I, I, V, I, V, I, I, I, I},
		{I, I, I, V, I, V, I, V, I, I, I},
		{I, I, V, I, V, I, V, I, V, I, I},
		{I, V, I, V, I, V, I, V, I, V, I},
		{I, I, V, I, V, I, V, I, V, I, I},
		{I, V, I, V, I, V, I, V, I, V, I},
		{V, I, V, I, V, I, V, I, V, I, V},
		{I, V, I, V, I, V, I, V, I, V, I},
		{V, I, V, I, V, I, V, I, V, I, V},
		{I, V, I, V, I, V, I, V, I, V, I},
		{V, I, V, I, V, I, V, I, V, I, V},
		{I, V, I, V, I, V, I, V, I, V, I},
		{V, I, V, I, V, I, V, I, V, I, V},
		{I, V, I, V, I, V, I, V, I, V, I},
		{I, I, V, I, V, I, V, I, V, I, I},
		{I, V, I, V, I, V, I, V, I, V, I},
		{I, I, V, I, V, I, V, I, V, I, I},
		{I, I, I, V, I, V, I, V, I, I, I},
		{I, I, I, I, V, I, V, I, I, I, I}
  };



  bool IsValidPoint(Point p);

  Symbol GetSymbolAtPosition(int x, int y);

  bool AddSymbolAtPosition(Point p, Symbol s);

  bool RemoveSymbolAtPosition(Point p);

  bool MoveSymbol(Point init, Point fin);

  bool FlipMarkers(Point init, Point fin, Point dir);
};


class GameState{
 int scoreA, scoreB;
 int current_player;
 Board board;
public:
  bool AddRingAt(Point pos,int p_id);

  bool MoveRingTo(Point init, Point fin, int p_id);

  bool IsValidRow(Point init, Point end, int p_id);

  bool RemoveRowAndRing(Point init, Point end, Point pos, Point dir, int p_id);

  vector<pair<int,vector<Point>>> ValidMovesList(Point pos);

  pair<int, vector<Point>> ValidPointsInARow(Point pos, Point dir);

  //vector<pair<Point,Point>> RowsFormed(int p_id);

};

#endif
