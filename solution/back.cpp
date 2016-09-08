#include<iostream>
#include<vector>
#include<set>
#include<climits>
#include<sstream>
#include<fstream>
#include<algorithm>
using namespace std;
inline int max(int &a, int &b){
	return a > b ? a : b;
}
inline int min(int &a, int &b){
	return a <= b ? a : b;
}

class Matrix{
	friend ostream &operator<<(ostream &os, const Matrix &matrix);
	friend istream& operator>>(istream &is,   Matrix &m);
	friend Matrix operator^(const Matrix &m1, const Matrix &m2);
	friend bool candidatePoint(const Matrix &m1, const Matrix &m2, const Matrix &mmxor,std::set<int> &points, std::set<int> &c);
	public:
		Matrix(int r, int c):N(r),M(c){
			matrix = new char*[N];
			for(int i = 0; i < N; i++){
				matrix[i] = new char[M];
			}
		}


	private:
		int N;
		int M;
		char **matrix;
	
};
ostream& operator<<(ostream &os,  const Matrix &m){
	for(int i = 0; i < m.N; i++){
		for(int j = 0; j < m.M; j++){
			os << m.matrix[i][j] << " " ;
		}
		os  << std::endl;
	}
	return os;
}

istream& operator>>(istream &is,   Matrix &m){
	for(int i = 0; i < m.N; i++){
		for(int j = 0; j < m.M; j++){
			is >> m.matrix[i][j] ;
		}
	}
	return is;
}

Matrix operator^(const Matrix &m1, const Matrix &m2){
	Matrix tmp = Matrix(m1.N,m2.M);
	for(int i =0; i < tmp.N; i++){
		for(int j = 0; j < tmp.M; j++){
			tmp.matrix[i][j] = m1.matrix[i][j] ^ m2.matrix[i][j];
		}
	}
	return tmp;
}

bool candidatePoint(const Matrix &m1, const Matrix &m2, const Matrix &mxor, std::set<int> &points,std::set<int> &c){
	bool iszero = true;
	for(int i =0; i < m1.N; i++){
		for(int j = 0; j < m1.M; j++){
			if(m1.matrix[i][j] &  mxor.matrix[i][j]){
				iszero = false;
				points.insert(i * m1.M + j);
				c.insert(i *m1.M + j);
			}
		}
	}
	if(iszero){
		for(int i =0; i < m2.N; i++){
			for(int j = 0; j < m2.M; j++){
				if(m2.matrix[i][j] &  mxor.matrix[i][j]){
					points.insert(i * m2.M +j);
					c.insert(i * m2.M + j);
				}
			}
		}
	}
	return iszero;
}


int extractset(std::vector<Matrix>& matrixes,int P,std::vector<std::set<int> > &vs,std::set<int> &totalpoints){
	for(int i = 0; i < P-1; i++){
		for(int j = i+1; j < P; j++){
			Matrix mxor = matrixes[i]^matrixes[j];
			std::set<int> points;
	//		cout << "-------"<< endl;
	//	cout << mxor;
//		cout << endl;
	//		cout << "---------"<<endl;
			candidatePoint(matrixes[i],matrixes[j],mxor,points,totalpoints);
			vs.push_back(points);
		}
	}
	
	if(totalpoints.size() == 0){
		return -1;
	}
/*
	std::vector<std::set<int> >::iterator vs_ity = vs.begin();
	while(vs_ity != vs.end()){
		std::set<int>::iterator vv = vs_ity->begin();
		while(vv != vs_ity->end()){
			cout << *vv<< " ";
			vv++;
		}
		cout << "print : "<< endl;
		vs_ity++;
	}
	
*/
	
	std::vector<std::set<int> >::iterator vs_it = vs.begin();
	std::vector<std::set<int> >::iterator vs_it2;
	bool isdelete = false;
	while(vs_it != vs.end()){
		isdelete = false;
		for(vs_it2 = vs_it+1;vs_it2 != vs.end();){
			if (std::includes(vs_it->begin(),vs_it->end(),vs_it2->begin(),vs_it2->end())){
				vs_it = vs.erase(vs_it);
				isdelete = true;
				break;
			}
			vs_it2++;
		}
		if(!isdelete){
			vs_it++;
		}
	}
/*	
	 vs_ity = vs.begin();
	while(vs_ity != vs.end()){
		std::set<int>::iterator vv = vs_ity->begin();
		while(vv != vs_ity->end()){
			cout << *vv<< " ";
			vv++;
		}
		cout << "print : "<< endl;
		vs_ity++;
	}
	*/
	
}
int init(std::vector<Matrix> &matrixes){
	int N, M , P;
	std::cin >> N >> M >> P;
	for(int i = 0; i < P; i++){
		Matrix m = Matrix(N,M);
		std::cin >> m;
		matrixes.push_back(m);
	}
//	std::cout << std::endl;
	return P;
}
int minPoint(){
	int k=0;
	std::vector<Matrix> matrixes;
	int P = init(matrixes);
	std::vector<std::set<int> > vs;
	std::set<int> totalpoints;
	int nnode = extractset(matrixes,P,vs,totalpoints);
	if(nnode == -1){
		return 0;
	}
/*
		std::vector<std::set<int> >::iterator vs_ity = vs.begin();
	while(vs_ity != vs.end()){
		std::set<int>::iterator vv = vs_ity->begin();
		while(vv != vs_ity->end()){
			cout << *vv<< " ";
			vv++;
		}
		cout << "print : "<< endl;
		vs_ity++;
	}
*/	
	std::vector<std::set<int> > totalsets;
	std::vector<std::set<int> >::iterator vs_it = vs.begin();
	std::set<int>::iterator tit= totalpoints.begin();
	std::set<int>::iterator ttt;
	bool iscover[32] = {false};
	int setsize = vs.size();
	//cout << "size" << setsize<<endl;
	int cursor = 0;
	int covernum = 0;
	register int element;
	
	vector<int> vtotalpoints(totalpoints.begin(),totalpoints.end());
/*	for(int i = 0; i < vtotalpoints.size();i++){
		cout << " " << vtotalpoints[i]<<" ";
	}
*/	
	bool found = false;
	int index = totalpoints.size();
	for( int i = totalpoints.size()-1; i >= 0 && !found; i--){
		vector<bool> vec(totalpoints.size(),false);
		fill(vec.begin()+i, vec.end(), true);
		//cout << endl;
		do{
			covernum = setsize;
			for(k = 0; k < 32; k++){
				iscover[k] = false;
			}
			for(int j = 0; j < vec.size(); j++){
				vs_it = vs.begin();
				cursor = 0;
				if(vec[j]){
					element = vtotalpoints[j];
					while(vs_it != vs.end()){
						if(!iscover[cursor] && vs_it->find(element) != vs_it->end()){
							iscover[cursor] = true;
							covernum--;
							//cout <<"covernum"<< covernum << endl;
						}
						vs_it++;
						cursor++;
					}
					if(covernum == 0){
					//	cout << "hit?"<<endl;
						break;
					}
				}
			}
			if(covernum == 0){
				found = true;

				for(k  = 0; k < vec.size(); k++){
				//	if(vec[k]){
				///		cout<< vtotalpoints[k]<< " ";
				//	}
				}

				//cout<< endl;
				//cout << "t"<< totalpoints.size()<<"i"<<i<<endl;
				index = totalpoints.size() - i ;
				break;
			}
		}while(!found && next_permutation(vec.begin(),vec.end()));
	}
	return index ;
}








int main(){
	cout <<"min "<< minPoint()<<endl;
}
