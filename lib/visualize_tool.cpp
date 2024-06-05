# include "../header/visualize_tool.h"
# include "../header/module.h"
# include <string>
# include <iostream>
# include <vector>
# include <fstream>
# include <limits>
using namespace std;

void draw_block(string fpth, vector<Point> chip_layout, vector<Block> &blks, vector<Region> &regions){
    ofstream ofs(fpth);
    if (!ofs.is_open()){
        cout << "Error: Failed to open output file." <<endl;
        return ;
    }
    string out_name = fpth.substr(0, fpth.find_last_of("."));
    string gnp_header = "reset\nset title \"result\"\nset xlabel \"X\"\nset ylabel \"Y\"\n";
    // string gnp_tics = "set xtics 1000\nset ytics 1000\n";
    string gnp_boundary = "plot ["+ to_string(chip_layout[0].x) +":" + to_string(chip_layout[1].x) + "][" + to_string(chip_layout[0].y) + ":" + to_string(chip_layout[1].y) + "]0\n"; 
    string gnp_end = "set terminal png size 2048,1536\nset output \""+ out_name+ ".png\"\nreplot\n";
    
    ofs << gnp_header;
    int i =0;
    // * Set each region.
    for (auto &reg : regions){
        int x1 = reg.diearea[0].x , y1 = reg.diearea[0].y;
        int x2 = reg.diearea[1].x , y2 = reg.diearea[1].y;
        ++i;
        ofs << "set object "<< i << " rect from ";
        ofs << x1 << "," << y1;
        ofs << " to "<< x2 << "," << y2<<endl;
        ofs << "set label \""<< reg.region_name << "\" at ";
        ofs << int((x1+x2)/2) << "," << int((y1+y2)/2) <<" center" <<endl;
        
    }
    // * Set each block.
    for (auto &blk : blks){
        ++i;
        
        if (blk.diearea.size() == 2){
            int x1 = blk.diearea[0].x , y1 = blk.diearea[0].y;
            int x2 = blk.diearea[1].x , y2 = blk.diearea[1].y;
            ofs << "set object "<< i << " rect from ";
            ofs << x1 << "," << y1;
            ofs << " to "<< x2 << "," << y2<<endl;
            ofs << "set label \""<< blk.block_name << "\" at ";
            ofs << int((x1+x2)/2) << "," << int((y1+y2)/2) <<" center" <<endl;
        }else if(blk.diearea.size() >0){
            ofs << "set object " << i << " polygon from " << blk.diearea[0].x<<"," << blk.diearea[0].y;
            int sum_x =0 , sum_y = 0, max_x, max_y, min_x, min_y;
            max_x = min_x = blk.diearea[0].x;
            max_y = min_y = blk.diearea[0].y;

            for (int j=1 ; j< blk.diearea.size() ; ++j){
                string last_str = (j != blk.diearea.size()-1)?" \\" :" fc rgb \"red\"";
                ofs << " to " << blk.diearea[j].x << "," << blk.diearea[j].y;
                sum_x += blk.diearea[j].x; sum_y += blk.diearea[j].y;
                if (blk.diearea[j].x > max_x) max_x = blk.diearea[j].x;
                else if (blk.diearea[j].x < min_x) min_x = blk.diearea[j].x;

                if (blk.diearea[j].y > max_y) max_y = blk.diearea[j].y;
                else if (blk.diearea[j].y < min_y) min_y = blk.diearea[j].y;
            }
            ofs << " to " << blk.diearea[0].x <<"," << blk.diearea[0].y;
            ofs << " fc rgb \"red\"" << endl;
            ofs << "set label \""<< blk.block_name << "\" at ";
            ofs << int((max_x + min_x)/2) << "," << int((max_y+min_y)/2) << " center" << endl;
        }
    }

    ofs << gnp_boundary;
    ofs << gnp_end;
    ofs.close();   
}