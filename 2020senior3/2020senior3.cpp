#include <bits/stdc++.h>
using namespace std;

bool marked[4][4];

void mark(int r, int c) {
	marked[r%4][c%4] = true;
}

bool at(int n, int r, int c) {
	if (marked[r][c]) return 0;
	return (n>>(15-4*(r%4)-(c%4)))%2;
}

// A=0; ~A=1; B=2; ~B=3; C=4; ~C=5; D=6; ~D=7; none=-1;
char singleKey[8][3] = {"A","~A","B","~B","C","~C","D","~D"};
int findSingleTerm(int n) {
	for (int r = 0; r<3; r++) {
		bool all = true;
		for (int a = 0; a<2; a++) {
			for (int c = 0; c<4; c++) {
				if (!at(n,r+a,c)) all=false;
			}
		}
		if (all) {
			mark(r,0);mark(r,1);mark(r,2);mark(r++,3);
			mark(r,0);mark(r,1);mark(r,2);mark(r--,3);
			if (r==0) return 2;
			if (r==1) return 6;
			if (r==2) return 3;
			//if (r==3) return 7;
		}
	}
	
	for (int c = 0; c<3; c++) {
		bool all = true;
		for (int a = 0; a<2; a++) {
			for (int r = 0; r<4; r++) {
				if (!at(n,r,c+a)) all=false;
			}
		}
		if (all) {
			mark(0,c);mark(1,c);mark(2,c);mark(3,c++);
			mark(0,c);mark(1,c);mark(2,c);mark(3,c--);
			if (c==0) return 0;
			if (c==1) return 4;
			if (c==2) return 1;
			//if (c==3) return 5;
		}
	}

	if (at(n,3,0)+at(n,3,1)+at(n,3,2)+at(n,3,3)+at(n,0,0)+at(n,0,1)+at(n,0,2)+at(n,0,3)==8) {
		mark(3,0);mark(3,1);mark(3,2);mark(3,3);mark(0,0);mark(0,1);mark(0,2);mark(0,3);
		return 7;
	}
	if (at(n,0,3)+at(n,1,3)+at(n,2,3)+at(n,3,3)+at(n,0,0)+at(n,1,0)+at(n,2,0)+at(n,3,0)==8) {
		mark(0,3);mark(1,3);mark(2,3);mark(3,3);mark(0,0);mark(1,0);mark(2,0);mark(3,0);
		return 5;
	}

	return -1;
}

/* AB=0; BC=1; ~AB=2; B~C=3;
 * AD=4; CD=5; ~AD=6; ~CD=7;
 * A~B=8; ~BC=9; ~A~B=10; ~B~C=11;
 * A~D=12; C~D=13; ~A~D=14; ~C~D=15;
 *
 * B~D=16; BD=17; ~BD=18; ~B~D=19;
 * A~C=20; AC=21; ~AC=22; ~A~C=23;
 *
 * none=-1;
 */
char doubleKey[24][5] = {"AB","BC","~AB","B~C","AD","CD","~AD","~CD",
	 					 "A~B","~BC","~A~B","~B~C","A~D","C~D","~A~D","~C~D",
						 "B~D","BD","~BD","~B~D","A~C","AC","~AC","~A~C"};
int findDoubleTerm(int n) {
	for (int r = 0; r<4; r++) {
		if (at(n,r,0)+at(n,r,1)+at(n,r,2)+at(n,r,3)==4) {
			mark(r,0);mark(r,1);mark(r,2);mark(r,3);
			return 16+r;
		}
	}
	for (int c = 0; c<4; c++) {
		if (at(n,0,c)+at(n,1,c)+at(n,2,c)+at(n,3,c)==4) {
			mark(0,c);mark(1,c);mark(2,c);mark(3,c);
			return 20+c;
		}
	}

	for (int r = 0; r<3; r++) {
		for (int c = 0; c<3; c++) {
			if (at(n,r,c)+at(n,r+1,c)+at(n,r,c+1)+at(n,r+1,c+1)==4) {
				mark(r,c);mark(r+1,c);mark(r,c+1);mark(r+1,c+1);
				return r*4+c;
			}
		}
	}

	int c = 3;
	for (int r = 0; r<3; r++) {
		if (at(n,r,c)+at(n,r+1,c)+at(n,r,c+1)+at(n,r+1,c+1)==4) {
			mark(r,c);mark(r+1,c);mark(r,c+1);mark(r+1,c+1);
			return r*4+c;
		}
	}
	int r = 3;
	for (int c = 0; c<3; c++) {
		if (at(n,r,c)+at(n,r+1,c)+at(n,r,c+1)+at(n,r+1,c+1)==4) {
			mark(r,c);mark(r+1,c);mark(r,c+1);mark(r+1,c+1);
			return r*4+c;
		}
	}

	if (at(n,0,0)+at(n,0,3)+at(n,3,0)+at(n,3,3)==4) {
		mark(0,0);mark(0,3);mark(3,0);mark(3,3);
		return 15;
	}

	return -1;
}

