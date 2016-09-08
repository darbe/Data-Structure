#include<iostream>
#include<list>
#include<vector>
using namespace std;
inline void getiterator(list<char>::iterator &it, int offset){
	for(int i = 0; i < offset; i++){
		it++;
	}
}
inline char getval( list<char> &input, int offset){
	list<char>::iterator it = input.begin();
	getiterator(it,offset);
	return *it;
}
inline bool equallist(const list<char> &a, const list<char> &b){
	list<char>::const_iterator ait, bit;
	ait = a.begin();
	bit = b.begin();
	while(ait != a.end() && bit != b.end() && *ait == *bit){
		ait++;
		bit++;
	}
	return (ait == a.end() && bit == b.end());
}
int main(){
	string str;
	unsigned long long n;
	cin >> str;
	cin >> n;
	list<char> input(str.begin(),str.end());
	int index;
	char c;
	char val;
	vector<list<char> > cycle;
	list<char>::iterator it;
	bool open = false;
	while(n){
		c = input.front();
		index = c - '0';
		it = input.begin();
		advance(it,index-1);
		val = *it;
		if(open || c == val){
			cycle.push_back(input);
			open = true;
		}
		input.pop_front();
		it = input.begin();
		//getiterator(it, index-1);
		advance(it,index-1);
		input.insert(it,c);
		if(cycle.size()>0)
		if(cycle.size() > 0 && equallist(cycle[0],input)){
			break;
		}
		n--;
	}
	if(n > 0){
		index = (n-1) % cycle.size();
		input = cycle[index];
	}
	for(list<char>::iterator it = input.begin(); it != input.end(); it++){
			cout << *it;
	}
	cout << endl;
	return 0;
}

