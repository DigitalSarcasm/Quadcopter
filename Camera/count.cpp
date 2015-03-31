#include <iostream>
#include <fstream>

using namespace std;

int main(){
	int count[256];
	ifstream file;
	file.open("l.txt");
	
	for(int i=0; i< 256; i++){
		count[i] = 0;
	}
	
	int x;
	while(file >> x){
		count[x]++;
	}
	
	for(int i=0; i< 256; i++){
		if(count[i] == 0)
			cout << i << endl;
	}
}