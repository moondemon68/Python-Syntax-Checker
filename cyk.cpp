#include <bits/stdc++.h>
#define lhs first
#define rhs1 second.first
#define rhs2 second.second
#define pb push_back
using namespace std;

pair<string, pair<string, string>> m[1005];
string a[1005];
bool P[505][505][505];
vector<string> v;
int kiri[1005], kanan[1005];

int finder(string s, int r) {
    int l=0,h=r,ans=0;
    while (l<=h) {
        int mid = (l+h)/2;
        if (v[mid] < s) {
            l=mid+1;
        } else if (v[mid] == s) {
            h=mid-1;
            ans=mid;
        } else {
            h=mid-1;
        }
    }
    return ans;
}

// int findstart(string s, int r) {
//     int l=1,h=r,ans=1;
//     while (l<=h) {
//         int mid = (l+h)/2;
//         if (m[mid].lhs < s) {
//             l=mid+1;
//         } else if (m[mid].lhs == s) {
//             h=mid-1;
//             ans=mid;
//         } else {
//             h=mid-1;
//         }
//     }
//     return ans;
// }

// int findend(string s, int r) {
//     int l=1,h=r,ans=1;
//     while (l<=h) {
//         int mid = (l+h)/2;
//         if (m[mid].lhs < s) {
//             l=mid+1;
//         } else if (m[mid].lhs == s) {
//             l=mid+1;
//             ans=mid;
//         } else {
//             h=mid-1;
//         }
//     }
//     return ans;
// }

