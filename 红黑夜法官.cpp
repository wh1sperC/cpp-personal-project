//���ҹ����
/*��Ϸ���򣺣�����Ҫ��
�趨���������n
���������Ϊż�������������������ݸ�ռһ�룻��Ϊ�������������ݶ�1��
ʹ��ָ����Χ����������췽�������ι����1-n֮�䲻�ظ�������������ճ��ֵ������������ҷ���ݣ�����ҵ����
����������������2���������䡣
��һ�죬��1-n�����˳���ԣ���Ҫ��ʾ��ǰ�������λ�á�һ�ַ��Ժ��1-n��˳��ͶƱѡ�ٴ峤��
��Ʊ������ҵ�ѡ�峤����������Ϊż�����峤ӵ��1.5Ʊ��������Ϊ�������峤ӵ��0.5Ʊ����Ʊ�������������ã�
���죺�峤�����Ӵ峤��߻����ұ߿�ʼ���Ե�˳�򣬷���˳�򹹳�Ϊk-1~�峤k~k+1�Ļػ���
��DOS����Ҫ��ʾ��ǰ�����˵�λ�ã����÷������Ѿ�����Ҫ��������������ܹ����ӻ���������뷢��λ�á�
ʹ�������߼����л���һ���˷��ԡ�������1-n����ҽ�������ͶƱ����Ʊ�����˱��������Ϸ��������ʾ��ݣ�
���峤��������Ҫ�ƽ���һ�δ峤��
ҹ����������ҹ���ҹ��������ҿ����������ۡ�
��ҹʱ�����۵ĺ���Ϊż����ڶ���峤ӵ��1Ʊ����ҹʱ�����۵ĺ���Ϊż����ڶ���峤ӵ��1Ʊ
��Ϸ���������еĺ��ƻ������еĺ��Ʊ�����
��1��ʹ��DOSʵ�ֿ��ӻ���Ϸ���̣�������60������
��2���Զ������ʾ��Ϸ���̣������ҹ�������ҹ�������ˣ�ĳĳ��ұ��������ΪX�ȡ�
������70������
��3��MFC��QT�����Ѻÿ��ӻ���������80������
��4����������ݽṹ�ܹ�ʹ���ж������ͶƱ���ܸ��ӱ�ݣ����Ҹ��ݲ�ͬ�Ĺ���ʹ�ò�ͬ�����ݽṹ�洢��Ϸ���ݡ�
������85������
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
struct player//����һ����ҵ���Ϣ
{
	int no, id, eye; //�����ţ����:1r0b����1��0��
	bool alive, village, able; //��Ҵ��1����1��0Ϊ�峤,��1��0���Ա�ѡΪ�峤
	double piao;//��ҵ�Ʊ��
};
void title(void)
{
	cout<<"    ��                                             ҹ"<<endl;
	cout<<"  ��    ������     �ںںںںںں�               ҹ"<<endl;
	cout<<"��          ��         �� �� �� �� ��      ҹҹҹҹҹҹҹҹҹҹ"<<endl;
	cout<<"  ��        ��         ��  �ںں�  ��           ҹ      ҹ"<<endl;
	cout<<"    ��      ��         �ںںںںںں�          ҹ     ҹ ҹ"<<endl;
	cout<<"    ��      ��               ��              ҹҹ   ҹ  ҹ ҹ"<<endl;
	cout<<"  ��        ��          �ںںںںں�       ҹ  ҹ ҹ ҹ   ҹ"<<endl;
	cout<<"��          ��               ��                ҹ      ҹҹ"<<endl;
	cout<<"   ��       ��         �ںںںںںں�          ҹ       ҹ"<<endl;
	cout<<"      ��    ��                                 ҹ      ҹ ҹ"<<endl;
	cout<<"   ��       ��         ��  ��  ��  ��          ҹ    ҹ     ҹ"<<endl;
	cout<<"���    ������    ��   ��  ��   ��        ҹ   ҹ         ҹ"<<endl;
	cout<<"\n                   ���� Enter ����ʼ��Ϸ��\n";
	getch();
}
void delay(int n)//����һ����ʱȦ������n��ѭ������
{
	for(int i = 0; i < n; i++)
	{
		cout << '|' << '\b';
		Sleep(250);//��ʱ250ms
		cout << '/' << '\b';
		Sleep(250);
		cout << '-' << '\b';
		Sleep(250);
		cout << '\\' << '\b';
		Sleep(250);
	}
}
int select_officer(player *p, int n) //����һ��ѡ�ٴ峤�ĺ���
{
	cout << "��ʼѡ�ٴ峤������Enter����ʼ��" << endl;
	getch();//������ͣ��
	int *vote = new int[n]; //����һ��n���ȵ����飬���ڼ�¼ͶƱ��
	int j, cnt = 0, max_vote=0, officer_point=0;
	for(int i = 0; i < n; i++)
	{
		if(p[i].alive == true)
			p[i].able = true;
	}
	do//��ʼͶƱ
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
			cout << i + 1 << "�����ͶƱ��";
			delay(1);
			cout << j + 1 << "����ҡ�" << endl;
			getch();
		}
		//Ѱ�����ֵ
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
			cout << "\n��Ʊ����ͬ����ң���Enter����ѡ��\n\n";
			getch();
		}
		for(int i = 0; i < n; i++)
		{
			if(vote[i] != max_vote)
				p[i].able = false;
		}
	}
	while(cnt); //�������������Ϊ0ʱ��˵���в�ֹһ�����Ʊ���ģ�Ҫ��������
	cout << "ͶƱ������" << officer_point + 1 << "����ҵ�ѡ�峤��\n" << endl;
	delete []vote;
	p[officer_point].village = true;
	return officer_point;
}
void status(player *p, int n, int &ye) //��Ϸ����
{
	if(ye == 1)
		cout << "�����ҹ" << endl;
	else if(ye == 0)
		cout << "�����ҹ" << endl;
	else
		cout << "���죺" << endl;
	for(int i = 0; i < n; i++)
	{
		if(p[i].village == true)
			cout << i + 1 << "������Ǵ峤��\n";
		if(p[i].alive == false)
		{
			cout << i + 1 << "����ұ����������";
			if(p[i].village == true)
				cout << "�峤";
			if(p[i].id == 1)
				cout << "����\n";
			else
				cout << "����\n";
		}
	}
	cout << "================================";
}
int officer_options(player *p, int n, int &ye) //�峤ѡ��
{
	cout << "================================";
	cout << "\n״̬��";
	status(p, n, ye);
	cout << "\n����峤ѡ�\n";
	cout << "1 ��������\n";
	cout << "2 ���������\n";
	cout << "3 ������\n";
	cout << "��ѡ��";
	int op;//�����������������
	char c;//������ַ�����
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
			cout << "����������������롣" << endl;
	}
	return op;
}
int night(player *p, int n, int op, int &ye) //����ҹ�����ش峤����Ʊ 
{
	int num = 0; //������Ҽ�����
	if(op == 1) //ѡ���ˡ��������ۡ�
	{
		for(int i = 0; i < n; i++)
			p[i].eye = false; //�������˱���
		delay(4);
		cout << "\n������Ҷ������۾�������\n";
		ye = rand() % 2; //���ѡ����ҹ
		if(ye == 1)
			cout << "���ڽ����ҹ������" << endl;
		else
		cout << "���ڽ����ҹ������" << endl;
		return 0;
	}
	if(op==2)//��������� 
	{
		if(ye==1)//��ҹ 
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
			cout<<"�����������\n";
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
			cout<<"�����������\n";
			if(num%2==0)
			return 1;
			else
			return 0;
		}
	}
}
void speak_left(int point, int n, player *p)
{
	cout << "�����ֱ߿�ʼ����\n";
	for(int i = point - 1; i >= 0; i--)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "����ҷ���";
		delay(2);
		getch();
		cout << "���" << endl;
	}
	for(int i = n - 1; i >= point; i--)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "����ҷ���";
		delay(2);
		getch();
		cout << "���" << endl;
	}
}
void speak_right(int point, int n, player *p)
{
	cout << "�����ֱ߿�ʼ����\n";
	for(int i = point + 1; i < n; i++)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "����ҷ���";
		delay(2);
		getch();
		cout << "���" << endl;
	}
	for(int i = 0; i <= point; i++)
	{
		if(p[i].alive == false)
			continue;
		cout << i + 1 << "����ҷ���";
		delay(2);
		getch();
		cout << "���" << endl;
	}
}
int kickout(int point, int n, player *p) //ͶƱ�������
{
	delay(2);
	cout << "\n���ڿ�ʼͶƱ����Enter����\n\n";
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
			cout << i + 1 << "�����";
			delay(1);
			cout << "ͶƱ��ϡ�\n";
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
			cout << "\n���ֶ������Ʊ��ͬ����ߣ���Ҫ����ѡƱ\n" << endl;
			getch();
		}
	}
	while(cnt);
	cout << num + 1 << "�������" << max_piao << "Ʊ������\n\n";
	delete []piao;
	//������ı��Ϊ����
	p[num].alive = false;
	p[num].village = false;
	return num;
}
int main()
{
	title();
	cout<<"��������Ҹ�����";
	int n, red, black, random; //��Ҹ���,�������,���������
	cin >> n;
	srand((unsigned)time(NULL));//��������ӻ�
	player *p = new player[n]; //��һ���������
	//������������������������ƱȺ��ƶ�1������ƽ��
	if(n % 2)
	{
		black = n / 2;
		red = black + 1;
	}
	else
		red = black = n / 2;
	//������ݣ�����������ҳ�ʼ��Ϊƽ��
	for(int i = 0; i < n; i++)
	{
		p[i].no = i + 1;
		p[i].alive = true;
		p[i].village = false;
		p[i].eye = true;
		p[i].able = true;
		random = rand() % 2; //��������
		if((random == 1) && (red > 0)) //�����1�һ���ʣ�����
		{
			p[i].id = 1;
			red--;
		}
		else if(black > 0) //�����0����ʣ��ĺ���
		{
			p[i].id = 0;
			black--;
		}
		else//�������ʱʣ����Ǹ��ض��Ǻ���
		{
			p[i].id = 1;
			red--;
		}
	}
	//ѡ�ٴ峤
	int point = select_officer(p, n); //��Ǵ峤��λ��
	cout << "\n������Ϊ�峤������Ϸ\n\n";
	//��ʱ���ǽ�����Ƽ�������λ������ͳ���ڳ���ǰ��ڴ������
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
	while(red > 0 && black > 0) //������һ��ȫ��������Ϸ����
	{
		if((red + black) % 2)
			p[point].piao = 0.5;
		else
			p[point].piao = 1.5;
		//���ӻ���Ϸ����
//		for(int i=0;i<n;i++)
//		cout<<p[i].id<<' '<<p[i].alive<<' '<<p[i].village<<' '<<p[i].eye<<' '<<p[i].piao<<endl;
		if(p[point].alive == false) //�峤���˾͵�����ѡ�峤
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
			cout<<"\n״̬��";
			status(p,n,ye);
			cout << "\n����������,���׼�����ԣ�\n";
			cout << "��峤�������ֻ������ַ��ԣ�" << endl;
			cout << "�����밴L�������밴R";
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
	cout<<"==============���к�����ұ�����==============\n";
	if(black==0)
	cout<<"==============���к�����ұ�����==============\n";
	cout<<"GGGGG    A    M   M EEEE   OO  V    V EEEE RRR\n";
	cout<<"G       A A   MM MM E     O  O  V  V  E    R  R\n";
	cout<<"G  GG  A   A  M M M EEE   O  O  V  V  EEE  RRR\n";
	cout<<"G   G  AAAAA  M   M E     O  O   VV   E    R R\n";
	cout<<"GGGGG A     A M   M EEEE   OO    V    EEEE R  R\n";
	delete []p;
	return 0;
}
