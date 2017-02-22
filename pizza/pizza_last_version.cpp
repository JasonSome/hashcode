#include <bits/stdc++.h>
#define MAX_N 1005
#define MAX_N2 MAX_N*MAX_N
#define MS 5
using namespace std;
int P[MAX_N][MAX_N];
int T[MAX_N][MAX_N];
int M[MAX_N][MAX_N];
char locked[MAX_N][MAX_N];
int A[100],B[100];
int R,C,L,H;

int Mnum(int a1,int b1,int a2,int b2)//a grammi,b stili
{
	return M[a2][b2]-M[a2][b1-1] - M[a1-1][b2] + M[a1-1][b1-1];
}

int Tnum(int a1,int b1,int a2,int b2)
{
	return T[a2][b2]-T[a2][b1-1] - T[a1-1][b2] + T[a1-1][b1-1];
}

int isValid(int a1,int b1,int a2,int b2)
{
	int tom = Tnum(a1,b1,a2,b2);
	int ma = Mnum(a1,b1,a2,b2);
	return ((tom >= L && ma >= L && tom+ma <= H)?1:0);
}

int A1[2][MAX_N2],A2[2][MAX_N2],B1[2][MAX_N2],B2[2][MAX_N2];
int NUM1 = 0,NUM2,res0 = -1;
int solve(int seed)
{
	int pa,pb,a,b,c,res = 0,tmp,tmpc;
	NUM2 = 0;
	for(pa = 1;pa <= R;pa++){
		for(pb = 1;pb <= C;pb++){
			c = 0;tmp=-1;
			if(locked[pa][pb] == 0){
				for(b = 1;b <= H && pb+b-1 <= C;b++){
					if(locked[pa][pb+b-1] == 1)
						break;
					for(a = 1;a <= H &&pa + a-1 <= R && a*b<= H;a++){
						if(isValid(pa,pb,pa+a-1,pb+b-1) == 1){
							if(b > tmp){
								tmpc = c;
								tmp = min(a,b)-1;
							}
							A[c] = a;
							B[c] = b;
							c++;
						}
					}
				}
			}else
				continue;
			///////////////////
			if(c == 0){
				locked[pa][pb] = 1;
				continue;
			}
			//c = rand()%c;
			//c--;
			c = tmpc;
			for(a = 0;a < A[c];a++)
				for(b = 0;b < B[c];b++)
					locked[pa+a][pb+b] = 1;
			res += A[c] * B[c];
			A1[1][NUM2] = pa;
			B1[1][NUM2] = pb;
			A2[1][NUM2] = pa+A[c]-1;
			B2[1][NUM2] = pb+B[c]-1;
			assert(A1[1][NUM2] <= A2[1][NUM2] && B1[1][NUM2] <= B2[1][NUM2]);
			NUM2++;
		}
	}
	return res;
}

int main(void)
{
	int a,b,c,res1,seed;
	scanf("%d%d%d%d\n",&R,&C,&L,&H);
	for(a = 1;a <= R;a++){
		for(b = 1;b <= C;b++)
			P[a][b] = getchar();
		getchar();
	}
	for(a = 1;a <= R;a++)
		for(c = 0,b = 1;b <= C;b++){
			if(P[a][b] == 'T')
				c++;
			T[a][b] = T[a-1][b]+c;
			M[a][b] = M[a-1][b]+(b-c);
			
		}
	for(seed = 1;seed <= MS;seed++){
		memset(locked,0,sizeof(locked));
		srand(seed);
		res1 = solve(seed);
		if(res1 > res0){
			for(a = 0;a < NUM2;a++){
				A1[0][a] = A1[1][a];
				A2[0][a] = A2[1][a];
				B2[0][a] = B2[1][a];
				B1[0][a] = B1[1][a];
			}
			res0 = res1;
			NUM1 = NUM2;
		}
	}
	printf("%d\n",NUM1);
	for(a = 0;a < NUM1;a++)
		printf("%d %d %d %d\n",A1[0][a]-1,B1[0][a]-1,A2[0][a]-1,B2[0][a]-1);
	return 0;
}
