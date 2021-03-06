#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H



//////////////////////////
class eight_puzzle{
  private: 
    int puzzle[9] = {1,2,3,4,5,6,7,8,0}; 
    int blank = 0;
    int depth = 0;
    int heuristic = 0;
    eight_puzzle* Parent = NULL;
    
  public:
    eight_puzzle(){};
    eight_puzzle(int p[] );
    
    
    //operators 
    int get_blank();
    int *get_puzzle();
    void blank_up();
    void blank_down();
    void blank_left();
    void blank_right();
    
    //methods
    void set_depth(int d);
    int get_depth();
    void set_heuristic_misplaced_tile();
    void set_heuristic_manhattan_distance();
    int get_heuristic();
    int get_A_star();
    
    //print function 
    void print();
    void rand_fill();
    void manual_fill(int p[]);
    
    //extras 
    void set_parent(eight_puzzle*);
    eight_puzzle* get_parent();
    //check for solution
    bool check_solve();
        
};

#endif