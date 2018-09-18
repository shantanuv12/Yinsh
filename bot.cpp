#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <climits>
#include <boost/algorithm/string.hpp>
#include <cmath>

using namespace std;

// valid_move_list(board, vector<pair<int,int>>)
vector<pair<int,int>> dirs = {make_pair(0,-2),make_pair(-1,1),make_pair(-1,-1),make_pair(0,2),make_pair(1,1),make_pair(1,-1)};
pair<int,int> sel_ring = make_pair(-1,-1);
pair<int,int> remove_row_start = make_pair(-1,-1);
pair<int,int> remove_row_end = make_pair(-1,-1);

vector<vector<int>> setMarker(vector<vector<int>> board, int x, int y, int marker){
  board[x][y] = marker;
  return board;
}

bool isValidPoint(vector<vector<int>> board,int col, int row){
  if(row > 19 || row < 0 || col < 0 || col > 10 || board[col][row] == -100)
        return false;
    return true;
}

vector<vector<int>> removeMarker(vector<vector<int>> board, int col, int row){
  board[col][row] = 0;
  return board;
}

vector<vector<int>> flipMarkers(vector<vector<int>> board, int x_init, int y_init, int x_fin, int y_fin){
  int ind = 0;
  for(int i = 0; i < dirs.size(); i++){
    if(dirs[i].first == 0){
      if( x_init == x_fin  && (y_fin - y_init) % dirs[i].second == 0 ){
                ind = i;
                break;
      }
    }
    else if( (x_fin - x_init) / dirs[i].first == (y_fin - y_init) / dirs[i].second){
            ind = i;
            break;
    }
  }
  int temp_x = x_init + dirs[ind].first;
  int temp_y = y_init + dirs[ind].second;
  int k = (y_fin - y_init) / dirs[ind].second;
  for(int l = 1 ; l < k; l++){
    if(board[temp_x][temp_y] == -1)
      board[temp_x][temp_y] = 1;
    else if(board[temp_x][temp_y] == 1)
      board[temp_x][temp_y] = -1;
    temp_x = temp_x + dirs[ind].first;
    temp_y = temp_y + dirs[ind].second;
  }
  return board;
}

vector<vector<int>> moveRing(vector<vector<int>> board,int x_init, int y_init, int x_fin, int y_fin){
  int ring = board[x_init][y_init];
  int marker = (ring == 2) ? 1 : -1;
  board[x_init][y_init] = marker;
  board = flipMarkers(board,x_init,y_init,x_fin,y_fin);
  board[x_fin][y_fin] = ring;
  return board;
}

vector<vector<int>> placeRingAt(vector<vector<int>> board, int x, int y, int id){
  if(id == 0){
    return setMarker(board, x, y, 2);
  }
  else{
    return setMarker(board,x,y,-2);
  }
}

vector<vector<int>> removeRing(vector<vector<int>> board, int x, int y, int id){
  return removeMarker(board,x,y);
}

vector<vector<int>> selectRing(vector<vector<int>> board, int x, int y){
  sel_ring.first = x;
  sel_ring.second = y;
  return board;
}

vector<vector<int>> removeRow(vector<vector<int>> board, int x_init, int y_init, int x_fin, int y_fin){
  int ind = 0;
  for(int i = 0; i < 6; i++){
    if(dirs[i].first == 0){
      if( x_init == x_fin  && (y_fin - y_init) % dirs[i].second == 0 ){
                ind = i;
                break;
      }
    }
    else if((x_fin - x_init) / dirs[i].first == (y_fin - y_init) / dirs[i].second){
    ind = i;
    break;
    }
  }
  int temp_x = x_init;
  int temp_y = y_init;
  int k = (y_fin - y_init) / dirs[ind].second;
  for(int k = 1; k < 4; k++){
    board[temp_x][temp_y] = 0;

    temp_x = temp_x + dirs[ind].first;
    temp_y = temp_y + dirs[ind].second;
  }
  return board;
}

vector<vector<int>> selectRowStart(vector<vector<int>> board, int x, int y){
  remove_row_start.first = x;
  remove_row_start.second = y;
  return board;
}

