#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <ctime>
#include <stack>
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
class District;
class Holmes_team;
class Desktop;
class District {
public :
    District(char c);//constructer
    int set_direction(int deg); // set the direction of card;
    int get_deg(); //get the direction of card now;
    inline int to_die() {
        die =1;
    }; // turn over the card
    inline int isDie() {
        return die;
    };
    char id;
private:
    int deadroad;//only one road is dead
    bool die =0;

};
class Holmes_team {
public :
    friend class Desktop;
    Holmes_team();
    int chpos(int partner,int pos);
    void get_all_pos();
    inline int get_hol() {
        return pos_hol;
    }
    inline int get_wat() {
        return pos_wat;
    }
    inline int get_dog() {
        return pos_dog;
    }
private:
    int pos_hol;
    int pos_dog;
    int pos_wat;

};

class Desktop {
public :

    Desktop();
    void parse_cmd(bool turn);
    void print_map();
    void print_status();
    inline void judge();
    void judge(int pos);
    //inline void top(){printf("card top :%c\n",Card.top());};
    friend void print_act(const Desktop& desk,int* act_lock);
    inline char get_jack(){return jack_id;}
private:
    string map[5][5];
    District people[9] {'a','b','c','d','e','f','g','h','i'};
    char jack_id;
    Holmes_team hol_tm;
    stack<District*> Card;
    int score[2];
    pair<string,string> ActCard[4];
};
District::District(char c): id(tolower(c)) {
    //initialize foreground road
    srand(id+time(NULL));
    set_direction(rand()%4 * 90);
}
int District::set_direction(int dir) {
    switch(dir) {
    case UP:
        if(id=='a'&& die)deadroad=NON;
        else deadroad=UP;
        break;
    case RIGHT:
        if(id=='a'&& die)deadroad=NON;
        else deadroad=RIGHT;
        break;
    case DOWN:
        if(id=='a'&& die)deadroad=NON;
        else deadroad=DOWN;
        break;
    case LEFT:
        if(id=='a'&& die)deadroad=NON;
        else deadroad=LEFT;
        break;
    default:
        return -1;
        break;
    }
    return 0;
}
int District::get_deg() {
    switch(deadroad) {
    case NON:
        return NON;
    case UP :
        return UP;
    case RIGHT :
        return RIGHT;
    case DOWN :
        return DOWN;
    case LEFT :
        return LEFT;
    }
}

