#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::sort;
using std::map;
using std::lower_bound;

string InverseBWT(const string& bwt) {
  string text = "";
  string cop = bwt;
  map<char,vector<int>> tr1;
  map<char,vector<int>> tr2;
  sort(cop.begin(),cop.end());
  for(int i = 0; i < bwt.size();++i)
    tr1[bwt[i]].push_back(i);
  for(int i = 0; i < cop.size();++i)
    tr2[cop[i]].push_back(i);
  int i = 0;
  while(text.size() != bwt.size()){
      text += cop[i];
      int ind = lower_bound(tr1[bwt[i]].begin(),tr1[bwt[i]].end(),i)-tr1[bwt[i]].begin();
      i = tr2[bwt[i]][ind];
  }
  reverse(text.begin(),text.end());
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