vector<vector<int>> selectRowEnd(vector<vector<int>> board, int x, int y){
  remove_row_end.first = x;
  remove_row_end.second = y;
  return removeRow(board,remove_row_start.first,remove_row_start.second,remove_row_end.first, remove_row_end.second);
}

vector<vector<int>> execute(vector<vector<int>> board, string cmd,int id);

vector<vector<int>> execute_sequence(vector<vector<int>> board,vector<string> moves,int id){
  vector<string> moves_list = {};
  //cout << "lol" << endl;
  string move;
  for(int i = 0; i < moves.size(); i++){
    move = moves[i];
  //  cout << "move " << move << endl;
    if( i % 3 == 2){
      moves_list.push_back(move);
      string lol;
      for (auto const& s : moves_list) { lol = lol + s + " "; }
    // cout <<"lol :  " << lol << endl;
      board = execute(board,lol.substr(0,lol.length()-1), id);
      moves_list = {};
    }
    else{
      moves_list.push_back(move);
    }
  }
  return board;
}

vector<vector<int>> execute(vector<vector<int>> board, string cmd,int id){
  //vector<vector<int>> temp = board;
  vector<string> moves;
  boost::split(moves, cmd, [](char c){return (c == ' ');});
  if(moves.size() > 3){
    //cout << moves.size() << "moves[0]: " << moves[0] << endl;
    return execute_sequence(board,moves,id);
  }
  string move_type = moves[0];
  int x = stoi(moves[1]);
  int y = stoi(moves[2]);
  //cout << "Error in next funs" << endl;
  if(move_type == "P")
        return placeRingAt(board, x, y, id);
  else if (move_type == "S")
        return selectRing(board, x ,y);
  else if (move_type == "M")
        return moveRing(board,sel_ring.first,sel_ring.second,x,y);
  else if (move_type == "RS")
        return selectRowStart(board, x, y);
  else if (move_type == "RE")
        return selectRowEnd(board, x, y);
  else if (move_type == "X")
        return removeMarker(board, x, y);
  else
    return board;
}

vector<float> CalculateScore(int wRings,int bRings,int wMarkers,int bMarkers, char Error_state){
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
      scores[0] = -1;
      scores[1] = -1;
    }
    score[0] = scores[0] + ((float) wMarkers)/1000;
    score[1] = scores[1] + ((float) bMarkers)/1000;
    return score;
}

float get_score(vector<vector<int>> board, int p_id, char Error_state = '0'){
  int w_rings = 0;
  int b_rings = 0;
  int w_markers = 0;
  int b_markers = 0;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 19; j++){
      int s = board[i][j];
      if(s == 0 || s == -100){
        continue;
      }
      else if(s == 2){
        w_rings++;
      }
      else if(s == -2){
        b_rings++;
      }
      else if(s == 1){
        w_markers++;
      }
      else if(s == -1){
        b_markers++;
      }
    }
  }
  return CalculateScore(5-w_rings,5-b_rings,w_markers,b_markers,Error_state)[p_id];
}


int lenRowsFormed(vector<vector<int>> board, pair<int,int> dir, int i, int j){
  int row = j + dir.second;
  int col = i + dir.first;
  int marker = 1;
  int len = 1;
  while(row > -1 && row < 19 && col > -1 && col < 19){
    if(board[col][row] == marker){
      len++;
    }
    else{
      break;
    }
  }
  return len;
}


float fun1(vector<vector<int>> board){
  float score = 0.0f;
  int len = 0;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 19; j++){
      if(board[i][j] == 1){
        for(int k = 0 ; k < 6; k++){
          len = lenRowsFormed(board,dirs[k], i, j);
          score += pow(2.0f,len);
        }
      }
    }
  }
  //cout << "Working fine fun1" << endl;
  return score;
}

float fun2(vector<vector<int>> board){
  float score = 0.0f;
  float weight = 0.0f;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 19; j++){
      if(board[i][j] == 2){
        if(i == 5 && j == 9){
          weight = 1000.0f;
        }
        else{
          int l = (i-5 > 0) ? i-5:5-i;
          int m = (j-9 > 0) ? j-9:9-j;
          weight = (100.0f/sqrt(pow((float)l,2) + pow((float)m,2)));
        }
        score += weight;
      }
    }
  }
  return score;
}