/* AB~D=0; BC~D=1; ~AB~D=2; B~C~D=3;
 * ABD=4; BCD=5; ~ABD=6; B~CD=7;
 * A~BD=8; ~BCD=9; ~A~BD=10; ~B~CD=11;
 * A~B~D=12; ~BC~D=13; ~A~B~D=14; ~B~C~D=15;
 *
 * AB~C=16; ABC=17; ~ABC=18; ~AB~C=19;
 * A~CD=20; ACD=21; ~ACD=22; ~A~CD=23;
 * A~B~C=24; A~BC=25; ~A~BC=26; ~A~B~C=27;
 * A~C~D=28; AC~D=29; ~AC~D=30; ~A~C~D=31;
 *
 * none=-1;
 */
char tripleKey[32][7] = {"AB~D","BC~D","~AB~D","B~C~D","ABD","BCD","~ABD","B~CD",
	 					 "A~BD","~BCD","~A~BD","~B~CD","A~B~D","~BC~D","~A~B~D","~B~C~D",
						 "AB~C","ABC","~ABC","~AB~C","A~CD","ACD","~ACD","~A~CD",
						 "A~B~C","A~BC","~A~BC","~A~B~C","A~C~D","AC~D","~AC~D","~A~C~D"};
int findTripleTerm(int n) {
	for (int r = 0; r<4; r++) {
		for (int c = 0; c<3; c++) {
			if (at(n,r,c)+at(n,r,c+1)==2) {
				mark(r,c);mark(r,c+1);
				return r*4+c;
			}
		}
	}
	for (int c = 0; c<4; c++) {
		for (int r = 0; r<3; r++) {
			if (at(n,r,c)+at(n,r+1,c)==2) {
				mark(r,c);mark(r+1,c);
				return 16+r*4+c;
			}
		}
	}

	if (at(n,0,0)&&at(n,0,3)) {mark(0,0);mark(0,3);return 3;}
	if (at(n,1,0)&&at(n,1,3)) {mark(1,0);mark(1,3);return 7;}
	if (at(n,2,0)&&at(n,2,3)) {mark(2,0);mark(2,3);return 11;}
	if (at(n,3,0)&&at(n,3,3)) {mark(3,0);mark(3,3);return 15;}
	if (at(n,0,0)&&at(n,3,0)) {mark(0,0);mark(3,0);return 28;}
	if (at(n,0,1)&&at(n,3,1)) {mark(0,1);mark(3,1);return 29;}
	if (at(n,0,2)&&at(n,3,2)) {mark(0,2);mark(3,2);return 30;}
	if (at(n,0,3)&&at(n,3,3)) {mark(0,3);mark(3,3);return 31;}

	return -1;
}

char quadKey[16][9] = {"AB~C~D","ABC~D","~ABC~D","~AB~C~D",
					   "AB~CD","ABCD","~ABCD","~AB~CD",
					   "A~B~CD","A~BCD","~A~BCD","~A~B~CD",
					   "A~B~C~D","A~BC~D","~A~BC~D","~A~B~C~D"};
ifstream fin("input.txt");
ofstream fout("output.txt");
int combine(int n) {
	bool plus = false;
	int single = findSingleTerm(n);
	if (single>=0) {plus = true; fout<<singleKey[single];}
	single = findSingleTerm(n);
	if (single>=0) {plus = true; fout<<'+'<<singleKey[single];}

	int d0uble = findDoubleTerm(n);
	while (d0uble>=0) {
		fout<<(plus?"+":"")<<doubleKey[d0uble];
		d0uble = findDoubleTerm(n);
		plus = true;
	}

	int triple = findTripleTerm(n);
	while (triple>=0) {
		fout<<(plus?"+":"")<<tripleKey[triple];
		triple = findTripleTerm(n);
		plus = true;
	}

	for (int r = 0; r<4; r++) {
		for (int c = 0; c<4; c++) {
			if (at(n,r,c)) fout<<(plus?"+":"")<<quadKey[4*r+c];
			plus = true;
		}
	}
	fout<<endl;
}

int main(void) {
	for (int i = 0; i<5; i++) {
		fill_n((bool*)marked,16,false);
		int n = 0;
		fin>>hex>>n;
		/*for (int r = 0; r<4; r++) {
			for (int c = 0; c<4; c++)
				cout<<at(n,r,c);
			cout<<endl;
		}*/
		combine(n);
	}

	fin.close();
	fout.close();
	return 0;
}
