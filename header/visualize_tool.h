# ifndef VISUALIZE_H
# define VISUALIZE_H
# include <string>
# include <vector>
# include "./module.h"

using namespace std;

void draw_block(string fpth, vector<Point> chip_layout, vector<Block> &blks, vector<Region> &regions);
# endif
