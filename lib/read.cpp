# include <nlohmann/json.hpp>
# include <iostream>
# include <string>
# include <fstream>
# include <tuple>
# include <filesystem>
# include "../header/module.h"
using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

tuple<vector<Block>, vector<Connection_Matrix>> read_json(string cfg_fpth, string net_fpth){
    vector<Connection_Matrix> connections;
    vector<Block> blocks;
    ifstream file1(net_fpth);
    if (!file1.is_open()) {
        cerr << "Failed to open 1st file." << endl;
        return make_tuple(blocks, connections);
    }
    json data1;
    file1 >> data1;
    // 解析JSON数据并存储到结构体中

    for (const auto& item1 : data1) {
        Connection_Matrix temp_connection;
        temp_connection.ID = item1["ID"];
        temp_connection.TX = item1["TX"];
        temp_connection.RX = item1["RX"].get<vector<string>>();
        temp_connection.NUM = item1["NUM"];
        temp_connection.MUST_THROUGH = item1["MUST_THROUGH"];
        temp_connection.HMFT_MUST_THROUGH = item1["HMFT_MUST_THROUGH"];
        temp_connection.TX_COORD = item1["TX_COORD"].get<vector<double>>();
        temp_connection.RX_COORD = item1["RX_COORD"].get<vector<vector<double>>>();
        connections.push_back(temp_connection);
    }
    file1.close();

    ifstream file2(cfg_fpth);
    if (!file2.is_open()) {
        cerr << "Failed to open 2nd file." << endl;
        return make_tuple(blocks, connections);
    }
    json data2;
    file2 >> data2;

    for (const auto& block : data2) {
        // 创建一个新的Block结构体实例
        Block temp_block;
        temp_block.block_name = block["block_name"];
        temp_block.through_block_net_num = block["through_block_net_num"];
        if (block["is_feedthroughable"] == "True"){
        temp_block.is_feedthroughable = true;}
        else{temp_block.is_feedthroughable = false;}
        if (block["is_tile"] == "True"){
            temp_block.is_tile = true;}
        else{temp_block.is_tile = false;}
        cout << temp_block.block_name << " " << temp_block.through_block_net_num << " " \
        << temp_block.is_feedthroughable << " " << temp_block.is_tile << endl;
        cout << "HI" <<endl;
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
    // cout<<"ENDDDDDDDDDd";
    // file2.close();
    //  data1 的輸出
    for (const auto& item : connections) {
        cout << "ID:" << item.ID << ", TX: " << item.TX << ", RX:";
        for (const auto& rx : item.RX) {
            cout << rx << " ";
        }
        cout << ", NUM:" << item.NUM << ", TX_COORD:[";
        for (const auto& coord : item.TX_COORD) {
            cout << coord << " ";
        }
        cout << "], RX_COORD:[";
        for (const auto& coord : item.RX_COORD) {
            cout << "[";
            for (const auto& c : coord) {
                cout << c << " ";
            }
            cout << "]";
        }
        cout << "]" << endl;
    }

    return make_tuple(blocks, connections);
}

vector<int> update_blk_coor(string def_fpth, vector<Block> &blks){
    if (!fs::exists(def_fpth) || !fs::is_directory(def_fpth)){
        cout << "DEF path doesn't exist."<<endl;
        exit(0);
    }
    // * Read blk.def files
    for (const auto& entry : fs::directory_iterator(def_fpth)){
        if (entry.path().string().find("blk") == string::npos) continue;
        string fname = entry.path().stem().string();
        int blk_indx = stoi(fname.substr(fname.find("_")+1, -1));
        string line, token;
        ifstream ifs(entry.path()); 
        while(getline(ifs, line)){
            // * Get the line with coordinates.
            if (line.find("DIEAREA") == string::npos) continue;
            istringstream iss(line);
            iss >> token;
            int cnt =0, var;
            // * Iteratively get each point.
            while(iss >> token){
                if ( token == "(" || token == ")") continue;
                if (token == ";" ) break;
                if (cnt==1){
                    blks[blk_indx].diearea.push_back(Point(var, stoi(token)));
                    --cnt;
                }else{
                    var = stoi(token);
                    ++cnt;
                }
            }
            break;
        }
        ifs.close();
    }

    
    // for (int i=0; i<blks.size() ; i++){
    //     cout << "blk_" <<i<< " ";
    //     for (int j=0 ; j< blks[i].diearea.size(); ++j){
    //         cout << "(" <<blks[i].diearea[j].x <<","<<blks[i].diearea[j].y<<")"<<"\t";
    //     }
    //     cout << endl;
    // }


    vector<int> chip_layout;
    ifstream ifs(def_fpth +"/chip_top.def");

    return chip_layout;
}