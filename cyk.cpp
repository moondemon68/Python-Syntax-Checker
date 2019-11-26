#include <bits/stdc++.h>
#define rhs first
#define lhs1 second.first
#define lhs2 second.second
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

int findstart(string s, int r) {
    int l=1,h=r,ans=1;
    while (l<=h) {
        int mid = (l+h)/2;
        if (m[mid].rhs < s) {
            l=mid+1;
        } else if (m[mid].rhs == s) {
            h=mid-1;
            ans=mid;
        } else {
            h=mid-1;
        }
    }
    return ans;
}

int findend(string s, int r) {
    int l=1,h=r,ans=1;
    while (l<=h) {
        int mid = (l+h)/2;
        if (m[mid].rhs < s) {
            l=mid+1;
        } else if (m[mid].rhs == s) {
            l=mid+1;
            ans=mid;
        } else {
            h=mid-1;
        }
    }
    return ans;
}

int main () {
    clock_t start = clock();
    /* INITS */
    // Basically memsetting the array
    for (int i=0;i<=1000;i++) {
        m[i].rhs = "~";
        m[i].lhs1 = "~";
        m[i].lhs2 = "~";
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
    
    for (int i=1;i<=r;i++) {
        if (m[i].rhs == "newline") m[i].rhs = "n";
        else if (m[i].rhs == "variable") m[i].rhs = "v";
        else if (m[i].rhs == "equal") m[i].rhs = "e";
        else if (m[i].rhs == "if") m[i].rhs = "i";
        else if (m[i].rhs == "return") m[i].rhs = "r";
        else if (m[i].rhs == "openparentheses") m[i].rhs = "o";
        else if (m[i].rhs == "closeparentheses") m[i].rhs = "c";
        else if (m[i].rhs == "colon") m[i].rhs = "co";
        else if (m[i].rhs == "elif") m[i].rhs = "e";
        else if (m[i].rhs == "else") m[i].rhs = "el";
        else if (m[i].rhs == "true") m[i].rhs = "t";
        else if (m[i].rhs == "false") m[i].rhs = "f";
        else if (m[i].rhs == "constant") m[i].rhs = "con";
        else if (m[i].rhs == "arithmeticop") m[i].rhs = "a";
        else if (m[i].rhs == "logicalop") m[i].rhs = "l";
        else if (m[i].rhs == "and") m[i].rhs = "an";
        else if (m[i].rhs == "or") m[i].rhs = "or";
        else if (m[i].rhs == "not") m[i].rhs = "no";
        else if (m[i].rhs == "for") m[i].rhs = "fo";
        else if (m[i].rhs == "in") m[i].rhs = "in";
        else if (m[i].rhs == "range") m[i].rhs = "ra";
        else if (m[i].rhs == "comma") m[i].rhs = "com";
        else if (m[i].rhs == "while") m[i].rhs = "w";
        else if (m[i].rhs == "import") m[i].rhs = "im";
        else if (m[i].rhs == "logicalop") m[i].rhs = "l";
        else if (m[i].rhs == "from") m[i].rhs = "fr";
        else if (m[i].rhs == "as") m[i].rhs = "as";
        else if (m[i].rhs == "def") m[i].rhs = "d";
        else if (m[i].rhs == "class") m[i].rhs = "cl";
        else if (m[i].rhs == "pass") m[i].rhs = "p";
        else if (m[i].rhs == "raise") m[i].rhs = "rai";
        else if (m[i].rhs == "with") m[i].rhs = "wi";

        if (m[i].lhs1 == "newline") m[i].lhs1 = "n";
        else if (m[i].lhs1 == "variable") m[i].lhs1 = "v";
        else if (m[i].lhs1 == "equal") m[i].lhs1 = "e";
        else if (m[i].lhs1 == "if") m[i].lhs1 = "i";
        else if (m[i].lhs1 == "return") m[i].lhs1 = "r";
        else if (m[i].lhs1 == "openparentheses") m[i].lhs1 = "o";
        else if (m[i].lhs1 == "closeparentheses") m[i].lhs1 = "c";
        else if (m[i].lhs1 == "colon") m[i].lhs1 = "co";
        else if (m[i].lhs1 == "elif") m[i].lhs1 = "e";
        else if (m[i].lhs1 == "else") m[i].lhs1 = "el";
        else if (m[i].lhs1 == "true") m[i].lhs1 = "t";
        else if (m[i].lhs1 == "false") m[i].lhs1 = "f";
        else if (m[i].lhs1 == "constant") m[i].lhs1 = "con";
        else if (m[i].lhs1 == "arithmeticop") m[i].lhs1 = "a";
        else if (m[i].lhs1 == "logicalop") m[i].lhs1 = "l";
        else if (m[i].lhs1 == "and") m[i].lhs1 = "an";
        else if (m[i].lhs1 == "or") m[i].lhs1 = "or";
        else if (m[i].lhs1 == "not") m[i].lhs1 = "no";
        else if (m[i].lhs1 == "for") m[i].lhs1 = "fo";
        else if (m[i].lhs1 == "in") m[i].lhs1 = "in";
        else if (m[i].lhs1 == "range") m[i].lhs1 = "ra";
        else if (m[i].lhs1 == "comma") m[i].lhs1 = "com";
        else if (m[i].lhs1 == "while") m[i].lhs1 = "w";
        else if (m[i].lhs1 == "import") m[i].lhs1 = "im";
        else if (m[i].lhs1 == "logicalop") m[i].lhs1 = "l";
        else if (m[i].lhs1 == "from") m[i].lhs1 = "fr";
        else if (m[i].lhs1 == "as") m[i].lhs1 = "as";
        else if (m[i].lhs1 == "def") m[i].lhs1 = "d";
        else if (m[i].lhs1 == "class") m[i].lhs1 = "cl";
        else if (m[i].lhs1 == "pass") m[i].lhs1 = "p";
        else if (m[i].lhs1 == "raise") m[i].lhs1 = "rai";
        else if (m[i].lhs1 == "with") m[i].lhs1 = "wi";

        if (m[i].lhs2 == "newline") m[i].lhs2 = "n";
        else if (m[i].lhs2 == "variable") m[i].lhs2 = "v";
        else if (m[i].lhs2 == "equal") m[i].lhs2 = "e";
        else if (m[i].lhs2 == "if") m[i].lhs2 = "i";
        else if (m[i].lhs2 == "return") m[i].lhs2 = "r";
        else if (m[i].lhs2 == "openparentheses") m[i].lhs2 = "o";
        else if (m[i].lhs2 == "closeparentheses") m[i].lhs2 = "c";
        else if (m[i].lhs2 == "colon") m[i].lhs2 = "co";
        else if (m[i].lhs2 == "elif") m[i].lhs2 = "e";
        else if (m[i].lhs2 == "else") m[i].lhs2 = "el";
        else if (m[i].lhs2 == "true") m[i].lhs2 = "t";
        else if (m[i].lhs2 == "false") m[i].lhs2 = "f";
        else if (m[i].lhs2 == "constant") m[i].lhs2 = "con";
        else if (m[i].lhs2 == "arithmeticop") m[i].lhs2 = "a";
        else if (m[i].lhs2 == "logicalop") m[i].lhs2 = "l";
        else if (m[i].lhs2 == "and") m[i].lhs2 = "an";
        else if (m[i].lhs2 == "or") m[i].lhs2 = "or";
        else if (m[i].lhs2 == "not") m[i].lhs2 = "no";
        else if (m[i].lhs2 == "for") m[i].lhs2 = "fo";
        else if (m[i].lhs2 == "in") m[i].lhs2 = "in";
        else if (m[i].lhs2 == "range") m[i].lhs2 = "ra";
        else if (m[i].lhs2 == "comma") m[i].lhs2 = "com";
        else if (m[i].lhs2 == "while") m[i].lhs2 = "w";
        else if (m[i].lhs2 == "import") m[i].lhs2 = "im";
        else if (m[i].lhs2 == "logicalop") m[i].lhs2 = "l";
        else if (m[i].lhs2 == "from") m[i].lhs2 = "fr";
        else if (m[i].lhs2 == "as") m[i].lhs2 = "as";
        else if (m[i].lhs2 == "def") m[i].lhs2 = "d";
        else if (m[i].lhs2 == "class") m[i].lhs2 = "cl";
        else if (m[i].lhs2 == "pass") m[i].lhs2 = "p";
        else if (m[i].lhs2 == "raise") m[i].lhs2 = "rai";
        else if (m[i].lhs2 == "with") m[i].lhs2 = "wi";
    }

    sort (m+1, m+r+1);  // binser preprocess
    /* For debugging purposes, this is the productions */
    // for (int i=1;i<=r;i++) {
    //     cout  << i << ' ' << m[i].rhs << " -> ";
    //     cout << m[i].lhs1;
    //     if (m[i].lhs2 != "~") {
    //         cout << " " << m[i].lhs2;
    //     }
    //     cout << endl;
    // }

    for (int i=1;i<=r;i++) {
        if (v.empty()) {
            v.pb(m[i].rhs);
            kiri[0] = 1;
            kanan[0] = 1;
        }
        else if (m[i].rhs != m[i-1].rhs) {
            v.pb(m[i].rhs);
            kiri[finder(m[i].rhs, v.size()-1)] = i;
            kanan[finder(m[i].rhs, v.size()-1)] = i;
        }
        else {
            kanan[finder(m[i].rhs, v.size()-1)] = i;
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
            if (m[v].lhs1 == a[s]) {
                P[1][s][v] = 1;
            }
        }
    }

    for (int l=2;l<=n;l++) {
        cout << l << " " << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
        for (int s=1;s<=n-l+1;s++) {
            for (int p=1;p<=l-1;p++) {
                for (int a=1;a<=r;a++) {
                    int bloc = finder(m[a].lhs1, v.size()-1);
                    for (int b=kiri[bloc];b<=kanan[bloc];b++) {
                        int cloc = finder(m[a].lhs2, v.size()-1);
                        for (int c=kiri[cloc];c<=kanan[cloc];c++) {
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
    cout << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}