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
    int set_direction(int deg); // set the direction of card; //deg = 0~270
    int get_deg(); //get the direction of card now;
    inline bool die() {
        dead = true;
    }; // turn over the card
    inline bool isDie() {
        return dead;
    };
    char id;
private:
    int deadroad;//only one road is dead
    bool dead =0;

};
class Holmes_team {
public :
    friend class Desktop;
    Holmes_team();
    int set_character_pos(int partner,int pos);//set posistion to the character
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
    void parse_cmd(bool turn, int cnt, int* act_lock, bool* used);
    void print_map();
    void print_status();
    //inline void top(){printf("card top :%c\n",Card.top());};
    friend void print_act(const Desktop& desk,int* act_lock);
    inline char get_jack(){return jack_id;}
private:
    char display_map[9];
    District people[9] {'a','b','c','d','e','f','g','h','i'};
    char jack_id;
    Holmes_team hol_tm;
    stack<char> Card;
    int score[2];
    pair<string,string> ActCard[4];
};
District::District(char c): id(tolower(c)) {
    //initialize foreground road
    srand(id+time(NULL));
    set_direction(rand()%4 * 90);
}
int District::set_direction(int deg) {
    switch(deg) {
    case 0:
        if(id=='a'&& dead)deadroad=NON;
        else deadroad=UP;
        break;
    case 90:
        if(id=='a'&& dead)deadroad=NON;
        else deadroad=RIGHT;
        break;
    case 180:
        if(id=='a'&& dead)deadroad=NON;
        else deadroad=DOWN;
        break;
    case 270:
        if(id=='a'&& dead)deadroad=NON;
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
        return 360;
    case UP :
        return 0;
    case RIGHT :
        return 90;
    case DOWN :
        return 180;
    case LEFT :
        return 270;
    }
}

