# ifndef MODULE_H
# define MODULE_H
# include <vector>
# include <string>
# include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct Connection_Matrix {
    int ID;
    string TX;
    vector<string> RX;
    int NUM;
    json MUST_THROUGH;
    json HMFT_MUST_THROUGH;
    vector<double> TX_COORD;
    vector<vector<double>> RX_COORD;
};

struct Point {
    int x;
    int y;
    Point(){};
    Point(int x, int y): x(x),y(y){};
};

struct Points{
    Point start;
    Point end;
};

struct Edge {
    Point start;
    Point end;
    int value;
};

struct Block {
    string block_name;
    int through_block_net_num;
    vector<Edge> through_block_edge_net_num;
    vector<Points> block_port_region;
    bool is_feedthroughable;
    bool is_tile;
    vector<Point> diearea;
    void show_diearea();
    void rotate(string ori, Point anchor);
};

struct Region{
    string region_name;
    vector<Point> diearea;
    Region(){};
    Region(string name, vector<Point> pts):region_name(name), diearea(pts){};
}; 

# endif