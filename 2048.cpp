#include<iostream>
#include<time.h>
#include<stdlib.h>
//#include<conio.h>
#include<Windows.h>
#define KEY_DOWN(x) ((GetAsyncKeyState(x)&0x8000)?1:0)
using namespace std;
int M[10][10];
int score;
int win=2018;
bool lose=0;
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
    score+=re;
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
int print(int size){
    lose=1;
    system("cls");
    for(int k=1;k<=(size*11)+1;k++) printf("-");
    cout<<endl;
    for(int i=1;i<=size;i++){
        printf("|");
        for(int j=1;j<=size;j++){
            int tmp=M[i][j];
            if(tmp==0)  lose=0;
            if( (M[i][j]==M[i+1][j] and i+1<=size) or 
                (M[i][j]==M[i-1][j] and i-1>0) or 
                (M[i][j]==M[i][j-1] and j-1>0) or 
                (M[i][j]==M[i][j+1] and j+1<=size) )    lose=0;
            if(tmp==win){
                system("cls");
                cout<<"You Win"<<endl;
                cout<<"score : "<<score;
                return 1;
            }
            int l=7;
            while(tmp/=10)  l--;
            while(l--)  printf(" ");
            if(M[i][j]!=0)  printf("%d",M[i][j]);
            else    printf(" ");
            printf("  |");
        }
        cout<<endl;
        for(int k=1;k<=(size*11)+1;k++) cout<<"-";
        cout<<endl;
    }
    cout<<"score : "<<score<<endl;
    cout<<"r : restart a game"<<endl;
    return 0;
}
void move_right(int size){
    cout<<"right"<<endl;
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
        x%=size,x++;
        y%=size,y++;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
    cout<<"right:down"<<endl;
}
void move_left(int size){
    cout<<"left"<<endl;
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
    print(size);
    if(flag){
        srand(time(0)+times);
        int x,y;
        x%=size,x++;
        y%=size,y++;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
    cout<<"left:down"<<endl;
}
void move_up(int size){
    cout<<"up"<<endl;
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
        x%=size,x++;
        y%=size,y++;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
    cout<<"up:done"<<endl;
}
void move_down(int size){
    cout<<"down"<<endl;
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
        x%=size,x++;
        y%=size,y++;
        while(M[x][y]!=0)   x=(rand()%size)+1 , y=(rand()%size)+1;
        M[x][y]=rand_number();
    }
    cout<<"down:done"<<endl;
}
int main(){
    int Size=4;
    while(1){
        score=0;
        lose=0;
        times++;
        char o;
        system("cls");
        cout<<"s:start"<<endl<<"e:exit"<<endl;
        cin>>o;
        if(o=='e') break;
        system("cls");
        init(Size);
        print(Size);
        while(1){
            if(lose){
                cout<<"You lose"<<endl;
                cout<<"score : "<<score<<endl;
                cout<<"press \"r\" to restart game"<<endl;
                while(!KEY_DOWN(82));
                system("cls");
                break;
            }
            int pd=0;
            if(KEY_DOWN(65)){
                move_left(Size),pd=print(Size);//A 
                if(pd)  break;
                while(KEY_DOWN(65));
            }
            if(KEY_DOWN(68)){
                move_right(Size),pd=print(Size);//D   
                if(pd)  break;
                while(KEY_DOWN(68));  
            }
            if(KEY_DOWN(87)){
                move_up(Size),pd=print(Size);//W  
                if(pd)  break;
                while(KEY_DOWN(87));   
            }
            if(KEY_DOWN(83)){
                move_down(Size),pd=print(Size);//S  
                if(pd)  break;
                while(KEY_DOWN(83));  
            }
            if(KEY_DOWN(82)){//R
                break;
            }
            /*if (1){   //_kbhit()){
                char ch ;//= getchar();
                cin>>ch;
                if(ch=='r') {   break;  }
                if(ch=='d') move_right(Size);
                if(ch=='a') move_left(Size);
                if(ch=='w') move_up(Size);
                if(ch=='s') move_down(Size);
                //getchar();
                print(Size);
            }
            */
        }
    }
    return 0;
}