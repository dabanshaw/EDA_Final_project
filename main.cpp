# include <iostream>
# include <fstream>
# include "./header/read_json.h"
# include "./header/module.h"
# include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


int main(int argc, char**argv) {
    // read_json(argv[3], argv[4]);
    vector<Block> res_blocks;
    vector<Connection_Matrix> res_connections;
    tie(res_blocks, res_connections) = read(argv[1], argv[2], argv[3]);

    return 0;
}