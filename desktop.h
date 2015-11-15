#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define NON 4
#define Holmes 0
#define Watson 1
#define Dog 2
//desktop map
//        1  2  3
// wat 12 a  b  c  4 hol
//     11 d  e  f  5
//     10 g  h  i  6
//        9  8  7
//          dog
using namespace std;

class District {
	public :
    District(char c);//constructer
    int set_direction(int deg); // set the direction of card;
    int get_deg(); //get the direction of card now;
    inline int to_die(){die =1;}; // turn over the card
    char id;
	private:
	int deadroad;//only one road is dead
	bool die =0;

};
class Holmes_team {
	public :
	    Holmes_team();
        int chpos(int partner,int pos);
        void get_all_pos();
        inline int get_hol(){return pos_hol;}
        inline int get_wat(){return pos_wat;}
        inline int get_dog(){return pos_dog;}
	private:
    int pos_hol;
    int pos_dog;
    int pos_wat;

};
class Desktop{
	public :
	    Desktop();
	    void parse_cmd(string);
	    void judge_jack();
	    void action(int);
        void print_map();
	private:
	    char dis_map[9];
	    District people[9]{'a','b','c','d','e','f','g','h','i'};
	    Holmes_team hol_tm;
};
District::District(char c): id(tolower(c)){
        //initialize foreground road
        srand(id+time(NULL));
        set_direction(rand()%4 * 90);
}
int District::set_direction(int deg){
        switch(deg){
        case 0:
            if(id=='a'&& die)deadroad=NON;
            else deadroad=UP;
            break;
        case 90:
            if(id=='a'&& die)deadroad=NON;
            else deadroad=RIGHT;
            break;
        case 180:
            if(id=='a'&& die)deadroad=NON;
            else deadroad=DOWN;
            break;
        case 270:
            if(id=='a'&& die)deadroad=NON;
            else deadroad=LEFT;
            break;
        default:
            return -1;
            break;
        }
        return 0;
}
int District::get_deg(){
    switch(deadroad){
            case NON: return 360;
            case UP : return 0;
            case RIGHT : return 90;
            case DOWN : return 180;
            case LEFT : return 270;
    }
}

Holmes_team::Holmes_team():pos_hol(4),pos_dog(8),pos_wat(12){}
int Holmes_team::chpos(int partner,int pos){
    switch(partner){
    case Holmes :pos_hol = pos; break;
    case Watson :pos_wat = pos; break;
    case Dog :pos_dog = pos; break;
    default :return -1;
    }
    return 0;
}
void Holmes_team::get_all_pos(){
    printf("Holmes's position :%d\n",pos_hol);
    printf("Watson;s position :%d\n",pos_wat);
    printf("Dog's possiton :%d\n",pos_dog);
}
//desktop map
//  |   |   |   |   |   |   |
//      x   1   2   3   x
//  wat 12  a   b   c   4   hol
//      11  d   e   f   5
//      10  g   h   i   6
//      x   9   8   7   x
//             dog
//map table
//     0,0 1,0 2,0 3,0 4,0
//     0,1 1,1 2,1 3,1 4,1
//     0,2 1,2 2,2 3,2 4,2
//     0,3 1,3 2,3 3,3 4,3
//     0,4 1,4 2,4 3,4 4,4
Desktop::Desktop(){
    int num[9]{0,1,2,3,4,5,6,7,8};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(begin(num),end(num),std::default_random_engine(seed));
    char* p=dis_map;
    for(int i=0;i<9;++i)*p=people[num[i]].id,++p;
}
void Desktop::print_map(){
    string map[5][5];
    struct coord{int x;int y;}xy;
    auto trans_pos=[&](int pos){
        switch(pos){
        case 1:xy.x=1;xy.y=0;break;
        case 2:xy.x=2;xy.y=0;break;
        case 3:xy.x=3;xy.y=0;break;
        case 4:xy.x=4;xy.y=1;break;
        case 5:xy.x=4;xy.y=2;break;
        case 6:xy.x=4;xy.y=3;break;
        case 7:xy.x=3;xy.y=4;break;
        case 8:xy.x=2;xy.y=4;break;
        case 9:xy.x=1;xy.y=4;break;
        case 10:xy.x=0;xy.y=3;break;
        case 11:xy.x=0;xy.y=2;break;
        case 12:xy.x=0;xy.y=1;break;
        }
    };
    trans_pos(hol_tm.get_hol());
    map[xy.x][xy.y]="hol";
    trans_pos(hol_tm.get_wat());
    map[xy.x][xy.y]="wat";
    trans_pos(hol_tm.get_dog());
    map[xy.x][xy.y]="dog";
    int k=0;
    for(int i=1;i<4;++i)
        for(int j=1;j<4;++j)
            map[i][j]=string()+dis_map[k++];
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){
            cout <<map[i][j]<<"\t";
        }
        cout <<endl;
    }

}