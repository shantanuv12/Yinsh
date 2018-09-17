#include "node.h"
#include <string.h>
#include <boost/algorithm/string.hpp>
using namespace std;

class Bot{
public:
  GameState gamestate;

  Bot();

  const int start_depth = 5;

  const int end_dept = 6;

  bool ExecuteMove(String move);

  vector<GameState> GenerateChildren();

  string ReturnMove();

  string Minimax();

}
