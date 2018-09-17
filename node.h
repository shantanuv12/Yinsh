#ifndef NODE_NODE_H
#define NODE_NODE_H

#include <vector>
#include <utility>
using namespace std;

int whiteRings = 5;
int blackRings = 5;   // Number of Black rows
const int Rows = 19;  // Number of rows on board
const int Cols = 11;  // Number of columns on board
vector<int> weights = {1,1,1,1,1,1,1,1};
vector<float> aux = {0.5,0.5,0.5}

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
  vector<vector<Element>> board_state;
  Board(){
    board_state = {
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
  }

  bool IsValidPoint(Point p);

  Symbol GetSymbolAtPosition(int x, int y);

  bool AddSymbolAtPosition(Point p, Symbol s);

  bool RemoveSymbolAtPosition(Point p);

  bool MoveSymbol(Point init, Point fin);

  bool FlipMarkers(Point init, Point fin, Point dir);

  float MarkerScore(Symbol marker,Symbol ring);

  int FlippedScoreUtil(Symbol marker, Symbol ring, Point dir, int i , int j);

  float FlippedScore(Symbol marker, Symbol ring);

  int MobilityUtil(Symbol ring, Point dir, int i, int j);

  float MobilityScore(Symbol s);

};


class GameState{
public:

  int scoreWhite, scoreBlack;

  int current_player;

  int whiteRings = 5;

  int blackRings = 5;

  int whiteRingsOnBoard = 0;

  int blackRingsOnBoard = 0;

  Board board;

  Point selectedRing;

  Point rowStart, rowEnd;


  GameState(int currentplayer);

  bool AddRingAt(Point pos,int p_id);

  bool SelectRing(Point pos, int p_id);

  bool RowStart(Point pos,int p_id);

  bool RowEnd(Point pos,int p_id);

  bool MoveRingTo(Point init, Point fin, int p_id);

  bool IsValidRow(Point init, Point fin, int p_id);

  bool RemoveRow(Point init, Point fin, Point dir, int p_id);

  bool RemoveRing(Point pos, int p_id);

  bool CheckTerminal();

  float Evaluate();

  vector<float> CalculateScore(int wRings,int bRings,int wMarkers,int bMarkers, char Error_state);

  float GetScore(int p_id, char Error_state = '0');

  vector<Point> ValidMovesList(Point pos);

  vector<Point> ValidPointsInARow(Point pos, Point dir);

  vector<pair<Point, Point>> RowsFormed(int p_id);

  vector<Point> GetValidPointsForRings();

  vector<Point> Rings(int p_id);

  Board Clone(Board b);

};

#endif
