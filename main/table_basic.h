
void table_fill(u16 color)
{
	u16 i,j;
	for(i=0;i<table_h;i++)
	{
		for(j=0;j<table_w;j++)
		{
			display_table[i][j] = color;
		}
	}
}


void table_image(u16 x0,u16 y0,u16 x1,u16 y1 ,const short unsigned A[])
{
	u16 i,j;
	int k=0;
	for(i=x0;i<x1;i++)
	{
		for(j=y0;j<y1;j++)
		{
			display_table[j][i] = (word)pgm_read_word(A+k);
			k++;
		}
	}
}

void table_fill_Rect(u16 x, u16 y, u16 w, u16 h,u16 color)
{

	if((x >= LCD_W) || (y >= LCD_H)) return;
	if((x + w - 1) >= LCD_W)  w = LCD_W  - x;
	if((y + h - 1) >= LCD_H) h = LCD_H - y;

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
			display_table[y][x] = color;
		}
	}
}

void table_HLine(u16 x, u16 y, u16 w, u16 color)
{
	if((x >= LCD_W) || (y >= LCD_H)) return;
	if((x+w-1) >= LCD_W)
	w = LCD_W-x;
	while (w--) {
		display_table[y][x+w] = color;
	}
}
void table_VLine(u16 x, u16 y, u16 h,u16 color) {
	// Rudimentary clipping
	if((x >= LCD_W) || (y >= LCD_H)) return;
	if((y+h-1) >= LCD_H)
	h = LCD_H-y;
	while (h--) {
		display_table[y+h][x] = color;
	}
}
void table_Pixel(u16 x, u16 y,u16 thin ,u16 color)
{
	if((x < 0) ||(x >= LCD_W) || (y < 0) || (y >= LCD_H)) return;
	for(int a=0;a<thin;a++){
		for(int b=0;b<thin;b++){
			display_table[y+a][x+b] = color;
		}
	}
}


void table_drawCircleHelper( u16 x0, u16 y0,u16 r, uint8_t cornername,u16 thin, u16 color) {
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & 0x4) {
			table_Pixel(x0 + x, y0 + y,thin, color);
			table_Pixel(x0 + y, y0 + x,thin, color);
		}
		if (cornername & 0x2) {
			table_Pixel(x0 + x, y0 - y,thin, color);
			table_Pixel(x0 + y, y0 - x,thin, color);
		}
		if (cornername & 0x8) {
			table_Pixel(x0 - y, y0 + x,thin, color);
			table_Pixel(x0 - x, y0 + y,thin, color);
		}
		if (cornername & 0x1) {
			table_Pixel(x0 - y, y0 - x,thin, color);
			table_Pixel(x0 - x, y0 - y,thin, color);
		}
	}
}

void table_fillCircleHelper(u16 x0, u16 y0, u16 r,uint8_t cornername, u16 delta, u16 color) {

	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1) {
			table_VLine(x0+x, y0-y, 2*y+1+delta, color);
			table_VLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			table_VLine(x0-x, y0-y, 2*y+1+delta, color);
			table_VLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}

