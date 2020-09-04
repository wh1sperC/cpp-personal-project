#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

typedef long long ll;
using namespace std;
vector<int> GenerateDiffNumber(int min,int max,int num)
{
    int rnd;
    vector<int> diff;
    vector<int> tmp;//??????
    //???
    for(int i = min;i < max+1 ; i++ )
    {
        tmp.push_back(i);
    }
    srand((unsigned)time(0)); //????????
    for(int i = 0 ; i < num ; i++)
    {
        do{
            rnd = min+rand()%(max-min+1);
     
        }while(tmp.at(rnd-min)==-1);
        diff.push_back(rnd);
        tmp.at(rnd-min) = -1;
    }
    return diff;
}
int main()
{
	int min,max,num;
	cin>>min>>max>>num;
	vector<int> diff;
	GenerateDiffNumber(min,max,num);
	for(int i=0;i<num;i++)
	cout<<diff[i]<<' ';
	return 0;
}
