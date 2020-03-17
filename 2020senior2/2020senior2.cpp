#include <bits/stdc++.h>
using namespace std;

char str1[205], str2[205];
int len1, len2;
bool intersect[205][205];
struct substring {
	int i, j, length; // str1 position, str2 position, length
	substring(int i_, int j_, int length_) {
		i = i_; j = j_; length = length_;
	}
};
vector<substring> substrings;

void printrange(int a1, int a2, char* ptr) {
	for (;a1<a2;a1++) cout<<ptr[a1];
	cout<<endl;
}

bool inRange(int a, int b, int p) {
	return (a<=p && p<=b);
}
bool insideBox(int i1, int i2, int j1, int j2, substring a) { // a = substring
	int x1=a.i,x2=a.i+a.length,y1=a.j,y2=a.j+a.length;
	while (x1<x2) {
		x1++; y1++;
		if (inRange(i1,i2,x1)&&inRange(j1,j2,y1)) return true;
	}
	return false;
}

int comparesubstr(int i, int j) {
	return strncmp(str1+substrings[i].i*sizeof(char), str1+substrings[j].i*sizeof(char), min(substrings[i].length,substrings[j].length));
}
int clamplength(int a1, int a2, int c1, int c2) { // a2>a1, c2>c1 (ENDS NOT INCLUDED)
	int new1 = a1, new2 = a2;
	if (a1<c1) new1 = c1;
	if (a2>c2) new2 = c2;
	return new2-new1;
}

int ADF(int i1, int i2, int j1, int j2) { // str1 start, str1 end, str2 start, str2 end (ENDS NOT INCLUDED)
	//cout<<"Currently:"<<endl<<"str1: ";
	//printrange(i1,i2,str1); cout<<"str2: "; printrange(j1,j2,str2);
	if (i2==i1 || j2==j1) return 0;
	int maxlength = -1;
	int maxsubstr = -1;
	for (int i = 0; i<substrings.size(); i++) {
		substring cur = substrings[i];
		if (insideBox(i1,i2,j1,j2,cur)) {
			//cout<<"Considering: ";
			//printrange(cur.i, cur.i+cur.length, str1);
			int length = min(clamplength(cur.i,cur.i+cur.length,i1,i2),clamplength(cur.j,cur.j+cur.length,j1,j2));
			//cout<<"Length: "<<length<<endl;
			if (length>maxlength) {
				maxlength = length;
				maxsubstr = i;
			}
			else if (length == maxlength) {
				int cmp = comparesubstr(i, maxsubstr);
				if (cmp<0) {
					maxsubstr = i;
				}
			}
		}
	}
	if (maxsubstr<0) return 0;

	substring maxptr = substrings[maxsubstr];
	/*cout<<"maxptr found: "<<maxptr.i<<' '<<maxptr.j<<' '<<maxptr.length<<endl;
	cout<<"maxptr: "; printrange(maxptr.i, maxptr.i+maxptr.length, str1);
	cout<<"maxlength: "<<maxlength<<endl;*/
	int maxbegini = max(maxptr.i,i1); int maxbeginj = max(maxptr.j,j1);
	return maxlength + ADF(i1,maxbegini,j1,maxbeginj)
		+ ADF(maxbegini+maxlength,i2,maxbeginj+maxlength,j2);
}


int main(void) {
	ifstream fin("sr-sample-input.txt");
	ofstream fout("output.txt");

	char* ptrs[2] = {str1, str2};
	for (int i = 0; i<2; i++) {
		char c;
		int index = 0;
		while (true) {
			fin>>noskipws>>c;
			if (fin.eof() || c == '\n') {
				ptrs[i][index] = '\0';
				break;
			}
			if (isalpha(c)) {
				ptrs[i][index++] = toupper(c);
			}
		}
	}
	len1 = strlen(str1); len2 = strlen(str2);
	cout<<str1<<' '<<len1<<endl;
	cout<<str2<<' '<<len2<<endl;

	for (int i = 0; i<len1; i++) {
		for (int j = 0; j<len2; j++)
			intersect[i][j] = (str1[i] == str2[j]);
	}
	bool visited[len1][len2];
	fill_n((bool*)visited, len1*len2, false);
	for (int i = 0; i<len1; i++) {
		for (int j = 0; j<len2; j++) {
			if (visited[i][j]) continue;
			if (intersect[i][j]) {
				int curi = i, curj = j;
				while (intersect[curi][curj] && curi<len1 && curj<len2) {
					visited[curi][curj] = true;
					curi++; curj++;
				}
				substrings.push_back(substring(i,j,curi-i));
				cout<<i<<' '<<j<<' '<<curi-i<<endl;
			}
		}
	}

	cout<<ADF(0,len1,0,len2);

	fout.close();
	return 0;
}
