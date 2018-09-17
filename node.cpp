#include "node.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/***
* Directions - N, NE, SE, N, NW, SW
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

GameState::GameState(int currentplayer){
  current_player = currentplayer;
  Board board = new Board();
}

bool GameState::AddRingAt(Point pos, int p_id){
  if(!board.IsValidPoint(pos)){
    return false;
  }
  if(p_id == 0 && whiteRings > 0){
    if(board.GetSymbolAtPosition(pos.x,pos.y) != V)
      return false;
    board.AddElementAt(pos,White_Ring);
    //whiteRings -= 1;
    whiteRingsOnBoard++;
    return true;
  }
  else if(p_id == 1 && blackRings > 0){
    if(board.GetSymbolAtPosition(pos.x,pos.y) != V)
      return false;
    board.AddElementAt(pos,Black_Ring);
    //blackRings -= 1;
    blackRingsOnBoard++;
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

bool GameState::RemoveRow(Point init, Point fin, Point dir,int p_id){
  if(!board.IsValidPoint(init) || !board.IsValidPoint(fin))
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
    return true;
  }
}

bool GameState::RemoveRing(Point pos, int p_id){
  if(!board.IsValidPoint(pos))
    return false;
  Symbol ring = p_id == 1 ? Black_ring : White_Ring;
  if(board.GetSymbolAtPosition(pos.x,pos.y) == ring){
     return board.AddSymbolAtPosition(pos,V);
  }
  if(p_id == 0){
    whiteRings--;
  }
  else{
    blackRings--;
  }
  return false;
}

vector<Point> GameState::ValidMovesList(Point pos){
  vector<Point> valid_moves;
  for(int i = 0 ; i < 6; i++){
    vector<Point> points = ValidPointsInARow(pos,dirs[i]);
    for(int j = 0; j < points.size(); j++){
        valid_moves.push_back(points[i]);
    }
  }
  return valid_moves;
}

/* CheckOut this function, I have doubt that it works
*/
vector<Point> GameState::ValidPointsInARow(Point pos, Point dir){
    vector<Point> valid_points = {};
    if(board.IsValidPoint(pos) == true){
      Point i;
      i.x = pos.x;
      i.y = pos.y;
      bool jump[] = {false, false};
      do{
        i.x += dir.x;
        i.y += dir.y;
        if(board.GetSymbolAtPosition(i.x,i.y) == White_Ring || board.GetSymbolAtPosition(i.x,i.y) == Black_Ring){
          return valid_points;
        }
        else if(board.GetSymbolAtPosition(i.x, i.y) == V){
          valid_points.push_back(i);
          if(jump[1]){
            return valid_points;
          }
          else{
            jump[0] = true;
          }
        }
        else if(board.GetSymbolAtPosition(i.x,i.y) == White_Marker || board.GetSymbolAtPosition(i.x,i.y) == Black_Ring){
          if(jump[0]){
            return valid_points;
          }
          else{
            jump[1] = true;
          }
        }
      } while(board.IsValidPoint(i) == true);
     }
     return valid_points;
}

vector<float> GameState::CalculateScore(int wRings,int bRings,int wMarkers,int bMarkers, char Error_state){
    vector<int> scores = {0,0};
    vector<float> score = {0.0,0.0};
    if(Error_state == '1'){
      wRings = 0;
      bRings = 3;
    }
    else if(Error_state == '2'){
      bRings = 0;
      wRings = 3;
    }
    if(wRings == 3){
      scores[0] = 10 - bRings;
      scores[1] = bRings;
    }
    else if(bRings == 3){
      scores[0] = wRings;
      scores[1] = 10 - wRings;
    }
    else if(wRings == bRings){
      scores[0] = 5;
      scores[1] = 5;
    }
    else if(wRings - bRings == 2){
      scores[0] = 7;
      scores[1] = 3;
    }
    else if(bRings - wRings == 2){
      scores[0] = 3;
      scores[1] = 7;
    }
    else if(wRings > bRings){
      scores[0] = 6;
      scores[1] = 4;
    }
    else if(bRings > wRings){
      scores[0] = 4;
      scores[1] = 6;
    }
    else{
      scores[0] = scores[1] = -1;
    }
    score[0] = scores[0] + ((float) wMarkers)/1000;
    score[1] = scores[1] + ((float) bMarkers)/1000;
    return score;
}

float GameState::GetScore(int p_id, char Error_state = '0'){
  int w_rings = 0;
  int b_rings = 0;
  int w_markers = 0;
  int b_markers = 0;
  for(int i = 0; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      Symbol s = board.GetSymbolAtPosition(i,j);
      if(s == V || s == I){
        continue;
      }
      else if(s == White_Ring){
        w_rings++;
      }
      else if(s == Black_Ring){
        b_rings++;
      }
      else if(s == White_Marker){
        w_markers++;
      }
      else if(s == Black_Marker){
        b_markers++;
      }
    }
  }
  return CalculateScore(5-w_rings,5-b_rings,w_markers,b_markers,Error_state)[p_id];
}

