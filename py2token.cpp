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
    ofstream fout("token.txt");
    fout << " " << endl;
    bool success = 1, commentmode = 0;
    int linenum = 0;
    ifstream cin("piton.py");
    string line;
    while (getline(cin, line)) {
        bool out = 0;
        linenum++;
        line += " \x90";
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
                    while (p < word.size() && cnt > 0 && success) {
                        p++;
                        if (p == word.size()) {
                            read >> word;
                            if (word == "\x90") {
                                success = 0;
                                break;
                            }
                            p = 0;
                        }
                        if (getchar(word, p) == '[') cnt++;
                        if (getchar(word, p) == ']') cnt--;
                    }
                    if (p < word.size() && cnt == 0) tokens.pb("constant");
                    else {
                        success = 0;
                        cout << "A [ is unclosed in line " << linenum << endl;
                        exit(0);
                    }
                } 
                else if (getchar(word, p) == ']') {
                    success = 0;
                    cout << "Extra ] in line " << linenum << endl;
                    exit(0);
                }
                else if (getchar(word, p) == '{') {
                    int cnt = 1;
                    while (p < word.size() && cnt > 0 && success) {
                        p++;
                        if (p == word.size()) {
                            read >> word;
                            if (word == "\x90") {
                                success = 0;
                                break;
                            }
                            p = 0;
                        }
                        if (getchar(word, p) == '{') cnt++;
                        if (getchar(word, p) == '}') cnt--;
                    }
                    if (p < word.size() && cnt == 0) tokens.pb("constant");
                    else {
                        success = 0;
                        cout << "A { is unclosed in line " << linenum << endl;
                        exit(0);
                    }
                } 
                else if (getchar(word, p) == '}') {
                    success = 0;
                    cout << "Extra } in line " << linenum << endl;
                    exit(0);
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
                    while (p < word.size() && success) {
                        p++;
                        if (p == word.size()) {
                            read >> word;
                            if (word == "\x90") {
                                success = 0;
                                break;
                            }
                            p = 0;
                        }
                        if (getchar(word, p) == '\'') break;
                    }
                    if (success) {
                        tokens.pb("constant");
                    } else {
                        cout << "Unclosed string in line " << linenum << endl;
                        exit(0);
                    }
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

    int curline = 1, curpara = 0;
    string firsttoken = tokens[0];
    for (int i=0;i<tokens.size();i++) {
        if (tokens[i] == "newline") {
            if (curpara > 0) {
                cout << "Unclosed ( in line " << curline << endl;
                exit(0);
            } else if (curpara < 0) {
                cout << "Extra ) in line " << curline << endl;
                exit(0);
            }
            if (i != 0 && tokens[i-1] != "colon" && (firsttoken == "def" || firsttoken == "if" || firsttoken == "elif" || firsttoken == "else" || firsttoken == "class" || firsttoken == "for" || firsttoken == "while" || firsttoken == "with")) {
                cout << "Missing colon in line " << curline << endl;
                exit(0);
            }
            curline++;
            if (i != tokens.size()-1) firsttoken = tokens[i+1];
        }
        else if (tokens[i] == "openparentheses") curpara++;
        else if (tokens[i] == "closeparentheses") curpara--;
    }

    for (int i=0;i<tokens.size();i++) {
        if (tokens[i] == "newline") tokens[i] = "n";
        else if (tokens[i] == "variable") tokens[i] = "v";
        else if (tokens[i] == "equal") tokens[i] = "e";
        else if (tokens[i] == "if") tokens[i] = "i";
        else if (tokens[i] == "return") tokens[i] = "r";
        else if (tokens[i] == "openparentheses") tokens[i] = "o";
        else if (tokens[i] == "closeparentheses") tokens[i] = "c";
        else if (tokens[i] == "colon") tokens[i] = "co";
        else if (tokens[i] == "elif") tokens[i] = "e";
        else if (tokens[i] == "else") tokens[i] = "el";
        else if (tokens[i] == "true") tokens[i] = "t";
        else if (tokens[i] == "false") tokens[i] = "f";
        else if (tokens[i] == "constant") tokens[i] = "con";
        else if (tokens[i] == "arithmeticop") tokens[i] = "a";
        else if (tokens[i] == "logicalop") tokens[i] = "l";
        else if (tokens[i] == "and") tokens[i] = "an";
        else if (tokens[i] == "or") tokens[i] = "or";
        else if (tokens[i] == "not") tokens[i] = "no";
        else if (tokens[i] == "for") tokens[i] = "fo";
        else if (tokens[i] == "in") tokens[i] = "in";
        else if (tokens[i] == "range") tokens[i] = "ra";
        else if (tokens[i] == "comma") tokens[i] = "com";
        else if (tokens[i] == "while") tokens[i] = "w";
        else if (tokens[i] == "import") tokens[i] = "im";
        else if (tokens[i] == "logicalop") tokens[i] = "l";
        else if (tokens[i] == "from") tokens[i] = "fr";
        else if (tokens[i] == "as") tokens[i] = "as";
        else if (tokens[i] == "def") tokens[i] = "d";
        else if (tokens[i] == "class") tokens[i] = "cl";
        else if (tokens[i] == "pass") tokens[i] = "p";
        else if (tokens[i] == "raise") tokens[i] = "rai";
        else if (tokens[i] == "with") tokens[i] = "wi";
    }

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