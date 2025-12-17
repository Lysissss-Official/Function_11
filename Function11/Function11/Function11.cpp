#include <graphics.h>
#include <iostream>
#include <thread>

int DLTX = 100;
int DLTY = 100;
int RDOX = 800;
int RDOY = 800;
int LIMIT = 16;

double num_in, num_in2;
double ans;
double l_r;
int user_limit;
double mem[10001];
bool flag;
int tmp_x, tmp_y;
int ori_x, ori_y;

ExMessage m;

double _abs(double opt)
{
	return opt > 0.00 ? opt : -opt;
}

void dfs(double x, double y, int steps)
{
	if (steps > LIMIT)
		return;
	putpixel(x * RDOX + DLTX, y * RDOY + DLTY, RGB(255,255,255));
	mem[(int)(x * 10000.00)] = y;
	//std::cerr << x << " " << y << std::endl;
	//Sleep(10);
	//getchar();
	dfs(x/10.00, y/2.00, steps + 1);
	dfs(1.00 - x/10.00,1 - y/2.00, steps + 1);
	return;
}

void dfs2(double x, double y, int steps)
{
	if (steps > user_limit)
		return;
	
	if (_abs(x - num_in) < l_r)
	{
		std::cerr << _abs(x - num_in) << std::endl;
		ans = y;
		l_r = _abs(x - num_in);
	}
	dfs2(x / 10.00, y / 2.00, steps + 1);
	dfs2(1.00 - x / 10.00, 1 - y / 2.00, steps + 1);
	return;
}

void dfs11(double xl, double xr, double yl, double yr, int steps)
{
	if (steps > LIMIT)
		return;
	double y = (yl + yr) / 2.00;
	line((xl + (xr - xl) / 10.00) * RDOX + DLTX, y * RDOY + DLTY, (xr - (xr - xl) / 10.00) * RDOX + DLTX, y * RDOY + DLTY);
	dfs11(xl, xl + (xr - xl) / 10.00, yl, y, steps + 1);
	dfs11(xr - (xr - xl) / 10.00, xr, y, yr, steps + 1);
}

void mouse_catch()
{
	while (true)
	{
		m = getmessage(EX_MOUSE);

		if (WM_MOUSEMOVE)
		{
			TCHAR s[32];
			swprintf_s(s, _T("%llf"), (m.x - DLTX)/(double)RDOX);
			outtextxy(20, 20, s);
			swprintf_s(s, _T("%llf"), (m.y - DLTY) / (double)RDOY);
			outtextxy(20, 50, s);
		}
	}
}

void gui_fresh()
{
	while (true)
	{
		if (m.mbutton)
		{
			while (m.mbutton)
			{
				if (flag)
				{
					ori_x = m.x;
					ori_y = m.y;
					flag = false;
				}
				tmp_x = m.x;
				tmp_y = m.y;
				DLTX = DLTX + (tmp_x - ori_x);
				DLTY = DLTY + (tmp_y - ori_y);
				cleardevice();
				line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 1 * RDOX + DLTX, 0 * RDOY + DLTY);
				line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 0 * RDOX + DLTX, 1 * RDOY + DLTY);
				dfs(0.50, 0.50, 1);
				//dfs11(0.00, 1.00, 0.00, 1.00, 1);
				DLTX = DLTX - (tmp_x - ori_x);
				DLTY = DLTY - (tmp_y - ori_y);
				//Sleep(1);
			}
			DLTX = DLTX + (m.x - ori_x);
			DLTY = DLTY + (m.y - ori_y);
			flag = true;
			cleardevice();
			line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 1 * RDOX + DLTX, 0 * RDOY + DLTY);
			line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 0 * RDOX + DLTX, 1 * RDOY + DLTY);
			dfs(0.50, 0.50, 1);
			//dfs11(0.00, 1.00, 0.00, 1.00, 1);
		}
		if (m.lbutton)
		{
			RDOX *= 1.01;
			RDOY *= 1.01;
			cleardevice();
			line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 1 * RDOX + DLTX, 0 * RDOY + DLTY);
			line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 0 * RDOX + DLTX, 1 * RDOY + DLTY);
			dfs(0.50, 0.50, 1);
			//dfs11(0.00, 1.00, 0.00, 1.00, 1);
			Sleep(1);
		}
		if (m.rbutton)
		{
			RDOX /= 1.01;
			RDOY /= 1.01;
			cleardevice();
			line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 1 * RDOX + DLTX, 0 * RDOY + DLTY);
			line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 0 * RDOX + DLTX, 1 * RDOY + DLTY);
			dfs(0.50, 0.50, 1);
			//dfs11(0.00, 1.00, 0.00, 1.00, 1);
			Sleep(1);
		}
		//Sleep(1);
	}
}

