#include "bot.h"

using namespace std;


Bot::Bot(int p_id){
  GameState gamestate = new GameState(p_id);
}

int Bot::ExecuteMoveOpponent(string move, int p_id){
  vector<string> results;
  boost::split(results, move, [](char c){return (c == ' ');});
  if(results.size() >3){
    return ExecuteSequenceOppnent(results,p_id);
  }
  Point i;
  i.x = convertPoint(result[1],result[2]).first;
  i.y = convertPoint(result[1],result[2]).second;

  int success = 1;

  if(results[0] == "P"){
    gamestate.AddRingAt(i,p_id);
  }
  else if(results[0] == "S"){
    gamestate.SelectRing(i,p_id);
  }
  else if(results[0] == "M"){
    Point p;
    p.x = gamestate.selectedRing.x;
    p.y = gamestate.selectedRing.y;
    gamestate.MoveRingTo(p,i,p_id);
  }
  else if(results[0] == "RS"){
    gameState.RowStart(i,p_id);
  }
  else if(results[0] == "RE"){
    gameState.RowEnd(i,p_id);
  }
  else if(results[0] == "X"){
    Point init;
    init.x = gameState.rowStart.x;
    init.y = gameState.rowStart.y;
    Point fin;
    fin.x = gameState.rowEnd.x;
    fin.y = gameState.rowEnd.y;
    Point dir;
    dir.x = (fin.x - init.x)/4;
    dir.y = (fin.y - init.y)/4;
    gameState.RemoveRow(init, fin, dir, p_id);
    gameState.RemoveRing(i,p_id);
  }

  bool won = gameState.CheckTerminal();
  if(won){
    sucess = 2;
  }
  return sucess;
}

int Bot::ExecuteSequenceOppnent(vector<string> moves, int p_id){
    int sucess = 1;
    vector<string> moves_list;
    for(int i = 0; i < moves.size(); i++){
      if(i % 3 == 2){
        moves_list.push_back(moves[i]);
        int move_success = this.ExecuteMove(moves[i]);
        if(move_success == 0){
          return 0;
        }
        if(success && move_success ! = 0){
          success = 1;
        }
        else{
          success = 1;
        }
        moves_list = {};
      }
      else{
        moves_list.push_back(moves[i]);
      }
    }
    return success;
}

vector<GameState> GenerateChildren(int p_id){
  vector<GameState> children;
  if(gamestate.whiteRingsOnBoard < 5 || gamestate.blackRingsOnBoard < 5){
    vector<points> moves = gamestate.GetValidPointsForRings();
    for(int i = 0 ; i < moves.size(); i++){
      GameState child = new GameState(p_id);
      child.board = gameState.Clone(child.board);
      child.AddRingAt(moves[i],p_id);
      children.push_back(child);
    }
    return children;
  }
  else{Markers
    vector<Point, Point> rows_formed = RowsFormed(p_id);
    if(rows_formed.size() > 0){
      for(int i = 0; i < rows_formed.size(); i++){
        GameState child = new GameState(p_id);
        child.board = gamestate.Clone(child.board);
        child.RemoveRow(rows_formed.first,rows_formed.second);
        vector<Point> markers = Rings(p_id);
        for(int j = 0; j < markers.size(); j++){

        }
      }
    }
    vector<Points> points = Rings(p_id){
      for(int i = 0; i < points.size(); i++){
        vector<Point> moves = ValidMovesList(points[i]);
        for(int j = 0; j < moves.size(); j++){
          GameState child = new GameState(p_id);
          child.board = gameState.Clone(child.board);
          child.MoveRingTo(points[i],moves[j],p_id);

        }
      }
    }
  }

}
