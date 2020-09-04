//红黑夜法官
/*游戏规则：（基本要求）
设定玩家人数：n
若玩家人数为偶数，则红牌身份与黑牌身份各占一半；若为奇数，则红牌身份多1；
使用指定范围的随机数构造方法，依次构造出1-n之间不重复的随机数，按照出现的随机数给该玩家发身份，该玩家的身份
随机但总体满足规则2的人数分配。
第一天，从1-n号玩家顺序发言，需要显示当前发言玩家位置。一轮发言后从1-n号顺序投票选举村长，
得票最多的玩家当选村长，若总人数为偶数，村长拥有1.5票，总人数为奇数，村长拥有0.5票。（票数后续讲解作用）
白天：村长决定从村长左边或者右边开始发言的顺序，发言顺序构成为k-1~村长k~k+1的回环，
（DOS下需要显示当前发言人的位置，若该发言人已经死亡要宣布，其余界面能够可视化存亡情况与发言位置。
使用鼠标或者键盘切换下一个人发言。）最后从1-n号玩家进行匿名投票，得票最多的人被放逐出游戏，并且显示身份，
若村长被放逐则要移交下一任村长。
夜晚：随机进入红夜或黑夜，所有玩家可以自由睁眼。
红夜时：睁眼的红牌为偶数则第二天村长拥有1票；黑夜时：睁眼的黑牌为偶数则第二天村长拥有1票
游戏结束：所有的红牌或者所有的黑牌被放逐。
（1）使用DOS实现可视化游戏进程；（到此60起评）
（2）自动添加提示游戏进程：进入黑夜，进入红夜，天亮了，某某玩家被放逐身份为X等。
（到此70起评）
（3）MFC或QT界面友好可视化；（到此80起评）
（4）优秀的数据结构能够使得判断身份与投票功能更加便捷，请大家根据不同的功能使用不同的数据结构存储游戏数据。
（到此85起评）
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
struct player//编辑一个玩家的信息
{
	ll no;
	char id;
	bool alive,is_village;
	
};

int main()
{
	std::ios::sync_with_stdio(false);
	//设定玩家人数n,红牌数和黑牌数 
	ll n,redCard,blackCard;
	cin>>n;
	//如果n是偶数，则红黑牌一样多；否则红牌+1 
	redCard=blackCard=n/2;
	if(n%2)
	redCard++;
	//创建玩家信息
	player *p=new player[n];
	for(ll i=0;i<n;i++)
	{
		(p+i)->alive=true;
		(p+i)->is_village=false;
	}
	for(ll i=0;i<n;i++)
		(p+i)->no=i+1;
	//依次构造出1-n之间不重复的随机数，按照出现的随机数给该玩家发身份，这里我用容器完成 
	srand((unsigned)time(NULL));
	ll *num=new ll [n];
	for(ll i=0;i<n;i++)
	num[i]=(p+i)->no;
	random_shuffle(num,num+n);
//	for(ll i=0;i<n;i++)	
//	cout<<num[i]<<' ';
	
	return 0;
}
