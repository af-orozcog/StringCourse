#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

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

void dfs(int p, vector<string> &ans, trie &tri, string &actual){
    if((!tri[p].size() || (int)tri[p].size() > 1) && actual.size()) ans.push_back(actual);
    string temp = "";
    for(auto va:tri[p]){
        if((int)tri[p].size() > 1){temp += va.first;dfs(va.second,ans,tri,temp); temp.pop_back();}
        else {actual += va.first;dfs(va.second,ans,tri,actual); actual.pop_back();}
    }
}


// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> patterns;
  for(int i = 0; i < text.size();++i)
    patterns.push_back(text.substr(i,text.size()));
  trie tri = build_trie(patterns);
  vector<string> result;
  string actual = "";
  dfs(0,result,tri,actual);
  // Implement this function yourself
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
