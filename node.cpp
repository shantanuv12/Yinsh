#include "node.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/***
* Directions - N, NE, NW, S, SE, SW
**/
Point dirs[6] = {{-2,0},{-1,1},{-1,-1},{2,0},{1,1},{1,-1}};


bool Board::IsValidPoint(Point p){
    if(board_state[p.x][p.y] != I && p.x < Rows && p.x > -1 &&
    p.y < Cols && p.y > -1){
      return true;
    }
    return false;
}

bool Board::GetSymbolAtPosition(int x, int y){
    return board_state[x][y];

}

bool Board::AddSymbolAtPosition(Point p, Symbol s){
    if(!Board::IsValidPoint()){
      return false;
    }
    board_state[p.x][p.y] = s;
    return true;
}

bool Board::RemoveSymbolAtPosition(Point p){
    if(!Board::IsValidPoint()){
      return false;
    }
    board_state[p.x][p.y] = V;
    return true;
}

bool Board::MoveSymbol(Point init, Point fin){
  if(!Board::IsValidPoint(fin)){
    return false;
  }
  board_state[fin.x][fin.y] = board_state[init.x][init.y];
  board_state[init.x][init.y] = V;
  return true;
}

bool Board::FlipMarkers(Point init, Point fin, Point dir){
  if(!Board::IsValidPoint(init) || !Board::IsValidPoint(fin)){
    return false;
  }
  float x = fin.x - init.x;
  float y = fin.y - init.y;
  if((( x != dir.x && (x / dir.x != int(x / dir.x)))
      || (y != dir.y && (y / dir.y != int(y / dir.y))))){
        return false;
  }
  if(dir.x != 0 && dir.y != 0){
    if( y/dir.y != x/dir.x){
      return false;
    }
  }
  Point i;
  i.x = init.x;
  i.y = init.y;
  while( i.x != fin.x){
    Symbol s = Board::GetSymbolAtPosition(i.x,i.y);
    if(s == Black_Marker){
      board_state[i.x][i.y] = White_Marker;
    }
    else if( s == White_Marker){
      board_state[i.x][i.y] = Black_Marker;
    }
    i.x += dir.x;
    i.y += dir.y;
  }
  return true;
}

bool GameState::AddRingAt(Point pos, int p_id){
  if(!board.IsValidPoint(pos)){
    return false;
  }
  if(p_id == 0 && whiteRings > 0){
    if(board.GetSymbolAtPosition(pos.x,pos.y) != V)
      return false;
    board.AddElementAt(pos,White_Ring);
    whiteRings -= 1;
    return true;
  }
  else if(p_id == 1 && blackRings > 0){
    if(board.GetSymbolAtPosition(pos.x,pos.y) != V)
      return false;
    board.AddElementAt(pos,Black_Ring);
    blackRings -= 1;
    return true;
  }
  return false;
}

bool GameState::MoveRingTo(Point init, Point fin, int p_id){
  Symbol ring,marker;
  if(p_id == 0){
    ring = White_Ring;
    marker = White_Marker;
  }
  else{
    ring = Black_Ring;
    marker = Black_Marker;
  }
  if(!board.IsValidPoint(init) || (board.GetSymbolAtPosition(init.x,init.y) != ring) ||
      (board.GetSymbolAtPosition(fin.x,fin.y) != V))
      return false;

  int dx = fin.x - init.x;
  int dy = fin.y - init.y;
  int px = 0;
  int py = 0;
  int dir_ind = 1;

  for(int i = 0; i < 6; i += 1){
    if( (dx == 0 && dirs[i].x != 0) || (dx != 0 && dirs[i].x == 0)
     || (dx * dirs[i].x < 0)){
      px = -1;
    }
    else if(dx != 0 && dirs[i].x != 0 && dx * dirs[i].x > 0){
      px = dx % dirs[i].x;
    }

    if( (dy == 0 && dirs[i].y != 0) || (dy != 0 && dirs[i].y == 0)
     || (dy * dirs[i].y < 0)){
      py = -1;
    }
    else if(dy != 0 && dirs[i].y != 0 && dy * dirs[i].y > 0){
      py = dy % dirs[i].y;
    }

    if(px == 0 && py == 0){
      dir_ind = i;
      break;
    }
  }
  if(dir_ind == -1)
    return false;

  pair<int, vector<Point>> v = ValidPointsInARow(init, dirs[dir_ind]);
  if(std::find(v.second.begin(), v.second.end(), fin) == v.second.end()){
    return false;
  }
  else{
    AddRingAt(fin,p_id);
    board.AddSymbolAtPosition(init,marker);
    board.FlipMarkers(init,fin,dirs[dir_ind]);
    return true;
  }
}

bool GameState::IsValidRow(Point init, Point fin,Point dir, int p_id){
  if(!board.IsValidPoint(init) || !board.IsValidPoint(fin))
    return false;
  Symbol marker = p_id == 1 ? Black_Marker : White_Marker;
  Point p;
  p.x = init.x;
  p.y = init.y;
  for(int i = 0; i <= 4; i+= 1){
    if(board.GetSymbolAtPosition(p.x,p.y) == marker){
      p.x += dir.x;
      p.y += dir.y;
    }
    else{
      return false;
    }
  }
  return true;
}

bool GameState::RemoveRowAndRing(Point init, Point fin, Point pos, Point dir,int p_id){
  if(!board.IsValidPoint(init) || !board.IsValidPoint(fin) || !board.IsValidPoint(pos))
    return false;
  Symbol ring = p_id == 1 ? Black_Ring :  White_Ring;
  if(!IsValidRow(init,fin,dir,p_id) || board.GetSymbolAtPosition(pos.x,pos.y) != ring)
    return false;
  else{
    Point pos;
    pos.x = init.x;
    pos.y = init.y;
    for(int i = 0; i < 5; i += 1){
      if(board.AddSymbolAtPosition(pos,V) == false)
        return false;
      pos.x += dir.x;
      pos.y += dir.y;
    }
    if(board.AddSymbolAtPosition(init,V) == false){
      return false;
    }
    return true;
  }
}

pair<int,vector<Point>> GameState::ValidMovesList(Point pos){
  vector<pair<int, vector<Point>>> valid_moves;
  for(int i = 0 ; i < 6; i++){
    valid_moves.push_back(ValidPointsInARow(pos,dirs[i]));
  }
  return valid_moves;
}

pair<int, vector<Point>>> GameState::ValidPointsInARow(Point pos, Point dir){
    if(board.IsValidPoint(pos) == true){
      Point i;
      i.x = pos.x;
      i.y = pos.y;
      vector<Point> valid_points;
      bool jump[] = {false, false};
      do{
        i.x += dir.x;
        i.y += dir.y;
        if(board.GetSymbolAtPosition(i.x,i.y) == White_Ring || board.GetSymbolAtPosition(i.x,i.y) == Black_Ring){
          return make_pair(0,valid_points);
        }
        else if(board.GetSymbolAtPosition(i.x, i.y) == V){
          valid_points.push_back(i);
          if(jump[1]){
            return make_pair(1,valid_points);
          }
          else{
            jump[0] = true;
          }
        }
        else if(board.GetSymbolAtPosition(i.x,i.y) == White_Marker || board.GetSymbolAtPosition(i.x,i.y) == Black_Ring){
          if(jump[0]){
            return make_pair(2,valid_points);
          }
          else{
            jump[1] = true;
          }
        }
      } while(board.IsValidPoint(i) == true);
     }
}
