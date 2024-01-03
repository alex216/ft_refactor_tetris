#include "tetris.h"

void	set_timeout(int time)
const Struct	StructsArray[7] = {
	{(char *[]){(char[]){0, 1, 1},
				(char[]){1, 1, 0},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){1, 1, 0},
				(char[]){0, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){0, 1, 0},
				(char[]){1, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){0, 0, 1},
				(char[]){1, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){1, 0, 0},
				(char[]){1, 1, 1},
				(char[]){0, 0, 0}}, 3
	},
	{(char *[]){(char[]){1, 1},
				(char[]){1, 1}}, 2
	},
	{(char *[]){(char[]){0, 0, 0, 0},
				(char[]){1, 1, 1, 1},
				(char[]){0, 0, 0, 0},
				(char[]){0, 0, 0, 0}}, 4
	}
};

// initialize t_game_info struct variable
void	initiate_game(t_game_info *info)
{
	char	aTable[ROW_MAX][COL_MAX] = {0};

	info->final_score = 0;
	info->timer = 400000;
	info->GameOn = true;
	info->decrease = 1000;
	// for (int i = 0; i < ROW_MAX; i++) {
	// 	for (int j = 0; j < COL_MAX; j++) {
	// 		info->Table[i][j] = 0;
	// 	}
	// }
	// info->Table = aTable;
}

{
	time = 1;
	timeout(1);
}