int flippedUtil(vector<vector<int>> board, int marker, int ring, pair<int,int> dir, int i, int j){
  int row = i + dir.second;
  int col = j + dir.first;
  int marker_count = 0;
  while (row < 19 && row > -1 && col < 11 && col > -1 && board[col][row] == 0){
        row += dir.second;
        col += dir.first;
      }
  while (row < 19 && row > -1 && col < 11 && col > -1 && board[col][row] != -100){
      if(board[col][row] == marker)
            marker_count += 1;
      else if (board[col][row] == 0)
            return marker_count;
      else if (board[col][row] == -2 || board[col][row] == 2 ){
            return 0;
      }
      row += dir.second;
      col += dir.first;
      }
    return 0;
}

float flippedScore(vector<vector<int>> board, int marker, int ring){
  float flipped_score = 0.0;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 19; j++){
      if(board[i][j] == ring){
        for(int k = 0; j < 6; k++){
          flipped_score += 1.0 * flippedUtil(board, marker, ring, dirs[k], i ,j);
        }
      }
    }
  }
  return flipped_score;
}

int countMarkers(vector<vector<int>> board, int marker){
  int marker_count = 0;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 19; j++){
      if(board[i][j] == marker){
        marker_count++;
      }
    }
  }
  return marker_count;
}

int mobilityUtil(vector<vector<int>> board, int ring, pair<int,int> dir, int i, int j){
  int row = j + dir.second;
  int col = i + dir.first;
  int space_count = 0;
  while (row < 19 && row > -1 && col < 11 && col > -1 && board[col][row] == 0){
        space_count++;
        row += dir.second;
        col += dir.first;
      }
  while (row < 19 && row > -1 && col < 11 && col > -1 && board[col][row] != -100){
      if(board[col][row] == 0)
            return space_count+1;
      else if (board[col][row] == -2 || board[col][row] == 2 )
            return space_count;
        row += dir.second;
        col += dir.first;
      }
  return space_count;
}

float mobilityScore(vector<vector<int>> board, int ring){
  float mobility_score = 0.0;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 19; j++){
      if(board[i][j] == ring){
        for(int k = 0; j < 6; k++){
          mobility_score += 1.0 * mobilityUtil(board,ring, dirs[k], i ,j);
        }
      }
    }
  }
  return mobility_score;
}

float evaluate(vector<vector<int>> board, int current_player){
  //cout << "Before countMarkers white" << endl;
  int num_w_marker = 0;//countMarkers(board,1);
  //cout << "Before countMarkers black" << endl;
  int num_b_marker = 0;//countMarkers(board,-1);

  //  black_row = markerScore(board,-1,-2)
  //  white_row = markerScore(board,1,2)
  //cout << "Before countMarkers " << endl;
  int flip_ring = (current_player == 0) ? 2 : -2;
  //cout << "Before flippedscore white" << endl;
  int flip_white_marker = 0;//flippedScore(board,-1,flip_ring);
  //cout << "Before flippedscore blacks" << endl;
  int flip_black_marker = 0;//flippedScore(board,1,flip_ring);
  //cout << "Before mobilityscore white" << endl;
  int mobility_black_ring = 0;//mobilityScore(board,-2);
  //cout << "Before mobilityscore black" << endl;
  int mobility_white_ring = 0;//mobilityScore(board,2);
  //cout << "Before get_score white" << endl;
  int val1 = fun1(board);
  int val2 = fun2(board);
  int white_score = get_score(board, 0);
  //cout << "Before get_score blacak" << endl;
  int black_score = get_score(board, 1);
  //cout << "after all this time? always" << endl;

  return (num_w_marker +flip_white_marker + mobility_white_ring + white_score) * (0.5 * (1 + white_score)) + (num_b_marker + flip_black_marker + mobility_black_ring + black_score) * (0.5 * (1 + black_score)) + val1 + val2;

}

