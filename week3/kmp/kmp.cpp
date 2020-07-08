#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
    vector<int> result;
    string use = pattern + "$" + text;
    vector<int> temp(use.size(),0);
    int border = 0;
    for(int i = 1; i < use.size();++i){
        while(border > 0 && use[i] != use[border])
            border = temp[border-1];
        if(use[i] == use[border])
            ++border;
        else border = 0;
        temp[i] = border;
        if(border == (int)pattern.size()){
            //cout << "wut" << "\n";
            result.push_back(i-(int)pattern.size()-(int)pattern.size());
        }
    }
    // Implement this function yourself
    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<int> result = find_pattern(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
