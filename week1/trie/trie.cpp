#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges add;
  t.push_back(add);
  for(auto &va:patterns){
    int start = 0;
    for(int i = 0; i < va.size();++i){
        if(!t[start].count(va[i])){
            edges temp;
            t[start][va[i]] = (int)t.size();
            start = t.size();
            t.push_back(temp);
        }
        else start = t[start][va[i]];
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
