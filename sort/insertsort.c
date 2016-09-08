#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<time.h>
void Insertsort(int *nums, int n){
	if(n < 2){
		return;
	}
	int val = 0;
	int i = 0,j = 0;
	for(j = 1; j < n; j++){
		val = nums[j];
		for( i = j-1; i >= 0,val < nums[i];i--){
			nums[i+1] = nums[i];
		}
		nums[i+1] = val;
	}
}
void Insertsort(float *nums, int n){
	if(n < 2){
		return;
	}
	float val = 0;
	int i = 0,j = 0;
	for(j = 1; j < n; j++){
		val = nums[j];
		for( i = j-1; i >= 0,val < nums[i];i--){
			nums[i+1] = nums[i];
		}
		nums[i+1] = val;
	}
}
void Merge(int *nums,int p, int q, int r){
	int leftsize = q-p+1;
	int rightsize = r-q;
	int *leftnums = (int *)malloc(sizeof(int) * (leftsize+1));
	int *rightnums = (int *)malloc(sizeof(int) * (rightsize+1));
	int i, j,k;
	for(i = 0; i < leftsize ; i++){
		leftnums[i] = nums[p+i];
	}
	leftnums[i] = INT_MAX;
	for(i = 0; i < rightsize; i++){
		rightnums[i] = nums[q+1+i];
	}
	rightnums[i] = INT_MAX;
	for(int k = p,i = 0,j = 0; k <= r;k++){
		if(leftnums[i] <= rightnums[j]){
			nums[k] = leftnums[i];
			i++;
		}else{
			nums[k] = rightnums[j];
			j++;
		}
	}
	free(leftnums);
	free(rightnums);
}



void Merge(int *nums,int p, int q, int r,int *tmp){
	int i = p;
	int j = q+1;
	int k = p;
	while(i != q+1 && j != r+1){
		if(nums[i] <=  nums[j]){
			tmp[k++] = nums[i++];
		}else {
			tmp[k++] = nums[j++];
		}
	}
	while(i != q+1){
		tmp[k++] = nums[i++];
	}
	while(j != r+1){
		tmp[k++] = nums[j++];
	}
	for(i = p; i <= r; i++){
		nums[i] = tmp[i];
	
	}
}

void Mergesort(int *nums, int p ,int r){
   	if(p < r){
		int q = (r+p)/2;
		Mergesort(nums,p,q);
		Mergesort(nums,q+1,r);
		Merge(nums,p,q,r);
	}
}

void Mergesort(int *nums, int p ,int r, int *tmp){
	if(p <r){
		int q = p+(r-p)/2;
		Mergesort(nums,p,q,tmp);
		Mergesort(nums,q+1,r,tmp);
		Merge(nums,p,q,r,tmp);
	}
}
void inline swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}
void Bubble(int *nums, int n){
	for(int i = 0; i < n; i++){
		for(int j = n-1; j > i; j--){
			if(nums[j] < nums[j-1]){
				swap(nums[j],nums[j-1]);
			}
		}
	}
}

void newBubble(int *nums,int n){
	int swaped = 1;
	int newn;
	while(n){
		//swaped = 0;
		newn = 0;
		for(int i = 1; i < n; i++){
			if(nums[i-1] > nums[i]){
				swap(nums[i-1],nums[i]);
				//swaped = 1;
				newn = i;
			}
		}
		n = newn;
	}
}


void maxHeapify(int *nums, int i, int n){
	int left = 2 * i;
	int right = 2 * i + 1;
	int largest  = 0;
	if(left <= n && nums[left] > nums[i]){
		largest = left;
	}else{
		largest = i;
	}
	if(right <= n && nums[right] > nums[largest]){
		largest = right;
	}
	if(largest != i){
		swap(nums[largest],nums[i]);
		maxHeapify(nums,largest,n);
	}
}

void buildMaxHeap(int *nums, int n){
	for(int i = n / 2; i >= 1; i--){
		maxHeapify(nums,i,n);
	}
}

void heapSort(int *nums, int n){
	buildMaxHeap(nums,n);
	for(int i = n ; i >= 2; i--){
		swap(nums[1],nums[i]);
		n--;
		maxHeapify(nums,1,n);
	}
}
	
int heapMaximum(int *nums,int n){
	if(n < 1){
		return 0;
	}
	return nums[1];
}

int heapExtractMax(int *nums,int &n){
	if(n < 1){
		printf("empty heap\n");
		return 0;
	}
	int max = nums[1];
	nums[1] = nums[n];
	n--;
	maxHeapify(nums,1,n);
	return max;
}


void heapIncreaseKey(int *nums, int i, int key,int n){
	if(n < i){
		printf("empty heap\n");
		return ;
	}
	if(key < nums[i]){
		printf("new key is smaller\n");
	}
	nums[i] = key;
	while(i > 1 && nums[i] > nums[i/2]){
		swap(nums[i],nums[i/2]);
		i /= 2;
	}
}


