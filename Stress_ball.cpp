#include <iostream>
#include <ctime>
#include "Collection.h"
#include "Stress_ball.h"
using namespace std;


		// generate random stress ball with random color and size
		Stress_ball::Stress_ball(){
			color=static_cast<Stress_ball_colors>(rand()%4);
			
			size=static_cast<Stress_ball_sizes>(rand()%2);
		}
		
		Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s){
			color = c;
			size = s;
		}
		// command to return the color of the stress ball
		Stress_ball_colors Stress_ball::get_color() const{
			return color;
		}
		// command t return the size of the stress ball
		Stress_ball_sizes Stress_ball::get_size() const{
			return size;
		}
		// overloads the == constuctor to return true if this and sb are the same
		bool Stress_ball::operator==(const Stress_ball&sb){
			return color==sb.color && size==sb.size;
		}
		
		// overloading << operator
		ostream& operator <<(ostream& out, const Stress_ball& sb){
			// formatting for output of the color 
			if(sb.get_color() == Stress_ball_colors::red){
				out << "(red, ";
			} else if (sb.get_color() == Stress_ball_colors::blue) {
				out << "(blue, ";
			} else if (sb.get_color() == Stress_ball_colors::yellow) {
				out << "(yellow, ";
			} else {out << "(green, ";}
			// formatting for output of the size of the stress ball
			if(sb.get_size() == Stress_ball_sizes::small){
				out << "small)";
			} else if (sb.get_size() == Stress_ball_sizes::medium){
				out << "medium)";
			} else {out << "large)";}

			return out;
		}
