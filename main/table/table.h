
#define table_w 160
#define table_h 160
unsigned short display_table[table_h][table_w] = {0};

int table_x = 0,table_y = 0;
int display_x=0,display_y=0;

#include "table_basic.h"

word color_sub(word A,word B){ //RGB => 5/6/5 16bit
	unsigned short A_B=0,A_G=0,A_R=0,B_B=0,B_G=0,B_R=0;
	unsigned short sub_R=0,sub_G=0,sub_B=0;
	A_R = A & 0xF800;
	A_G = A & 0x07E0;
	A_B = A & 0x001F;
	B_R = B & 0xF800;
	B_G = B & 0x07E0;
	B_B = B & 0x001F;
	
	if(A_R <= B_R) sub_R = 0;
	else sub_R = A_R-B_R;
	if(A_G <= B_G) sub_G = 0;
	else sub_G = A_G-B_G;
	if(A_B <= B_B) sub_B = 0;
	else sub_B = A_B-B_B;
	return (sub_R+sub_G+sub_B);
}
word color_sum(word A,word B){ //RGB => 5/6/5 16bit
	unsigned short A_B=0,A_G=0,A_R=0,B_B=0,B_G=0,B_R=0;
	unsigned short sub_R=0,sub_G=0,sub_B=0;
	A_R = A & 0xF800;
	A_G = A & 0x07E0;
	A_B = A & 0x001F;
	B_R = B & 0xF800;
	B_G = B & 0x07E0;
	B_B = B & 0x001F;
	
	sub_R = A_R+B_R;
	if(sub_R > 0xF800) sub_R = 0xF800;
	sub_G = A_G+B_G;
	if(sub_G > 0x07E0) sub_G = 0x07E0;
	sub_B = A_B+B_B;
	if(sub_B > 0x001F) sub_B = 0x001F;
	
	return (sub_R+sub_G+sub_B);
}
void initial_table(){
	for(table_y = 0 ; table_y<80 ;table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = BLACK;
		}
	}
	for(table_y = 80 ; table_y < 160 ; table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = BLUE;
		}
	}
	table_y=0;
	table_x=0;
	for (int i=0;i<160;i++)
	{
		Xpin[i]=1;
		Ypin[i]=1;
		Zpin[i]=1;
	}
}

void print_display(int x, int y){
	u16 i,j;
	LCD_CS_Clr();
	SPI.beginTransaction(mySPISettings);
	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
	LCD_WR_REG(0x2c);
	for(i=y;i<LCD_H+y;i++)
	{
		for(j=x;j<LCD_W+x;j++)
		{
			LCD_WR_DATA((word)pgm_read_word(display_table[i]+j));
		}
	}
	SPI.endTransaction();
	LCD_CS_Set();
	delay(1);
}

void table_set_frame(word x, word y ,word frame_size_w, word frame_size_h,const short unsigned A[])
{
	u16 i,j;
	int k=0;
	for(i=y;i<y+frame_size_h;i++)
	{
		for(j=x;j<x+frame_size_w;j++)
		{
			display_table[i][j] = color_sub(display_table[i][j],pgm_read_word(A+k));
			k++;
		}
	}
}
void table_set_background(word x, word y ,word frame_size_w, word frame_size_h,const short unsigned A[])
{
	u16 i,j;
	int k=0;
	for(i=y;i<y+frame_size_h;i++)
	{
		for(j=x;j<x+frame_size_w;j++)
		{
			display_table[i][j] = (word)pgm_read_word(A+k);
			k++;
		}
	}
}
void table_set_background(word x, word y ,word frame_size_w, word frame_size_h,word A)
{
	u16 i,j;
	int k=0;
	for(i=y;i<y+frame_size_h;i++)
	{
		for(j=x;j<x+frame_size_w;j++)
		{
			display_table[i][j] = A;
			k++;
		}
	}
}

void loadTableSetBackground(word x, word y ,word frame_size_w, word frame_size_h, unsigned short array[])
{
	u16 i,j;
	int k=0;
	for(i=y;i<y+frame_size_h;i++)
	{
		for(j=x;j<x+frame_size_w;j++)
		{
			display_table[i][j] = array[k];
			k++;
		}
	}
}
//PAGE
#include "health.h"
#include "motion.h"
#include "setting.h"
#include "temperature.h"
#include "folder.h"
