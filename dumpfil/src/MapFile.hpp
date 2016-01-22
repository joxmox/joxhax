#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <sys/ioctl.h>
#include "strings.hpp"
#include "dfloat.hpp"
#include "Condition.hpp"

using namespace std;


struct mapVar {
  string name = "";
  char type = 'U';
  int size = 0;
  int count = 0;
  int pos = -1;
  int num = -1;
  bool selected = false;
  string toString() const;
};

class MapFile {
  vector<mapVar> vars;
  unordered_map<string, int> varMap;
  vector<int> fltArr;
  vector<int> selArr;
  int varCnt = 0;
  int varPos = 0;
  int varLen = 0;
  winsize ws;
  bool flagDfloat = true;
  string prefix;
public:
  MapFile(const string&, int = 1);
  void setDfloat() {flagDfloat = true;}
  void print(int);
  void print(const string&);
  void print(const mapVar&);
  void dump();
  void display();
  void display(char*);
  void display(char*, Condition&)
  string getValue(char*, int);
  string getStringVal(char*, int);
  string getWordVal(char*, int);
  string getDoubleVal(char*, int);
  bool isDate(char*, int);
  string getDate(char*, int);
  vector<int>& getFloats() {return fltArr;}
  int getSize() {return varPos;}
  int getCount() {return varCnt;}
  void select(int i) {if (i >= 0 && i < vars.size()) {vars[i].selected = true; selArr.push_back(i);}}
  bool selected(int i) {if (i >= 0 && i < vars.size()) return vars[i].selected; else return false;}
  vector<int> getSelected() {return selArr;}
  mapVar& getVar(int i) {if (i > 0 && i < vars.size()) return vars[i];}
  bool compare(char*, int, string);
};


void MapFile::print(int i) {
  if (i < vars.size()) {
    this->print(vars[i]);
  } else {
    cout << "?Index for print (" << i << ") is out of bounds" << endl;
  }
}

void MapFile::print(const string& s) {
  if (varMap.find(s) != varMap.end()) {
    this->print(varMap[s]);
  } else {
    cout << "?Variable name (" << s << ") for print does not exist" << endl;
  }
}

void MapFile::print(const mapVar& mv) {
  cout << mv.toString() << endl;
}

void MapFile::dump() {
  for (auto& a : vars) print(a);
  cout << "Size: " << getSize() << endl;
  cout << "Count: " << getCount() << endl;
  cout << "Length: " << varLen << endl;
}

void find_map(string& line, int& mapCnt) {
  smatch sm;
  if (regex_match(line, sm, regex {"MAP ?\\([A-Z0-9\\.]+\\) ?(.*)"})) {
    mapCnt++;
    line = sm[1];
  }
}

void parse_var(string& line, mapVar& mv) {
  smatch sm;
  if (regex_match(line, sm, regex {"(STRING |INTEGER |WORD |REAL |DOUBLE )(.*)"})) {
    if (sm[1] == "STRING ") mv.type = 'S';
    if (sm[1] == "INTEGER ") mv.type = 'L';
    if (sm[1] == "WORD ") mv.type = 'W';
    if (sm[1] == "REAL ") mv.type = 'F';
    if (sm[1] == "DOUBLE ") mv.type = 'D';
    line = sm[2];
  }
  if (regex_match(line, sm, regex {"(.*?) ?= ?(\\d+)\\%?"})) {
    line = sm[1];
    mv.size = stoi(sm[2]);
  }
  if (regex_match(line, sm, regex {"(.*?) ?\\( ?(\\d+)\\%?\\) ?"})) {
    line = sm[1];
    mv.count = stoi(sm[2]);
  }
  if (regex_match(line, sm, regex {" ?(.*)([\\%\\$]) ?"})) {
    line = sm[1];
    if (mv.type == 'U') {
      if (sm[2] == "%") mv.type = 'W';
      if (sm[2] == "$") mv.type = 'S';
    }
  }
 if (mv.type == 'U') mv.type = 'D';
  mv.name = line;
  if (mv.count == 0) mv.count = 1;
  if (mv.size == 0) {
    if (mv.type == 'S') throw logic_error("string with no size");
    if (mv.type == 'L') mv.size = 4;
    if (mv.type == 'W') mv.size = 2;
    if (mv.type == 'F') mv.size = 4;
    if (mv.type == 'D') mv.size = 8;
  }
}