// 主函数
int main()
{
	initgraph(1000, 1000, EX_SHOWCONSOLE);
	setlinecolor(RGB(63,63,63));
	line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 1 * RDOX + DLTX, 0 * RDOY + DLTY);
	line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 0 * RDOX + DLTX, 1 * RDOY + DLTY);
	//dfs(0.50, 0.50, 1);
	setlinecolor(RGB(255, 255, 255));
	dfs11(0.00, 1.00, 0.00, 1.00, 1);
	setlinecolor(RGB(63, 63, 63));
	outtextxy(20, 20, _T("这里是x坐标"));
	outtextxy(20, 50, _T("这里是y坐标"));
	outtextxy(300, 160, _T("--- K e y   i n f o ---"));
	outtextxy(300, 190, _T("长按鼠标左键放大"));
	outtextxy(300, 220, _T("长按鼠标中键拖动"));
	outtextxy(300, 250, _T("长按鼠标右键缩小"));
	outtextxy(300, 310, _T("在后台窗口输入x可查询y"));
	outtextxy(300, 340, _T("输入格式：分子 分母 递归深度"));
	outtextxy(300, 370, _T("示例：输入x的值(NUM_IN>>>)时键入2024 2025,输入递归深度(DEPTH>>>)时键入16"));
	outtextxy(300, 400, _T("示例：输出f(2024/2025)的值即ANS=0.9375(15/16)"));
	outtextxy(300, 430, _T("支持小数输入，如0.333 1，即求f(0.333)"));
	outtextxy(300, 460, _T("单击以继续..."));
	while (true)
	{
		m = getmessage(EX_MOUSE);
		if (m.lbutton)
		{
			break;
		}
	}
	Sleep(100);
	cleardevice();
	line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 1 * RDOX + DLTX, 0 * RDOY + DLTY);
	line(0 * RDOX + DLTX, 0 * RDOY + DLTY, 0 * RDOX + DLTX, 1 * RDOY + DLTY);
	dfs(0.50, 0.50, 1);

	//for (double i = 0.10; i <= 0.90; i = i + 0.001)
	//{
	//	dfs(i, 0.50, 1);
	//}
	//dfs(0.00, 0.00, 1);
	//dfs(1.00, 1.00, 1);
	//dfs(1.00/11.00, 1.00/3.00, 1);
	//dfs(10.00 / 11.00, 2.00 / 3.00, 1);

	std::thread t1(mouse_catch);
	std::thread t2(gui_fresh);

	while (true)
	{
		std::cout << "NUM_IN:" << std::endl << ">>> ";
		std::cin >> num_in >> num_in2;
		num_in = num_in / num_in2;
		std::cout << "DFS_DEPTH_LIMIT:" << std::endl << ">>> ";
		std::cin >> user_limit;

		ans = -1;
		l_r = 999999.00;
		dfs2(0.50, 0.50, 1);
		std::cout << "dfs2(...): ANS= " << ans << " L-R= " << l_r << std::endl;
	}

	closegraph();
	return 0;
}
