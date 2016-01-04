#include "desktop.h"

using namespace std;
const int round_time = 8;
void print_act(const Desktop& desk,int* act_lock){

            for(int i=0;i<4;++i){
                if(act_lock[i]){printf("ActCard %d pos: ",i+1);
                cout <<desk.ActCard[i].first<<endl;}
                else if(!act_lock[i]){printf("ActCard %d back: ",i+1);
                cout <<desk.ActCard[i].second<<endl;}
                else printf("ActCard %d : Not available\n",i+1);
            }
}
int main()
{
    int round(0),cnt=0;
    bool turn[4]{0,1,1,0};//false = holmes, true = jack
	bool used[4]{false,false,false,false};
    Desktop desk;
    while(round != round_time){
        string id;
        while(printf("Choose your character :"),cin >>id){
            if(id==string("Jack")){
                    printf("You are Jack , id : %c \n" ,desk.get_jack());
                    break;
            }
            else if(id==string("Holmes")){
                    printf("You are Holmes\n");
                    break;
            }
        }
        string cmd;
        // throw action card
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        int act_lock[4];
        srand(seed);
        if(!(round&1))
            for(int i=0;i<4;++i)
                act_lock[i]=rand()%2;//1 front ;0 back;
        // throw done
        printf("This turn is :");
        if(turn[cnt])printf("Jack\n");
        else printf("Holmes\n");
        desk.print_map(); // print desktop
        desk.print_status(); // status of districts
        print_act(desk,act_lock);// available act card
        desk.parse_cmd(turn[cnt],cnt,act_lock,used);
        if(cnt==4){
			round ++;
			for(int i = 0; i < 4; i++)used[i]= false;
		}
        for(int i=0;i<4;i++)turn[i]=!turn[i];
        cnt = (cnt + 1) % 4;
    }
	return 0;
}

