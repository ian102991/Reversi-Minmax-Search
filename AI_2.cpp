#include<bits/stdc++.h>
#define INF 37
using namespace std;
int legal(int x){
    if(x>=0 && x<=5) return 1;
    return 0;
}
int countFlipPieces(string state, int player, string position, int direct){
    int x=position[0]-'A',y=position[1]-'a';
    int move_x[8]={-1,-1,0,1,1,1,0,-1},move_y[8]={0,1,1,1,0,-1,-1,-1};
    int cnt=0;
    while(legal(x+move_x[direct])&&legal(y+move_y[direct])){
        x=x+move_x[direct];
        y=y+move_y[direct];
        if(state[6*x+y]=='+'){
            return 0;
        }
        if(player==1){
            if(state[6*x+y]=='O'){
                cnt++;
            }
            else{
                return cnt;
            }
        }
        else{
            if(state[6*x+y]=='X'){
                cnt++;
            }
            else{
                return cnt;
            }
        }

    }
    return 0;
}
string flipPieces(string state, int player, string position){
    int x=position[0]-'A',y=position[1]-'a',in=0;
    int move_x[8]={-1,-1,0,1,1,1,0,-1},move_y[8]={0,1,1,1,0,-1,-1,-1};
    char c=(player==1?'X':'O');
    for(int i=0;i<8;i++){
        int orix=x,oriy=y;
        int time=countFlipPieces(state,player,position,i);
        for(int j=0;j<time;j++){
            in=1;
            x=x+move_x[i],y=y+move_y[i];
            state[6*x+y]=c;
        }
        x=orix,y=oriy;
    }
    if(in) state[6*x+y]=c;
    return state;
}
int countColorPieces(string state,int player){
    char c=(player==1?'X':'O');
    int cnt=0;
    for(int i=0;i<state.length();i++){
        if(state[i]==c){
            cnt++;
        }
    }
    return cnt;
}
int heuristicScore(string state,int player){
    int opponent=((player-1)^1)+1;
    return countColorPieces(state,player)-countColorPieces(state,opponent);
}
int minimaxSearch(string state, int player, int maxdepth,int depth=0,int no_play=0,int alpha=-1*INF,int beta=INF){
    string row[6]={"A","B","C","D","E","F"},col[6]={"a","b","c","d","e","f"};
    int ma=-1*INF,mi=INF,po=0,in=0;
    if(depth==maxdepth){
        return depth%2?heuristicScore(state,((player-1)^1)+1):heuristicScore(state,player);
    }
    for(int i=0;i<36;i++){
        if(state[i]!='+') continue;
        if(alpha>=beta){
            return depth%2?mi:ma;
        }
        int x=i/6,y=i%6;
        string s=flipPieces(state,player,row[x]+col[y]);
        if(s==state) continue;
        in=1;
        no_play=0;
        if(depth%2){
            int tmp=minimaxSearch(s,((player-1)^1)+1,maxdepth,depth+1,no_play,alpha,beta);
            if(mi>tmp){
                beta=tmp;
                po=i;
                mi=tmp;
            }
        }
        else{
            int tmp=minimaxSearch(s,((player-1)^1)+1,maxdepth,depth+1,no_play,alpha,beta);
            if(depth==0){
                //cout<<char('A'+(i/6))<<char('a'+(i%6))<<" "<<tmp<<'\n';
            }
            if(ma<tmp){
                alpha=tmp;
                po=i;
                ma=tmp;
            }
        }
    }
    if(depth==0) cout<<char('A'+(po/6))<<char('a'+(po%6))<<'\n';
    if(!in){
        if(no_play==1){
            return depth%2?heuristicScore(state,((player-1)^1)+1):heuristicScore(state,player);
        }
        no_play++;
        return minimaxSearch(state,((player-1)^1)+1,maxdepth,depth+1,no_play,alpha,beta);
    }
    if(depth==0){
        return po;
    }
    return depth%2?mi:ma;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        string state;
        int player,dep;
        cin>>state>>player>>dep;
        minimaxSearch(state,player,dep);
    }
    return 0;
}
