# include <nlohmann/json.hpp>
# include <iostream>
# include <string>
# include <fstream>
# include "../header/module.h"
using namespace std;
using json = nlohmann::json;

int read(string net_fpth, string cfg_fpth){
    std::ifstream file1(net_fpth);
    if (!file1.is_open()) {
        std::cerr << "Failed to open 1st file." << std::endl;
        return 1;
    }
    json data1;
    file1 >> data1;

    std::ifstream file2(cfg_fpth);
    if (!file2.is_open()) {
        std::cerr << "Failed to open 2nd file." << std::endl;
        return 1;
    }
    json data2;
    file2 >> data2;

    // 解析JSON数据并存储到结构体中
    vector<Connection_Matrix> connections;
    vector<Block> blocks;

    for (const auto& item1 : data1) {
        Connection_Matrix temp_connection;
        temp_connection.ID = item1["ID"];
        temp_connection.TX = item1["TX"];
        temp_connection.RX = item1["RX"].get<std::vector<std::string>>();
        temp_connection.NUM = item1["NUM"];
        temp_connection.MUST_THROUGH = item1["MUST_THROUGH"];
        temp_connection.HMFT_MUST_THROUGH = item1["HMFT_MUST_THROUGH"];
        temp_connection.TX_COORD = item1["TX_COORD"].get<std::vector<double>>();
        temp_connection.RX_COORD = item1["RX_COORD"].get<std::vector<std::vector<double>>>();
        connections.push_back(temp_connection);
    }
    // for (const auto& block : data2){
    //     Block temp_block;
    //     temp_block.block_name
    //     temp_block.
    // }

    for (const auto& block : data2) {
        // 创建一个新的Block结构体实例
        Block temp_block;
        temp_block.block_name = block["block_name"];
        temp_block.through_block_net_num = block["through_block_net_num"];
        temp_block.is_feedthroughable = block["is_feedthroughable"];

        // 解析through_block_edge_net_num
        if (!block["through_block_edge_net_num"].empty()) {
            for (const auto& edge : block["through_block_edge_net_num"]) {
                Edge e;
                e.start.x = edge["start"]["x"];
                e.start.y = edge["start"]["y"];
                e.end.x = edge["end"]["x"];
                e.end.y = edge["end"]["y"];
                e.value = edge["value"];
                temp_block.through_block_edge_net_num.push_back(e);
            }
        }

        // 解析block_port_region
        for (const auto& points : block["block_port_region"]) {
            Points p;
            p.start.x = points["start"]["x"];
            p.start.y = points["start"]["y"];
            p.end.x = points["end"]["x"];
            p.end.y = points["end"]["y"];
            temp_block.block_port_region.push_back(p);
        }

        // 将解析后的Block结构体添加到vector中
        blocks.push_back(temp_block);
    }

}