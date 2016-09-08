#include<iostream>
#include<unordered_set>
#include<set>
#include<vector>
#include<string>
void Perm(std::set <std::string> &res, std::string nums, int k){
    int i;
    if(k == nums.size()-1){
        res.insert(nums);
    }else{
        for(i = k; i <= nums.size()-1; i++){
            std::swap(nums[k],nums[i]);
            Perm(res,nums,k+1);
            std::swap(nums[k],nums[i]);
        }
    }
}
int main(){
    std::string str;
    std::string word = "abcd";
    std::cin >> str;
    std::set<std::string>result;
    std::unordered_set<std::string> res;
    for(int i = str.size()-1; i >= 0; i--){
        std::string sol = str;
        for(int j = 0; j < word.size(); j++){
            sol[i] = word[j];
            res.insert(sol);
        }
    }
    for(std::string stringval : res){
        Perm(result,stringval,0);
    }
       for(std::string set_it : result){
		   std::cout << set_it<<std::endl;
     }
} 
