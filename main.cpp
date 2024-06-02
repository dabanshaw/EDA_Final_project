# include <iostream>
# include <fstream>
# include "./header/read.h"
# include "./header/module.h"
# include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


int main(int argc, char**argv) {
    vector<Block> res_blocks;
    vector<Connection_Matrix> res_connections;
    tie(res_blocks, res_connections) = read_json(argv[3], argv[4]);
    update_blk_coor(argv[2], res_blocks);
    return 0;
}