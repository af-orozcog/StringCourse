#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#define mod(x,y)(((x%y)+y)%y)


using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::max;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> tempClasses;
vector<int> tempResult;
vector<int> classes;
vector<int> result;
vector<int> BuildSuffixArray(const string& text) {
    int siz = text.size();
    vector<int> counting(max(255, (int)text.size()),0);
    tempClasses.resize(text.size(),0);
    tempResult.resize(text.size(),0);
    result.resize(text.size(),0);
    classes.resize(text.size(),0);
    for(char va:text)
        ++counting[va];
    for(int i = 1; i < counting.size();++i)
        counting[i] += counting[i-1];
    for(int i = (int)text.size()-1; i > -1;--i){
        result[counting[text[i]]-1] = i;
        --counting[text[i]];
    }
    classes[result[0]] = 0;
    int biggest = 0;
    for(int i = 1; i < result.size();++i){
        if(text[result[i]] == text[result[i-1]])
            classes[result[i]] = classes[result[i-1]];
        else
            classes[result[i]] = classes[result[i-1]] + 1;
        biggest = max(biggest,classes[result[i]]);
    }
    for(int k = 1; k < (int)text.size(); k<<= 1){
        fill(tempResult.begin(), tempResult.end(), 0);
        fill(counting.begin(),counting.end(),0);
        fill(tempClasses.begin(),tempClasses.end(),0);
        for(int i = 0; i < (int)result.size();++i)
            ++counting[classes[i]];
        for(int i = 1; i < counting.size();++i)
            counting[i] += counting[i-1];
        for(int i = (int)result.size()-1; i > -1;--i){
            int where = result[i]-k;
            if(where < 0)
                where += siz;
            int imp1 = classes[where];
            int imp2 = counting[classes[where]];
            tempResult[counting[classes[where]]-1] = where;
            --counting[classes[where]];
        }
        tempClasses[tempResult[0]] = 0;
        for(int i = 1; i < (int)result.size();++i){
            int act1 = classes[tempResult[i]],prev1 = classes[tempResult[i-1]];
            int act2 = classes[(tempResult[i] + k)%siz], prev2 = classes[(tempResult[i-1] + k)%siz];
            if(act1 != prev1 || act2 != prev2)
                tempClasses[tempResult[i]] = tempClasses[tempResult[i-1]] + 1;
            else
                tempClasses[tempResult[i]] = tempClasses[tempResult[i-1]];
            biggest = max(biggest,tempClasses[tempResult[i]]);
        }
        result.swap(tempResult);
        classes.swap(tempClasses);
    }
    return result;
}

int main() {
    string text;
    cin >> text;
    vector<int> suffix_array = BuildSuffixArray(text);
    for (int i = 0; i < suffix_array.size(); ++i) {
        cout << suffix_array[i] << ' ';
    }
    cout << endl;
    return 0;
}
