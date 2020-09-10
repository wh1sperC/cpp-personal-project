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
#include <windows.h>
#include <conio.h>
using namespace std;
struct player//定义一个玩家的信息
{
	int no, id, eye; //玩家序号，身份:1r0b，睁1闭0眼
	bool alive, village, able; //玩家存活1，是1否0为村长,是1否0可以被选为村长
	double piao;//玩家的票数
};
void title(void)
{
	cout<<"    红                                             夜"<<endl;
	cout<<"  红    红红红红红     黑黑黑黑黑黑黑               夜"<<endl;
	cout<<"红          红         黑 黑 黑 黑 黑      夜夜夜夜夜夜夜夜夜夜"<<endl;
	cout<<"  红        红         黑  黑黑黑  黑           夜      夜"<<endl;
	cout<<"    红      红         黑黑黑黑黑黑黑          夜     夜 夜"<<endl;
	cout<<"    红      红               黑              夜夜   夜  夜 夜"<<endl;
	cout<<"  红        红          黑黑黑黑黑黑       夜  夜 夜 夜   夜"<<endl;
	cout<<"红          红               黑                夜      夜夜"<<endl;
	cout<<"   红       红         黑黑黑黑黑黑黑          夜       夜"<<endl;
	cout<<"      红    红                                 夜      夜 夜"<<endl;
	cout<<"   红       红         黑  黑  黑  黑          夜    夜     夜"<<endl;
	cout<<"红红    红红红红红    黑   黑  黑   黑        夜   夜         夜"<<endl;
	cout<<"\n                   （按 Enter 键开始游戏）\n";
	getch();
}
void delay(int n)//制作一个延时圈，其中n是循环次数
{
	for(int i = 0; i < n; i++)
	{
		cout << '|' << '\b';
		Sleep(250);//延时250ms
		cout << '/' << '\b';
		Sleep(250);
		cout << '-' << '\b';
		Sleep(250);
		cout << '\\' << '\b';
		Sleep(250);
	}
}
int select_officer(player *p, int n) //制作一个选举村长的函数
{
	cout << "开始选举村长：（按Enter键开始）" << endl;
	getch();//可以暂停的
	int *vote = new int[n]; //开辟一个n长度的数组，用于记录投票数
	int j, cnt = 0, max_vote=0, officer_point=0;
	for(int i = 0; i < n; i++)
	{
		if(p[i].alive == true)
			p[i].able = true;
	}
	do//开始投票
	{
		cnt=0;
		for(int i = 0; i < n; i++)
			vote[i] = 0;
		for(int i = 0; i < n; i++)
		{
			if(p[i].alive == false)
				continue;
			do
			{
				j = rand() % n;
			}
			while((p[j].alive == false) || ( p[j].able == false));
			vote[j]++;
			cout << i + 1 << "号玩家投票给";
			delay(1);
			cout << j + 1 << "号玩家。" << endl;
			getch();
		}
		//寻找最大值
		max_vote = vote[0];
		for(int i = 1; i < n; i++)
		{
			if(max_vote == vote[i])
				cnt++;
			if(max_vote < vote[i])
			{
				cnt = 0;
				max_vote = vote[i];
				officer_point = i;
			}
		}
		if(cnt)
		{
			cout << "\n有票数相同的玩家，按Enter键重选：\n\n";
			getch();
		}
		for(int i = 0; i < n; i++)
		{
			if(vote[i] != max_vote)
				p[i].able = false;
		}
	}
	while(cnt); //当这个计数器不为0时，说明有不止一个最高票数的，要继续分配
	cout << "投票结束，" << officer_point + 1 << "号玩家当选村长！\n" << endl;
	delete []vote;
	p[officer_point].village = true;
	return officer_point;
}
void status(player *p, int n, int &ye) //游戏进程
{
	if(ye == 1)
		cout << "进入红夜" << endl;
	else if(ye == 0)
		cout << "进入黑夜" << endl;
	else
		cout << "白天：" << endl;
	for(int i = 0; i < n; i++)
	{
		if(p[i].village == true)
			cout << i + 1 << "号玩家是村长。\n";
		if(p[i].alive == false)
		{
			cout << i + 1 << "号玩家被放逐，身份是";
			if(p[i].village == true)
				cout << "村长";
			if(p[i].id == 1)
				cout << "红牌\n";
			else
				cout << "黑牌\n";
		}
	}
	cout << "================================";
}
int officer_options(player *p, int n, int &ye) //村长选项
{
	cout << "================================";
	cout << "\n状态：";
	status(p, n, ye);
	cout << "\n进入村长选项：\n";
	cout << "1 天黑请闭眼\n";
	cout << "2 请玩家睁眼\n";
	cout << "3 天亮了\n";
	cout << "请选择：";
	int op;//最终输出的整型命令
	char c;//出入的字符命令
	cin >> c;
	switch(c)
	{
		case'1':
			op = 1;
			break;
		case'2':
			op = 2;
			break;
		case'3':
			op = 3;
			break;
		default:
			cout << "错误命令，请重新输入。" << endl;
	}
	return op;
}
int night(player *p, int n, int op, int &ye) //进入夜晚，返回村长的增票 
{
	int num = 0; //睁眼玩家计数器
	if(op == 1) //选择了“天黑请闭眼”
	{
		for(int i = 0; i < n; i++)
			p[i].eye = false; //让所有人闭眼
		delay(4);
		cout << "\n所有玩家都闭上眼睛。。。\n";
		ye = rand() % 2; //随机选择红黑夜
		if(ye == 1)
			cout << "现在进入红夜。。。" << endl;
		else
		cout << "现在进入黑夜。。。" << endl;
		return 0;
	}
	if(op==2)//玩家请睁眼 
	{
		if(ye==1)//红夜 
		{
			delay(2);
			for(int i=0;i<n;i++)
			{
				if(p[i].alive==false)
				continue;
				p[i].eye=rand()%2;
				if((p[i].eye==1)&&(p[i].id==1))
				num++;
				if(p[i].eye==1)
				cout<<i+1<<' ';
			}
			cout<<"号玩家睁眼了\n";
			if(num%2==0)
			return 1;
			else
			return 0;
		}
		if(ye==0)
		{
			delay(2);
			for(int i=0;i<n;i++)
			{
				if(p[i].alive==false)
				continue;
				if((p[i].eye==1)&&(p[i].id==0))
				num++;
				if(p[i].eye==1)
				cout<<i+1<<' ';
			}
			cout<<"号玩家睁眼了\n";
			if(num%2==0)
			return 1;
			else
			return 0;
		}
	}
}
void speak_left(int point, int n, player *p)
{
	cout << "从左手边开始发言\n";
	for(int i = point - 1; i >= 0; i--)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "号玩家发言";
		delay(2);
		getch();
		cout << "完毕" << endl;
	}
	for(int i = n - 1; i >= point; i--)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "号玩家发言";
		delay(2);
		getch();
		cout << "完毕" << endl;
	}
}
void speak_right(int point, int n, player *p)
{
	cout << "从右手边开始发言\n";
	for(int i = point + 1; i < n; i++)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "号玩家发言";
		delay(2);
		getch();
		cout << "完毕" << endl;
	}
	for(int i = 0; i <= point; i++)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "号玩家发言";
		delay(2);
		getch();
		cout << "完毕" << endl;
	}
}
int kickout(int point, int n, player *p) //投票驱逐玩家
{
	delay(2);
	cout << "\n现在开始投票，按Enter继续\n\n";
	getch();
	double *piao = new double[n];
	double max_piao;
	int t, cnt, num = 0;
	do
	{
		cnt = 0;
		for(int i = 0; i < n; i++)
			piao[i] = 0;
		for(int i = 0; i < n; i++)
		{
			if(p[i].alive == false)
				continue;
			do
			{
				t = rand() % n;
			}
			while((p[t].alive == false) || (t == i));
			if(p[i].village==false)
			piao[t]++;
			else
			piao[t]+=p[i].piao;
			cout << i + 1 << "号玩家";
			delay(1);
			cout << "投票完毕。\n";
			getch();
		}
		max_piao = piao[0];
		for(int i = 1; i < n; i++)
		{
			if(max_piao == piao[i])
				cnt++;
			if(max_piao < piao[i])
			{
				cnt = 0;
				max_piao = piao[i];
				num = i;
			}
		}
		if(cnt)
		{
			cout << "\n出现多名玩家票数同等最高，需要重新选票\n" << endl;
			getch();
		}
	}
	while(cnt);
	cout << num + 1 << "号玩家以" << max_piao << "票被驱逐！\n\n";
	delete []piao;
	//被放逐的标记为死亡
	p[num].alive = false;
	p[num].village = false;
	return num;
}
int main()
{
	title();
	cout<<"请输入玩家个数：";
	int n, red, black, random; //玩家个数,红黑人数,随机数变量
	cin >> n;
	srand((unsigned)time(NULL));//随机数种子化
	player *p = new player[n]; //开一个玩家数组
	//分配红黑人数。如果奇数，红牌比黑牌多1，否则平分
	if(n % 2)
	{
		black = n / 2;
		red = black + 1;
	}
	else
		red = black = n / 2;
	//分配身份，并将所有玩家初始化为平民
	for(int i = 0; i < n; i++)
	{
		p[i].no = i + 1;
		p[i].alive = true;
		p[i].village = false;
		p[i].eye = true;
		p[i].able = true;
		random = rand() % 2; //随机红黑牌
		if((random == 1) && (red > 0)) //随机到1且还有剩余红牌
		{
			p[i].id = 1;
			red--;
		}
		else if(black > 0) //随机到0且有剩余的黑牌
		{
			p[i].id = 0;
			black--;
		}
		else//奇数玩家时剩余的那个必定是红牌
		{
			p[i].id = 1;
			red--;
		}
	}
	//选举村长
	int point = select_officer(p, n); //标记村长的位置
	cout << "\n您将作为村长操作游戏\n\n";
	//此时我们将红黑牌计数器复位，用于统计在场当前红黑存活人数
	if(n % 2)
	{
		red = n / 2 + 1;
		black = n / 2;
		p[point].piao = 0.5;
	}
	else
	{
		red = black = n / 2;
		p[point].piao = 1.5;
	}
	int ye = 2;
	while(red > 0 && black > 0) //两方有一方全被驱逐游戏结束
	{
		if((red + black) % 2)
			p[point].piao = 0.5;
		else
			p[point].piao = 1.5;
		//可视化游戏进程
//		for(int i=0;i<n;i++)
//		cout<<p[i].id<<' '<<p[i].alive<<' '<<p[i].village<<' '<<p[i].eye<<' '<<p[i].piao<<endl;
		if(p[point].alive == false) //村长死了就得重新选村长
			point = select_officer(p, n);
		int op = officer_options(p, n,ye);
		if(op == 1)
			night(p, n,op,ye);
		if(op == 2)
		{
			if(night(p, n,op,ye)== true)
				p[point].piao = 1;
		}
		if(op == 3)
		{
			ye=2;
			cout<<"================================";
			cout<<"\n状态：";
			status(p,n,ye);
			cout << "\n天亮请睁眼,玩家准备发言：\n";
			cout << "请村长决定左手还是右手发言：" << endl;
			cout << "左手请按L，右手请按R";
			char c;
			cin >> c;
			switch(c)
			{
				case'l':
				case'L':
					speak_left(point, n, p);
					break;
				case'r':
				case'R':
					speak_right(point, n, p);
					break;
				default:
					break;
			}
			int result = kickout(point, n, p);
			if(p[result].id == 1)
				red--;
			else
				black--;
		}
	}
	if(red==0)
	cout<<"==============所有红牌玩家被放逐！==============\n";
	if(black==0)
	cout<<"==============所有黑牌玩家被放逐！==============\n";
	cout<<"GGGGG    A    M   M EEEE   OO  V    V EEEE RRR\n";
	cout<<"G       A A   MM MM E     O  O  V  V  E    R  R\n";
	cout<<"G  GG  A   A  M M M EEE   O  O  V  V  EEE  RRR\n";
	cout<<"G   G  AAAAA  M   M E     O  O   VV   E    R R\n";
	cout<<"GGGGG A     A M   M EEEE   OO    V    EEEE R  R\n";
	delete []p;
	return 0;
}
