#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>

int main(){
  std::string text = "Let me split this into words";
  std::vector<std::string> results;

  boost::split(results, text, [](char c){return c == ' ';});
  for(int i = 0 ; i < results.size(); i++){
    std::cout << results[i] << std::endl;
  }
  return 0;
}