Holmes_team::Holmes_team():pos_hol(4),pos_dog(8),pos_wat(12) {}
int Holmes_team::chpos(int partner,int pos) {
    switch(partner) {
    case Holmes :
        pos_hol = pos;
        break;
    case Watson :
        pos_wat = pos;
        break;
    case Dog :
        pos_dog = pos;
        break;
    default :
        return -1;
    }
    return 0;
}
void Holmes_team::get_all_pos() {
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
//     0,0 0,1 0,2 0,3 0,4
//     1,0 1,1 1,2 1,3 1,4
//     2,0 2,1 2,2 2,3 2,4
//     3,0 3,1 3,2 3,3 3,4
//     4,0 4,1 4,2 4,3 4,4
Desktop::Desktop() {
    score[0]=0;
    score[1]=0;
    int num[9] {0,1,2,3,4,5,6,7,8};
    // shuffle 9 districts
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(begin(people),end(people),std::default_random_engine(seed));
    // act card shuffle
    pair<string,string>  act[4] {
        pair<string,string>(string("draw card"),string("Watson")),
        pair<string,string>(string("Dog"),string("Holmes")),
        pair<string,string>(string("Spin"),string("3in1")),
        pair<string,string>(string("Spin"),string("Exchange"))
    };
    shuffle(begin(act),end(act),std::default_random_engine(seed));
    for(int i=0; i<4; i++)ActCard[i] = act[i];
    // push card
    District* cd[9];
    for(int i=0; i<9; i++)cd[i]=&people[i];
    shuffle(begin(cd),end(cd),std::default_random_engine(seed));
    for(int i=0; i<9; ++i)Card.push(cd[i]);
    jack_id = Card.top()->id; //initial jack identity;
    Card.pop();
}
void Desktop::parse_cmd(bool turn) {//0 Holmes;1 jacks
    string cmd;

    while(cout <<"Input the command :",cin >>cmd) {
       //system("cls");
        if(cmd == string("-draw")) {
            if(turn) {
                switch(Card.top()->id) {
                case 'a':
                    score[1]+= 1;
                    break;
                case 'b':
                    score[1]+= 2;
                    break;
                case 'c':
                    score[1]+= 1;
                    break;
                case 'd':
                    score[1]+= 1;
                    break;
                case 'e':
                    score[1]+= 1;
                    break;
                case 'f':
                    score[1]+= 1;
                    break;
                case 'g':
                    score[1]+= 1;
                    break;
                case 'h':
                    score[1]+= 0;
                    break;
                case 'i':
                    score[1]+= 0;
                    break;
                }
            } else {
                District* d = Card.top();
                printf("%c die\n",d->id);
                d->to_die();
                }
            Card.pop();
            break;

        } else if(cmd == string("-dog")) {
            int step;
            while(cout <<"Input the step :",cin >>step) {
                if(step > 0&& step <= 2 )break;
                else cout <<"Error step !\n";
            }
            hol_tm.chpos(Dog,(hol_tm.pos_dog+step)%12);
            break;
        } else if(cmd == string("-hol")) {
            int step;
            while(cout <<"Input the step :",cin >>step) {
                if(step > 0&& step <= 2 )break;
                else cout <<"Error step !\n";
            }
            hol_tm.chpos(Dog,(hol_tm.pos_hol+step)%12);
            break;
        } else if(cmd == string("-wat")) {
            int step;
            while(cout <<"Input the step :",cin >>step) {
                if(step > 0&& step <= 2 )break;
                else cout <<"Error step !\n";
            }
            hol_tm.chpos(Dog,(hol_tm.pos_wat+step)%12);
            break;
        } else if(cmd == string("-3in1")) {
            string charater;
            int cha;
            int step;
            while(cout <<"Select the charater :",cin >>charater){
                if(charater==string("Holmes"))cha= Holmes;break;
                if(charater==string("Watson"))cha= Watson;break;
                if(charater==string("Dog"))cha= Dog;break;
            }
            while(cout <<"Input the step :",cin >>step) {
                if(step > 0&& step <= 1 )break;
                else cout <<"Error step !\n";
            }
            hol_tm.chpos(cha,(hol_tm.pos_wat+step)%12);
            break;
        }else if(cmd == string("-spin")) {
            char sel;
            while(cout <<"Input the poeple(a~i):",cin >>sel) {
                if(sel>='a' && sel <='i')break;
                else cout <<"Error people !\n";
            }
            int deg;
            while(cout <<"Input the degree(90*n):",cin >>deg) {
                if(deg % 90 == 0  )break;
                else cout <<"Error degree !\n";
            }
            for(int i=0; i<9; i++ ) {
                if(people[i].id==sel)people[i].set_direction(deg % 360);
                break;
            }
            break;
        } else if(cmd == string("-xhcg")) {
            char sel;
            while(cout <<"Input the people(a~i):",cin >>sel) {
                if(sel>='a' && sel <='i')break;
                else cout <<"Error people !\n";
            }
            char sel2;
            while(cout <<"Input the people(a~i):",cin >>sel2) {
                if(sel>='a' && sel <='i')break;
                else cout <<"Error people !\n";
            }
            int p3=0,p4=0;
            for(int i=0; i<9; i++ ) {
                if(people[i].id==sel)p3=i;
                if(people[i].id==sel2)p4=i;
            }

            std::swap(people[p3],people[p4]);
            break;
        }else if(cmd == string("-help")){
        printf("-draw\n");
        printf("-dog [step] \n");
        printf("-wat [step] \n");
        printf("-hol [step]\n");
        printf("-3in1 [charater] [steps]\n");
        printf("-spin\n");
        printf("-xhcg [op1] [op2]\n");
        }
    }
}
void Desktop::print_map() {
    struct coord {
        int x;
        int y;
    } xy;
    auto trans_pos=[&](int pos) {
        switch(pos) {
        case 1:
            xy.y=1;
            xy.x=0;
            break;
        case 2:
            xy.y=2;
            xy.x=0;
            break;
        case 3:
            xy.y=3;
            xy.x=0;
            break;
        case 4:
            xy.y=4;
            xy.x=1;
            break;
        case 5:
            xy.y=4;
            xy.x=2;
            break;
        case 6:
            xy.y=4;
            xy.x=3;
            break;
        case 7:
            xy.y=3;
            xy.x=4;
            break;
        case 8:
            xy.y=2;
            xy.x=4;
            break;
        case 9:
            xy.y=1;
            xy.x=4;
            break;
        case 10:
            xy.y=0;
            xy.x=3;
            break;
        case 11:
            xy.y=0;
            xy.x=2;
            break;
        case 12:
            xy.y=0;
            xy.x=1;
            break;
        }
    };
    trans_pos(hol_tm.get_hol());
    map[xy.x][xy.y]="hol";
    trans_pos(hol_tm.get_wat());
    map[xy.x][xy.y]="wat";
    trans_pos(hol_tm.get_dog());
    map[xy.x][xy.y]="dog";
    int k=0;
    for(int i=1; i<4; ++i)
        for(int j=1; j<4; ++j) {
            if(people[k].isDie()) {
                map[i][j]=string()+'0';
                k++;
            } else map[i][j]=string()+people[k++].id;
        }
    for(int i=0; i<5; ++i) {
        for(int j=0; j<5; ++j) {
            cout <<map[i][j]<<"\t";
        }
        cout <<endl;
    }

}
void Desktop::print_status() {
    for(int i=0; i<9; ++i) {
        printf("%c's direction:%d\n",people[i].id,people[i].get_deg());
    }
    printf("Holmes score:%d\n",score[0]);
    printf("Jack score:%d\n",score[1]);

}
void Desktop::judge(){
    judge(hol_tm.get_dog());
    judge(hol_tm.get_wat());
    judge(hol_tm.get_hol());
}
void Desktop::judge(int pos){
    vector<District*> looker;
    bool see(0);
     int cur;
    switch(pos){
    case 1:case 2:case 3:
        cur = pos + 1;
        for(int i=1;i<4;i++){
            for(int j=0;j<9;j){
                if(map[i][cur]==string()+people[j].id){
                    if(people[j].get_deg()!=270){
                        looker.push_back(&people[j]);
                        if(jack_id == people[j].id)see= true;
                        break;
                    }else{break;}
                }
            }
        }
        break;
    case 4:case 5:case 6:
        cur= pos-3;
        for(int i=3;i>0;--i){
            for(int j=0;j<9;j){
                if(map[cur][i]==string()+people[j].id){
                    if(people[j].get_deg()!=270){
                        looker.push_back(&people[j]);
                        if(jack_id == people[j].id)see= true;
                        break;
                    }else{break;}
                }
            }
        }
        break;
    case 7:case 8:case 9://7 : 4 , 8: 3 ,9 : 2
        cur = 11-pos;
        for(int i=3;i>0;--i){
            for(int j=0;j<9;j){
                if(map[i][pos]==string()+people[j].id){
                    if(people[j].get_deg()!=270){
                        looker.push_back(&people[j]);
                        if(jack_id == people[j].id)see= true;
                        break;
                    }else{break;}
                }
            }
        }
    break;
    case 10:case 11:case 12:
        cur = 13 - pos;
        for(int i=3;i>0;--i){
            for(int j=0;j<9;j){
                if(map[cur][i]==string()+people[j].id){
                    if(people[j].get_deg()!=270){
                        looker.push_back(&people[j]);
                        if(jack_id == people[j].id)see= true;
                        break;
                    }else{break;}
                }
            }
        }
        break;
    }

    if(see){

        for(int i=0,sz=looker.size();i<sz;++i){
            looker[i]->to_die();
            printf("%c die\n",looker[i]->id);
        }
    }
    else{

    }
    return ;
}
