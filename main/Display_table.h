
#define table_w 160
#define table_h 160
unsigned short display_table[table_h][table_w] = {0};

int table_x = 0,table_y = 0;
int display_x=0,display_y=0;

#include "table_basic.h"

word color_sub(word A,word B);
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
}
void table_set_acc(){
	int k=0;
	for(table_y = 80 ; table_y < 160 ; table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = (word)pgm_read_word(winter+k);
			k++;
		}
	}
}
void table_set_bio(){
	int k=0;
	for(table_y = 80 ; table_y < 160 ; table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = (word)pgm_read_word(bio+k);
			k++;
		}
	}
}
void table_set_setting(){
	int k=0;
	for(table_y = 80 ; table_y < 160 ; table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = (word)pgm_read_word(setting+k);
			k++;
		}
	}
}
void table_set_temp(){
	int k=0;
	for(table_y = 80 ; table_y < 160 ; table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = (word)pgm_read_word(rainbow+k);
			k++;
		}
	}
}

void display_frame()
{
	u16 i,j;
	int k=0;
	uint8_t line;
  word color;
	for(i=80;i<160;i++)
	{
		for(j=0;j<160;j++)
		{
      color = color_sub(display_table[i][j],pgm_read_word(frame_popup+k));
			display_table[i][j] = color;
			k++;
		}
	}
}
word color_sub(word A,word B){
  unsigned short A_B=0,A_G=0,A_R=0,B_B=0,B_G=0,B_R=0;
  unsigned short sub_R=0,sub_G=0,sub_B=0;
  A_B = A<<11;
  A_B = A_B >> 11;
  A_G = A<<5;
  A_G = A_G >> 10;
  A_R = A>>11;
  B_B = B<<11;
  B_B = B_B>>11;
  B_G = B<<5;
  B_G = B_G>>10;
  B_R = B>>11;
  if(A_R <= B_R) sub_R = 0;
  else sub_R = A_R-B_R;sub_R = sub_R<<11;
  if(A_G <= B_G) sub_G = 0;
  else sub_G = A_G-B_G;sub_G = sub_G<<5;
  if(A_B <= B_B) sub_B = 0;
  else sub_B = A_B-B_B;
  return (sub_R+sub_G+sub_B);
}
