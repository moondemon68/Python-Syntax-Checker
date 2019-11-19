#include <bits/stdc++.h>
#define pb push_back

using namespace std;

vector<string> dict;
string m[105][105][105];
/*
S -> A S B | a
Dummy: '~'
*/

void add(string a, string b) {
    // inserts string b to string a
    bool y = 0;
    for (int i=0;i<dict.size();i++) {
        if (dict[i] == a) y = 1;
    }
    if (!y) dict.pb(a);
    m[a].pb(b);
}

string givecode(string a, int x) {
    // gives numbered code to a string
    // Ex: givecode("S", 1) -> "S1"
    char cx = x + '0';
    return a + cx;
}

int main () {
    ifstream cin("cfg.txt");
    ofstream cout("cnf.txt");
    
    // Read the given cfg text file
    string line;
    while (getline(cin, line)) {
        istringstream read (line);
        string rhs, lhs, arrow;
        read >> rhs;
        read >> arrow;
        while (read >> lhs) {
            if (lhs != "|" && lhs != "ε") add(rhs, lhs);
        }
    }

    add("S1", "S");  // Eliminating the start state 

    // Output the cnf
    for (int i=0;i<dict.size();i++) {
        cout << dict[i] << " -> ";
        for (int j=0;j<m[dict[i]].size();j++) {
            cout << m[dict[i]][j] << " ";
        }
        cout << endl;
    }

    return 0;
}