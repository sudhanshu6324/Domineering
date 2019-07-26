#include <bits/stdc++.h>
using namespace std;

#define boardSize 13
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sec second
#define fr first

int gameBoard[boardSize][boardSize],me,isBomb,maxdepth,wonPlayer = 0;
pair <int,int> pos;
typedef pair<int,int> loc;
clock_t start;
int minimax(int,bool,int,int);
int winValue = 1000000;
int CheckValid(int,int,int);
loc iterativeDeepening(int,bool,int,int);
loc FindBestMove(int,bool,int,int);
loc checkSpecialH();
loc checkSpecialV();
void takeInput();
int evaluate(int[][13],int);

bool cmpd (const pair<int,pair<int,int> > &p1,const pair<int,pair<int,int> > &p2)
{
    return p1.fr>p2.fr;
}

int CheckValid(int i , int j ,int player){

    if(gameBoard[i][j] !=0)
        return 0;
    if(player == 1){
        if(gameBoard[i][j+1] !=0 || j == 12)
            return 0;
    }else{
        if(gameBoard[i+1][j] != 0 || i == 12)
                return 0;
     }


    return 1;
}

int minimax(int depth,bool ismaxturn,int alpha,int beta)
{
   // printf("hello");
   int player;
    if(ismaxturn){
        if(me == 1){
            player = 1;
        }else{
            player = 2;
        }
    }else{
        if(me == 2){
            player = 1;
        }else{
            player = 2;
        }
    }
   //int currentColor = (ismaxturn) ? !me : me;

   long long int eval = evaluate(gameBoard,me);
   if(me==1&&wonPlayer==1){
        wonPlayer = 0;
        return 10*winValue-depth;
   }
   if(me==1&&wonPlayer==2) {
        wonPlayer = 0;
        return -10*winValue+depth;
   }
   if(me==2&&wonPlayer==2){
        wonPlayer = 0;
        return 10*winValue-depth;
   }
   if(me==2&&wonPlayer==1){
        wonPlayer = 0;
        return -10*winValue+depth;
   }



    clock_t finish=clock();
    if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
    {return eval;}

   if(depth==maxdepth) {return eval;}


int src1,src2;
vector<pair<int,pair<int,int> > > v;
for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++)
    {
        if(CheckValid(i,j,player))
        {   //printf("found");
            if(player == 1){

                gameBoard[i][j] = 1;
                gameBoard[i][j+1] = 1;
                int evl = evaluate(gameBoard,me);  //gameBoard,me,player
                gameBoard[i][j] = 0;
                gameBoard[i][j+1] = 0;
                v.push_back(make_pair(evl,make_pair(i,j)));
            }else{
               // printf("hello1");
                gameBoard[i][j] = 2;
                gameBoard[i+1][j] = 2;
                int evl = evaluate(gameBoard,me);
                gameBoard[i][j] = 0;
                gameBoard[i+1][j] = 0;
                v.push_back(make_pair(evl,make_pair(i,j)));
            }
        }
    }
}
///////////////////////////ADD SPECIAL MOVE//////////////////////////////////////////////////
//printf("hello");
if(ismaxturn) sort(v.begin(),v.end(),&cmpd);
else sort(v.begin(),v.end());


   int x,y;
   int val;
   if(ismaxturn)
   {
      val=INT_MIN;
      if(player == 1){
            for(int i=0;i<v.size();i++){
                x=v[i].sec.fr;
                y=v[i].sec.sec;

            gameBoard[x][y] = 1;
            gameBoard[x][y+1] = 1;
            if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return val;
            int calc=minimax(depth+1,!ismaxturn,alpha,beta);
            val = max(val,calc);
            alpha=max(val,alpha);
            gameBoard[x][y] = 0;
            gameBoard[x][y+1] = 0;

            if(alpha>=beta)
                {return val;}

            clock_t finish=clock();
            if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return val;
            }
      }else{
            val=INT_MIN;
            for(int i=0;i<v.size();i++){
                    x=v[i].sec.fr;
                    y=v[i].sec.sec;

                gameBoard[x][y] = 2;
                gameBoard[x+1][y] = 2;
                if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                    return val;
                int calc=minimax(depth+1,!ismaxturn,alpha,beta);
                val = max(val,calc);
                alpha=max(val,alpha);
                gameBoard[x][y] = 0;
                gameBoard[x+1][y] = 0;

                if(alpha>=beta)
                    {return val;}

                clock_t finish=clock();
                if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                    return val;

            }
        }

    }else{
        //printf("hello");
         val=INT_MAX;
        if(player == 1){

              for(int i=0;i<v.size();i++)
              {
                x=v[i].sec.fr;
                y=v[i].sec.sec;
                gameBoard[x][y] = 1;
                gameBoard[x][y+1] = 1;
                if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return val;
                int calc=minimax(depth+1,!ismaxturn,alpha,beta);
                val=min(val,calc);
                beta=min(beta,val);
                gameBoard[x][y] = 0;
                gameBoard[x][y+1] = 0;
                if(alpha>=beta) {return val;}
                clock_t finish=clock();
                if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return val;
              }
        }else{
            for(int i=0;i<v.size();i++)
              {
                x=v[i].sec.fr;
                y=v[i].sec.sec;
                gameBoard[x][y] = 2;
                gameBoard[x+1][y] = 2;
                if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return val;
                int calc=minimax(depth+1,!ismaxturn,alpha,beta);
                val=min(val,calc);
                beta=min(beta,val);
                gameBoard[x][y] = 0;
                gameBoard[x+1][y] = 0;
                if(alpha>=beta) {return val;}
                clock_t finish=clock();
                if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return val;
                }
            }
      }


   return val;
}

