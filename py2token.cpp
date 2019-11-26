#include <bits/stdc++.h>
#define pb push_back

using namespace std;

vector<string> tokens;
string signs = "{}()[]+-*/%!#^|~&=,:";
string alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string numbers = "0123456789";

char getchar(string s, int x) {
    if (x >= s.size()) return '~';
    else return s[x];
}

string getstring(string s, int x, int y) {
    string ret = "";
    for (int i=x;i<=y;i++) {
        if (i < s.size()) {
            ret += s[i];
        } else {
            return "~";
        }
    }
    return ret;
}

bool sign(char c) {
    for (int i=0;i<signs.size();i++) {
        if (c == signs[i]) return 1;
    }
    return 0;
}

bool alphabet(char c) {
    for (int i=0;i<alphabets.size();i++) {
        if (c == alphabets[i]) return 1;
    }
    return 0;
}

bool number(char c) {
    for (int i=0;i<numbers.size();i++) {
        if (c == numbers[i]) return 1;
    }
    return 0;
}

int main () {
    bool success = 1, commentmode = 0;
    int linenum = 0;
    ifstream cin("piton.py");
    string line;
    while (getline(cin, line)) {
        bool out = 0;
        linenum++;
        istringstream read(line);
        string word;
        while (read >> word) {
            if (out) continue;
            int p = 0;
            while (p < word.size()) {
                if (getstring(word, p, p+2) == "\'\'\'" && !commentmode) {
                    commentmode = 1;
                    p+=3;
                    continue;
                }
                else if (getstring(word, p, p+2) == "\'\'\'" && commentmode) {
                    commentmode = 0;
                    p+=3;
                    continue;
                }
                if (commentmode) {
                    p++;
                    continue;
                }
                if (getchar(word, p) == '~' && p < word.size()) tokens.pb("arithmeticop");
                else if (getchar(word, p) == '#') {
                    out = 1;
                    break;    // comment
                }
                else if (getchar(word, p) == '(') tokens.pb("openparentheses");
                else if (getchar(word, p) == ')') tokens.pb("closeparentheses");
                else if (getchar(word, p) == '.') {
                    tokens.pb("dot");
                }
                else if (getchar(word, p) == '[') {
                    int cnt = 1;
                    while (p < word.size() && cnt > 0) {
                        p++;
                        if (getchar(word, p) == '[') cnt++;
                        if (getchar(word, p) == ']') cnt--;                        
                    }
                    if (p < word.size()) tokens.pb("constant");
                    else {
                        success = 0;
                        cout << "A [ is unclosed in line " << linenum << endl;
                    }
                } 
                else if (getchar(word, p) == ']') {
                    success = 0;
                    cout << "Extra ] in line " << linenum << endl;
                }
                else if (getchar(word, p) == '{') {
                    int cnt = 1;
                    while (p < word.size() && cnt > 0) {
                        p++;
                        if (getchar(word, p) == '{') cnt++;
                        if (getchar(word, p) == '}') cnt--;                        
                    }
                    if (p < word.size()) tokens.pb("constant");
                    else {
                        success = 0;
                        cout << "A { is unclosed in line " << linenum << endl;
                    }
                } 
                else if (getchar(word, p) == '}') {
                    success = 0;
                    cout << "Extra } in line " << linenum << endl;
                }
                else if (getstring(word, p, p+1) == "->" && sign(getchar(word, p+2))) {
                    read >> word;
                    p=0;
                    while (!sign(getchar(word, p+1))) p++;
                    p--;
                }
                else if ((getchar(word, p) == '>' && getchar(word, p+1) == '=') || (getchar(word, p) == '<' && getchar(word, p+1) == '=') || (getchar(word, p) == '=' && getchar(word, p+1) == '=') || (getchar(word, p) == '!' && getchar(word, p+1) == '=')) {
                    tokens.pb("logicalop");
                    p++;
                }
                else if (getchar(word, p) == ',') tokens.pb("comma");
                else if (getchar(word, p) == ':') tokens.pb("colon");
                else if (getchar(word, p) == '=') tokens.pb("equal");
                else if ((getchar(word, p) == '*' && getchar(word, p+1) == '*') || (getchar(word, p) == '/' && getchar(word, p+1) == '/')) {
                    tokens.pb("arithmeticop");
                    p++;
                }
                else if (getchar(word, p) == '+' || getchar(word, p) == '-' || getchar(word, p) == '*' || getchar(word, p) == '/'|| getchar(word, p) == '%' || getchar(word, p) == '|' || getchar(word, p) == '&') tokens.pb("arithmeticop");
                else if (getchar(word, p) == '>' || getchar(word, p) == '<') tokens.pb("logicalop");
                else if (getchar(word, p) == '\'') {
                    p++;
                    while (getchar(word, p) != '\'' && p < word.size()) {
                        p++;
                        if (p == word.size()) {
                            if (read >> word) p = 0; else {
                                success = 0;
                                cout << "Unclosed string in line " << linenum << endl;
                            }
                        }
                    }
                    tokens.pb("constant");
                    p++;
                }
                else if (getstring(word, p, p+7) == "continue" && sign(getchar(word, p+8))) {
                    tokens.pb("variable");
                    p+=7;
                }
                else if (getstring(word, p, p+5) == "import" && sign(getchar(word, p+6))) {
                    tokens.pb("import");
                    p+=5;
                }
                else if (getstring(word, p, p+5) == "return" && sign(getchar(word, p+6))) {
                    tokens.pb("return");
                    p+=5;
                }
                else if (getstring(word, p, p+4) == "False" && sign(getchar(word, p+5))) {
                    tokens.pb("false");
                    p+=4;
                }
                else if (getstring(word, p, p+4) == "range" && sign(getchar(word, p+5))) {
                    tokens.pb("range");
                    p+=4;
                }
                else if (getstring(word, p, p+4) == "break" && sign(getchar(word, p+5))) {
                    tokens.pb("variable");
                    p+=4;
                }
                else if (getstring(word, p, p+4) == "while" && sign(getchar(word, p+5))) {
                    tokens.pb("while");
                    p+=4;
                }
                else if (getstring(word, p, p+4) == "class" && sign(getchar(word, p+5))) {
                    tokens.pb("class");
                    p+=4;
                }
                else if (getstring(word, p, p+4) == "raise" && sign(getchar(word, p+5))) {
                    tokens.pb("raise");
                    p+=4;
                }
                else if (getstring(word, p, p+3) == "elif" && sign(getchar(word, p+4))) {
                    tokens.pb("elif");
                    p+=3;
                }
                else if (getstring(word, p, p+3) == "else" && sign(getchar(word, p+4))) {
                    tokens.pb("else");
                    p+=3;
                }
                else if (getstring(word, p, p+3) == "True" && sign(getchar(word, p+4))) {
                    tokens.pb("true");
                    p+=3;
                }
                else if (getstring(word, p, p+3) == "from" && sign(getchar(word, p+4))) {
                    tokens.pb("from");
                    p+=3;
                }
                else if (getstring(word, p, p+3) == "pass" && sign(getchar(word, p+4))) {
                    tokens.pb("pass");
                    p+=3;
                }
                else if (getstring(word, p, p+3) == "with" && sign(getchar(word, p+4))) {
                    tokens.pb("with");
                    p+=3;
                }
                else if (getstring(word, p, p+3) == "None" && sign(getchar(word, p+4))) {
                    tokens.pb("constant");
                    p+=3;
                }
                else if (getstring(word, p, p+2) == "and" && sign(getchar(word, p+3))) {
                    tokens.pb("and");
                    p+=2;
                }
                else if (getstring(word, p, p+2) == "not" && sign(getchar(word, p+3))) {
                    tokens.pb("not");
                    p+=2;
                }
                else if (getstring(word, p, p+2) == "for" && sign(getchar(word, p+3))) {
                    tokens.pb("for");
                    p+=2;
                }
                else if (getstring(word, p, p+2) == "def" && sign(getchar(word, p+3))) {
                    tokens.pb("def");
                    p+=2;
                }
                else if (getstring(word, p, p+1) == "if" && sign(getchar(word, p+2))) {
                    tokens.pb("if");
                    p++;
                }
                else if (getstring(word, p, p+1) == "or" && sign(getchar(word, p+2))) {
                    tokens.pb("or");
                    p++;
                }
                else if (getstring(word, p, p+1) == "in" && sign(getchar(word, p+2))) {
                    tokens.pb("in");
                    p++;
                }
                else if (getstring(word, p, p+1) == "as" && sign(getchar(word, p+2))) {
                    tokens.pb("as");
                    p++;
                }
                else if (getstring(word, p, p+1) == "is" && sign(getchar(word, p+2))) {
                    tokens.pb("logicalop");
                    p++;
                }
                else if (alphabet(getchar(word, p))) {
                    while (getchar(word, p) != '~' && (alphabet(getchar(word, p)) || number(getchar(word, p)) || getchar(word, p) == '_')) {
                        p++;
                    }
                    p--;
                    if (tokens.size() > 2 && tokens[tokens.size()-1] == "dot" && tokens[tokens.size()-2] == "constant" && tokens[tokens.size()-3] == "constant") {
                        tokens.pop_back();
                        tokens.pop_back();
                        tokens.pop_back();
                    }
                    else if (tokens.size() > 1 && tokens[tokens.size()-1] == "dot" && tokens[tokens.size()-2] == "constant") {
                        tokens.pop_back();
                        tokens.pop_back();
                    }
                    else if (tokens.size() > 0 && tokens[tokens.size()-1] == "dot") {
                        tokens.pop_back();
                    }
                    else tokens.pb("variable");
                }
                else if (number(getchar(word, p))) {
                    while (number(getchar(word, p))) {
                        p++;
                    }
                    p--;
                    tokens.pb("constant");
                }
                p++;
            }
        }
        tokens.pb("newline");
    }
    ofstream fout("token.txt");
    if (success) {
        for (int i=0;i<tokens.size();i++) {
            cout << tokens[i] << " ";
            fout << tokens[i] << " ";
        }
    } else {
        cout << "PARSE FAILED" << endl;
    }
    return 0;
}