#include<iostream>
#include<vector>
#include<set>
#include<climits>
#include<sstream>
#include<fstream>
#include<algorithm>

class Matrix{
	friend std::istream& operator>>(std::istream &is,   Matrix &m);
	friend Matrix operator^(const Matrix &m1, const Matrix &m2);
	friend bool candidatePoint(const Matrix &m1, const Matrix &m2, const Matrix &mmxor,std::set<int> &points);
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

std::istream& operator>>(std::istream &is,   Matrix &m){
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

bool candidatePoint(const Matrix &m1, const Matrix &m2, const Matrix &mxor, std::set<int> &points){
	bool iszero = true;
	for(int i =0; i < m1.N; i++){
		for(int j = 0; j < m1.M; j++){
			if(m1.matrix[i][j] &  mxor.matrix[i][j]){
				iszero = false;
				points.insert(i * m1.M + j);
			}
		}
	}
	if(iszero){
		for(int i =0; i < m2.N; i++){
			for(int j = 0; j < m2.M; j++){
				if(m2.matrix[i][j] &  mxor.matrix[i][j]){
					points.insert(i * m2.M +j);
				}
			}
		}
	}
	return iszero;
}


int extractset(std::vector<Matrix>& matrixes,int P,std::vector<std::set<int> > &vs){
	for(int i = 0; i < P-1; i++){
		for(int j = i+1; j < P; j++){
			Matrix mxor = matrixes[i]^matrixes[j];
			std::set<int> points;
			candidatePoint(matrixes[i],matrixes[j],mxor,points);
			vs.push_back(points);
		}
	}
	
	
	std::vector<std::set<int> >::iterator vs_it = vs.begin();
	std::vector<std::set<int> >::iterator vs_it2;
	bool isdelete = false;
	std::cout<< "_________________"<<std::endl;
	for(auto h : vs){
		for(auto s : h){
			std::cout << s<< " ";
		}
		std::cout<< std::endl;
	}
	std::cout<< "_________________"<<std::endl;
	
	/*while(vs_it != vs.end()){
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
	*/
	while(vs_it != vs.end()){
		isdelete = false;
		for(vs_it2 = vs.begin();vs_it2 != vs.end();){
			if(vs_it == vs_it2){
				vs_it2++;
				continue;
			}
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


std::cout<< "_________________"<<std::endl;
	for(auto h : vs){
		for(auto s : h){
			std::cout << s<< " ";
		}
		std::cout<< std::endl;
	}
	std::cout<< "_________________"<<std::endl;


}
int init(std::vector<Matrix> &matrixes){
	int N, M , P;
	std::cin >> N >> M >> P;
	for(int i = 0; i < P; i++){
		Matrix m = Matrix(N,M);
		std::cin >> m;
		matrixes.push_back(m);
	}
	return P;
}
bool verify(std::vector<std::set<int> > &vs,std::vector<int> &com,int P, int setsize, bool *iscover){
	
	int covernum = setsize;
	for(int k = 0; k < 32; k++){
		iscover[k] = false;
	}
	for(int i = 0; i < com.size(); i++){
		int element = com[i];
	//	std::cout << "ele "<<element<<std::endl;
		int cursor = 0;
		auto vs_it = vs.begin();
		while(vs_it != vs.end()){
	//		for(auto UU : *vs_it){
	//			std::cout  << UU<<" ";
	//		}
	//		std::cout<<std::endl;
	//		std::cout << "cc "<<cursor<< std::endl;
			if(!iscover[cursor] && vs_it->find(element) != vs_it->end()){
				iscover[cursor] = true;
				covernum--;
	//			std::cout << "c "<<cursor<< std::endl;
			}
			vs_it++;
			cursor++;
		}
		if(covernum == 0){
			return true;
		}
	}
	return false;
}
bool findmin(std::vector<int> vec,int start, int n, std::vector<int> &com, 
		      std::vector<std::set<int> > &vs,int P,int setsize, bool *iscover){
	int nums = vec.size();
	for(int j = start; j < nums - (n-1); j++){
		com.push_back(vec[j]);
		if(n == 1){
	//		for(auto h : com){
	//			std::cout << h << " ";
	//		}
			//std::cout << std::endl;
			if(verify(vs,com,P,setsize,iscover)){
	//			std::cout << "!!!!!!!!!!!"<<std::endl;
                for(auto r : com){
		            std::cout<< r << " ";
		        }
	            std::cout<<std::endl;			
				return true;
			}
		}else{
			if(findmin(vec,j+1,n-1,com,vs,P,setsize, iscover)){
				return true;
			}
		}
		com.pop_back();
	}
	return false;
}

int minPoint(){
	int k=0;
	std::vector<Matrix> matrixes;
	int P = init(matrixes);
	if(P == 1){
		return P;
	}
	time_t start,end,time;
	start = clock();
	std::vector<std::set<int> > vs;
	std::set<int> totalpoints;
	std::vector<int> vtotalpoints;
	int nnode = extractset(matrixes,P,vs);
	if(nnode == -1){
		return 0;
	}
	for(auto iv : vs){
		for(auto i : iv){
			totalpoints.insert(i);
		}
	}
	for(auto point : totalpoints){
			vtotalpoints.push_back(point);
	}
	int i = 0;
	bool iscover[32] = {false};
	int setsize = vs.size();
	if(P == 1 ){// P == 2){
		return P;
	}
	double tmp = log(P) / log(2);
	int m = tmp;
	if(m < tmp){
		m += 1;
	}
	std::vector<int> com;
//	for(auto i : vs){
//		for(auto j : i){
//			std::cout << j <<" ";
//		}
//		std::cout<<"--- "<<std::endl;
//	}
//for(auto i : vtotalpoints){
	//std::cout << "I: "<< i<< std::endl;
//}
//std::cout << "mm "<< m << "p "<< P << std::endl;
//	exit(0);
    int q;
	for(q = m;  q < vtotalpoints.size() && q < P -1; q++){
		//std::cout << "L "<< q<<std::endl;
		if(findmin(vtotalpoints,0,q,com,vs,P,setsize,iscover)){
	//	std::cout << "L L"<< q<<std::endl;
			break;
		}
	//	std::cout << "L "<< q<<std::endl;
	}
	///	std::cout << "L "<< q<<std::endl;
	
	end = clock();
	time = end - start;
	std::cout << std::endl<<"time:"<< time * 1000.0 / CLOCKS_PER_SEC << std::endl;
	return q;
}
	
			
			

int main(){
	std::cout <<"min "<< minPoint()<<std::endl;
}
