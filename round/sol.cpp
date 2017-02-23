#include <bits/stdc++.h>
#define MAX_V 10005
#define MAX_E 1005
#define MAX_R 1000005
#define MAX_C 1005
#define MAX_MB 500005
#define I64 long long int
using namespace std;
I64 V,E,R,C,X;
I64 V_SIZE[MAX_V];

typedef struct{
	I64 req,ds,end;
}reqs;

typedef struct{
	I64 profit,vid,cache;
}pr_s;

typedef struct{
	I64 lat,cache;
}cache_con;

bool operator<(const pr_s& a,const pr_s& b)
{
	return a.profit < b.profit;
}

priority_queue<pr_s> Q;
vector<reqs> P_reqs[MAX_V];
vector<cache_con> P_lat[MAX_E];
I64 v_profit[MAX_V][MAX_C];
I64 dist_ds[MAX_E];
I64 cap[MAX_C];
char visited[MAX_V][MAX_C];
char up_cache[MAX_C];
I64 old_ds[MAX_E];

int main(void)
{
	I64 a,b,c,d,LD,K,m;
	pr_s tmp;
	scanf("%lld%lld%lld%lld%lld",&V,&E,&R,&C,&X);
	for(a = 0;a < V;a++)
		scanf("%lld",&V_SIZE[a]);
	for(a = 0;a < E;a++){
		scanf("%lld%lld",&dist_ds[a],&K);
		for(b = 0;b < K;b++){
			scanf("%lld%lld",&c,&d);
			P_lat[a].push_back({d,c});
		}
	}
	for(a = 0;a < C;a++)
		cap[a] = X;
	for(a = 0;a < R;a++){
		scanf("%lld%lld%lld",&b,&c,&d);
		P_reqs[b].push_back({d,dist_ds[c],c});
	}
	//arxikopoioume priority queue
	for(a = 0;a < V;a++){
		for(int it = 0;it != P_reqs[a].size();it++){
			for(int it2 = 0;it2 < P_lat[P_reqs[a][it].end].size();it2++){
				v_profit[a][P_lat[P_reqs[a][it].end][it2].cache] += (dist_ds[P_reqs[a][it].end] - P_lat[P_reqs[a][it].end][it2].lat)*P_reqs[a][it].req;
			}
		}
	}
	for(a = 0;a < V;a++){
		for(b = 0;b < C;b++){
			//v_profit[a][b]/=V_SIZE[a];
			Q.push({v_profit[a][b]/V_SIZE[a],a,b});
		}
	}
	//pare to kalytero
	while(!Q.empty()){
		tmp = Q.top();
		Q.pop();
		//an  einai palio i den xwraei
		if(visited[tmp.vid][tmp.cache] == 1 
		|| tmp.profit != v_profit[tmp.vid][tmp.cache]/V_SIZE[tmp.vid]
		|| V_SIZE[tmp.vid] > cap[tmp.cache]){
			continue;
		}
		visited[tmp.vid][tmp.cache] = 1;
		cap[tmp.cache] -= V_SIZE[tmp.vid];
		//ypologizoume ds
		for(a = 0;a < P_reqs[tmp.vid].size();a++){
				m = dist_ds[P_reqs[tmp.vid][a].end];
				old_ds[P_reqs[tmp.vid][a].end] = m;
				for(b = 0;b < P_lat[P_reqs[tmp.vid][a].end].size();b++){
					if(visited[tmp.vid][P_lat[P_reqs[tmp.vid][a].end][b].cache] == 1
					&& m > P_lat[P_reqs[tmp.vid][a].end][b].lat)
						m = P_lat[P_reqs[tmp.vid][a].end][b].lat;
				}
				P_reqs[tmp.vid][a].ds = m;
		}
		//nea profit
		memset(up_cache,0,sizeof(up_cache));
		for(a = 0;a < P_reqs[tmp.vid].size();a++){//fora all ends
				for(b = 0;b < P_lat[P_reqs[tmp.vid][a].end].size();b++){
					m = (old_ds[P_reqs[tmp.vid][a].end] - P_reqs[tmp.vid][a].ds)*P_reqs[tmp.vid][a].req;
					v_profit[tmp.vid][P_reqs[tmp.vid][a].end] -= m;
					if(m > 0)
						up_cache[a] = 1;
				}
		}
		for(a = 0;a < C;a++){
			if(up_cache[a] == 1)
				Q.push({v_profit[tmp.vid][P_reqs[tmp.vid][a].end]/V_SIZE[tmp.vid],tmp.vid,a});
		}
	}
	c = 0;
	for(a = 0;a < C;a++){
		for(b = 0;b < V;b++){
			if(visited[b][a] == 1){
				c++;
				break;
			}
		}
	}
	printf("%lld\n",c);
	for(a = 0;a < C;a++){
		for(b = 0,c = 0;b < V;b++){
			if(visited[b][a] == 1){
				if(c == 0)
					printf("%lld ",a);
				printf("%lld ",b);
				c++;
			}
		}
		if(c != 0){
			putchar('\n');
		}
		//putchar('\n');
	}
	return 0;
}