//valid_moves_list()
// execute()
// rows_formed()
// evaluate()
vector<pair<int,int>> validPointsInARow(vector<vector<int>> board, pair<int,int> point, pair<int,int> dir){
    vector<pair<int,int>> lis;
    int col = point.first + dir.first;
    int row = point.second + dir.second;
    bool no_jump = true;
    bool first_jump = false;
    while(row > -1 && row < 19 && col > -1 && col < 11){
      if(board[col][row] == 2 || board[col][row] == -2){
        return lis;
      }
      else if(board[col][row] == 1 || board[col][row] == -1){
        first_jump = true;
        no_jump = false;
      }
      else if(board[col][row] == 0){
        if(no_jump){
          lis.push_back(make_pair(col,row));
        }
        if(first_jump){
          lis.push_back(make_pair(col,row));
          return lis;
        }
      }
      col += dir.first;
      row += dir.second;
    }
    return lis;
}

vector<pair<int,int>> addList(vector<pair<int,int>> lis1, vector<pair<int,int>> lis2){
  for(auto it = lis2.begin(); it != lis2.end();it++){
    lis1.push_back((*it));
  }
  return lis1;
}

vector<pair<int,int>> valid_moves_list(vector<vector<int>> board, pair<int, int> point){
  vector<pair<int,int>> lis;
  for(int i = 0; i < 6; i++){
    lis = addList(lis,validPointsInARow(board,point,dirs[i]));
  }
  return lis;
}

vector<pair<pair<int,int>,pair<int,int>>> rows_formed(vector<vector<int>> board, int pid){
  vector<vector<int>> temp = board;
  int marker = (pid == 0) ? 1 : -1;
  vector<pair<pair<int,int>,pair<int,int>>> lis;
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 11; j++){
      if(temp[i][j] != marker){
        continue;
      }
      bool isrow = true;
      for(int k = 1; k < 5; k++){
        if(temp[i][j+k*2] != marker){
          isrow = false;
          break;
        }
      }
      if(!isrow){
        continue;
      }
      lis.push_back(make_pair(make_pair(i,j),make_pair(i,j+8)));
    }
  }
  for(int i = 0; i < 7; i++){
    for(int j = 4; j < 19; j++){
      if(temp[i][j] != marker){
        continue;
      }
      bool isrow = true;
      for(int k = 1; k < 5; k++){
        if(temp[i+k][j-k] != marker){
          isrow = false;
          break;
        }
      }
      if(!isrow){
        continue;
      }
      lis.push_back(make_pair(make_pair(i,j),make_pair(i+4,j-4)));
    }
  }
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 15; j++){
      if(temp[i][j] != marker){
        continue;
      }
      bool isrow = true;
      for(int k = 1; k < 5; k++){
        if(temp[i][j+k*2] != marker){
          isrow = false;
          break;
        }
      }
      if(!isrow){
        continue;
      }
      lis.push_back(make_pair(make_pair(i,j),make_pair(i+4,j+4)));
    }
  }
  return lis;
}

class Node{
public:
  vector<vector<int>> board;
  string move;
  vector<Node> list_children;
  int won;
  int num_ring;
  int utility;

  Node(vector<vector<int>> b, string m, vector<Node> lis,int rings_num, int w){
    this->board = b;
    this->move = m;
    this->num_ring = rings_num;
    this->list_children = lis;
    this->utility = 0;
    this->won = w;
  }