int evaluate(int gameBoard[][13],int me){

    int i,j,flag;
    long long int both=10,only=100,value=0;
    if(me == 1){
        for(i=0;i<13;i++){
            for(j=0;j<12;j++){
                if(gameBoard[i][j]+gameBoard[i][j+1] == 0){
                    flag = 1;
                    if(i != 0){
                        if(gameBoard[i-1][j] == 0 || gameBoard[i-1][j+1] == 0){
                            flag = 0;
                        }
                    }
                    if(i!=12){
                        if(gameBoard[i+1][j] == 0|| gameBoard[i+1][j+1] == 0){
                             flag =0;
                        }

                    }
                    if(flag == 0){
                        value += both;
                    }else{
                        value += only;
                       // j++;
                    }
                }
            }
        }
//        int count1 = 0;
//        for(j=0;j<13;j++){
//                for(i=0;i<12;i++){
//                        if(gameBoard[i][j] == 0 && gameBoard[i+1][j] == 0){
//                            count1++;
//                            i++;
//                        }
//                }
//        }
//        value -= count1;

        //very imp don't delete
        if(value<10){
            wonPlayer = 2;
        }

    }else{
        for(j=0;j<13;j++){
            for(i=0;i<12;i++){
                    if(gameBoard[i][j]+gameBoard[i+1][j] == 0){
                        flag = 1;
                        if(j != 0){
                            if(gameBoard[i][j-1] == 0 || gameBoard[i+1][j-1] == 0){
                                flag = 0;
                            }
                        }
                        if(j!=12){
                            if(gameBoard[i][j+1] == 0|| gameBoard[i+1][j+1] == 0){
                                 flag =0;
                            }

                        }
                        if(flag == 0){
                            value += both;
                        }else{
                            value += only;
                        }
                    }
                }
            }
//        int count1 = 0;
//        for(i=0;i<13;i++){
//                for(j=0;j<12;j++){
//                        if(gameBoard[i][j] == 0 && gameBoard[i][j+1] == 0){
//                            count1++;
//                            j++;
//                        }
//                }
//        }
//        value -= count1;
        if(value <10){
            wonPlayer = 1;
        }
    }

        return value;
}

loc FindBestMove(int depth,bool ismaxturn,int alpha,int beta)
{
   loc source,dest;
   loc bestmove;
   int player = me;
   int bestval=INT_MIN;

   for(int i=0;i<boardSize;i++)
        for(int j=0;j<boardSize;j++){
            if(CheckValid(i,j,player)){
                if(player== 1){
                    gameBoard[i][j] = 1;
                    gameBoard[i][j+1] = 1;
                }else{
                    gameBoard[i][j] = 2;
                    gameBoard[i+1][j] = 2;
                }
                int val=minimax(depth,false,alpha,beta);

                if(val>bestval){
                  bestval=val;
                  bestmove.first=i;
                  bestmove.second=j;
                }
                if(player== 1){
                    gameBoard[i][j] = 0;
                    gameBoard[i][j+1] = 0;
                }else{
                    gameBoard[i][j] = 0;
                    gameBoard[i+1][j] = 0;
                }
            }

            clock_t finish=clock();
            if((double)(finish-start)/CLOCKS_PER_SEC>0.75)
                return bestmove;
         }

   return bestmove;
}
loc iterativeDeepening(int depth,bool ismaxturn,int alpha,int beta)
{

    loc finalMove;
    start=clock();
    maxdepth=1;
    while(maxdepth<7)
    {  // printf("Hello");
        loc temp=FindBestMove(1,true,alpha,beta);
        clock_t finish=clock();
        if((double)(finish-start)/CLOCKS_PER_SEC>0.75){
               // printf("Working maxdepth=%d",maxdepth);
                return finalMove;
            }
        finalMove=temp;
        maxdepth++;
    }
    return finalMove;
}