void maxHeapInsert(int *nums, int key, int &n){
	n++;
	nums[n] = INT_MIN;
	heapIncreaseKey(nums,n,key,n);
}
void priority(int *nums, int n){
	for(int i = 1; i <n+1; i++){
		printf("%d ",nums[i]);
	}
	printf("\n");
	buildMaxHeap(nums,n);
	for(int i = 1; i <n+1; i++){
		printf("%d ",nums[i]);
	}
	printf("\n");

	int max = heapMaximum(nums,n);
	printf("max %d\n",max);
	max = heapExtractMax(nums,n);
	printf("max %d\n",max);
	for(int i = 1; i <n+1; i++){
		printf("%d ",nums[i]);
	}
	
	printf("\n");
	heapIncreaseKey(nums,8,100,n);
	for(int i = 1; i <n+1; i++){
		printf("%d ",nums[i]);
	}
	printf("\n");
	maxHeapInsert(nums,1000,n);
	for(int i = 1; i <n+1; i++){
		printf("%d ",nums[i]);
	}
	printf("\n");

	heapSort(nums,n);
	for(int i = 1; i <n+1; i++){
		printf("%d ",nums[i]);
	}

	printf("\n");
}
int partition(int *nums, int p, int r){
	int x = nums[r];
	int i = p-1;
	for(int j = p; j < r; j++){
		if(nums[j] <= x){
			i++;
			swap(nums[i],nums[j]);
		}
	}
	swap(nums[i+1],nums[r]);
	return i+1;
}
void quickSort(int *nums, int p ,int r){
	if(p < r){
		int q = partition(nums,p,r);
		quickSort(nums,p,q-1);
		quickSort(nums,q+1,r);
	}
}

void countintSort(int *A, int *B, int k, int n){
	int *C = (int*)malloc(sizeof(int)*k);
	int i = 0;
	for(i = 0; i < k; i++){
		C[i] = 0;
	}
	for(i = 0; i < n; i++){
		C[A[i]]++;
	}
	for(i = 1; i < k; i++){
		C[i] +=  C[i-1];
	}
	for(i = n-1; i >= 0; i--){
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
}

void countintSort(int *A,int k, int bit,int n){
	int *C = (int*)malloc(sizeof(int)*k);
	int *B = (int*)malloc(sizeof(int)*n);
	int i = 0;
	int index;
	for(i = 0; i < k; i++){
		C[i] = 0;
	}
	for(i = 0; i < n; i++){
		C[A[i]/bit % 10]++;
	}
	for(i = 1; i < k; i++){
		C[i] +=  C[i-1];
	}
	for(i = n-1; i >= 0; i--){
		index = A[i] / bit %10;
		B[C[index]-1] = A[i];
		C[index]--;
	}
	for(i = 0; i < n; i++){
		A[i] = B[i];
	}
	free(C);
	free(B);

}
void randixSort(int *nums,int d,int n){
	int bit = 1;
	while(d > 0){
		countintSort(nums,10,bit,n);
		bit *= 10;
		d--;
	}
}

void  bucketSort(float *nums,int n,float max){
	float **bucket = (float **)malloc(sizeof(float*)*n);
	int *bucketSize = (int*)malloc(sizeof(int)*n);
	int i;
	int index;
	for(i = 0 ; i < n; i++){
		bucket[i] = (float*)malloc(sizeof(float)* n);
		bucketSize[i] = 0;
	}
	for(i = 0; i < n; i++){
		index = nums[i]/max*n;
		bucket[index][bucketSize[index]] = nums[i];
		bucketSize[index]++;
	}
	for(i = 0; i < n; i++){
		Insertsort(bucket[i],bucketSize[i]);
	}
	printf("\n");
	int k = 0;
	for(i = 0; i < n; i++){
		for(int j = 0; j < bucketSize[i]; j++){
			nums[k++] = bucket[i][j];
		}
	}
}
int randomizedPartition(int *nums,int p,int r){
	srand(time(NULL)) ;
	int key =  rand() % (r-p+1) + p;
	swap(nums[key],nums[r]);
	return partition(nums,p,r);
}


int randomizedSelect(int *nums, int p, int r, int i){
	if(p == r){
		return nums[p];
	}
	int q = randomizedPartition(nums,p,r);
	int k = q - p + 1;
	if(k == i){
		return nums[q];
	}
	if(i < k){
		return randomizedSelect(nums,p,q-1,i);
	}else{
		return randomizedSelect(nums,q+1,r,i-k);
	}
}

int main(){
	//float nums[] = {3001,100,101,121,122,345,365,344,544,2,10,7,2000,3000,121};
	int nums[] = {3,2,9,0,7,5,4,8,6,1};
	//float nums[] = {0.78,0.17,0.39,0.26,0.72,0.94,0.21,0.12,0.23,0.68};
	//int nums[] = {1,2,2,6,7,3,4,8,5,9,0,8};
	int tmp[100];
	int n  = sizeof(nums)/sizeof(nums[0]);
	for(int i = 0; i <n; i++){
		printf("%d ",nums[i]);
	}
	printf("\n");
	for(int j = 1; j <= n; j++){
		int key = randomizedSelect(nums,0,n-1,j);
		printf("j %d key : %d\n",j,key);
	}
	quickSort(nums,0,n-1);
	//countintSort(nums,tmp,10,n);
	
	//randixSort(nums,4,n);
	//bucketSort(nums,n,3002);
	for(int i = 0; i <n; i++){
		printf("%d ",nums[i]);
	}
	printf("\n");
	//priority(nums,10);
	//Insertsort(nums,5);
//	Mergesort(nums,0,4);
    //newBubble(nums,5);
	//heapSort(nums,10);
}

