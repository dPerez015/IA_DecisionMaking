#include "Heuristics.h"

int Heuristics::manhatanDistance(Vector2D init, Vector2D fin) {
		/*fin = pix2cell(fin);
		init = pix2cell(init);*/

		int ret1 = fin.x - init.x;
		if (abs(ret1) >= (SRC_WIDTH / (CELL_SIZE * 2))) {
			if (ret1 < 0) {
				return abs((fin.x + (SRC_WIDTH / CELL_SIZE)) - init.x) + abs(fin.y - init.y);
			}
			else {
				return abs(fin.x - (init.x + (SRC_WIDTH / CELL_SIZE))) + abs(fin.y - init.y);
			}
		}
		else {
			return abs(ret1) + abs(init.y - fin.y);
		}

	}
	