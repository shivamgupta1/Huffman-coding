
#include <bits/stdc++.h>
#define PRECISION 0.0000000000001
#define EPSILON 0.000000000001
using namespace std;

struct myPoint {
	int r, c;
	long long int n;
	double distance;
	vector<pair<int,int> > path;
	set<pair<int,int> > gems;
	long long int gemtotal;
	bool power, powerused;
	myPoint(int h, int k, double d, long long int number, vector<pair<int,int> > p, set<pair<int,int> > g ,long long int gemt, bool pw, bool pu) : r(h), c(k), n(number), distance(d), path(p), gems(g), gemtotal(gemt), power(pw), powerused(pu) {}
	bool operator< (const myPoint &rhs) const{
        return (rhs.distance-this->distance>=PRECISION);
	}
};

int main()
{
    int t, m, n, eeta, alpha, a, b;
    cin>>t;
    while(t--) {
    	cin>>m>>n>>eeta>>alpha;
    	set<myPoint> myset;
    	long long int number = 0;
    	vector<vector<int> > grid(m, vector<int>(n));
    	vector<pair<int,int> > arg1;
    	set<pair<int,int> >arg2;
    	map<pair<pair<pair<int,int>,set<pair<int,int> > >, bool>, double> minDistance;
    	for(int i = 0; i<m; i++) {
    		for(int j = 0; j<n; j++) {
    			cin>> grid[i][j];
    		}
    	}
    	cin>> a >> b;
    	arg1.push_back(pair<int,int>(a,b));
    	if(grid[a][b]>0) {
    		arg2.insert(pair<int,int>(a,b));
    		myset.insert(myPoint(a,b,alpha,0,arg1,arg2,grid[a][b],false,false));
            minDistance[make_pair(make_pair(pair<int,int>(a,b),arg2),false)] = alpha;
    	} else {
    	    if(grid[a][b]==-2) {
                myset.insert(myPoint(a,b,0,0,arg1,arg2, 0, true,false));
                minDistance[make_pair(make_pair(pair<int,int>(a,b),arg2),true)] = 0;
            }
            else {
                myset.insert(myPoint(a,b,0,0,arg1,arg2, 0, false,false));
                minDistance[make_pair(make_pair(pair<int,int>(a,b),arg2),false)] = 0;
            }
    	}
    	while(!myset.empty()) {
    		myPoint curr = *(myset.begin());
    		myset.erase(myset.begin());
    		/*cout << curr.r << " " << curr.c << " " << curr.distance<<" ";
    		if(curr.path.size()>1){
                cout << curr.path[curr.path.size()-2].first << " " << curr.path[curr.path.size()-2].second;
    		}
    		cout << endl;*/
    		if(curr.gemtotal >= eeta) {
    			for(int i = 0; i<curr.path.size(); i++) {
    				cout << curr.path[i].first << " " << curr.path[i].second << " ";
    			}
    			cout << endl;
    			break;
    		}
    		if(curr.c+1 <n && grid[curr.r][curr.c+1] != -1) {
    			++number;
    			myPoint temp(curr.r, curr.c+1, curr.distance+1+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.r+1 <m && curr.c+1<n && grid[curr.r+1][curr.c+1]!=-1 ) {
    			++number;
    			myPoint temp(curr.r+1, curr.c+1, curr.distance+sqrt(2)+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2&& !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.r+1<m && grid[curr.r+1][curr.c] != -1 ) {
    			++number;
    			myPoint temp(curr.r+1, curr.c, curr.distance+1+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2&& !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.r+1<m && curr.c-1>=0 && grid[curr.r+1][curr.c-1]!= -1) {
    			++number;
    			myPoint temp(curr.r+1, curr.c-1, curr.distance+sqrt(2)+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.c-1>=0 && grid[curr.r][curr.c-1]!=-1 ) {
    			++number;
    			myPoint temp(curr.r, curr.c-1, curr.distance+1+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.r-1>=0 && curr.c-1>=0 && grid[curr.r-1][curr.c-1]!=-1 ) {
    			++number;
    			myPoint temp(curr.r-1, curr.c-1, curr.distance+sqrt(2)+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.r-1>=0 && grid[curr.r-1][curr.c]!=-1 ) {
    			++number;
    			myPoint temp(curr.r-1, curr.c, curr.distance+1+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
    		if(curr.r-1>=0 && curr.c+1<n && grid[curr.r-1][curr.c+1]!=-1 ) {
    			++number;
    			myPoint temp(curr.r-1, curr.c+1, curr.distance+sqrt(2)+number*EPSILON, number, curr.path, curr.gems, curr.gemtotal,curr.power, curr.powerused);
                if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
    			temp.path.push_back(pair<int, int>(temp.r, temp.c));
    			if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
    				temp.gemtotal += grid[temp.r][temp.c];
    				temp.gems.insert(pair<int,int>(temp.r, temp.c));
    				temp.distance += alpha;
    			}
    			if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                    minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                    myset.insert(temp);
                }
    		}
            if(curr.power && !curr.powerused) {
                for(int ir = curr.r-5; ir<=curr.r+5; ir++) {
                    for(int ic = curr.c-5; ic<=curr.c+5; ic++) {
                        if((ir-curr.r)*(ir-curr.r)+(ic-curr.c)*(ic-curr.c) <= 25) {
                        if(ir>=0 && ir<m && ic>=0 && ic<n && grid[ir][ic]!=-1) {
                            ++number;
                            myPoint temp(ir,ic,curr.distance+1+number*EPSILON,number,curr.path,curr.gems,curr.gemtotal,false,true);
                            if(grid[temp.r][temp.c]==-2 && !temp.powerused) temp.power = true;
                            temp.path.push_back(pair<int,int>(temp.r,temp.c));
                            if(grid[temp.r][temp.c]>0 && temp.gems.find(pair<int,int>(temp.r, temp.c))== temp.gems.end()) {
                                temp.gemtotal += grid[temp.r][temp.c];
                                temp.gems.insert(pair<int,int>(temp.r, temp.c));
                                temp.distance += alpha;
                            }
                            if(minDistance.find(make_pair(make_pair(pair<int,int>(temp.r,temp.c), temp.gems),temp.power))==minDistance.end() ||
                                minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)]-temp.distance >= PRECISION) {
                                minDistance[make_pair(make_pair(pair<int,int>(temp.r,temp.c),temp.gems),temp.power)] = temp.distance;
                                myset.insert(temp);
                            }
                        }
                        }
                    }
                }
            }
    	}
    }
    return 0;
}
