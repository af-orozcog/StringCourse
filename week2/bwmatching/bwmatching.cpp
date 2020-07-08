#include<bits/stdc++.h>
using namespace std;
// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
                     const string& bwt) {
    // Implement this function yourself
    int top = 0;
    int buttom = (int)bwt.size()-1;
    string pat = pattern;
    string see = bwt;
    sort(see.begin(),see.end());
    map<char,vector<int>> tr1;
    map<char,vector<int>> tr2;
    for(int i = 0; i < bwt.size();++i)
        tr1[bwt[i]].push_back(i);
    for(int i = 0; i < see.size();++i)
        tr2[see[i]].push_back(i);
    int lo = 0;
    int hi = bwt.size()-1;
    for(int i = 0; i < pattern.size();++i)
        if(!tr1.count(pattern[i])) return 0;
    while(lo <= hi && pat.size()){
        char look = pat.back();
        pat.pop_back();
        lo = lower_bound(tr1[look].begin(),tr1[look].end(),lo)-tr1[look].begin();
        if(lo == (int)tr1[look].size() || tr1[look][lo] > hi) return 0;
        int lastHi = hi;
        hi = lower_bound(tr1[look].begin(),tr1[look].end(),hi)-tr1[look].begin();
        if(hi == (int)tr1[look].size() || tr1[look][hi] > lastHi) --hi;
        lo = tr2[look][lo];
        hi = tr2[look][hi];
    }
    return hi-lo+1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string bwt;
    cin >> bwt;
    int pattern_count;
    cin >> pattern_count;
    // Start of each character in the sorted list of characters of bwt,
    // see the description in the comment about function PreprocessBWT
    map<char, int> starts;
    // Occurrence counts for each character and each position in bwt,
    // see the description in the comment about function PreprocessBWT
    map<char, vector<int> > occ_count_before;
    // Preprocess the BWT once to get starts and occ_count_before.
    // For each pattern, we will then use these precomputed values and
    // spend only O(|pattern|) to find all occurrences of the pattern
    // in the text instead of O(|pattern| + |text|).
    for (int pi = 0; pi < pattern_count; ++pi) {
        string pattern;
        cin >> pattern;
        int occ_count = CountOccurrences(pattern, bwt);
        printf("%d ", occ_count);
    }
    printf("\n");
    return 0;
}
