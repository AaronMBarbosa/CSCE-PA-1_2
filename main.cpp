#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Stress_ball.h"
#include "Collection.h"

using namespace std;

int main(){
        Stress_ball stress_ball_1 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::small);
        Stress_ball stress_ball_2 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large);
        Stress_ball stress_ball_3 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large);
        Stress_ball stress_ball_4 = Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::medium);
        Collection collection_0;
        Collection collection_1;
        Collection collection_2(3);
        Collection collection_3(5);
        Collection collection_file(1);
        collection_0.insert_item(stress_ball_1);
        collection_0.make_empty();
        collection_1.insert_item(stress_ball_1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::small));
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_4);
        collection_2.insert_item(stress_ball_3);
        Collection collection_copy(collection_1);
        Collection collection_4 = collection_copy;
        Collection collection_5(move(collection_1));
        collection_1.insert_item(Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small));
        Collection collection_7 = move(collection_1);
        collection_7.insert_item(Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::large));
        collection_5.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large));
        collection_4.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium));
        collection_copy.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large));
        collection_4.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::small));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.remove_this_item(stress_ball_2);
        collection_4.remove_this_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium));
        collection_5.remove_any_item();
        collection_2.print_items();
        collection_copy.make_empty();
        if(collection_2.is_empty()){
            collection_2.insert_item(Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::small));
        }else{
            collection_4.insert_item(Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::small));
            collection_4.print_items();
        }
        ifstream ifs("stress_ball1.data");
        ifs >> collection_file;
        collection_file.insert_item(stress_ball_3);
        collection_file.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_1);
        collection_file.print_items();
        collection_3 = make_union(collection_file,collection_2);
        if(collection_3.total_items() == (collection_file.total_items() + collection_2.total_items())){
             if(collection_3.total_items(Stress_ball_colors::yellow) == (collection_file.total_items(Stress_ball_colors::yellow) + collection_2.total_items(Stress_ball_colors::yellow))){
                 if(collection_3.total_items(Stress_ball_sizes::small) == (collection_file.total_items(Stress_ball_sizes::small) + collection_2.total_items(Stress_ball_sizes::small))){
                     swap(collection_file,collection_2);                   
                     if((collection_3.total_items() - collection_2.total_items()) == collection_file.total_items()){
                          sort_by_size(collection_1,Sort_choice::selection_sort);
                          sort_by_size(collection_2,Sort_choice::insertion_sort);  
                          sort_by_size(collection_3,Sort_choice::bubble_sort);
                          cout<<collection_3;
                     }
                }
            }
        }
    return 0;
}