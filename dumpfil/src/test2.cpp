
#include <iostream>
#include <stdexcept>

using namespace std;



class astNode {
public:
	enum nodeType {undef, eq, ne, lt, le, gt, ge, nope, sval, ival, dval, vnam, land, lor};
	static int nodeCnt;
private:
	int nodeNum = 0;
	nodeType type = undef;
	astNode* left = nullptr;
	astNode* right = nullptr;
	astNode* up = nullptr;;
	string svalue = "";
	int ivalue = 0;
	double dvalue = 0.0;
public:
	astNode() {nodeNum = ++nodeCnt;}
	astNode* pop() {
		astNode* tmpNode = up;
		while (tmpNode->up != nullptr && tmpNode->right != nullptr) tmpNode = tmpNode->up;
		if (tmpNode->right == nullptr) {
			up->right = this;
			return up;
		}
		astNode* astNew = new astNode;
		astNew->left = this;
		up = astNew;
		return astNew;
	}
	astNode* push() {
		if (right != nullptr) throw logic_error("Cannot push - operator expected");
		astNode* astNew = new astNode;
		astNew->up = this;
		if (left == nullptr) left = astNew; else right = astNew;
		return astNew;
	}
	astNode* doSpace(char, string&);
	void dump();
	void print();
};

bool isQuoted(string& s) {
	if (s.size() < 2) return false;
	if (s[0] != '"') return false;
	if (s[s.size() - 1] != '"') return false;
	return true;
}

bool isNumeric(string s) {
	for (auto c : s) {
		if (((c < '0') or (c > '9')) and (c != '.')) return false;
	}
	return true;
}

bool containsDot(string s) {
	for (auto c : s) {
		if (c == '.') return true;
	}
	return false;
}

bool okVariable(string s) {
	return true;
}

void doDef(char c, astNode*& astEle, string& tmp) {

}

astNode* astNode::doSpace(char c, string& tmp) {
	bool goUp = true;
	if (isQuoted(tmp)) {
		type = sval;
		svalue = tmp;

	} else if (tmp == "and") {
		cout << "found and!" << endl;
		type = land;
		goUp = false;

	} else if (tmp == "or") {
		type = lor;
		goUp = false;

	} else if (tmp == "=") {
		type = eq;
		goUp = false;

	} else if (tmp == ">") {
		type = gt;
		goUp = false;

	} else if (isNumeric(tmp)) {
		if (containsDot(tmp)) {
			type = dval;
			dvalue = stod(tmp);
		} else {
			type = ival;
			ivalue = stoi(tmp);
		}

	} else if (okVariable) {
		type = vnam;
		svalue = tmp;

	} else throw logic_error("invalid variable name");

	tmp = "";
	if (goUp) return  this->pop(); else return this->push();
}

astNode* parse(const string& s) {
	astNode* curAst = new astNode();
	string tmp;
	int state = 0;
	for (auto c : s + " ") {
		cout << c << ":> ";
		curAst->print();
		switch(c) {
		case '(': {
			curAst = curAst->push();
			break;
		}
		case ')': {
			curAst = curAst->pop();
			break;
		}
		case ' ' : {
			curAst = curAst->doSpace(c, tmp);
			break;
		}
		default: {
			tmp += c;
		}
		}
	}
	return curAst;
}

void astNode::dump() {
	cout << "at node " << nodeNum << endl;
	cout << "type :" << type << endl;
	cout << "up: " << (up != nullptr? to_string(up->nodeNum) : "<nullptr>") << endl;
	cout << "left: " << (left != nullptr? to_string(left->nodeNum) : "<nullptr>") << endl;
	cout << "right: " << (right != nullptr? to_string(right->nodeNum) : "<nullptr>") << endl << endl;
	if (left != nullptr) left->dump();
	if (right != nullptr) right->dump();
}

void astNode::print() {
	cout << "Node " << nodeNum << ", this:" << this << ", up:" << up << ", left:" << left << ", right" << right << endl;
}

int astNode::nodeCnt = 0;

int main() {
	astNode* kaka = parse("a > 3 and b = 1");
	kaka->print();
	kaka->dump();
}
