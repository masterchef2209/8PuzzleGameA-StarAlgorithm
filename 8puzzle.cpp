		/*Read the problem carefully before starting to work on it*/
#include <bits/stdc++.h>

//#include <boost/multiprecision/cpp_int.hpp>
//using namespace boost::multiprecision;
//#include <ext/pb_ds/assoc_container.hpp> 
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#include <functional>
//using namespace __gnu_pbds;

typedef long long ll;

//ll ncr(ll n,ll r){ll ans=1;r=min(r,n-r);for (int i=1;i<=r;i++){ans*=(n-r+i);ans/=i;}return ans;}

#define pb push_back
#define eb emplace_back
#define mp(x,y) make_pair(x,y)
#define mod 1000000007

double PI=3.1415926535897932384626;

//template<typename T> T power(T x,T y,ll m=mod){T ans=1;while(y>0){if(y&1LL) ans=(ans*x)%m;y>>=1LL;x=(x*x)%m;}return ans%m;}

//typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> ost;

typedef pair<vector<vector<int> > , int> state;

#define fi first
#define se second

map<vector<vector<int> > , bool> visited;
map<vector<vector<int> > , vector<vector<int> > > parent;
vector<vector<int> > goal(3,vector<int> (3));

int manhattan(vector<vector<int> > grid , int movessofar)
{
	int dist=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(grid[i][j]!=0)
			{
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						if(grid[i][j]==goal[k][l])
							dist+=abs(i-k)+abs(j-l);
					}
				}
			}
		}
	}
	int h=dist;
	int g=movessofar;
	int f=(h+g);
	return f;
}

bool isGoal(vector<vector<int> > grid)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(grid[i][j]!=goal[i][j])
				return false;
		}
	}

return true;
}

inline bool ingrid(int i,int j)
{
	return (i>=0 && i<=2 && j>=0 && j<=2);
}

int dx[]={-1,+1,0,0};
int dy[]={0,0,-1,+1};
vector<vector<vector<int> > > neighbours(vector<vector<int> > grid)
{
	pair<int,int> blank;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(grid[i][j]==0)
			{
				blank.first=i;
				blank.second=j;
				break;
			}
		}
	}
	vector<vector<vector<int> > > ans;
	for(int k=0;k<4;k++)
	{
		int x = blank.first;
		int y = blank.second;
		vector<vector<int> > tem = grid;
		if(ingrid(x+dx[k],y+dy[k]))
		{
			swap(tem[x+dx[k]][y+dy[k]],tem[x][y]);
			ans.push_back(tem);
		}
	}
return ans; 
}

struct cmp
{
	bool operator() (state &a, state &b)
	{
		int f1 = manhattan(a.first,a.second);
		int f2 = manhattan(b.first,b.second);
		return f1<f2;
	}
};

void printgrid(vector<vector<int> > grid)
{
   for(int i=0;i<3;i++)
   {
   	printf("+-+-+-+\n");
	 for(int j=0;j<3;j++)
	 {
	 	printf("|");
	 	if(grid[i][j]==0)
	 		printf(" ");
	 	else 
			printf("%d",grid[i][j]);
		if(j==2)
		{
			printf("|");
		}
	 }
	cout<<endl;
   }
   printf("+-+-+-+\n");
   cout<<endl;
}

void print_path(vector<vector<int> > grid)
{
   if(parent.count(grid))
   print_path(parent[grid]);
   
   printgrid(grid);
}

void solve(vector<vector<int> > grid, int movessofar)
 {
	
	priority_queue<state,vector<state>,cmp > pq;
	pq.push(state(grid,movessofar));
	while(!pq.empty())
	{
		vector<vector<int> > curr = pq.top().first;
		pq.pop();
		visited[curr]=true;
		if(curr==goal)
		{
			print_path(curr);
			break;
		}
		vector<vector<vector<int> > > nei = neighbours(curr);
		for(auto &temp:nei)
		{
			if(!visited[temp])
			{
				parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp,curr));
				pq.push(state(temp,movessofar+1));
			}
		}
	}
	return;
 }

int main()
{
	vector<vector<int> > startgrid(3,vector<int> (3));
	cout<<"8 PUZZLE Game using A* algorithm\n";
	cout<<"Please enter initial state\n";
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>startgrid[i][j];	
		}
	}
	cout<<"Please enter goal state\n";
	for(ll i=0;i<3;i++)
	{
	    for(ll j=0;j<3;j++)
	    {
	        cin>>goal[i][j];
	    }
	}
	cout<<"Processing...\n\n";
	solve(startgrid,0);
}


//252908XL