MapFile::MapFile(const string& fileName, int mapNum) {
  ioctl(0, TIOCGWINSZ, &ws);
  ifstream f {fileName};
  if (!f) throw runtime_error("Cannot open map file"); 
  string line;
  int mapCnt = 0;
  unordered_set<string> prefixSet;
  while (getline(f, line)) {
    string orig_line = line;
    s_decomment(line);
    s_compress(line);
    s_trim(line);
    if (line.length() > 0) {
      mapVar mv;
      s_upper(line);
      find_map(line, mapCnt);
      if (line != "" && mapNum == mapCnt) {
        parse_var(line, mv); 
        if (mv.type == 'U') throw logic_error("Error: could not determine type of variable\n " + orig_line);
        if (mv.size == 0) throw logic_error("Error: could not determine size of variable\n " + orig_line);

        mv.pos = varPos;
        varPos += mv.size * mv.count;
        if (mv.count > 1) varPos += mv.size;
        if (mv.name != "FILL") {
          vector<string> vx {s_split(mv.name, "\\.")};
          prefixSet.insert(vx[0]);
          mv.num = varCnt++;
          vars.push_back(mv);
          if (mv.type == 'D') fltArr.push_back(mv.pos);
        }
        if (prefixSet.size() == 1) prefix = *prefixSet.begin();
        for (auto& mv : vars) {
          if (prefix != "") s_remove(mv.name, "^" + prefix + "\\.");
          varMap[mv.name] = mv.num;
          if (mv.name.length() > varLen) varLen = mv.name.length();
        }  
      }
    }
  }
}

void MapFile::display() {
	int cols = ws.ws_col / (varLen + 9);
	int varNum = 0;
	for (auto& v : vars) {
		if (varNum > 0 && (varNum % cols == 0)) cout << endl;
		cout << setw(3) << right << varNum + 1;
		cout << "-[" << v.type << "]";
		cout << setw(varLen + 2) << left << v.name;
		varNum++;
	}
	cout << right << endl;
}

string MapFile::getStringVal(char* buff, int i) {
  if (isDate(buff, i)) {
    return getDate(buff, i);
  } else {
    char tmp[vars[i].size + 1];
    memcpy(tmp, buff + vars[i].pos, vars[i].size);
    tmp[vars[i].size] = '\0';
    return string {tmp};
  }
}

bool MapFile::isDate(char* buff, int i) {
  if (vars[i].size != 6) return false;
  bool f = false;
  for (int j=0; j<6; j++) {
    char c = buff[vars[i].pos + j];
    if (c < 32 || c > 126) f = true;
  }
  return f;
}

string MapFile::getDate(char* buff, int i) {
  short y;
  short m;
  short d;
  int pos = vars[i].pos;
  memcpy((char*) &y, buff + pos, 2);
  memcpy((char*) &m, buff + pos + 2, 2);
  memcpy((char*) &d, buff + pos + 4, 2);
  ostringstream os;
  os << y << "-";
  os << setfill('0') << setw(2) << m << "-";
  os << setfill('0') << setw(2) << d;
  return os.str();
}

string MapFile::getWordVal(char* buff, int i) {
  short val;
  memcpy((char*) &val, buff + vars[i].pos, 2);
  return to_string(val);
}

string MapFile::getDoubleVal(char* buff, int i) {
  double val;
  memcpy((char*) &val, buff + vars[i].pos, 8);
  if (flagDfloat) val = cvt_d2t(val);
  return to_string(val);
}

string MapFile::getValue(char* buff, int i) {
  string str;
  switch (vars[i].type) {
    case 'S' : str = getStringVal(buff, i); break;
    case 'W' : str = getWordVal(buff, i); break;
    case 'D' : str = getDoubleVal(buff, i); break;
  }
  return str;
}

void MapFile::display(char *buff) {
  for (auto i : selArr) {
    string str = getValue(buff, i);
    cout << setw(3) << i + 1 << "-";
    cout << "[" << vars[i].type << "]";
    cout << setw(varLen) << left << vars[i].name << " : ";
    cout << right << str << endl;
  }
}

void MapFile::display(char *buff, Condition& cond) {
	  for (auto i : selArr) {
	    string str = getValue(buff, i);
	    cout << setw(3) << i + 1 << "-";
	    cout << "[" << vars[i].type << "]";
	    cout << setw(varLen) << left << vars[i].name << " : ";
	    cout << right << str << endl;
	  }
}

string mapVar::toString() const{
  return name + "[" + type + "] " + to_string(pos) + ": " + to_string(size) + "(" + to_string(count) + ")";
}

bool MapFile::compare(char *buff, int i, string aVal) {
  string bVal = getValue(buff, i);
  if (aVal == bVal) return true;
  return false;
}

