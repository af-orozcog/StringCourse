#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string shiftRight(string &temp){
    string ans = "";
    for(int i = 1,j = 0; j < temp.size(); ++j){
        ans += temp[i];
        ++i;
        if(i == (int)temp.size())
            i = 0;
    }
    return ans;
}

string BWT(const string& text) {
  string result = "";
  vector<string> check;
  check.push_back(text);
  for(int i = 0; i < (int)text.size()-1;++i){
    check.push_back(shiftRight(check.back()));
  }
  sort(check.begin(),check.end());
  for(int i = 0; i < text.size();++i){
    result += check[i].back();
  }
  // write your code here

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
