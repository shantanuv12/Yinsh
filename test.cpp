#include <bits/stdc++.h>
#include <vector>
#include <cmath>
using namespace std;

class Node{
public:
  int x;
  vector<vector<int>> vec;
  vector<Node> nodes;
  Node(){
    this->x = 0;
  }
  Node(int x){
    this->x = x;
  }

  Node(int x, vector<vector<int>> vec){
    this->x = x;
    this->vec = vec;
  }
  int ret(){
    return x;
  }
  int addvector(Node n){
    nodes.push_back(n);
    return n.ret();
  }
};


Node fun(Node a){
  Node n(3);
  n.x = a.x;
  n.vec = {};
  n.nodes = {};
  return n;
}

int succeess(vector<int> lol){
  if(lol.size() == 0){
    return 1;
  }
  return 0;
}

int m = 0;
int fun(){
  int x = m;

  return x;
}

int fu(){
  m = 3;
  return m;
}
int main(){
  //vector<Node> li = {Node(3), Node(4), Node(2), Node(1)};
  //vector<Node> lim;
  //vector<int> lis = {1,2,3,4,5,6};
  //vector<Node>::iterator it;
  //for(it = li.begin(); it != li.end(); it++){
  //  lim.push_back((*it));
  //}
  //cout << lim.size() << endl;
  //cout << Node(1).ret() << endl;
  /*for(auto it1 = lim.begin(); it1 != lim.end(); it1++){
    cout << it1->ret() << endl;
  }
  for(int i = 0; i < lis.size(); i++){
    cout << lis[i] << endl;
  }
  Node n(3,{{1,3},{2}});
  Node m(4,{});
  Node o(3,{{1,3},{2}});
  Node p = fun(m);
  //cout << n.vec[0].size() << endl;
  //cout << max(1,2) << endl;
  cout << p.ret() << endl;
  cout << p.vec.size() << endl;
  cout << p.nodes.size() << endl;

  pair<int,int> null = make_pair(-10,-10);
  vector<vector<pair<int,int>>> b_to_h = {{null, null, null, null, null, null, make_pair(5,24), null, make_pair(5,23), null, make_pair(5,22), null, make_pair(5,21), null, null, null, null, null, null}, {null, null, null, make_pair(5,26), null, make_pair(4,20), null, make_pair(4,19), null, make_pair(4,18), null, make_pair(4,17), null, make_pair(4,16), null, make_pair(5,19), null, null, null}, {null, null, make_pair(5,27), null, make_pair(4,21), null, make_pair(3,15), null, make_pair(3,14), null, make_pair(3,13), null, make_pair(3,12), null, make_pair(4,15), null, make_pair(5,18), null, null}, {null, make_pair(5,28), null, make_pair(4,22), null, make_pair(3,16), null, make_pair(2,10), null, make_pair(2,9), null, make_pair(2,8), null, make_pair(3,11), null, make_pair(4,14), null, make_pair(5,17), null}, {make_pair(5,29), null, make_pair(4,23), null, make_pair(3,17), null, make_pair(2,11), null, make_pair(1,5), null, make_pair(1,4), null, make_pair(2,7), null, make_pair(3,10), null, make_pair(4,13), null, make_pair(5,16)}, {null, make_pair(4,0), null, make_pair(3,0), null, make_pair(2,0), null, make_pair(1,0), null, make_pair(0,0), null, make_pair(1,3), null, make_pair(2,6), null, make_pair(3,9), null, make_pair(4,12), null}, {make_pair(5,1), null, make_pair(4,1), null, make_pair(3,1), null, make_pair(2,1), null, make_pair(1,1), null, make_pair(1,2), null, make_pair(2,5), null, make_pair(3,8), null, make_pair(4,11), null, make_pair(5,14)}, {null, make_pair(5,2), null, make_pair(4,2), null, make_pair(3,2), null, make_pair(2,2), null, make_pair(2,3), null, make_pair(2,4), null, make_pair(3,7), null, make_pair(4,10), null, make_pair(5,13), null}, {null, null, make_pair(5,3), null, make_pair(4,3), null, make_pair(3,3), null, make_pair(3,4), null, make_pair(3,5), null, make_pair(3,6), null, make_pair(4,9), null, make_pair(5,12), null, null}, {null, null, null, make_pair(5,4), null, make_pair(4,4), null, make_pair(4,5), null, make_pair(4,6), null, make_pair(4,7), null, make_pair(4,8), null, make_pair(5,11), null, null, null}, {null, null, null, null, null, null, make_pair(5,6), null, make_pair(5,7), null, make_pair(5,8), null, make_pair(5,9), null, null, null, null, null, null}};

  vector<vector<pair<int,int>>> h_to_b = {{make_pair(5,9)},{make_pair(5,7),make_pair(6,8),make_pair(6,10),make_pair(5,11),make_pair(4,10),make_pair(4,8)},{make_pair(5,5),make_pair(6,6),make_pair(7,7),make_pair(7,9),make_pair(7,11),make_pair(6,12),make_pair(5,13),make_pair(4,12),make_pair(3,11),make_pair(3,9),make_pair(3,7),make_pair(4,6)},{make_pair(5,3),make_pair(6,4),make_pair(7,5),make_pair(8,6),make_pair(8,8),make_pair(8,10),make_pair(8,12),make_pair(7,13),make_pair(6,14),make_pair(5,15),make_pair(4,14),make_pair(3,13),make_pair(2,12),make_pair(2,10),make_pair(2,8),make_pair(2,6),make_pair(3,5),make_pair(4,4)},{make_pair(5,1),make_pair(6,2),make_pair(7,3),make_pair(8,4),make_pair(9,5),make_pair(9,7),make_pair(9,9),make_pair(9,11),make_pair(9,13),make_pair(8,14),make_pair(7,15),make_pair(6,16),make_pair(5,17),make_pair(4,16),make_pair(3,15),make_pair(2,14),make_pair(1,13),make_pair(1,11),make_pair(1,9),make_pair(1,7),make_pair(1,5),make_pair(2,4),make_pair(3,3),make_pair(4,2)},{null,make_pair(6,0),make_pair(7,1),make_pair(8,2),make_pair(9,3),null,make_pair(10,6),make_pair(10,8),make_pair(10,10),make_pair(10,12),null,make_pair(9,15),make_pair(8,16),make_pair(7,17),make_pair(6,18),null,make_pair(4,18),make_pair(3,17),make_pair(2,16),make_pair(1,15),null,make_pair(0,12),make_pair(0,10),make_pair(0,8),make_pair(0,6),null,make_pair(1,3),make_pair(2,2),make_pair(3,1),make_pair(4,0)}};

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
  cout << board[0][0] << endl;
  */
  float score = 0.0f;
  for(int i = 0; i < 10; i++){
    score+= pow(2.0f,i);
  }
  cout << score << endl;


  return 0;

}
