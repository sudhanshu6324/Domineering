#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
#define debug(x) cout<<#x<<" :: "<<x<<endl;
#define boost1 ios::sync_with_stdio(0)
#define boost2 cin.tie(0)
#define size1 100005
#define mod 1000000007
#define vll         vector < ll >
#define vpll        vector < pair < ll ,ll> >
#define pii         pair < int,int >
#define pll         pair < ll,ll >
#define fi          first
#define se          second
#define pb(x)       push_back(x)
#define endl        "\n"
#define mem1(x)     memset(x,-1,sizeof x)
#define mem(x)      memset(x,0,sizeof x)
#define mem63(x)    memset(x,63,sizeof x)


int a[size1],s;
int seg[4*size1],lazy[4*size1];

void update(int l,int r,int low,int high,int pos){
    if(low > high){
        return;
    }
    lazy[pos] %= 2;

    if(lazy[pos]){
        s = r - l + 1;
        seg[pos]  = s - seg[pos];
        if(l != r){
            lazy[2*pos + 1] += lazy[pos];
            lazy[2*pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(high < l || low > r){
        return;
    }
    if(low<=l && r <= high){
        s = r - l + 1;
        seg[pos]  = s - seg[pos];
        if(l != r){
            lazy[2*pos + 1] += 1;
            lazy[2*pos + 2] += 1;
        }
        return;
    }

    int m = (l+r)/2;

    update(l,m,low,high,2*pos+1);
    update(m+1,r,low,high,2*pos+2);

    seg[pos] = seg[2*pos + 1] + seg[2*pos + 2];
}

int query(int l,int r,int low,int high,int pos){
    if(low > high){
        return 0;
    }

    lazy[pos] %= 2;

    if(lazy[pos]){
        s = r - l + 1;
        seg[pos]  = s - seg[pos];
        if(l != r){
            lazy[2*pos + 1] += lazy[pos];
            lazy[2*pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    if(high < l || low > r){
        return 0;
    }

    if(low<=l && r <= high){
        return seg[pos];
    }
    int m = (l + r)/2;
    return query(l,m,low,high,2*pos+1) + query(m+1,r,low,high,2*pos+2);
}
int main()
{
    boost1;
    //boost2;
    int n,m,i,j,t,x,y,w;
    cin>>n>>m;
    for(i=0;i<m;i++){
        cin>>t>>x>>y;
        if(t == 0){
            update(0,n-1,x-1,y-1,0);
        }else{
            cout<<query(0,n-1,x-1,y-1,0)<<endl;
        }
    }
    return 0;
}