  void append_children(int num, int player){
    int ring,marker;
    if(num == 0){
      for(int i = 0; i < 11; i++){
        for(int j = 0; j < 19; j++){
          if(board[i][j] == 0){
            string temp_move = "P " + to_string(i) + " " + to_string(j);
            vector<vector<int>> b = this->board;
            vector<vector<int>> temp_board = execute(b,temp_move,player);
            Node a(temp_board,temp_move, {} ,0,0);
            (this->list_children).push_back(a);
          }
        }
      }
    }
    if(num == 1){
      if(player == 0){
        ring = 2;
        marker = 1;
      }
      else{
        ring = -2;
        marker = -1;
      }
      if(won == 0){
        while(rows_formed(board,0).size() != 0){
          vector<pair<pair<int,int>,pair<int,int>>> temp = rows_formed(board,0);
          vector<Node> lol;
          for(int j = 0; j < temp.size(); j++){
            string temp_move = "RS " + to_string(temp[j].first.first) + " " + to_string(temp[j].first.second) + " RE " + to_string(temp[j].second.first) + " " + to_string(temp[j].second.second);
            lol.push_back(Node(execute(board,temp_move,player),temp_move, {}, num_ring, won));
          }
          vector<Node> lol1;
          for(int i = 0; i < lol.size(); i++){
            for(int j = 0; j < 11; j++){
              for(int k = 0; k < 19; k++){
                if(lol1[i].board[j][k] == ring){
                  string temp_move = lol1[i].move + " X " + to_string(j) + " " + to_string(k);
                  int ring_num = num_ring + 1;
                  if(ring_num > 2){
                    lol1.push_back(Node(execute(lol1[i].board,temp_move,player),temp_move, lol1[i].list_children, ring_num, 1));
                  }
                  else{
                    lol1.push_back(Node(execute(lol1[i].board,temp_move,player),temp_move, lol1[i].list_children, ring_num, 0));
                  }
                }
              }
            }
          }
          int max_score = INT_MIN;
          int index = -1;
          Node max_node({},"",{},0,0);

          for(int i = 0; i < lol1.size(); i++){
            int score = evaluate(lol1[i].board, 0);
            if(score > max_score){
              max_score = score;
              max_node = lol1[i];
              index = i;
            }
          }
          this->board = lol1[index].board;
          this->move = lol1[index].move;
          this->won = lol1[index].won;
          this->num_ring = lol1[index].num_ring;
          this->list_children = lol1[index].list_children;
        }
        if(rows_formed(board,0).size() == 0){
          for(int i = 0; i < 11; i++){
            for(int j = 0; j < 19; j++){
              if(board[i][j] == ring){
                vector<pair<int, int>> moves_list = valid_moves_list(board,make_pair(i,j));
                for(int k = 0; k < moves_list.size(); k++){
                  string temp_move = "S " + to_string(i) + " " + to_string(j) + " M " + to_string(moves_list[k].first) + " " + to_string(moves_list[k].second);
                   list_children.push_back(Node(execute(board,temp_move,player), temp_move, {}, num_ring, won));
                }
              }
            }
          }
          vector<Node>::iterator it;
          for(it = list_children.begin(); it != list_children.end(); it++){
            if(rows_formed((*it).board,0).size() != 0 || rows_formed((*it).board,1).size() != 0){
              if(won == 0){
                it = list_children.erase(it);
                --it;
                vector<pair<pair<int,int>,pair<int,int>>> temp_rows = rows_formed(board,0);
                vector<Node> temp;
                for(int j = 0; j < temp_rows.size();j++){
                  string temp_move = (*it).move + " RS " + to_string(temp_rows[j].first.first) + " " + to_string(temp_rows[j].first.second) + " RE " + to_string(temp_rows[j].second.first) + " "  + to_string(temp_rows[j].second.second);
                  temp.push_back(Node(execute((*it).board, temp_move, player), temp_move, (*it).list_children, (*it).num_ring, (*it).won));
                }
                vector<Node> temp1;
                for(int j = 0; j < temp.size(); j++){
                  for(int k = 0; k < 11; k++){
                    for(int l = 0; l < 19; l++){
                      if(temp[j].board[k][l] == ring){
                        string temp_move = temp[j].move + " X " +to_string(k) + " " + to_string(l);
                        int rings_num = temp[j].num_ring + 1;
                        if(rings_num > 2){
                          temp1.push_back(Node(execute(temp[j].board, temp_move, player), temp_move, temp[j].list_children, rings_num, 1));
                        }
                        else{
                          temp1.push_back(Node(execute(temp[j].board, temp_move, player), temp_move, temp[j].list_children, rings_num, 0));
                        }
                      }
                    }
                  }
                }
                vector<Node>:: iterator it1;
                for(it1 = temp1.begin(); it1 != temp1.end(); it1++){
                  list_children.push_back((*it1));
                }
              }
            }
          }
        }
      }
    }
  }
};

