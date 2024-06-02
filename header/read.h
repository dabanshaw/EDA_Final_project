# ifndef READ_DEF_H
# define READ_DEF_H
# include "./module.h"
# include <vector>
# include <tuple>
# include <string>

using namespace std;

tuple<vector<Block>, vector<Connection_Matrix>> read_json( string cfg_fpth, string net_fpth);

vector<int> update_blk_coor(string def_fpth, vector<Block> &blks);

# endif