float Board::MarkerScore(Symbol marker,Symbol ring){
  float marker_score = 0.0;
  for(int i = 0; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      if(Board::GetSymbolAtPosition(i,j) == marker){
        marker_score += 1;
      }
      else if(Board::GetSymbolAtPosition(i,j) == ring){
        marker_score += 0.5;
      }
    }
  }
  return marker_score;
}


int Board::FlippedScoreUtil(Symbol marker, Symbol ring, Point dir, int i, int j){
    int row = i+dir.x;
    int col = j+dir.y;
    int marker_count = 0;
    while(Board::GetSymbolAtPosition(i,j)== V){
      row += dir.x;
      col += dir.y;
    }
    while(Board::GetSymbolAtPosition(i,j) != I){
      if(Board::GetSymbolAtPosition(i,j) == marker){
        marker_count++;
      }
      else if(Board::GetSymbolAtPosition(i,j) == V){
        return marker_count;
      }
      else if(Board::GetSymbolAtPosition(i,j) == B_RING || Board::GetSymbolAtPosition(i,j) == White_Ring){
        return 0;
      }
      row = row + dir.x;
      col = col + dir.y;
    }
    return 0;
}

float Board::FlippedScore(Symbol marker, Symbol ring){
  float flip_score = 0.0;
  for(int i = 0; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      if(Board::GetSymbolAtPosition(i,j) == ring){
        for(int k = 0; k < 6; k++){
          flip_score += FlippedScoreUtil(marker,ring,dirs[k],i,j);
        }
      }
    }
  }
  return flip_score;
}

/*int Board::CountMarkers(Symbol s){
  int marker = 0;
  for(int i = 0 ; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      if(Board::GetSymbolAtPosition(i,j) == s){
        marker++;
      }
    }
  }
  return marker;
}
*/
int Board::MobilityUtil(Symbol ring, Point dir, int i, int j){
  int row,col;
  row = i + dir.x;
  col = j + dir.y;
  int count = 0;
  while(Board::GetSymbolAtPosition(row,col) == V){
    count++;
    row += dir.x;
    col += dir.y;
  }
  while(Board::GetSymbolAtPosition(row,col) != I){
    if(Board::GetSymbolAtPosition(row,col) == V){
      return count + 1;
    }
    else if(Board::GetSymbolAtPosition(row,col) == Black_Ring || Board::GetSymbolAtPosition(row,col) == White_Ring){
      return count;
    }
    row += dir.x;
    col += dir.y;
  }
  return count;
}


float Board::MobilityScore(Symbol s){
  float mob_score = 0.0;
  for(int i = 0; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      if(Board::GetSymbolAtPosition(i,j) == s){
        for(int k = 0; k < 6; k++){
          mob_score += board.MobilityUtil(s,dirs[k],i,j);
        }
      }
    }
  }
  return mob_score;
}

float GameState::Evaluate(){
  //float num_black_marker = board.CountMarkers(Black_Marker);
  //float num_white_marker = board.CountMarkers(White_Marker);

  float white_maker_score = board.MarkerScore(Black_Marker, Black_Ring);
  float black_marker_score = board.MarkerScore(White_Marker, White_Ring);

  Symbol flipped_ring = (current_player == 0) ? White_Ring : Black_ring;

  float flip_Black_Marker = board.FlippedScore(Black_Marker,flipped_ring);
  float flip_White_Marker = board.FlippedScore(White_Marker,flipped_ring);

  float mobility_black_ring = board.MobilityScore(Black_Ring);
  float mobility_white_ring = board.MobilityScore(White_Ring);

  float fin_score = (weights[0] * white_maker_score
    + weights[1] * mobility_white_ring
    + weights[2] * flip_White_Marker
    + weights[3] * board.GetScore(0))* (aux[0] + aux[1] * board.GetScore(0))
    + (weights[4] * black_maker_score
    + weights[5] * mobility_black_ring
    + weights[6] * flip_Black_Marker
    + weights[7] * board.GetScore(1))* (aux[0] + aux[2] * board.GetScore(1));

    return fin_score;
}

