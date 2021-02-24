#include "Collection.h"
#include "Stress_ball.h"
#include <exception>
#include <cstdlib>
using namespace std;


		void Collection::resize() {
			capacity = capacity*2;
			if( capacity == 0){
				capacity = 2;
			} 
			// creates temp pointer to transfer all the old data to the new resized array
			Stress_ball *temp = new Stress_ball[capacity];
			for(int i = 0; i < size; i++) {
				temp[i] = array[i];
			}
			// memory leak fix
			delete []array;
			array = temp;
		}

		Collection::Collection() {
			size = 0;
			capacity = 0;
			array = nullptr;
		}
		
		Collection::Collection(int sze) {
			size = 0;
			capacity = sze;
			array = new Stress_ball[capacity];
		}
		
		Collection::Collection(const Collection &T) {
			size = T.size;
			capacity = T.capacity;
			array = new Stress_ball[capacity];
			for (int i = 0; i < size; i++) {
				array[i] = T.array[i];
			}
		}

		Collection::Collection(Collection&& c): size(c.size), capacity(c.capacity), array(c.array){
			c.array = NULL;
			c.size = 0;
			c.capacity = 0;
		}
		
		Collection& Collection::operator=(const Collection& T) {
			if(this != &T) {
				if(array != nullptr) {
					delete []array;
				}
				size = T.size;
				array = new Stress_ball[capacity];
				for(int i = 0; i < size; i++) {
					array[i] = T.array[i];
				}
			}
			return *this;
		}
		
		Collection& Collection::operator=(Collection&& c) {
			
			if(this != &c) {
				make_empty();
				size = c.size;
				capacity = c.capacity;
				array = c.array;
				c.array = NULL;
				c.size = 0;
				c.capacity = 0;
			}
			return *this;
		}
		
		Collection::~Collection() {
			make_empty();
		}
		// inserts new item into current stress ball, resizes array if full
		void Collection::insert_item( const Stress_ball &sb) {
			if(size == capacity) {
				resize();
			}
			array[size] = sb;
			size++;
		}
		// checks if item is within current stress ball
		bool Collection::contains(const Stress_ball &sb) const{
			for(int i = 0; i < size; i++) {
				if(array[i] == sb){
					return true;
				}
			}
			return false;
		}
		
		Stress_ball Collection::remove_any_item(){
			// checks if the array is already empty and throws an error if it is
			if(is_empty()) {
				throw Empty_Collection();
			}
			int indx = rand()% size;
			Stress_ball sb = array[indx];
			remove_this_item(sb);
			return sb;
		}
		
		void Collection::remove_this_item( const Stress_ball &sb) {
			// checks if the array is already empty and throws an error if it is
			if(size == 0){
				throw Empty_Collection();
			}
			int indx = -1;
			for (int i = 0; i < size; i++) {
				if(array[i] == sb) {
					indx = i;
					break;
				}
			}
			if( indx == -1) {
				return;
			}
			for(int i = indx; i < size; i++) {
				array[i] = array[i+1];
			}
			size--;
		}
		
		void Collection::make_empty(){
			 
				
				array = nullptr;
				size = 0;
				capacity = 0;
			 
		}
		
		bool Collection::is_empty() const{
			return size == 0;
		}
		
		int Collection::total_items() const {
			return size;
		}
		
		int Collection::total_items(Stress_ball_sizes s) const{
			int cnt = 0;
			for (int i = 0; i < size; i++){
				if(array[i].get_size() == s) {
					cnt++;
				}
			}
			return cnt;
		}
		
		int Collection::total_items(Stress_ball_colors c) const{
			int cnt = 0;
			for (int i = 0; i < size; i++){
				if( array[i].get_color() == c){
					cnt++;
				}
			}
			return cnt;
		}
		
		void Collection::print_items() const{
			for(int i = 0; i < size; i++) {
				cout << array[i] << endl;
			}
		}
		
		Stress_ball& Collection::operator[](int i) {
			return array[i];
		}
		
		const Stress_ball& Collection::operator[](int i) const{
			return array[i];
		}
		
		
		ostream& operator<<(ostream& o,const Collection& c){
			
			for (int i = 0; i < c.total_items(); i++) {
				o << c[i] << endl;
			}
			return o;
		}
		
		istream& operator>>(istream& is, Collection& c) {
			Stress_ball_colors clr;
			Stress_ball_sizes sze;
			string size_s;
			string color_s;
			bool fail = false;
			while(true) {
				is >> color_s >> size_s;
				if(!is) {
					break;
				}
				if(color_s == "red") {
					clr = Stress_ball_colors::red;
				} else if(color_s == "blue") {
					clr = Stress_ball_colors::blue;
				}else if(color_s == "green") {
					clr = Stress_ball_colors::green;
				}else if(color_s == "yellow") {
					clr = Stress_ball_colors::yellow;
				} else {
					fail = true;
					break;
				}
				
				if(size_s == "small") {
					sze = Stress_ball_sizes::small;
				} else if(size_s == "medium") {
					sze = Stress_ball_sizes::medium;
				} else if(size_s == "large") {
					sze = Stress_ball_sizes::large;
				} else {
					fail = true;
					break;
				}
				c.insert_item(Stress_ball(clr,sze));
			}
			if(fail) {
				cout <<">>> Wrong Stress_ball input\n";
				cout <<">>> Collection is empty\n";
				c.make_empty();
			}
			return is;
		}
		
		Collection make_union(const Collection& c1, const Collection& c2) {
			Collection c3 = c1;
			for (int i = 0; i < c2.total_items(); i++) {
				c3.insert_item(c2[i]);
			}
			return c3;
		}
		
		void swap(Stress_ball& sb1, Stress_ball& sb2) {
			Stress_ball temp = sb1;
			sb1 = sb2;
			sb2 = temp;
		}
		
		void swap(Collection& c1, Collection& c2) {
			Collection temp = move(c1);
			c1 = move(c2);
			c2 = move(temp);
		}

		void bubble_sort(Collection& c) {
			int n = c.total_items();
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n-i-1; j++) {
					if(c[j].get_size()>c[j+1].get_size()) {
						swap(c[j], c[j+1]);
					}
				}
			}
		}
		
		void insertion_sort(Collection& c) {
			Collection small, med, large;
			for (int k = 1; k < c.total_items(); k++) {
				int temp = k;
				int j = k;
				for(; j > 0 && c[temp].get_size() < c[j-1].get_size(); j--) {
					c[j] = c[j-1];
				}
				c[j] = c[temp];
			}
		}
		
		void selection_sort(Collection& c){
			int smallest_value;
			
			for(int i = 0; i < c.total_items(); i++) {
				smallest_value = i;
				for(int j = i; j < c.total_items(); j++) {
					if(c[j].get_size() < c[smallest_value].get_size()) {
						smallest_value = j;
					}
				}
				swap(c[i],c[smallest_value]);
			}
		}
		
		void sort_by_size (Collection& c, Sort_choice sort) {
			switch (sort) {
				case Sort_choice::bubble_sort:
				bubble_sort(c);
				break;
				case Sort_choice::insertion_sort:
				insertion_sort(c);
				break;
				case Sort_choice::selection_sort:
				selection_sort(c);
				break;
			}
		}