void table_fill_Circle(u16 x0, u16 y0, u16 r,u16 color) {
	table_VLine(x0, y0-r, 2*r+1, color);
	table_fillCircleHelper(x0, y0, r, 3, 0, color);
}
void table_Circle(u16 x0, u16 y0, u16 r,u16 thin,u16 color) {
	table_Pixel(x0,y0-r,thin,color);
	table_Pixel(x0,y0+r,thin,color);
	table_Pixel(x0-r,y0,thin,color);
	table_Pixel(x0+r,y0,thin,color);
	table_drawCircleHelper(x0,y0,r,15,thin,color);
}
void table_Rect(u16 x, u16 y,u16 w, u16 h,u16 color) {
	table_HLine(x, y, w, color);
	table_HLine(x, y+h-1, w, color);
	table_VLine(x, y, h, color);
	table_VLine(x+w-1, y, h, color);
}
void table_Round_Rec(u16 x, u16 y, u16 w,u16 h, u16 r, u16 color) {
	// smarter version
	table_HLine(x+r  , y    , w-2*r, color); // Top
	table_HLine(x+r  , y+h-1, w-2*r, color); // Bottom
	table_VLine(x    , y+r  , h-2*r, color); // Left
	table_VLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	table_drawCircleHelper(x+r    , y+r    , r, 1,1, color);
	table_drawCircleHelper(x+w-r-1, y+r    , r, 2,1, color);
	table_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4,1, color);
	table_drawCircleHelper(x+r    , y+h-r-1, r, 8,1, color);
}
void table_Line(u16 x0, u16 y0,u16 x1, u16 y1, u16 thin, u16 color) {
	u16 steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		LCD_swap(x0, y0);
		LCD_swap(x1, y1);
	}

	if (x0 > x1) {
		LCD_swap(x0, x1);
		LCD_swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
		} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			table_Pixel(y0, x0, thin, color);
			} else {
			table_Pixel(x0, y0, thin, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}
void table_Char_bg(u16 x, u16 y, unsigned c,u16 color, u16 bg, uint8_t size) {

	if((x >= table_w)            || // Clip right
	(y >= table_h)           || // Clip bottom
	((x + 6 * size - 1) < 0) || // Clip left
	((y + 8 * size - 1) < 0))   // Clip top
	return;

	for (int8_t i=0; i<6; i++ ) {
		uint8_t line;
		if (i == 5)
		line = 0x0;
		else
		line = pgm_read_byte(font+(c*5)+i);
		for (int8_t j = 0; j<8; j++) {
			if (line & 0x1) {
				table_Pixel(x+i*size, y+j*size,size,color);
			}
			else if (bg != color) {
				table_Pixel(x+i*size, y+j*size,size,bg);
			}
			line >>= 1;
		}
	}
}

void table_Char(u16 x, u16 y, unsigned c,u16 color, uint8_t size) {

	if((x >= table_w)            || // Clip right
	(y >= table_h)           || // Clip bottom
	((x + 6 * size - 1) < 0) || // Clip left
	((y + 8 * size - 1) < 0))   // Clip top
	return;

	for (int8_t i=0; i<6; i++ ) {
		uint8_t line;
		if (i == 5)
		line = 0x0;
		else
		line = pgm_read_byte(font+(c*5)+i);
		for (int8_t j = 0; j<8; j++) {
			if (line & 0x1) {
				table_Pixel(x+i*size, y+j*size,size,color);
			}
			line >>= 1;
		}
	}
}


void table_needle(u16 x,u16 y, u16 w,u16 thin, int value ,u16 color)
{
	int separate = 60;
	int S = w*sin(2*PI*value/separate);
	int C = w*cos(2*PI*value/separate);
	table_Line(x,y,x+S,y-C,thin,color);
}
void table_dot(u16 x,u16 y, u16 r,u16 thin ,u16 color)
{
	int separate = 60;
	for(int a=0;a<separate;a++){
		int S = r*sin(2*PI*a/separate);
		int C = r*cos(2*PI*a/separate);
		table_Pixel(x+S,y-C,thin,color);
	}
}
void table_dot_needle(u16 x,u16 y, u16 w,u16 thin, int value ,u16 color)
{
	int separate = 60;
	int S = w*sin(2*PI*value/separate);
	int C = w*cos(2*PI*value/separate);
	table_Line(x,y,x+S,y-C,thin,color);
	if(value >= (separate*0/4)&&value < (separate*1/4))
	table_Pixel(x+S+thin,y-C-thin,thin,color);
	if(value >= (separate*1/4)&&value < (separate*2/4))
	table_Pixel(x+S+thin,y-C+thin,thin,color);
	if(value >= (separate*2/4)&&value < (separate*3/4))
	table_Pixel(x+S-thin,y-C+thin,thin,color);
	if(value >= (separate*3/4)&&value < (separate*4/4))
	table_Pixel(x+S-thin,y-C-thin,thin,color);
}


void table_print_background(u16 x,u16 y, const char c[],u16 color ,u16 bgcolor ,uint8_t size)
{
	
	int i = 0;
	while(c[i] != '\0'){
		if (c[i] == '\n') {
			y += size*8;
			x  = 0;
		}
		else {
			table_Char_bg(x, y, c[i], color, bgcolor, size);
			x += 6*size;
			i++;
			if (x > (LCD_W - size*6)) {
				y += size*8;
				x = 0;
			}
		}
		
	}
}
void table_print(u16 x,u16 y, const char c[],u16 color ,uint8_t size)
{
	int i = 0;
	while(c[i] != '\0'){
		if (c[i] == '\n') {
			y += size*8;
			x  = 0;
		}
		else {
			table_Char(x, y, c[i], color, size);
			x += 6*size;
			i++;
			if (x > (LCD_W - size*6)) {
				y += size*8;
				x = 0;
			}
		}
	}
}
void table_print_background(u16 x,u16 y, int c,u16 color ,u16 bgcolor ,uint8_t size)
{
	char A[10];
	int i =0;
	sprintf(A, "%d", c);
	while(A[i] != '\0'){
		if (A[i] == '\n') {
			y += size*8;
			x  = 0;
		}
		else {
			table_Char_bg(x, y, A[i], color, bgcolor, size);
			x += 6*size;
			if (x > (LCD_W - size*6)) {
				y += size*8;
				x = 0;
			}
		}
		i++;
	}
}
void table_print(u16 x,u16 y, int c,u16 color ,uint8_t size)
{
	char A[10];
	int i =0;
	sprintf(A, "%d", c);
	while(A[i] != '\0'){
		if (A[i] == '\n') {
			y += size*8;
			x  = 0;
		}
		else {
			table_Char(x, y, A[i], color, size);
			x += 6*size;
			if (x > (LCD_W - size*6)) {
				y += size*8;
				x = 0;
			}
		}
		i++;
	}
	
}