Node get_tree(int num,vector<vector<int>> b, int num_moves){
  Node root = Node(b, " ", {}, 0, 0);
  if(num == 0){
    root.append_children(num, 0);
    for(auto it = root.list_children.begin(); it != root.list_children.end(); it++){
      (*it).append_children(num,1);
    //  for(auto jt = (*it).list_children.begin(); jt != (*it).list_children.end(); jt++){
    //    (*jt).append_children(num,0);
    //  }
    }
    return root;
  }
  if(num == 1){
    if(num_moves < 30){
      root.append_children(num,0);
      for(auto it = root.list_children.begin(); it != root.list_children.end(); it++){
        (*it).append_children(num,1);
      // for(auto jt = (*it).list_children.begin(); jt != (*it).list_children.end(); jt++){
      //    (*jt).append_children(num,0);
        //}
      }
    }
    else{
      root.append_children(num,0);
      for(auto it = root.list_children.begin(); it != root.list_children.end(); it++){
        (*it).append_children(num,1);
        for(auto jt = (*it).list_children.begin(); jt != (*it).list_children.end(); jt++){
          (*jt).append_children(num,0);
          //for(auto kt = (*jt).list_children.begin(); kt != (*jt).list_children.end(); kt++){
            //(*kt).append_children(num,1);
            //for(auto lt = (*kt).list_children.begin(); lt != (*kt).list_children.end(); lt++){
            //  (*lt).append_children(num,0);
            //}
          //}
        }
      }
    }
    return root;
  }
  return root;
}
int max_val(Node node, int alpha, int beta, int player);

int min_val(Node node, int alpha, int beta, int player){
//  cout << "In min : size of children " << node.list_children.size() << endl;
  if(node.list_children.size() == 0){
  //  cout << "before evaluate " << endl;
    node.utility = evaluate(node.board, player);
  //  cout << "after evaluate " << endl;
    return node.utility;
  }

  int value = INT_MAX;

  vector<Node> children = node.list_children;

  for(auto it = children.begin(); it != children.end(); it++){
    //cout << "move " << (*it).move << endl;
    Node child = *it;
    value = min(value, max_val(child,alpha,beta, 1-player));
  //  cout << "value " << value << "alpha "<< alpha <<endl;
    if(value <= alpha){
      return value;
    }
    beta = min(beta, value);
  }
  return value;
}

int max_val(Node node, int alpha, int beta, int player){
//  cout << "In max " << node.move << endl;
  if(node.list_children.size() == 0){
    node.utility = evaluate(node.board, player);
    return node.utility;
  }

  int value = INT_MIN;

  vector<Node> children = node.list_children;

  for(auto it = children.begin(); it != children.end(); it++){
    Node child = *it;
    value = max(value, min_val(child,alpha,beta, 1-player));
  //  cout << "value " << value << "beta "<< beta <<endl;
    if(value >= beta){
      return value;
    }
    alpha = max(alpha, value);
  }
  return value;
}


Node main_minimax(Node node){
  int best_val = INT_MIN;
  int beta = INT_MAX;

  vector<Node> children = node.list_children;
  Node best_child({},"",{},0,0);
  for(auto it = children.begin(); it != children.end(); it++){
    //cout <<"size of children  "<< children.size() << endl;
    //cout << "size of list_children " << node.list_children.size() << endl;
    //cout << "In main minimax "<<(*child).move << endl;
    Node child = *it;
    int value = max_val(child,best_val,beta, 0);
  //  cout << "after max_val in main minmax" << endl;
    if(value > best_val){
      best_val = value;
      best_child.board = child.board;
      best_child.move = child.move;
      best_child.list_children = child.list_children;
      best_child.won = child.won;
    }
  }
  //cout << best_child.move << endl;
  return best_child;
}

string minimax(int num_moves, vector<vector<int>> b){
  //cout << "In minimax" << endl;
  Node tree({},"",{},0,0);
  if(num_moves < 5){
    tree = get_tree(0,b,num_moves);
    //cout << "get_tree working" << endl;
  }
  else{
    tree = get_tree(1,b,num_moves);
  }
  //for(auto it = tree.list_children.begin(); it != tree.list_children.end();it++){
  //  cout << (*it).move << endl;
  //}
  Node child = main_minimax(tree);
  return child.move;
}

