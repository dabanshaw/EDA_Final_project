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
<<<<<<< HEAD
    tie(res_blocks, res_connections) = read(argv[2], argv[3], argv[4]);

=======
    tie(res_blocks, res_connections) = read_json(argv[3], argv[4]);
    update_blk_coor(argv[2], res_blocks);
>>>>>>> 6572494567b7158a1e723993527223c1c7e7e211
    return 0;
}