#include<iostream>
#include<time.h>
#include<stdlib.h>
//#include<conio.h>
using namespace std;
int M[10][10];
int times=0;
bool In(int n,int size){
    return (n>=1 and n<=size);
}
int next_nonzero_add(int size,int i,int j,int di,int dj){
    int ti=i,tj=j;
    while( M[ti][tj]==0 and In(ti,size) and In(tj,size) ) ti+=di,tj+=dj;
    if(ti!=i)   return ti;
    if(tj!=j)   return tj;
    return 0;
}
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
    for(int k=1;k<=(size*11)+1;k++) cout<<"-";
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
        for(int k=1;k<=(size*11)+1;k++) cout<<"-";
        cout<<endl;
    }
}
void move_right(int size){
    bool flag=0;
    for(int i=1;i<=size;i++){
        for(int j=size;j>=1;j--){
            int tmp=next_nonzero_add(size,i,j,0,-1);
            if(tmp!=0){
                swap(M[i][j],M[i][tmp]);
                flag=1;
            }
            if(M[i][j+1]==M[i][j] and j!=size and M[i][j]!=0){
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag=1;
                M[i][j+1]*=2;
                M[i][j]=0;
                swap(M[i][j],M[i][next_nonzero_add(size,i,j,0,-1)]);
            }
        }
    }
    if(flag){
        srand(time(0)+times);
        int x,y;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
}
void move_left(int size){
    bool flag=0;
    for(int i=1;i<=size;i++){
        for(int j=1;j<=size;j++){
            int tmp=next_nonzero_add(size,i,j,0,1);
            if(tmp!=0 and tmp!=size+1){
                swap(M[i][j],M[i][tmp]);
                flag=1;
            }
            if(M[i][j-1]==M[i][j] and j-1!=0 and M[i][j]!=0){
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag=1;
                M[i][j-1]*=2;
                M[i][j]=0;
                swap(M[i][j],M[i][next_nonzero_add(size,i,j,0,1)]);
            }
        }
    }
    if(flag){
        srand(time(0)+times);
        int x,y;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
}
void move_up(int size){
    bool flag=0;
    for(int i=1;i<=size;i++){
        for(int j=1;j<=size;j++){
            int tmp=next_nonzero_add(size,i,j,1,0);
            if(tmp!=0 and tmp!=size+1){
                swap(M[i][j],M[tmp][j]);
                flag=1;
            }
            if(M[i-1][j]==M[i][j] and i-1!=0 and M[i][j]!=0){
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag=1;
                M[i-1][j]*=2;
                M[i][j]=0;
                swap(M[i][j],M[next_nonzero_add(size,i,j,1,0)][j]);
            }
        }
    }
    if(flag){
        srand(time(0)+times);
        int x,y;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
}
void move_down(int size){
    bool flag=0;
    for(int i=size;i>=1;i--){
        for(int j=1;j<=size;j++){
            int tmp=next_nonzero_add(size,i,j,-1,0);
            if(tmp!=0 and tmp!=size+1){
                swap(M[i][j],M[tmp][j]);
                flag=1;
            }
            if(M[i+1][j]==M[i][j] and i+1!=0 and M[i][j]!=0){
                //cout<<i<<","<<j<<" :  "<<M[i][j]<<endl;
                flag=1;
                M[i+1][j]*=2;
                M[i][j]=0;
                swap(M[i][j],M[next_nonzero_add(size,i,j,-1,0)][j]);
            }
        }
    }
    if(flag){
        srand(time(0)+times);
        int x,y;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
}
int main(){
    int Size=4;
    while(1){
        times++;
        char o;
        system("cls");
        cout<<"s:start"<<endl<<"e::exit"<<endl;
        cin>>o;
        if(o=='e') break;
        init(Size);
        print(Size);
        while(1){
            if (/*_kbhit()*/1){
                char ch ;//= _getch();
                cout<<"r:restart a game"<<endl;
                cin>>ch;
                if(ch=='r') {   break;  }
                if(ch=='d') move_right(Size);
                if(ch=='a') move_left(Size);
                if(ch=='w') move_up(Size);
                if(ch=='s') move_down(Size);
                getchar();
                system("cls");
                print(Size);
            }
        }
    }
    return 0;
}