pair<int,int> null = make_pair(-10,-10);
vector<vector<pair<int,int>>> b_to_h = {{null, null, null, null, null, null, make_pair(5,24), null, make_pair(5,23), null, make_pair(5,22), null, make_pair(5,21), null, null, null, null, null, null}, {null, null, null, make_pair(5,26), null, make_pair(4,20), null, make_pair(4,19), null, make_pair(4,18), null, make_pair(4,17), null, make_pair(4,16), null, make_pair(5,19), null, null, null}, {null, null, make_pair(5,27), null, make_pair(4,21), null, make_pair(3,15), null, make_pair(3,14), null, make_pair(3,13), null, make_pair(3,12), null, make_pair(4,15), null, make_pair(5,18), null, null}, {null, make_pair(5,28), null, make_pair(4,22), null, make_pair(3,16), null, make_pair(2,10), null, make_pair(2,9), null, make_pair(2,8), null, make_pair(3,11), null, make_pair(4,14), null, make_pair(5,17), null}, {make_pair(5,29), null, make_pair(4,23), null, make_pair(3,17), null, make_pair(2,11), null, make_pair(1,5), null, make_pair(1,4), null, make_pair(2,7), null, make_pair(3,10), null, make_pair(4,13), null, make_pair(5,16)}, {null, make_pair(4,0), null, make_pair(3,0), null, make_pair(2,0), null, make_pair(1,0), null, make_pair(0,0), null, make_pair(1,3), null, make_pair(2,6), null, make_pair(3,9), null, make_pair(4,12), null}, {make_pair(5,1), null, make_pair(4,1), null, make_pair(3,1), null, make_pair(2,1), null, make_pair(1,1), null, make_pair(1,2), null, make_pair(2,5), null, make_pair(3,8), null, make_pair(4,11), null, make_pair(5,14)}, {null, make_pair(5,2), null, make_pair(4,2), null, make_pair(3,2), null, make_pair(2,2), null, make_pair(2,3), null, make_pair(2,4), null, make_pair(3,7), null, make_pair(4,10), null, make_pair(5,13), null}, {null, null, make_pair(5,3), null, make_pair(4,3), null, make_pair(3,3), null, make_pair(3,4), null, make_pair(3,5), null, make_pair(3,6), null, make_pair(4,9), null, make_pair(5,12), null, null}, {null, null, null, make_pair(5,4), null, make_pair(4,4), null, make_pair(4,5), null, make_pair(4,6), null, make_pair(4,7), null, make_pair(4,8), null, make_pair(5,11), null, null, null}, {null, null, null, null, null, null, make_pair(5,6), null, make_pair(5,7), null, make_pair(5,8), null, make_pair(5,9), null, null, null, null, null, null}};

vector<vector<pair<int,int>>> h_to_b = {{make_pair(5,9)},{make_pair(5,7),make_pair(6,8),make_pair(6,10),make_pair(5,11),make_pair(4,10),make_pair(4,8)},{make_pair(5,5),make_pair(6,6),make_pair(7,7),make_pair(7,9),make_pair(7,11),make_pair(6,12),make_pair(5,13),make_pair(4,12),make_pair(3,11),make_pair(3,9),make_pair(3,7),make_pair(4,6)},{make_pair(5,3),make_pair(6,4),make_pair(7,5),make_pair(8,6),make_pair(8,8),make_pair(8,10),make_pair(8,12),make_pair(7,13),make_pair(6,14),make_pair(5,15),make_pair(4,14),make_pair(3,13),make_pair(2,12),make_pair(2,10),make_pair(2,8),make_pair(2,6),make_pair(3,5),make_pair(4,4)},{make_pair(5,1),make_pair(6,2),make_pair(7,3),make_pair(8,4),make_pair(9,5),make_pair(9,7),make_pair(9,9),make_pair(9,11),make_pair(9,13),make_pair(8,14),make_pair(7,15),make_pair(6,16),make_pair(5,17),make_pair(4,16),make_pair(3,15),make_pair(2,14),make_pair(1,13),make_pair(1,11),make_pair(1,9),make_pair(1,7),make_pair(1,5),make_pair(2,4),make_pair(3,3),make_pair(4,2)},{null,make_pair(6,0),make_pair(7,1),make_pair(8,2),make_pair(9,3),null,make_pair(10,6),make_pair(10,8),make_pair(10,10),make_pair(10,12),null,make_pair(9,15),make_pair(8,16),make_pair(7,17),make_pair(6,18),null,make_pair(4,18),make_pair(3,17),make_pair(2,16),make_pair(1,15),null,make_pair(0,12),make_pair(0,10),make_pair(0,8),make_pair(0,6),null,make_pair(1,3),make_pair(2,2),make_pair(3,1),make_pair(4,0)}};