Holmes_team::Holmes_team():pos_hol(4),pos_dog(8),pos_wat(12) {}
int Holmes_team::set_character_pos(int partner,int step) {
    switch(partner) {
    case Holmes :
        pos_hol += step;
		if(pos_hol>12)pos_hol-=12;
        break;
    case Watson :
        pos_wat += step;
		if(pos_wat>12)pos_wat-=12;
        break;
    case Dog :
        pos_dog += step;
		if(pos_dog>12)pos_dog-=12;
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
//     0,0 1,0 2,0 3,0 4,0
//     0,1 1,1 2,1 3,1 4,1
//     0,2 1,2 2,2 3,2 4,2
//     0,3 1,3 2,3 3,3 4,3
//     0,4 1,4 2,4 3,4 4,4
Desktop::Desktop() {
    score[0]=0;
    score[1]=0;
    int num[9] {0,1,2,3,4,5,6,7,8};
    // shuffle 9 districts
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(begin(num),end(num),std::default_random_engine(seed));
    char* p=display_map;
    for(int i=0; i<9; ++i)*p=people[num[i]].id,++p;
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
    char cd[9]{'a','b','c','d','e','f','g','h','i'};
    shuffle(begin(cd),end(cd),std::default_random_engine(seed));
    for(int i=0; i<9; ++i)Card.push(cd[i]);
    jack_id = Card.top(); //initial jack identity;
    Card.pop();
}
void Desktop::parse_cmd(bool turn, int cnt, int* act_lock, bool* used) {//0 Holmes;1 jacks
    string cmd;
	string acts[4];
	
	for(int i=0;i<4;++i){
		if(act_lock[i])acts[i] = desk.ActCard[i].first;
		else if(!act_lock[i])acts[i] = desk.ActCard.second;
	}
	bool flag = false;
    while(cout <<"Input the command (it's the "<<((cnt==0)?"first":(cnt==1)?"second":(cnt==2)?"third":"forth")<<" move):",cin >>cmd) {
        if(cmd == string("-draw")) {
			for(int i = 0; i < 4; i++){
				if(acts[i]=="draw card"&&used[i]==false){//if draw is available
					flag = true;
					used[i] = true;
					if(turn) {
						switch(Card.top()) {
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
						Card.pop();
					} 
					else {
						char d = Card.top();
						for(int i=0; i<9; i++ ) {
							if(people[i].id==d)people[i].die();
							break;
						}
						Card.pop();
					}
					break;
				}
			}
			if(flag==false)cout<<"\"draw\"is not available\n";
            else break;
            
        } 
		else if(cmd == string("-dog")) {
			for(int i = 0 ; i < 4; i++){
				if(acts[i]=="Dog"&&used[i]==false){
					used[i]=true;
					flag=true;
					int step;
					while(cout <<"Input the step :",cin >>step) {
						if(step > 0&& step <= 2 )break;
						else cout <<"Error step !\n";
					}
					hol_tm.set_character_pos(Dog,step);
					break;
				}
			}
			if(flag==false)cout<<"\"dog\" is not available\n";
			else break;
            
        } 
		else if(cmd == string("-hol")) {
			for(int i = 0; i<4 ; i++){
				if(acts[i]=="Holmes"&&used[i]==false){
					flag = true;
					used[i]=true;
					int step;
					while(cout <<"Input the step :",cin >>step) {
						if(step > 0&& step <= 2 )break;
						else cout <<"Error step !\n";
					}
					hol_tm.set_character_pos(Dog,step);
					break;
				}
			}
			if(flag==false)cout<<"\"Holmes\" is not available\n";
			else break;
            
        } 
		else if(cmd == string("-wat")) {
			for(int i = 0; i < 4; i++){
				if(acts[i]=="Watson"&&used[i]==false){
					used[i]=true;
					flag = true;
					int step;
					while(cout <<"Input the step :",cin >>step) {
						if(step > 0&& step <= 2 )break;
						else cout <<"Error step !\n";
					}
					hol_tm.set_character_pos(Dog,step)%12);
					break;
				}
			}
			if(flag ==false)cout<<"\"Watson\" is not available\n";
			else break;
            
        } 
		else if(cmd == string("-3in1")) {
			for(int i = 0 ; i < 4; i++){
				if("3in1"==acts[i]&&used[i]==false){
					used[i]=true;
					flag = true; 
					string character;
					int cha;
					int step;
					if(turn){//jack
						while(cout <<"Select the character (Holmes, Watson, Dog or no):",cin >>character){
							if(character==string("Holmes")){cha= Holmes;break;}
							else if(character==string("Watson")){cha= Watson;break;}
							else if(character==string("Dog")){cha= Dog;break;}
							else if(character==string("no")){cha = 30;break;}
							else cout<<"error character\n";
						}
						if(cha == 30)break;
						else {
							while(cout <<"Input the step :",cin >>step) {
								if(step > 0&& step <= 1 )break;
								else cout <<"Error step !\n";
							}
						}
					}
			
					else {
						while(cout <<"Select the character (Holmes, Watson or Dog):",cin >>character){
							if(character==string("Holmes"))cha= Holmes;break;
							if(character==string("Watson"))cha= Watson;break;
							if(character==string("Dog"))cha= Dog;break;
						}
						while(cout <<"Input the step :",cin >>step) {
							if(step > 0&& step <= 1 )break;
							else cout <<"Error step !\n";
						}
						hol_tm.set_character_pos(cha,step);
						break;
					}
				}
			}
			if(flag==false)cout<<"\"3in1\" is not available\n";
           
        }
		else if(cmd == string("-spin")) {
			for(int i = 0; i < 4; i++){
				if(acts[i]=="Spin"&&used[i]==false){
					used[i]=true;
					flag = true;
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
				}
			}
			if(flag == false)cout<<"\"Spin\" is not available\n";
			else break;
            
        } 
		else if(cmd == string("-xhcg")) {
			for(int i = 0 ;i < 4; i++){
				if(acts[i]=="Exchange"&&used[i]==false){
					used[i]=true;
					flag = true;
					char sel1, sel2;
					while(cout<<"Input the first selection(a~i):"){
						cin>>sel1;
						cout<<"Input the second selection(a~i):";
						cin>>sel2;
						if(sel1>='a'&&sel1<='i'&&sel2>='a'&&sel2<='i'&&sel1!=sel2)break;
						else cout<<"Input error!\n";
					}
					int p1=0,p2=0,p3=0,p4=0;
					for(int i=0; i<9; i++ ) {
						if(display_map[i]==sel1)p1=i;
						if(display_map[i]==sel2)p2=i;
						if(people[i].id==sel1)p3=i;
						if(people[i].id==sel2)p4=i;
					}
					std::swap(display_map[p1],display_map[p2]);
					std::swap(people[p3],people[p4]);
					break;
				}
				
			}
			if(flag==false)cout<<\"Exchange\" is not available\n";
			else break;
			
        }
		else if(cmd == string("-help")){
			printf("-draw\n");
			printf("-dog [step] \n");
			printf("-wat [step] \n");
			printf("-hol [step] \n");
			printf("-3in1 [charater] [steps]\n");
			printf("-spin\n");
			printf("-xhcg [op1] [op2]\n");
        }
		else printf("wrong command\n");
    }
}
void Desktop::print_map() {
    string map[5][5];
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
            int ch;
            for(int i=0; i<9; i++ ) {
                if(people[i].id==display_map[k])ch=i;
            }
            if(people[ch].isDie()) {
                map[i][j]=string()+'0';
                k++;
            } else map[i][j]=string()+display_map[k++];
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
}