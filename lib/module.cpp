# include<vector>
# include<string>
# include<limits>
# include "../header/module.h"

# include <iostream>
using namespace std;
void Block::show_diearea(){
    cout << this->block_name << " ";
    for (auto pt: this->diearea){
        cout << "(" << pt.x << " " << pt.y << "); ";
    }
    cout << endl;
}

void Block::rotate(string ori, Point anchor){
    cout << "***Before****" <<"|Orientation "<<ori<< " " << anchor.x << " " << anchor.y << endl;
    show_diearea();

    double rot_matrix[2][2] = {{1,0}, {0,1}};
    if (ori == "S"){ 
        rot_matrix[0][0] = -1;
        rot_matrix[1][1] = -1;
    } else if (ori == "W"){ 
        rot_matrix[0][0] = 0;
        rot_matrix[0][1] = -1;
        rot_matrix[1][0] = 1;
        rot_matrix[1][1] = 0;    
    } else if (ori == "E"){ 
        rot_matrix[0][0] = 0;
        rot_matrix[0][1] = 1;
        rot_matrix[1][0] = -1;
        rot_matrix[1][1] = 0;
    } else if (ori == "FN"){ 
        rot_matrix[0][0] = -1;
    } else if (ori == "FS"){ 
        rot_matrix[1][1] = -1;
    } else if (ori == "FW"){
        rot_matrix[0][0] = 0;
        rot_matrix[0][1] = -1;
        rot_matrix[1][0] = -1;
        rot_matrix[1][1] = 0;
    } else if (ori == "FE"){ 
        rot_matrix[0][0] = 0;
        rot_matrix[0][1] = 1;
        rot_matrix[1][0] = 1;
        rot_matrix[1][1] = 0;
    }
    
    // Rotate points.
    int min_x= numeric_limits<int>::max(), min_y = numeric_limits<int>::max();
    for (int  i = 0; i<diearea.size() ; ++i){
        int tmp_x = diearea[i].x, tmp_y = diearea[i].y;
        diearea[i].x = rot_matrix[0][0] * tmp_x + rot_matrix[0][1] * tmp_y;
        diearea[i].y = rot_matrix[1][0] * tmp_x + rot_matrix[1][1] * tmp_y;
        min_x = (min_x >diearea[i].x)?diearea[i].x : min_x;
        min_y = (min_y >diearea[i].y)?diearea[i].y : min_y;
    }
    // Translate points.
    int diff_x = anchor.x-min_x, diff_y = anchor.y-min_y;
    for (Point &pt : diearea){
        pt.x = pt.x + diff_x;
        pt.y = pt.y + diff_y;
    }

    if (diearea.size() == 2){
        if (diearea[0].x > diearea[1].x){
            diearea[0].x = diearea[0].x ^ diearea[1].x;
            diearea[1].x = diearea[0].x ^ diearea[1].x;
            diearea[0].x = diearea[0].x ^ diearea[1].x; 
        }
        if (diearea[0].y > diearea[1].y){
            diearea[0].y = diearea[0].y ^ diearea[1].y;
            diearea[1].y = diearea[0].y ^ diearea[1].y;
            diearea[0].y = diearea[0].y ^ diearea[1].y; 
        }
    }
}