string get_board_move(string move){
  vector<string> results = {};
  boost::split(results, move, [](char c){return (c == ' ');});
  vector<string> finals = {};
  int turn = results.size();
  int i = 0;
  while(turn > 0){
    if(i % 3 == 0){
      finals.push_back(results[i]);
      i++;
      turn--;
    }
    else{
      pair<int,int> points = h_to_b[stoi(results[i])][stoi(results[i+1])];
      finals.push_back(to_string(points.first));
      finals.push_back(to_string(points.second));
      i += 2;
      turn -= 2;
    }
  }
//  string result = "";
//  for(int i = 0; i < finals.size(); i++){
    //cout << "results[i] " << results[i] << endl;
//    result = result + finals[i] + " ";
//  }
  string result;
  for (auto const& s : finals) { result = result + s + " "; };
  return result.substr(0, result.length() - 1);
}

string get_hex_move(string move){
  vector<string> results = {};
  boost::split(results, move, [](char c){return (c == ' ');});
  vector<string> finals = {};
  int turn = results.size();
  int i = 0;
  while(turn > 0){
    if(i % 3 == 0){
      finals.push_back(results[i]);
      i++;
      turn--;
    }
    else{
      pair<int,int> points = b_to_h[stoi(results[i])][stoi(results[i+1])];
      finals.push_back(to_string(points.first));
      finals.push_back(to_string(points.second));
      i += 2;
      turn -= 2;
    }
  }
  string result;
  for (auto const& s : finals) { result = result + s + " "; }
  return result.substr(0,result.length() -1);
}

void print(vector<vector<int>> board){
  for(int i = 0; i < 19; i++){
    for(int j = 0; j < 11; j++){
      if(board[j][i] == -100){
          cout <<"*" <<"\t";
      }
      else{
        cout << board[j][i] << "\t";
      }
    }
    cout << "\n";
  }
  cout <<"\n--------------------------------------------\n";
}

int main(){
  vector<vector<int>> board;
  vector<int> column;
  for(int i = 0; i < 11; i++){
    column = {};
    for(int j = 0; j < 19; j++){
      column.push_back(-100);
    }
    board.push_back(column);
  }

  for(auto i = h_to_b.begin(); i != h_to_b.end(); i++){
    for(auto j = (*i).begin(); j != (*i).end(); j++){
      if((*j) != null){
        board[(*j).first][(*j).second] = 0;
      }
    }
  }
//  print(board);
  int num_moves = 0;
  int flag = 0;
  int current_player, board_size, time_limit;
  string data;
  cin >> current_player >> board_size >> time_limit;
  cin.ignore();
    //boost::split(res, move, [](char c){return (c == ' ');});

  int player = current_player -1;
  string op_move;
  while(true){
    if((flag == 0) && (player == 0)){
      string my_move = "P 5 9\n" ;
      board = execute(board,my_move, 0);
  //    print(board);
      num_moves++;
      flag = 1;
      cout << "P 0 0" << endl;
    }
    else{
      getline(cin,op_move);
      //cout << "op_move " << op_move << endl;
      op_move = get_board_move(op_move);
      //cout << "op_move " << op_move << endl;
    // cout << "\n";
      board = execute(board,op_move,1);
    //  cout << "opponent" << endl;
    //  print(board);
      string my_move = minimax(num_moves,board);
    //  cout << "my" << endl;
      board = execute(board,my_move, 0);
      my_move = get_hex_move(my_move);
    //  print(board);
      num_moves += 1;
      cout << my_move << endl;
    }
  }
  return 0;
}
