#include <stdio.h>
#include <string.h>


// 2500 ─
// 2502 │
// 250C ┌
// 2510 ┐
// 2514 └
// 2518 ┘
// 251C ├
// 2524 ┤
// 252C ┬
// 2534 ┴
// 253C ┼


#define HB "\u2500"
#define VB "\u2502"
#define TL "\u250C"
#define TR "\u2510"
#define BL "\u2514"
#define BR "\u2518"
#define LE "\u251C"
#define RE "\u2524"
#define TE "\u252C"
#define BE "\u2534"
#define MI "\u253C"

#define MAX_ROW 32
#define MAX_COL 256

#define FIXED_FORMAT "  %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"


typedef struct _point_2d {
	int x;
	int y;
} point_t;






const char * a_field[] = {
	"  22      ",
	"       0  ",
	"  0    0  ",
	"  0    0  ",
	"  0       ",
	"          ",
	"    1111  ",
	"          ",
	" 1111     ",
	"          ",
	NULL
};



point_t getPoint (const char * ps) {
	return {ps[0] - 65, ps[1] - 48};
}


bool hitTarget (char field[10][10], point_t point) {
	char * p = &field[point.x][point.y];
	*p = (*p != ' ') ? 'x' : 'o';
	return *p == 'x';
}

bool hitTarget (char field[10][10], int x, int y) {
	return hitTarget (field, {x, y});
}

bool hitTarget (char field[10][10], const char * point_str) {
	return hitTarget (field, getPoint (point_str));
}



void displayField (char f[10][10]) {
	char grid[MAX_ROW][MAX_COL] = {0};
	char tmpBuf[32];
	char (*p) [MAX_COL] = grid;



	sprintf (*p, "    %d   %d   %d   %d   %d   %d   %d   %d   %d   %d", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	++p;
	sprintf (*p, FIXED_FORMAT, TL,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TE,HB,HB,HB,TR);
	++p;

	for (int x=0 ; x<10 ; ++x, ++p) {

		sprintf (*p, "%c ", ('A' + x));
		for (int y=0 ; y<10 ; ++y) {
			if (f[x][y] == 'x') {
				sprintf (tmpBuf, "%s \033[31m%c\033[00m ", VB, f[x][y]);
			}
			else if (f[x][y] == 'o') {
				sprintf (tmpBuf, "%s \033[34m%c\033[00m ", VB, f[x][y]);
			}
			else if (f[x][y] != ' ') {
				sprintf (tmpBuf, "%s \033[90m%c\033[00m ", VB, f[x][y]);
			}
			else {
				sprintf (tmpBuf, "%s %c ", VB, f[x][y]);
			}
			strcat (*p, tmpBuf);
		}
		strcat (*p, VB);
		++p;

		sprintf (*p, FIXED_FORMAT, LE,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,MI,HB,HB,HB,RE);
	}

	--p;
	sprintf (*p, FIXED_FORMAT, BL,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BE,HB,HB,HB,BR);

	p = grid;

	while (*p[0]) {
		printf ("%s\n", *p);
		++p;
	}
}














int main(int argc, char ** argv) {

	printf ("This text is NOT \033[31mred\033[00m\n");


	const char * point_str = "B7";
	point_t point = getPoint (point_str);


	char field[10][10];

	for (int x=0 ; x<10 ; ++x) {
		for (int y=0 ; y<10 ; ++y) {
			field[x][y] = a_field[x][y];
		}
	}



	displayField (field);

	hitTarget (field, point);
	hitTarget (field, {0, 0});

	displayField (field);

	return 0;
}