#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <cstring>

#define uint16 uint16_t
#define uint64 uint64_t

using namespace std;

bool isblanks(double t) {
	char* ptr = (char*) &t;
	if (memcmp(ptr, "        ", 8) == 0) {
		return true;
	} else {
		return false;
	}
}

double cvt_d2t(const double& a) {
	uint16 *flp;
	uint64 sign, exp, mant, resint, *resintp=&resint;
	double *resflp=(double*)&resint;
	char *instr=(char*)&a, *outstr=(char*)&resint;

	if (a == 0) { //if input is 0 then just return 0
	    return 0;
	}
	if (memcmp(instr, "        ", 8) == 0) { //if input is just spaces: return similar value for ieee
		memcpy(outstr, "        ", 8);
		return *resflp;
	}
	flp = (uint16*) &a;
	sign = (uint64)((*flp) & 0x8000) << 48;
	exp = (((uint64)((*flp) & 0x7f80) >> 7) + 894) << 52;
	mant = (uint64)((*flp++) & 0x007f) << 45;
	mant |= ((uint64)(*flp++)) << 29;
	mant |= ((uint64)(*flp++)) << 13;
	mant |= ((uint64)(*flp++)) >> 3; // we lose the last three bits of precision
	resint = sign | exp | mant;
	return *resflp;
}

void cvt_d2t(char* str, int pos) {
	 double *ptr = (double*)&str[pos];
	  *ptr = cvt_d2t(*ptr);
}

void cvt_d2t_multi(char* buf, std::vector<int>& pvec) {
	for (auto i : pvec) {
		cvt_d2t(buf, i);
	}
}

int ana_dflt(const double& t) {
	int ret;
	double d, texp, dexp;

	d = cvt_d2t(t);
	texp = fabs(log10(fabs(t)));
	dexp = fabs(log10(fabs(d)));
	ret = 0;
	if (dexp < 12) ret = 2;
	if (dexp < 10) ret = 5;
	if (dexp < 7) ret = 7;
	if (dexp < 5) ret = 10;
	if (texp < 12) ret = -2;
	if (texp < 10) ret = -5;
	if (texp < 7) ret = -7;
	if (texp < 5) ret = -10;
	if (d == 0) ret = 666;
	if (isblanks(d)) ret = 666;
	return ret;
}

int ana_dflt(const char* buf, int pos) {
	double *ptr = (double*)&buf[pos];
	return ana_dflt(*ptr);
}

double ana_dflt(const char* buf, std::vector<int>& pvec) {
	int sum = 0;
	int cnt = 0;
	int ret;
	for (auto pos : pvec) {
		ret =  ana_dflt(buf, pos);
		if (ret != 666) {
			sum += ret;
			cnt++;
		}
	}
	if (cnt == 0) cnt = 1;
	return 1.0 * sum / cnt;
}





