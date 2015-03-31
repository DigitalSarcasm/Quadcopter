#include <iostream>
#include <fstream>
#include <vector>
#include "base64.h"

using namespace std;

int main(int argc, char** argv){

	ifstream file;
	vector<unsigned char> binBuf;
	file.open("Donate.jpg", ios::binary|ios::in);
	
	char c;
	while(file.get(c)){
		binBuf.push_back((unsigned char)c);
	}
		
	string s = base64_encode(&binBuf[0], binBuf.size());
	
	cout << s;
}