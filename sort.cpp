#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<vector>
#include<sys/types.h>
#include<iostream>
#include<math.h>
#include<sys/wait.h>
#include<fstream>
using namespace std;
#define N_BARRIERS 3
sem_t var0;
sem_t var1;
sem_t var2;

sem_t sema[3];

vector<int> vec;
int t=0;
//int N=vec.size();
//pthread_t tid[N/2];
int N_THREADS;
sem_t sem[N_BARRIERS];
//pthread_mutex_t mut[N_BARRIERS];

struct arg_struct {
    int arg1;
    int arg2;
}args;

int count=0;
int sorted(vector<int> vec1,int n){
	if(n==1 || n==0){
		return 1;
	}
	if(vec1.at(n-1)<vec.at(n-2)){
		return 0;
	}
	return sorted(vec1,n-1);
}
void *mythread(void *arg){
	int n=0;
	struct arg_struct *args = (struct arg_struct *)arg;
	int x=((struct arg_struct*)arg)->arg1;
	int pr=((struct arg_struct*)arg)->arg2;
	for(int k=1;k<=log2(vec.size());k++){

		for(int p=1;p<=log2(vec.size());p++){
		
			//cout<<x<<endl;
		//barrier_wait(N_THREADS,n);

			sem_wait(&sema[0]);
			count+=1;
			if(count==N_THREADS){
				sem_wait(&sema[2]);
				sem_post(&sema[1]);
			}
			sem_post(&sema[0]);
			sem_wait(&sema[1]);
			sem_post(&sema[1]);

		  	int num=pow(2,p-1);
    	int g_size=vec.size()/num;
    	int gindex=x/(g_size/2);
    	int mindex=x%(g_size/2);
    	int g_start=gindex*g_size;
    	int gend=(gindex+1)*g_size-1;
    	int d1=g_start+mindex;
    	int d2=gend-mindex;
    	
    	if(vec.at(d1)>vec.at(d2)){
    		int temp=vec.at(d1);
    		vec.at(d1)=vec.at(d2);
    		vec.at(d2)=temp;
    		
    	}
    	//cout<<vec.at(d1);

    	sem_wait(&sema[0]);
    	count-=1;
    	if(count==0){
    		if(pr==1){
    		cout<<"Thread "<<x<<" finished stage "<<k<<" phase "<<p<<endl;
    		for(int n=0;n<vec.size();n++){
    		cout<<vec.at(n)<<" ";
    	}
    	cout<<endl;}

    		sem_wait(&sema[1]);
    		sem_post(&sema[2]);
    	}
    	else{
    		if(pr==1){
    		cout<<"Thread "<<x<<" finished stage "<<k<<" phase "<<p<<endl;
    	}}
    	sem_post(&sema[0]);
    	sem_wait(&sema[2]);
    	sem_post(&sema[2]);

    }
    int res=sorted(vec,vec.size());
    if(res==1){
    	break;
    	
    }
    
}
	//sem_post(&mutex);
}

int main(int arg, char* argv[]){
	//sem_init(&mutex,0,0);
	//int arr[8]={12,318,95,0,-100,3,27,55};
	string file=argv[1];
	//cout<<file;
	//string file="text.txt";
	ifstream f;
	//string atr=".txt";
	//string cat=file+atr;
	f.open(file);
	string ar=argv[2];
	//cout<<ar;
	int pr=0;
	if(ar=="-o"){
		pr++;
	}
	int num;
	
	//cout<<"pr"<<pr;
	if(!f){cout<<"file not opened";}
	f>>num;
	while(num>0)
	{
	//cout<<"num"<<num;
	for(int s=0;s<num;s++){
		int n;
		f>>n;
		vec.push_back(n);
		//cout<<num;
		//num--;
	}
	//cout<<"hello";
	//int n=sizeof(arr)/sizeof(*arr);
	for(int h=0;h<vec.size();h++){
		cout<<vec.at(h)<<" ";
	}
	cout<<endl;

	ifstream f1;
	f1.open("sema.init");
	int ns;
	if(!f1){cout<<"file not opened";}
	f1>>ns;
	//cout<<"ns"<<ns<<endl;
	int arr[3];
	int i=0;
	while(ns>0 && i<3){
		int x;
		f1>>arr[i];
		ns--;
		i++;
	}
	//cout<<"dd"<<arr[2]<<endl;
	sem_init(&sema[0],0,arr[0]);
	sem_init(&sema[1],0,arr[1]);
	sem_init(&sema[2],0,arr[2]);
	
	//sem_init(&sem[0],0,1);

	//struct arg_struct args;
	
	//args.arg1=9;
	int n=vec.size();
	N_THREADS=n/2;
	int t=0;
	pthread_t tid[N_THREADS];
	for(int i=0;i<n/2;i++){
		struct arg_struct *val= (struct arg_struct *)malloc(sizeof(struct arg_struct));
		//t++;
		val->arg1=i;
		val->arg2=pr;
		//cout<<"hello"<<val->arg1<<endl;
		pthread_create(&tid[i],NULL,mythread,(void *)val);
	}
	//pthread_create(&tid[2],NULL,mythread,NULL);
	for(int i=0;i<n/2;i++){
	pthread_join(tid[i],NULL);
	}
	for(int i=0;i<vec.size();i++){
		cout<<vec.at(i)<<" ";}
		cout<<endl;
		for(int g=0;g<25;g++){
			cout<<"-";
		}cout<<endl;
        
	f>>num;
	vec.clear();
}
	return 1;
	}
