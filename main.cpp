# include <iostream>
# include <fstream>
# include "./header/read.h"
# include "./header/module.h"
# include "./header/visualize_tool.h"
# include <nlohmann/json.hpp>
# include "./header/graph.h"
using namespace std;
using json = nlohmann::json;


int main(int argc, char**argv) {
    vector<Block> res_blocks;
    vector<Connection_Matrix> res_connections;
    vector<Region> regions;
    vector<Point> chip_layout;
    tie(res_blocks, res_connections) = read_json(argv[3], argv[4]);
    tie(chip_layout, regions) = read_def(argv[2], res_blocks);
    draw_block("./case_test.gp", chip_layout, res_blocks, regions);
    int max_num = 0;
    int max_num_index = 0;
    for (auto& connection : res_connections){
        if (connection.NUM > max_num) {
            max_num = connection.NUM;
            max_num_index = connection.ID;
        }
    }

    res_blocks = build_graph(atoi(argv[1]), chip_layout[1].x, chip_layout[1].y, res_connections, res_blocks);
    
    return 0;
}