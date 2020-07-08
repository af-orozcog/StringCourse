#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;

struct Node
{
    Node *next [Letters];
    bool patternEnd = false;
	Node ()
	{
		fill (next, next + Letters, nullptr);
	}

	bool isLeaf () const
	{
	    return (next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
    Node *root = new Node();
	vector <int> result;
    for(auto &va:patterns){
        Node *temp = root;
        for(auto ve:va){
            if(temp->next[letterToIndex(ve)] == nullptr){
                Node *add = new Node();
                temp->next[letterToIndex(ve)] = add;
                temp = add;
            }
            else temp = temp->next[letterToIndex(ve)];
        }
        temp ->patternEnd = 1;
    }
    for(int i = 0; i < text.size();++i){
        Node *temp = root;
        int j = i;
        while(!temp->patternEnd && j < text.size()){
            if(temp->next[letterToIndex(text[j])] != nullptr)
                temp = temp->next[letterToIndex(text[j])];
            else break;
            ++j;
        }
        if(temp->patternEnd)
            result.push_back(i);
    }
	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