loc checkSpecialH(){
    int flag,l,i,j,k;

    for(i=1;i<12;i++){
        for(j=0;j<12;j++){
            if(CheckValid(i,j,me)){
             if(gameBoard[i-1][j] + gameBoard[i-1][j+1] + gameBoard[i+1][j] + gameBoard[i+1][j+1] != 0){
                continue;
            }
            if(i!=1){
                if(gameBoard[i-2][j] == 0 || gameBoard[i-2][j+1] ==0 ){
                    continue;
                }
            }
            if(i!=11){
                if(gameBoard[i+2][j] !=0 && gameBoard[i+2][j+1] != 0){
                    return make_pair(i,j);
                }
            }
            }

        }
    }
    return make_pair(13,13);
}
loc checkSpecialV(){
    int flag,l,i,j,k;
     for(j=1;j<12;j++){
        for(i=0;i<12;i++){
            if(CheckValid(i,j,me)){
                 if(gameBoard[i][j-1] + gameBoard[i+1][j-1] + gameBoard[i][j+1] + gameBoard[i+1][j+1] != 0){
                    continue;
                }
                if(j!=1){
                    if(gameBoard[i][j-2] == 0 || gameBoard[i+1][j-2] ==0 ){
                        continue;
                    }
                }
                if(j!=11){
                    if(gameBoard[i][j+2] !=0 && gameBoard[i+1][j+2] != 0){
                        return make_pair(i,j);
                    }
                }
            }

        }
    }
    return make_pair(13,13);
}



void takeInput(){
    int i,j;
    scanf("%d",&me);
    for(i=0;i<13;i++)
        for(j=0;j<13;j++)
            scanf("%d",&gameBoard[i][j]);
    scanf("%d",&isBomb);
}

int bombNeeded(int gameBoard[][13],int me){
    int flag =1,i,j;
    if(me ==1){
         for(i=0;i<13;i++){
            for(j=0;j<12;j++){
                    if(gameBoard[i][j]==0 && gameBoard[i][j+1] == 0){
                        flag = 0;
                        break;
                    }

            }
        }
    }else{
        for(i=0;i<12;i++){
            for(j=0;j<13;j++){
                    if(gameBoard[i][j] && gameBoard[i+1][j] == 0){
                        flag = 0;
                        break;
                    }
            }
        }
    }
    return flag;
}

loc findBombPos(int gameBoard[][13]){
    int flag,i,j,k,H,V,l,m;

    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            flag = 1;
           for(k=0;k<4;k++){
                if(j!=8){
                    for(l=0;l<5;l++){
                        H=0;
                        for(m=0;m+j+5<13;m++){
                            if(gameBoard[i+l][j+m+5]==1){
                                H++;
                            }
                        }
                        if(H%2 !=0 ){
                            flag = 0;
                        }
                        if(flag == 0)
                            break;
                    }
                }
                if(flag != 0 && i!= 8 ){
                    for(l=0;l<5;l++){
                        V=0;
                        for(m=0;m+i+5<13;m++){
                            if(gameBoard[i+m+5][j+l]==2){
                                V++;
                            }
                        }
                        if(V%2 !=0 ){
                            flag = 0;
                        }
                        if(flag == 0)
                            break;
                    }
                }
                if(flag != 0 && j!= 0){
                    for(l=0;l<5;l++){
                        H=0;
                        for(m=0;m<j;m++){
                            if(gameBoard[i+l][m] == 1){
                                H++;
                            }
                        }
                        if(H%2 != 0){
                            flag = 0;
                        }
                        if(flag == 0)
                            break;
                    }
                }
                if(flag!= 0 && i != 0){
                    for(l=0;l<5;l++){
                        V=0;
                        for(m=0;m<i;m++){
                            if(gameBoard[m][j+l] == 2){
                                V++;
                            }
                        }
                        if(V%2 !=0){
                            flag = 0;
                        }
                        if(flag == 0)
                            break;
                    }
                }
           }
           if(flag == 1){
                break;
           }
        }
        if(flag == 1){
            break;
        }
    }
    if(flag == 1)
        return make_pair(i,j);

    return make_pair(15,15);
}

int main()
{   int alpha=-1000000000,beta=1000000000;
    pair<int,int> test ;

    takeInput();
    if(bombNeeded(gameBoard,me)){
        loc ans = findBombPos(gameBoard);
        if(ans.first == 15){
            printf("There is flaw!!!NOObs");
           //printf("2 %d %d",ans.first,ans.second);
        }else
            printf("2 %d %d",ans.first,ans.second);
        exit(0);
    }
    if(me == 1){
       test = checkSpecialH();
       if(test.first <= 11){
           printf("1 %d %d",test.first,test.second);
           exit(0);
        }
    }else{
       test = checkSpecialV();
       if(test.first <= 11){
           printf("1 %d %d",test.first,test.second);
            exit(0);
        }
    }

    // maxMIN
    test= iterativeDeepening(1,1,alpha,beta);
    clock_t finish=clock();

   // printf("maxdepth = %d\n ",maxdepth);
    printf("1 %d %d",test.first,test.second);
    return 0;
}


