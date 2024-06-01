# ifndef READ_DEF_H
# define READ_DEF_H
# include "./module.h"
# include <vector>
# include <tuple>
# include <string>

using namespace std;

tuple<vector<Block>, vector<Connection_Matrix>> read(string def_fpth, string cfg_fpth, string net_fpth);

# endif