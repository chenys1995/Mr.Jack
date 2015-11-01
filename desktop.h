#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
class District;
class Desktop;
class Holmes;

class District {
	public :
    int rotate_deg(int deg){
        switch(sw){
        case 0:
            switch(deg){
            case 0:break;
            case 90:break;
            case 180:break;
            case 270:break;
            default:
                return -1;
                break;
            }
            break;
        case 1:
            break;
        default :
            cerr <<"Unexpected error !\n";
            break;
        }


    }
	private:
    Disrtict(char id);
	struct direction {bool up,down,left,right;} foregnd,backgnd;
	bool sw =0;
    char id;
};
class Holmes {
	public :
	private:

};
class Desktop{
	public :
	private:


};
District::District(char id): id(id){
        //initialize foreground road
        foregnd.up = 1;
        foregnd.down = 0;
        foregnd.left = 1;
        foregnd.right = 1;
        //initialize background road
        backgnd.up = 1;
        backgnd.down = 0;
        backgnd.left = 1;
        backgnd.right = 1;
}
