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
    bool turn[4]{0,1,1,0};
    Desktop desk;
    string id;
        while(printf("Choose your character :"),cin >>id){
            if(id=="Jack"|| id == "jack"){
                    printf("You are Jack , id : %c \n" ,desk.get_jack());
                    break;
            }
            else if(id=="Holmes"|| id =="holmes"){
                    printf("You are Holmes\n");
                    break;
            }
        }
    while(round != round_time){

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
        desk.parse_cmd(turn[cnt]);
        desk.judge();
        if(cnt==4){
            round ++;
            for(int i=0;i<4;i++)turn[i]=!turn[i];
        }
        cnt = (cnt + 1) % 4;
    }
	return 0;
}

