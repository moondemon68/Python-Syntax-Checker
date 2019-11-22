#include <bits/stdc++.h>
#define rhs first
#define lhs1 second.first
#define lhs2 second.second
#define pb push_back
using namespace std;

pair<string, pair<string, string>> m[1005];

int main () {

    /* INITS */
    // Basically memsetting the array
    for (int i=0;i<=1000;i++) {
        m[i].rhs = "~";
        m[i].lhs1 = "~";
        m[i].lhs2 = "~";
    }

    /* INPUTS */
    // Read program, and parse it
    int n;
    cin >> n;
    string a[n+5];
    for (int i=1;i<=n;i++) cin >> a[i];
    
    // Read cnf
    ifstream fin("cnf.txt");
    string line;
    int cnt = 0;
    while (getline(fin, line)) {
        istringstream read(line);
        string rhs, lhs, arrow;
        read >> rhs >> arrow;
        int i = 1;
        cnt++;
        while (read >> lhs) {
            if (lhs == "|") {
                i=1;
                cnt++;
            } else {
                m[cnt].rhs = rhs;
                if (i == 1) m[cnt].lhs1 = lhs;
                else m[cnt].lhs2 = lhs;
                i++;
            }
        }
    }
    int r = cnt;

    /* For debugging purposes, this is the productions */
    // for (int i=1;i<=r;i++) {
    //     cout  << i << ' ' << m[i].rhs << " -> ";
    //     cout << m[i].lhs1;
    //     if (m[i].lhs2 != "~") {
    //         cout << " " << m[i].lhs2;
    //     }
    //     cout << endl;
    // }

    /* ACTUAL CYK ALGO */

    /* From wikipedia: */
    // let the input be a string I consisting of n characters: a1 ... an.
    // let the grammar contain r nonterminal symbols R1 ... Rr, with start symbol R1.
    // let P[n,n,r] be an array of booleans. Initialize all elements of P to false.
    // for each s = 1 to n
    // for each unit production Rv → as
    //     set P[1,s,v] = true
    // for each l = 2 to n -- Length of span
    // for each s = 1 to n-l+1 -- Start of span
    //     for each p = 1 to l-1 -- Partition of span
    //     for each production Ra  → Rb Rc
    //         if P[p,s,b] and P[l-p,s+p,c] then set P[l,s,a] = true
    // if P[n,1,1] is true then
    // I is member of language
    // else
    // I is not member of language

    bool P[n+5][n+5][r+5];
    memset (P, 0, sizeof(P));
    for (int s=1;s<=n;s++) {
        for (int v=1;v<=r;v++) {
            if (m[v].lhs1 == a[s]) {
                P[1][s][v] = 1;
            }
            // cout << P[1][s][v];
        }
        // cout << endl;
    }

    for (int l=2;l<=n;l++) {
        for (int s=1;s<=n-l+1;s++) {
            for (int p=1;p<=l-1;p++) {
                for (int a=1;a<=r;a++) {
                    for (int b=1;b<=r;b++) {
                        for (int c=1;c<=r;c++) {
                            if (m[b].rhs == m[a].lhs1 && m[c].rhs == m[a].lhs2) {
                                if (P[p][s][b] && P[l-p][s+p][c]) P[l][s][a] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    bool y = 0;
    for (int i=1;i<=r;i++) {
        if (m[i].rhs == "S0" && P[n][1][i]) y = 1;
    }
    if (y) cout << "AC" << endl;
    else cout << "WA" << endl;

    return 0;
}