#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
int M[10][10];
int times=0;
int rand_number(){
    int num=rand()%8;
    num*=num,num*=num,num/=1000,num++;
    cout<<num<<endl;
    int re=1;
    num=min(10,num);
    while(num){
        re*=2;
        num--;
    }
    return re;
}
void init(int size){
    srand(time(0)+times);
    for(int i=1;i<=size;i++){
        for(int j=1;j<=size;j++){
            M[i][j] = (rand()%4) < 3 ? 0 : rand_number() ;
        }
    }
}
void print(int size){
    for(int k=1;k<=size*11;k++) cout<<"-";
    cout<<endl;
    for(int i=1;i<=size;i++){
        cout<<"|";
        for(int j=1;j<=size;j++){
            int tmp=M[i][j];
            int l=7;
            while(tmp/=10)  l--;
            while(l--)  cout<<" ";
            cout<<M[i][j]<<"  |";
        }
        cout<<endl;
        for(int k=1;k<=size*11;k++) cout<<"-";
        cout<<endl;
    }
}
int main(){
    int Size=4;
    while(1){
        times++;
        char o;
        cin>>o;
        if(o=='e') break;
        init(Size);
        print(Size);
    }
    return 0;
}