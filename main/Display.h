﻿#define table_w 160
#define table_h 160
unsigned short display_table[table_h][table_w] = {0};
	
int table_x = 0,table_y=0;

	
void initial_display(){
	for(table_y = 0 ; table_y<80 ;table_y++)
	{
		for(table_x = 0 ; table_x < 160 ; table_x++)
		{
			display_table[table_y][table_x] = BLACK;
		}
	}
  for(table_y = 30 ; table_y<50 ;table_y++)
  {
    for(table_x = 40 ; table_x < 120 ; table_x++)
    {
      display_table[table_y][table_x] = GREEN;
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
}

void display_set_bio(){
  for(table_y = 80 ; table_y < 160 ; table_y++)
  {
    for(table_x = 0 ; table_x < 160 ; table_x++)
    {
      display_table[table_y][table_x] = RED;
    }
  }
}
void display_set_setting(){
  for(table_y = 80 ; table_y < 160 ; table_y++)
  {
    for(table_x = 0 ; table_x < 160 ; table_x++)
    {
      display_table[table_y][table_x] = GREEN;
    }
  }
}
