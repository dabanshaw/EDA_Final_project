# include <nlohmann/json.hpp>
# include <iostream>
# include <string>
# include <fstream>
# include <tuple>
# include "../header/graph.h"

using namespace std;
using json = nlohmann::json;
void determine_vertex(int tracks_per_um, int length, int width, vector<Connection_Matrix> &connections, vector<Block> &blocks){
    int max_num = 0;
    int max_num_index = 0;
    for (const auto& connection : connections){
        if (connection.NUM > max_num){
            max_num = connection.NUM; 
            max_num_index = connection.ID; 
        }
    }
    int grid_length = length;
    int grid_width = width;
    if (grid_length % 2000 != 0) grid_length = ((grid_length/2000) +1);
    if (grid_width % 2000 != 0) grid_width = ((grid_width/2000) +1);
    // cout << "===============" << endl;
    // cout << "length = " << grid_length  << " "<< " width = " << grid_width << endl;
    // cout << "tracks_per_um = " << tracks_per_um << endl;
    // cout << "max_num = " << max_num << " max_num_index = " << max_num_index << endl;
    int cell_length = max_num/tracks_per_um;
    if (cell_length %10 != 0) cell_length = ((cell_length / 10) + 1) * 10; 
    // cout << "cell length = " << cell_length << endl;//一個cell是幾um

    
    cout << "========================" << endl;


    for (auto& block : blocks){
        vector<Point> temp_diearea = block.diearea;
        if (block.diearea.size() == 2){
            int min_x, min_y, max_x, max_y;
            min_x = temp_diearea[0].x;
            min_y = temp_diearea[0].y;
            max_x = temp_diearea[1].x;
            max_y = temp_diearea[1].y;
            // temp_diearea.clear();
            // temp_diearea.push_back({Point{min_x, min_y}});
            // temp_diearea.push_back({Point{max_x, min_y}});
            // temp_diearea.push_back({Point{max_x, max_y}});
            temp_diearea.insert(temp_diearea.begin()+1, {Point{max_x, min_y}});
            temp_diearea.push_back({Point{min_x, max_y}});
        }
        // cout << "block_name = " << block.block_name << endl;
        if (block.diearea.size() > 0){
            int temp_x = temp_diearea[0].x / 2000 / cell_length;
            int temp_y = temp_diearea[0].y / 2000 / cell_length;
            int ori_x = temp_diearea[0].x / 2000 / cell_length;
            int ori_y = temp_diearea[0].y / 2000 / cell_length;;
            int last_x, last_y;
            cout << block.block_name << endl;
            // cout << "temp_xy " << temp_x << " " << temp_y << endl;
            for (auto& vertex : temp_diearea){
                vertex.x = vertex.x / 2000 /cell_length;
                vertex.y = vertex.y / 2000 /cell_length;
                cout << vertex.x << " " << vertex.y << endl;
                if (temp_x == vertex.x){
                    if (temp_y < vertex.y){
                        for(int i=temp_y; i < vertex.y; i++){
                            block.edge_vertex.push_back(Point{vertex.x, i});
                        }
                    }
                    else if (temp_y > vertex.y){
                        for (int i=temp_y; i > vertex.y; i--){
                            block.edge_vertex.push_back(Point{vertex.x, i});
                        }
                    }
                    temp_y = vertex.y;
                }
                else if (temp_y == vertex.y){
                    if (temp_x < vertex.x){
                        for(int i = temp_x; i < vertex.x; i++){
                            block.edge_vertex.push_back(Point{i, vertex.y});
                        }
                    }
                    else if (temp_x > vertex.x){
                        for (int i = temp_x; i > vertex.x; i--){
                            block.edge_vertex.push_back({Point{i, vertex.y}});
                        }
                    }
                    temp_x = vertex.x;
                }    
                last_x = vertex.x;
                last_y = vertex.y;          
            }
            // cout << "last " << last_x << " " << last_y << endl;
            // cout << "Ori " << ori_x << " " << ori_y << endl;
            if (last_x == ori_x){
                if (last_y < ori_y){
                    for (int i = last_y; i < ori_y; i++){
                        block.edge_vertex.push_back({Point{ori_x, i}});
                    }
                }
                else if (last_y > ori_y){
                    for (int i = last_y; i > ori_y; i--){
                        block.edge_vertex.push_back({Point{ori_x, i}});
                    }
                }
            }
            else if (last_y == ori_y){
                if (last_x < ori_x){
                    for (int i = last_x; i < ori_x; i++){
                        block.edge_vertex.push_back({Point{i, ori_y}});
                    }
                }
                else if (last_x > ori_x){
                    for (int i = last_x; i > ori_x; i--){
                        block.edge_vertex.push_back({Point{i, ori_y}});
                    }
                }
            }
            // block.edge_vertex.push_back({Point{last_x, last_y}});
        }
        // cout << "===============" << endl;
    }
    for (auto& block : blocks){
        if (block.block_name == "BLOCK_0"){
            // cout << "block_name = " << block.block_name << endl;
            for (auto& vertex : block.edge_vertex){
                // cout << vertex.x << " " << vertex.y << endl;
            }
        }
    }
}