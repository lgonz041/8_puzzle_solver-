#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include "eight_puzzle.h"
#include "solver.h"


using namespace std;


//*********************************************************
////////////////////////////////////////////////////////////
//solver class stuff
///////////////////////////////////////////////////////////
solver::solver(eight_puzzle* p){
    puzzle_queue.push(p);
    puzzle_tree.push_back(p);
    
}
///////////////////////////////////////////////////////////////
//Important Operator function 
//Fills priority queue with childrend of the top of the queue.
//

void solver::operators(eight_puzzle *p, int algo){
    
    bool test_tree = false;
    int blank = p->get_blank();
    int dp = p->get_depth();        //depth of the parent
    
    //check posistion of blank tile to return operators
    if(blank > 2){
        eight_puzzle *a =new eight_puzzle(p->get_puzzle());
        a->set_depth(dp++);                                 //set deptph of child to 
        test_tree = check_tree(a);       
        a->blank_up();
       
        if(test_tree == true ){
            if(algo == 0 ){
                //wo not need to calculate the heuristic
            }else if(algo == 1){
                a->set_heuristic_misplaced_tile();
            }else if(algo == 2){
                a->set_heuristic_manhattan_distance();
            }
            puzzle_queue.push(a);
            puzzle_tree.push_back(a);
            
        }
    }    
    if(blank < 6){
        eight_puzzle *b = new eight_puzzle(p->get_puzzle());
        b->blank_down();
        b->set_depth(dp++);
        test_tree = check_tree(b);
        if(test_tree == true ){
            if(algo == 0 ){
                //wo not need to calculate the heuristic
            }else if(algo == 1){
                b->set_heuristic_misplaced_tile();
            }else if(algo == 2){
                b->set_heuristic_manhattan_distance();
            }
            puzzle_queue.push(b);
            puzzle_tree.push_back(b);
        }
    
    }
    if( blank != 0 && blank != 3 && blank != 6){
        eight_puzzle *c = new eight_puzzle(p->get_puzzle());
        c->blank_left();
        c->set_depth(dp++);
        test_tree = check_tree(c);
        if(test_tree == true ){
            if(algo == 0 ){
                //wo not need to calculate the heuristic
            }else if(algo == 1){
                c->set_heuristic_misplaced_tile();
            }else if(algo == 2){
                c->set_heuristic_manhattan_distance();
            }
            puzzle_queue.push(c);
            puzzle_tree.push_back(c);
        }
    
    }
    if( blank != 2 && blank != 5 && blank != 8){
         eight_puzzle *d = new eight_puzzle(p->get_puzzle());
         d->blank_right();
         d->set_depth(dp++);
         test_tree = check_tree(d);
         if(test_tree == true ){
             if(algo == 0 ){
                //wo not need to calculate the heuristic
            }else if(algo == 1){
                d->set_heuristic_misplaced_tile();
            }else if(algo == 2){
                d->set_heuristic_manhattan_distance();
            }
            puzzle_queue.push(d);
            puzzle_tree.push_back(d);
        }
    }
}
////////////////////////////////////////////////////////
//flag mess below beware
/////////////////////////////////////////////
bool solver::check_tree(eight_puzzle* p){
   
    bool flag = false;
    for(unsigned i = 0; i < puzzle_tree.size(); i++){
            flag = compare_puzzle(p->get_puzzle(),puzzle_tree[i]->get_puzzle());
            if(flag == true){
                return false;
            }
    }
    return true;
}
bool solver::compare_puzzle(int*a,int*b){
    for(int j = 0 ; j < 9; j++)
            {
                if ( a[j] != b[j] ) 
                    return false;
            }
    return true;
}
 int solver::get_moves(){
     
     return moves;
     
 }
 int solver::get_queue_size(){
     return queue_size;
 }
int solver::get_final_depth(){
    return final_depth;
}
/////////////////////////////////////////////////////
//AI Magic below here 
/////////////////////////////////////////////////////
/* 
function general-search(problem, QUEUEING-FUNCTION)  
    nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE)) 
    loop do
    if EMPTY(nodes) then return "failure" 
        node = REMOVE-FRONT(nodes) 
    if problem.GOAL-TEST(node.STATE) succeeds then return node
        nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))  
 end
*/
void solver::General_search(int algo){
    int choice = 1;
    moves = 0;
    bool solved = false;
    while(solved == false){
        
        if(puzzle_queue.empty()){
            cout << "Unsolvable :( !\n";
            break;
        }else{
            
            if(puzzle_queue.size() > queue_size) queue_size = puzzle_queue.size();
            
            eight_puzzle * p = puzzle_queue.top();
            puzzle_queue.pop();
            moves++;
            solved = p->check_solve();
            
            if(solved == true){
                cout << "Goal!!\n\n";
                final_depth = p->get_depth();
                break;
            }
            operators(p, algo);        //Algo refers to Uniform cost-0, Misplace_tile-1 Manhattan_distance-2
            p = puzzle_queue.top();
            cout << "The best state to expand with a g(n) ="<< p->get_depth()<< " and h(n) = "<<p->get_heuristic()<< " is…\n";
            p->print();
            if (choice == 1){
                cout << "1 - step, 2- solve all \n";
                cin >> choice;
            }
            
        }
    }
}
void solver::Uniform_Cost(){
    General_search(0);
}
void solver::Misplaced_tile(){
    General_search(1);
}
void solver::Manhattan_distance(){
       General_search(2);
}
