#include "calendar.h"
int month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31 };
int rili[6][7];
pos position[6][7];
int whatTheDay(int y, int m, int d)
{
	int iWeek;
	int result = 0;
	if (m <= 2) {
		m += 12;
		y--;
	}	
	iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
	switch (iWeek)
	{
		case 0: result = 1;break;
		case 1: result = 2;break;
		case 2: result = 3;break;
		case 3: result = 4;break;
		case 4: result = 5;break;
		case 5: result = 6;break;
		case 6: result = 7;break;
	}
	return result;
}
int isRunNian(int y) {
	if ((y % 4 == 0 && y % 400 != 0) || (y % 400 == 0 && y % 100 == 0))
		return 1;
	else
		return 0;
}
void generate(int y, int m) {
	int i, j;
	int first;
	int count;
	int day = 1;
	if (isRunNian(y))
		month[2] = 29;
	for (i = 0;i < 6;i++)
		for (j = 0;j < 7;j++)
			rili[i][j] = 0;
	first = whatTheDay(y, m, 1);
	count = month[m];
	i = 0;
	while (count--) {
		rili[i][first % 7] = day;
		day++;
		if ((first + 1) % 7 == 0)i++;
		first++;
	}
}

void InitPosition(){
	int height = 35, widght = 35;
	int first_y = 8, first_x = 90;
	int i, j;
	for(i = 0; i < 6; i ++){
		for(j = 0; j < 7; j ++){
			position[i][j].y = first_x + (i * widght);
			position[i][j].x = first_y + (j * height);
		}
	}
}

void show(int year, int month){
	int i, j;
	int wid = 34;
	int first_x = 10, first_y = 55;
	int y = calendar.w_year, m = calendar.w_month, d = calendar.w_date;
	generate(year, month);
	LCD_ShowString(65,30,120,16,16,"Present:     - ");
	LCD_ShowxNum(135, 30, year, 4, 16, 0);
	LCD_ShowxNum(183, 30, month, 2, 16, 1);
	LCD_ShowString(first_x,first_y,wid,16,16,"Sun");
	LCD_ShowString(first_x + 1*wid,first_y,wid,16,16,"Mon");
	LCD_ShowString(first_x + 2*wid,first_y,wid,16,16,"Tus");
	LCD_ShowString(first_x + 3*wid,first_y,wid,16,16,"Wed");
	LCD_ShowString(first_x + 4*wid,first_y,wid,16,16,"Tru");
	LCD_ShowString(first_x + 5*wid,first_y,wid,16,16,"Fri");
	LCD_ShowString(first_x + 6*wid,first_y,wid,16,16,"Sat");
	for(i = 0; i < 6; i ++){
		for(j = 0; j < 7; j ++){
			if(rili[i][j] != 0){
				if(year == y && month == m && rili[i][j] == d) {
					POINT_COLOR=BLACK;
					LCD_ShowxNum(position[i][j].x, position[i][j].y, rili[i][j], 2, 16, 0);
					POINT_COLOR=BLUE;
				}
				else
					LCD_ShowxNum(position[i][j].x, position[i][j].y, rili[i][j], 2, 16, 0);
				
			}
		}
	}
}