int main () {
    clock_t start = clock();
    /* INITS */
    // Basically memsetting the array
    for (int i=0;i<=1000;i++) {
        m[i].lhs = "~";
        m[i].rhs1 = "~";
        m[i].rhs2 = "~";
    }

    /* INPUTS */
    // Read tokens
    ifstream cin("token.txt");
    int n = 1;
    while (cin >> a[n]) n++;
    n--;
    cout << n << endl;
    
    // Read cnf
    ifstream fin("cnf.txt");
    string line;
    int cnt = 0;
    while (getline(fin, line)) {
        istringstream read(line);
        string lhs, lhs, arrow;
        read >> lhs >> arrow;
        int i = 1;
        cnt++;
        while (read >> lhs) {
            if (lhs == "|") {
                i=1;
                cnt++;
            } else {
                m[cnt].lhs = lhs;
                if (i == 1) m[cnt].rhs1 = lhs;
                else m[cnt].rhs2 = lhs;
                i++;
            }
        }
    }
    int r = cnt;
    
    for (int i=1;i<=r;i++) {
        if (m[i].lhs == "newline") m[i].lhs = "n";
        else if (m[i].lhs == "variable") m[i].lhs = "v";
        else if (m[i].lhs == "equal") m[i].lhs = "e";
        else if (m[i].lhs == "if") m[i].lhs = "i";
        else if (m[i].lhs == "return") m[i].lhs = "r";
        else if (m[i].lhs == "openparentheses") m[i].lhs = "o";
        else if (m[i].lhs == "closeparentheses") m[i].lhs = "c";
        else if (m[i].lhs == "colon") m[i].lhs = "co";
        else if (m[i].lhs == "elif") m[i].lhs = "e";
        else if (m[i].lhs == "else") m[i].lhs = "el";
        else if (m[i].lhs == "true") m[i].lhs = "t";
        else if (m[i].lhs == "false") m[i].lhs = "f";
        else if (m[i].lhs == "constant") m[i].lhs = "con";
        else if (m[i].lhs == "arithmeticop") m[i].lhs = "a";
        else if (m[i].lhs == "logicalop") m[i].lhs = "l";
        else if (m[i].lhs == "and") m[i].lhs = "an";
        else if (m[i].lhs == "or") m[i].lhs = "or";
        else if (m[i].lhs == "not") m[i].lhs = "no";
        else if (m[i].lhs == "for") m[i].lhs = "fo";
        else if (m[i].lhs == "in") m[i].lhs = "in";
        else if (m[i].lhs == "range") m[i].lhs = "ra";
        else if (m[i].lhs == "comma") m[i].lhs = "com";
        else if (m[i].lhs == "while") m[i].lhs = "w";
        else if (m[i].lhs == "import") m[i].lhs = "im";
        else if (m[i].lhs == "logicalop") m[i].lhs = "l";
        else if (m[i].lhs == "from") m[i].lhs = "fr";
        else if (m[i].lhs == "as") m[i].lhs = "as";
        else if (m[i].lhs == "def") m[i].lhs = "d";
        else if (m[i].lhs == "class") m[i].lhs = "cl";
        else if (m[i].lhs == "pass") m[i].lhs = "p";
        else if (m[i].lhs == "raise") m[i].lhs = "rai";
        else if (m[i].lhs == "with") m[i].lhs = "wi";

        if (m[i].rhs1 == "newline") m[i].rhs1 = "n";
        else if (m[i].rhs1 == "variable") m[i].rhs1 = "v";
        else if (m[i].rhs1 == "equal") m[i].rhs1 = "e";
        else if (m[i].rhs1 == "if") m[i].rhs1 = "i";
        else if (m[i].rhs1 == "return") m[i].rhs1 = "r";
        else if (m[i].rhs1 == "openparentheses") m[i].rhs1 = "o";
        else if (m[i].rhs1 == "closeparentheses") m[i].rhs1 = "c";
        else if (m[i].rhs1 == "colon") m[i].rhs1 = "co";
        else if (m[i].rhs1 == "elif") m[i].rhs1 = "e";
        else if (m[i].rhs1 == "else") m[i].rhs1 = "el";
        else if (m[i].rhs1 == "true") m[i].rhs1 = "t";
        else if (m[i].rhs1 == "false") m[i].rhs1 = "f";
        else if (m[i].rhs1 == "constant") m[i].rhs1 = "con";
        else if (m[i].rhs1 == "arithmeticop") m[i].rhs1 = "a";
        else if (m[i].rhs1 == "logicalop") m[i].rhs1 = "l";
        else if (m[i].rhs1 == "and") m[i].rhs1 = "an";
        else if (m[i].rhs1 == "or") m[i].rhs1 = "or";
        else if (m[i].rhs1 == "not") m[i].rhs1 = "no";
        else if (m[i].rhs1 == "for") m[i].rhs1 = "fo";
        else if (m[i].rhs1 == "in") m[i].rhs1 = "in";
        else if (m[i].rhs1 == "range") m[i].rhs1 = "ra";
        else if (m[i].rhs1 == "comma") m[i].rhs1 = "com";
        else if (m[i].rhs1 == "while") m[i].rhs1 = "w";
        else if (m[i].rhs1 == "import") m[i].rhs1 = "im";
        else if (m[i].rhs1 == "logicalop") m[i].rhs1 = "l";
        else if (m[i].rhs1 == "from") m[i].rhs1 = "fr";
        else if (m[i].rhs1 == "as") m[i].rhs1 = "as";
        else if (m[i].rhs1 == "def") m[i].rhs1 = "d";
        else if (m[i].rhs1 == "class") m[i].rhs1 = "cl";
        else if (m[i].rhs1 == "pass") m[i].rhs1 = "p";
        else if (m[i].rhs1 == "raise") m[i].rhs1 = "rai";
        else if (m[i].rhs1 == "with") m[i].rhs1 = "wi";

        if (m[i].rhs2 == "newline") m[i].rhs2 = "n";
        else if (m[i].rhs2 == "variable") m[i].rhs2 = "v";
        else if (m[i].rhs2 == "equal") m[i].rhs2 = "e";
        else if (m[i].rhs2 == "if") m[i].rhs2 = "i";
        else if (m[i].rhs2 == "return") m[i].rhs2 = "r";
        else if (m[i].rhs2 == "openparentheses") m[i].rhs2 = "o";
        else if (m[i].rhs2 == "closeparentheses") m[i].rhs2 = "c";
        else if (m[i].rhs2 == "colon") m[i].rhs2 = "co";
        else if (m[i].rhs2 == "elif") m[i].rhs2 = "e";
        else if (m[i].rhs2 == "else") m[i].rhs2 = "el";
        else if (m[i].rhs2 == "true") m[i].rhs2 = "t";
        else if (m[i].rhs2 == "false") m[i].rhs2 = "f";
        else if (m[i].rhs2 == "constant") m[i].rhs2 = "con";
        else if (m[i].rhs2 == "arithmeticop") m[i].rhs2 = "a";
        else if (m[i].rhs2 == "logicalop") m[i].rhs2 = "l";
        else if (m[i].rhs2 == "and") m[i].rhs2 = "an";
        else if (m[i].rhs2 == "or") m[i].rhs2 = "or";
        else if (m[i].rhs2 == "not") m[i].rhs2 = "no";
        else if (m[i].rhs2 == "for") m[i].rhs2 = "fo";
        else if (m[i].rhs2 == "in") m[i].rhs2 = "in";
        else if (m[i].rhs2 == "range") m[i].rhs2 = "ra";
        else if (m[i].rhs2 == "comma") m[i].rhs2 = "com";
        else if (m[i].rhs2 == "while") m[i].rhs2 = "w";
        else if (m[i].rhs2 == "import") m[i].rhs2 = "im";
        else if (m[i].rhs2 == "logicalop") m[i].rhs2 = "l";
        else if (m[i].rhs2 == "from") m[i].rhs2 = "fr";
        else if (m[i].rhs2 == "as") m[i].rhs2 = "as";
        else if (m[i].rhs2 == "def") m[i].rhs2 = "d";
        else if (m[i].rhs2 == "class") m[i].rhs2 = "cl";
        else if (m[i].rhs2 == "pass") m[i].rhs2 = "p";
        else if (m[i].rhs2 == "raise") m[i].rhs2 = "rai";
        else if (m[i].rhs2 == "with") m[i].rhs2 = "wi";
    }

    sort (m+1, m+r+1);  // binser preprocess
    /* For debugging purposes, this is the productions */
    // for (int i=1;i<=r;i++) {
    //     cout  << i << ' ' << m[i].lhs << " -> ";
    //     cout << m[i].rhs1;
    //     if (m[i].rhs2 != "~") {
    //         cout << " " << m[i].rhs2;
    //     }
    //     cout << endl;
    // }

    for (int i=1;i<=r;i++) {
        if (v.empty()) {
            v.pb(m[i].lhs);
            kiri[0] = 1;
            kanan[0] = 1;
        }
        else if (m[i].lhs != m[i-1].lhs) {
            v.pb(m[i].lhs);
            kiri[finder(m[i].lhs, v.size()-1)] = i;
            kanan[finder(m[i].lhs, v.size()-1)] = i;
        }
        else {
            kanan[finder(m[i].lhs, v.size()-1)] = i;
        }
    }

    // for (int i=0;i<v.size();i++) {
    //     cout  << i << ' ' << v[i] << " " << kiri[finder(v[i], v.size()-1)] << " " << kanan[finder(v[i], v.size()-1)] << endl;
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

    memset (P, 0, sizeof(P));
    for (int s=1;s<=n;s++) {
        for (int v=1;v<=r;v++) {
            if (m[v].rhs1 == a[s]) {
                P[1][s][v] = 1;
            }
        }
    }

    for (int l=2;l<=n;l++) {
        cout << l << " " << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
        for (int s=1;s<=n-l+1;s++) {
            for (int p=1;p<=l-1;p++) {
                for (int a=1;a<=r;a++) {
                    int bloc = finder(m[a].rhs1, v.size()-1);
                    for (int b=kiri[bloc];b<=kanan[bloc];b++) {
                        int cloc = finder(m[a].rhs2, v.size()-1);
                        for (int c=kiri[cloc];c<=kanan[cloc];c++) {
                            if (m[b].lhs == m[a].rhs1 && m[c].lhs == m[a].rhs2) {
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
        if (m[i].lhs == "S0" && P[n][1][i]) y = 1;
    }
    if (y) cout << "Accepted" << endl;
    else cout << "Syntax Error" << endl;
    cout << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}