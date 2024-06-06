# ifndef GRAPH_H
# define GRAPH_H
# include <vector>
# include "./module.h"
# include <string>
# include <tuple>
# include <nlohmann/json.hpp>
# include <vector>

using namespace std;
// using json = nlohmann::json;

void determine_vertex(int tracks_per_um, int length, int width, vector<Connection_Matrix> &connections, vector<Block> &blocks);

# endif