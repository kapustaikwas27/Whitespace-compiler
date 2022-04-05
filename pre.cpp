#include <iostream>
#include <string>
#include <map>

#define ignoreBlackspaces \
    while (cin.get(whitespace) \
    && whitespace != ' ' \
    && whitespace != '\t' \
    && whitespace != '\n');

#define check(s) \
    map<string, int>::iterator it = labels.find(s); \
    if (it == labels.end()) { \
        iarg = labels.size(); \
        labels[s] = iarg; \
    } else { \
        iarg = it->second; \
    }

#define convert \
    int i = 30; \
    while (i >= 0 && !(iarg & (1 << i))) { \
        i--; \
    } \
    for (; i>=0; i--) { \
        if (iarg & (1 << i)) { \
            cout << '\t'; \
        } else { \
            cout << ' '; \
        } \
    } \
    cout << '\n';

using namespace std;

map<string, int> labels;

int getArg(bool label) {
    char whitespace;
    int number = 0;
    bool isPositive;
    
    if (label) {
        isPositive = 1;
    } else {
        ignoreBlackspaces
        
        if (whitespace == ' ') {
            isPositive = 1;
        } else if (whitespace == '\t') {
            isPositive = 0;
        } else if (whitespace == '\n') {
            return 0;
        }
    }
    
    do {
        ignoreBlackspaces
        
        if (whitespace == ' ') {
            number <<= 1;
        } else if (whitespace == '\t') {
            number = (number << 1) | 1;
        } else if (whitespace == '\n') {
            if (isPositive) {
                return number;
            } else {
                return -number;
            }
        }
    } while(1);
}

void printArg(bool label) {
    int iarg;
    string sarg;
    
    if (label) {
        cin >> sarg;
        check(sarg)
    } else {
        cin >> iarg;
        
        if (iarg < 0) {
            cout << '\t';
            iarg = -iarg;
        } else {
            cout << ' ';
        }
    }
    
    convert
}

void translate1() {
    char whitespace;
    string command = "";
    
    while (cin.get(whitespace)) {
        if (whitespace == ' '
            || whitespace == '\t'
            || whitespace == '\n') {
            command += whitespace;
        }
            
        if (command == "  ") { /* push */
            cout << "\t  push(" << getArg(0) << ");\n";
        } else if (command == " \n ") { /* dup */
            cout << "\t  dup();\n";
        } else if (command == " \t ") { /* copy */
            cout << "\t  copy(" << getArg(0) << ");\n";
        } else if (command == " \n\t") { /* swap */
            cout << "\t  swap();\n";
        } else if (command == " \n\n") { /* drop */
            cout << "\t  drop();\n";
        } else if (command == " \t\n") { /* slide */
            cout << "\t  slide(" << getArg(0) << ");\n";
        } else if (command == "\t   ") { /* add */
            cout << "\t  add\n";
        } else if (command == "\t  \t") { /* sub */
            cout << "\t  sub\n";
        } else if (command == "\t  \n") { /* mul */
            cout << "\t  mul\n";
        } else if (command == "\t \t ") { /* div */
            cout << "\t  div\n";
        } else if (command == "\t \t\t") { /* mod */
            cout << "\t  mod\n";
        } else if (command == "\t\t ") { /* store */
            cout << "\t  store();\n";
        } else if (command == "\t\t\t") { /* retrieve */
            cout << "\t  retrieve();\n";
        } else if (command == "\n  ") { /* label */
            cout << "\tlabel_" << getArg(1) << ":\n";
        } else if (command == "\n \t") { /* call */
            cout << "\t  call(label_" << getArg(1) << ")\n";
        } else if (command == "\n \n") { /* jmp */
            cout << "\t  jmp(label_" << getArg(1) << ")\n";
        } else if (command == "\n\t ") { /* jz */
            cout << "\t  jz(label_" << getArg(1) << ")\n";
        } else if (command == "\n\t\t") { /* jn */
            cout << "\t  jn(label_" << getArg(1) << ")\n";
        } else if (command == "\n\t\n") { /* ret */
            cout << "\t  ret\n";
        } else if (command == "\n\n\n") { /* end */
            cout << "\t  end\n";
        } else if (command == "\t\n  ") { /* printc */
            cout << "\t  printc();\n";
        } else if (command == "\t\n \t") { /* printi */
            cout << "\t  printi();\n";
        } else if (command == "\t\n\t ") { /* readc */
            cout << "\t  readc();\n";
        } else if (command == "\t\n\t\t") { /* readi */
            cout << "\t  readi();\n";
        } else {
            goto skip;
        }
            
        command = "";
        skip:;
    }
}

