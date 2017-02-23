#include <cstdio>
#include <algorithm>
#include <priority_queue>

using namespace std;

int v, e, r, c, max_cap, video_size[10005], num_of_caches;
priority_queue<> p;

void solve() {
	
	
	
}

int main() {
	
	int i;
	
	scanf("%d%d%d%d%d", &v, &e, &r, &c, &max_cap);
	for (i=0; i < v; i++)
		scanf("%d", &video_size[i]);
		
	// if endpoint has 0 cache servers connected, ignore it.
	
	solve();
	
	printf("%d\n", num_of_caches);
	for (i=0; i < num_of_caches; i++) {
		printf("%d ", i); // if all used
		
		printf("\n");
	}
	
	return 0;

}
