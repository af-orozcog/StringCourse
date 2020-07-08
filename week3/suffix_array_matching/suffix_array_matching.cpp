#include<bits/stdc++.h>
using namespace std;


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


vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  vector<int> result;
  int lo = 0, hi = text.size()-1;
  int ans1 = -1;
  while(lo <= hi){
    int mid = (lo+hi)>>1;
    int see = pattern.compare(0,pattern.size(),text,suffix_array[mid],pattern.size());
    if(see < 0) hi = mid - 1;
    else if(see > 0) lo = mid + 1;
    else hi = mid -1, ans1 = mid;
  }
  lo = 0, hi = text.size()-1;
  int ans2 = -1;
  while(lo <= hi){
    int mid = (lo+hi)>>1;
    int see = pattern.compare(0,pattern.size(),text,suffix_array[mid],pattern.size());
    if(see < 0) hi = mid -1;
    else if(see > 0) lo = mid + 1;
    else lo = mid +1, ans2 = mid;
  }
  if(ans1 == -1) return result;
  for(int i = ans1; i <= ans2;++i)
    result.push_back(suffix_array[i]);
  return result;
}

int main() {
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
