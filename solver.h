#ifndef SOLVER_H
#define SOLVER_H
#include <queue>
#include <vector>

using namespace std;
class eight_puzzle;

///////////////Prioty based on smallest values of f(n) = g(n) + h(n)////////////
struct A_star_order{
    bool operator()( eight_puzzle* l,  eight_puzzle* r) 
    {
      return l->get_A_star() > r->get_A_star();
    }
};

class solver{
    public:
        solver();
        solver(eight_puzzle*);
        
        void operators(eight_puzzle*, int algo);
        bool check_tree(eight_puzzle*);
        bool compare_puzzle(int*,int*);
        int get_moves();
        int get_queue_size();
        int get_final_depth();
        
        
        //solving solutions 
        void General_search(int algo);
        void Uniform_Cost();
        void Misplaced_tile();
        void Manhattan_distance();
        
        //extra
        void print_solved_tree(eight_puzzle*);
    
    private:
    
        int moves = 0;
        unsigned queue_size = 0;
        int final_depth = 0; 
        priority_queue<eight_puzzle*, vector<eight_puzzle*>, A_star_order > puzzle_queue;
        vector<eight_puzzle*> puzzle_tree;
    
};


#endif