vector<pair<Point,Point>> GameState::RowsFormed(int p_id){
  int id;
  vector<pair<Point,Point>> rows_formed = {};
  for(int i = 0; i < 19; i++){
    for(int j = 0; j+4 < 11; j++){
      vector<Point> points;
      Point p;
      p.x = i;
      p.y = j;
      if(!board.IsValidPoint(p) || Board::GetSymbolAtPosition(i,j) == V || Board::GetSymbolAtPosition(i,j) == E || Board::GetSymbolAtPosition(i,j) == White_Ring || Board::GetSymbolAtPosition(i,j) == Black_Ring){
        continue;
      }
      id = Board::GetSymbolAtPosition(i,j) == White_Marker ? 0 : 1;
      if (id == p_id){
        Point temp;
        bool isrow = true;
        for(int k = 1; k < 4; k++){
          temp.x = i + k* dirs[4].x;
          temp.y = j + k* dirs[4].y;
          if(Board::GetSymbolAtPosition(i,j) != Board::GetSymbolAtPosition(temp.x,temp.y) || !Board::IsValidPoint(temp) || j+k > 10 || i+k > 18){
            isrow = false;
            break;
          }
          points.push_back(temp);
        }
        if(!isrow)
          continue;
        rows_formed.push_back(make_pair(p,temp));
        }
      }
  }

  for(int i = 0; i < 19; i++){
    for(int j = 4; j < 11; j++){
      Point p;
      p.x = i;
      p.y = j;
      if(!board.IsValidPoint(p) || Board::GetSymbolAtPosition(i,j) == V || Board::GetSymbolAtPosition(i,j) == E || Board::GetSymbolAtPosition(i,j) == White_Ring || Board::GetSymbolAtPosition(i,j) == Black_Ring){
        continue;
      }
      id = Board::GetSymbolAtPosition(i,j) == White_Marker ? 0 : 1;
      if(id == p_id){
        bool isrow = true;
        Point temp;
        for(int k = 1; k < 4; k++){
          temp.x = i + k* dirs[1].x;
          temp.y = j + k* dirs[1].y;
          if(Board::GetSymbolAtPosition(i,j) != Board::GetSymbolAtPosition(temp.x,temp.y) || !Board::IsValidPoint(temp) || i+k < 0 || j+k > 10){
            isrow = false;
            break;
          }
        }
        if(!isrow)
          continue;
        rows_formed.push_back(make_pair(p,temp));
        }
      }
    }

  for(int i = 0; i < 19; i++){
    for(int j = 0; j < 11; j++){
      Point p;
      p.x = i;
      p.y = j;
      if(!board.IsValidPoint(p) || Board::GetSymbolAtPosition(i,j) == V || Board::GetSymbolAtPosition(i,j) == E || Board::GetSymbolAtPosition(i,j) == White_Ring || Board::GetSymbolAtPosition(i,j) == Black_Ring){
        continue;
      }
      id = Board::GetSymbolAtPosition(i,j) == White_Marker ? 0 : 1;
      if(id == p_id){
        bool isrow = true;
        Point temp;
        for(int k = 1; k < 4; k++){
          temp.x = i + k* dirs[3].x;
          temp.y = j + k* dirs[3].y;
          if(Board::GetSymbolAtPosition(i,j) != Board::GetSymbolAtPosition(temp.x,temp.y) || !Board::IsValidPoint(temp) || i+k > 18){
            isrow = false;
            break;
          }
        }
        if(!isrow)
          continue;
          rows_formed.push_back(make_pair(p,temp));
        }
    }
  }
  return rows_formed;
}

bool GameState::CheckTerminal(){
  if(whiteRings <=3 || blackRings <= 3){
    return true;
  }
  return false;
}

bool GameState::SelectRing(Point pos, int p_id){
  int id = (board.GetSymbolAtPosition(pos.x,pos.y) == White_Ring) ? 1: 0;
  if(!board.IsValidPoint(pos) || p_id ! = id){
    return false;
  }
  selectedRing.x = pos.x;
  selectedRing.y = pos.y;
  return true;
}

bool GameState::RowStart(Point p, int p_id){
  int id = (board.GetSymbolAtPosition(pos.x,pos.y) == White_Ring) ? 1: 0;
  if(!board.IsValidPoint(pos) || p_id ! = id){
    return false;
  }
  rowStart.x p.x;
  rowStart.y = p.y;
  return true;
}

bool GameState::RowStart(Point p, int p_id){
  int id = (board.GetSymbolAtPosition(pos.x,pos.y) == White_Ring) ? 1: 0;
  if(!board.IsValidPoint(pos) || p_id ! = id){
    return false;
  }
  rowEnd.x p.x;
  rowEnd.y = p.y;
  return true;
}

vector<Point> GameState::GetValidPointsForRings(){
  vector<Point> points;
  for(int i = 0; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      Point p;
      p.x = i;
      p.y = j;
      if(!board.IsValidPoint(p) || board.GetSymbolAtPosition(i,j) == Black_Marker || board.GetSymbolAtPosition(i,j) == White_Marker){
        continue;
      }
      else if(board.GetSymbolAtPosition(i,j) == V){
        points.push_back(p);
      }
    }
  }
  return points;
}

Board GameState::Clone(Board b){
  for(int i = 0 ; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      Point p;
      p.x = i;
      p.y = j;
      b.AddSymbolAtPosition(p,board.GetSymbolAtPosition(i ,j));
    }
  }
  return b;
}

vector<Point> Rings(int p_id){
  vector<Point> points;
  for(int i = 0; i < Rows; i++){
    for(int j = 0; j < Cols; j++){
      int id = (GetSymbolAtPosition(i,j) == Black_Ring ? 1 : 0);
      if(id == p_id){
        Point p;
        p.x = i;
        p.y = j;
        points.push_back(p);
      }
    }
  }
  return points;
}
