#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <exception>
#include "MapFile.hpp"
#include "dfloat.hpp"

using namespace std;

const int MAX_VARS = 1024;
const int BUF_SIZE = 4096;
int gArgc;
char** gArgv;
int gArgx;

void saveArgs(int argc, char** argv) {
	gArgc = argc;
	gArgv = argv;
	gArgx = 1;
}

void dumpArgs() {
	for (int i = 0; i < gArgc; i++) {
		cout << "Arg " << i << " : " << gArgv[i] << endl;
	}
}

bool checkFile(const string& fileName) {
    ifstream f1 {fileName};
    if (f1) return true;
    return false;
}

string askFor(const string& prompt) {
	cout << prompt << ": ";
	string line;
	getline(cin, line);
	return line;
}

string getParamS(string p = "", bool v = true) {
	if (gArgx < gArgc) {
		if (v) cout << p << ": " << gArgv[gArgx] << endl;
	    return string(gArgv[gArgx++]);
	} else {
		if (p == "") p = "Param " + to_string(gArgx);
		gArgx++;
		return askFor(p);
	}
}

int getParamI(string p = "", bool v = true) {
	return stoi(getParamS(p, v));
}

void askNext(string s = "for next record") {
	getParamS("Press RETURN " + s, false);
}

int main(int argc, char* argv[]) {
	saveArgs(argc, argv);
//	dumpArgs();
	string datFile = getParamS("Data File");
	string mapFile = getParamS("Map File");
	string fltTmp = getParamS("Floating type [I/D/U]");
	char fltType = 'U';
	if (fltTmp.length() > 0) fltTmp = toupper(fltTmp[0]);
	MapFile map {mapFile};
	ifstream df {datFile, ifstream::binary};
	if (!df) throw logic_error("?file " + datFile + " not found");
	double sMean = 0;
	int recCnt = 0;
	char buff[map.getSize()];
	int curPos = 0;
	int bytes = -1;
	while (df && !df.eof() && (df.read(buff, map.getSize()))) {
		recCnt++;
		if  (((fabs(sMean) < 6.0) || (recCnt < 50)) && (fltType == 'U')) {
			double score = ana_dflt(buff, map.getFloats());
			sMean = (sMean * (recCnt - 1) + 1.0 * score) / recCnt;
		}
	}
	df.close();
	if (fltType == 'U') {
		if (sMean > 6.0) {
			fltType = 'D';
			cout << "Floating point type detected: D-Float" << endl;
		} else if (sMean < -6.0) {
			fltType = 'I';
			cout << "Floating point type detected: IEEE" << endl;
		} else {
			fltType = 'I';
			cout << "Could not detect floating point type - defaulting to IEEE" << endl;
		}
	}
	cout << "Map file record size: " << map.getSize() << endl;
	cout << "Number of variables in record: " << map.getCount() << endl;
	cout << "Number of records in data file: " << recCnt << endl;

	askNext("to display map variables");
	map.display();

	int searchInt = 0;
	string searchVal;
	string varStr = getParamS("Variables to display (RETURN for All)");
	string searchStr = askFor("Search criteria (RETURN for None)");

	s_collapse(varStr);
	for (auto str : s_split(varStr, ",")) {
		vector<string> v = s_split(str, "-");
		if (v.size() == 1) v.push_back(v[0]);
		for (int i=stoi(v[0]); i<=stoi(v[1]); i++) map.select(i - 1);
	}

	df.open(datFile, ifstream::binary);
	while (df && !df.eof() && df.read(buff, map.getSize())) {
		//    if (searchInt == 0 || map.compare(buff, searchStr)) {
		map.display(buff);
		askNext("for next record");
		//    }
	}
}