void translate2() {
	string command;
	int iarg;
	string sarg;
	
	while (cin >> command) {
		if (command == "push"
		|| command == "copy"
		|| command == "slide") {
			cin >> iarg;
			cout << "\t  " << command << '(' << iarg << ");\n";
		} else if (command == "dup"
		|| command == "swap"
		|| command == "drop"
		|| command == "store"
		|| command == "retrieve"
		|| command == "readi"
		|| command == "readc"
		|| command == "printi"
		|| command == "printc") {
			cout << "\t  " << command << "();\n";
		} else if (command == "add"
		|| command == "sub"
		|| command == "mul"
		|| command == "div"
		|| command == "mod"
		|| command == "ret"
		|| command == "end") {
			cout << "\t  " << command << '\n';
		} else if (command == "call"
		|| command == "jmp"
		|| command == "jz"
		|| command == "jn") {
			cin >> sarg;
			cout << "\t  " << command << '(' << sarg.substr(1) << ")\n";
		} else {
			cout << "\n\t" << command.substr(1) << '\n';
		}
	}
	
	cout << '\n';
}

void translate3() {
    string command;
    int iarg;
    string sarg;
    
    while (cin >> command) {
        if (command == "push") {
            cout << "  ";
            printArg(0);
        } else if (command == "copy") {
            cout << " \t ";
            printArg(0);
        } else if (command == "slide") {
            cout << " \t\n";
            printArg(0);
        } else if (command == "dup") {
            cout << " \n ";
        } else if (command == "swap") {
            cout << " \n\t";
        } else if (command == "drop") {
            cout << " \n\n";
        } else if (command == "store") {
            cout << "\t\t ";
        } else if (command == "retrieve") {
            cout << "\t\t\t";
        } else if (command == "readi") {
            cout << "\t\n\t\t";
        } else if (command == "readc") {
            cout << "\t\n\t ";
        } else if (command == "printi") {
            cout << "\t\n \t";
        } else if (command == "printc") {
            cout << "\t\n  ";
        } else if (command == "add") {
            cout << "\t   ";
        } else if (command == "sub") {
            cout << "\t  \t";
        } else if (command == "mul") {
            cout << "\t  \n";
        } else if (command == "div") {
            cout << "\t \t ";
        } else if (command == "mod") {
            cout << "\t \t\t";
        } else if (command == "ret") {
            cout << "\n\t\n";
        } else if (command == "end") {
            cout << "\n\n\n";
        } else if (command == "call") {
            cout << "\n \t";
            printArg(1);
        } else if (command == "jmp") {
            cout << "\n \n";
            printArg(1);
        } else if (command == "jz") {
            cout << "\n\t ";
            printArg(1);
        } else if (command == "jn") {
            cout << "\n\t\t";
            printArg(1);
        } else {
            cout << "\n  ";
            command = command.substr(0, command.size()-1);
            check(command)
            convert
        }
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        translate1();
    } else if (argc == 2
    && argv[1][0] == '-'
    && argv[1][1] == 'a'
    && argv[1][2] == '\0') {
        translate2();
    } else if (argc == 2
    && argv[1][0] == '-'
    && argv[1][1] == 'r'
    && argv[1][2] == '\0') {
        translate3();
    } else {
        cout << "usage: ./pre [-ar]\n\nWhitespace to C translator\n-a translates from Whitespace Assembler to C\n-r translates from Whitespace Assembler to Whitespace";
    }
	
	return 0;
}
