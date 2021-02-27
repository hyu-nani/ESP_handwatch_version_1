﻿
#define table_w 160
#define table_h 160
unsigned short display_table[table_h][table_w] = {0};

int table_x = 0,table_y = 0;
int display_x=0,display_y=0;

#include "table_basic.h"

void initial_table(){
	for(table_y = 0 ; table_y<80 ;table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = BLACK;
		}
	}
	table_print(1,10,"Wrote 3072 bytes (128 compressed) at 0x00008000 in 0.0 seconds (effective 1890.5 kbit/s)...Hash of data verified",WHITE,1);
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
			display_table[table_y][table_x] = (word)pgm_read_word(rainbow+k);
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
			display_table[table_y][table_x] = (word)pgm_read_word(winter+k);
			k++;
		}
	}
}

void display_frame()
{
	u16 i,j;
	int k=0;
	uint8_t line;
	for(i=80;i<160;i++)
	{
		for(j=0;j<160;j++)
		{
			if((word)pgm_read_word(frame+k)== 0xFFFF)
			display_table[i][j] = BLACK;
			k++;
		}
	}
}
