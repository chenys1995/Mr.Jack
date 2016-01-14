#include<cmath>
int seen_check(int dog_pos, int hol_pos, int wat_pos,int* direction, bool* dead);
int choose(int* num_seen, int num_dead, int num_of_option);
hol_last_turn_AI()
{
	switch(act){
		case "draw card":
			command = "-draw";
			break;
		case "Dog":
			int dog_pos = hol_tm.get_dog();
			int hol_pos = hol_tm.get_hol();
			int wat_pos = hol_tm.get_wat();
			int direction[9];
			bool dead[9];
			int num_dead = 0;
			int original_seen;
			int num_seen[2];
			for(int i = 0 ; i < 9; i++){
				dead[i] = people[i].isDie();
				if(dead[i])num_dead++;
			}
			for(int i = 0 ; i < 9; i++){
				direction[i] = people[i].get_deg();
			}
			original_seen = seen_check(dog_pos,hol_pos,wat_pos,direction,dead);
			num_seen[0] = seen_check(((dog_pos+1>12)?dog_pos-11:dog_pos+1),hol_pos,wat_pos,direction,dead);
			num_seen[1] = seen_check(((dog_pos+2>12)?dog_pos-10:dog_pos+2),hol_pos,wat_pos,direction,dead);
			int decision = choose(num_seen, num_dead, 2);
			if(decision == 0){
				command = "-dog 1";
			}
			else {
				command = "-dog 2";
			}
			break;
		case "Holmes":
			int dog_pos = hol_tm.get_dog();
			int hol_pos = hol_tm.get_hol();
			int wat_pos = hol_tm.get_wat();
			int direction[9];
			bool dead[9];
			int num_dead = 0;
			int original_seen;
			int num_seen[2];
			for(int i = 0 ; i < 9; i++){
				dead[i] = people[i].isDie();
				if(dead[i])num_dead++;
			}
			for(int i = 0 ; i < 9; i++){
				direction[i] = people[i].get_deg();
			}
			original_seen = seen_check(dog_pos,hol_pos,wat_pos,direction,dead);
			num_seen[0] = seen_check(dog_pos,((hol_pos+1>12)?hol_pos-11:hol_pos+1),wat_pos,direction,dead);
			num_seen[1] = seen_check(dog_pos,((hol_pos+2>12)?hol_pos-10:hol_pos+2),wat_pos,direction,dead);
			int decision = choose(num_seen, num_dead, 2);
			if(decision == 0){
				command = "-hol 1";
			}
			else {
				command = "-hol 2";
			}
			break;
		case "Watson":
			int dog_pos = hol_tm.get_dog();
			int hol_pos = hol_tm.get_hol();
			int wat_pos = hol_tm.get_wat();
			int direction[9];
			bool dead[9];
			int num_dead = 0;
			int original_seen;
			int num_seen[2];
			for(int i = 0 ; i < 9; i++){
				dead[i] = people[i].isDie();
				if(dead[i])num_dead++;
			}
			for(int i = 0 ; i < 9; i++){
				direction[i] = people[i].get_deg();
			}
			original_seen = seen_check(dog_pos,hol_pos,wat_pos,direction,dead);
			num_seen[0] = seen_check(dog_pos,hol_pos,((wat_pos+1>12)?wat_pos-11:wat_pos+1),direction,dead);
			num_seen[1] = seen_check(dog_pos,hol_pos,((wat_pos+2>12)?wat_pos-10:wat_pos+2),direction,dead);
			int decision = choose(num_seen, num_dead, 2);
			if(decision == 0){
				command = "-wat 1";
			}
			else {
				command = "-wat 2";
			}
			break;
		case "Spin":
			int dog_pos = hol_tm.get_dog();
			int hol_pos = hol_tm.get_hol();
			int wat_pos = hol_tm.get_wat();
			int direction[9];
			bool dead[9];
			int num_dead = 0;
			int original_seen;
			int num_seen[27];
			for(int i = 0 ; i < 9; i++){
				dead[i] = people[i].isDie();
				if(dead[i])num_dead++;
			}
			for(int i = 0 ; i < 9; i++){
				direction[i] = people[i].get_deg();
			}
			original_seen = seen_check(dog_pos,hol_pos,wat_pos,direction,dead);
			int now = 0;
			for(int i = 0 ; i < 9; i++){
				for(int j = 0 ;j < 4; j++){
					int tmp;
					if(direction[i] == 90*j )continue;
					tmp = direction[i];
					direction[i] = j*90 ;
					num_seen[now++] = seen_check(dog_pos,hol_pos,wat_pos,direction,dead);
					direction[i] = tmp;
				}
			}
			int decision = choose(num_seen, num_dead, 27);
			command = "-spin ";
			switch(direction[decision /3]){
				case 0:
					command += people[decision /3].id;
					command += " ";
					command += (decision %3+1)*90;
					break;
				case 90:
					command += people[decision /3].id;
					command += " ";
					command += ((decision %3 == 0)? 0 :(decision %3+1)*90);
					break;
				case 180:
					command += people[decision /3].id;
					command += " ";
					command += ((decision %3 == 2)? 270:(decision %3)*90);
					break;
				case 270:
					command += people[decision /3].id;
					command += " ";
					command += (decision %3)*90;
					break;
				default:
					command += people[decision /3].id;
					command += " ";
					command += 0;
					
			}
			break;
	}
}
int seen_check(int dog_pos, int hol_pos, int wat_pos,int* direction, bool* dead)
{
	bool seen[9];
	int num_seen = 0;
	for(int i = 0; i < 9; i++){
		seen[i] = false;
	}
	switch(hol_pos){
		case 1:
			if(direction[0] == 0)break;
			else if(direction[0] == 180||direction[3] == 0){
				seen[0]=true;
				break;
			}
			else if(direction[3] == 180||direction[6] == 0){
				seen[0] = true;
				seen[3] = true;
				break;
			}
			else {
				seen[0] = true;
				seen[3] = true;
				seen[6] = true;
				break;
			}
		case 2:
			if(direction[1] == 0)break;
			else if(direction[1] == 180||direction[4] == 0){
				seen[1]=true;
				break;
			}
			else if(direction[4] == 180||direction[7] == 0){
				seen[1] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[1] = true;
				seen[4] = true;
				seen[7] = true;
				break;
			}
		case 3:
			if(direction[2] == 0)break;
			else if(direction[2] == 180||direction[5] == 0){
				seen[2]=true;
				break;
			}
			else if(direction[5] == 180||direction[8] == 0){
				seen[2] = true;
				seen[5] = true;
				break;
			}
			else {
				seen[2] = true;
				seen[5] = true;
				seen[8] = true;
				break;
			}
		case 4:
			if(direction[2] ==90)break;
			else if(direction[2] == 270 || direction[1] == 90){
				seen[2] = true;
				break;
			}
			else if(direction[1] == 270 || direction[0] == 90){
				seen[2] = true;
				seen[1] = true;
				break;
			}
			else{
				seen[2] = true;
				seen[1] = true;
				seen[0] = true;
				break;
			}
		case 5:
			if(direction[5] ==90)break;
			else if(direction[5] == 270 || direction[4] == 90){
				seen[5] = true;
				break;
			}
			else if(direction[4] == 270 || direction[3] == 90){
				seen[5] = true;
				seen[4] = true;
				break;
			}
			else{
				seen[5] = true;
				seen[4] = true;
				seen[3] = true;
				break;
			}
		case 6:
			if(direction[8] ==90)break;
			else if(direction[8] == 270 || direction[7] == 90){
				seen[8] = true;
				break;
			}
			else if(direction[7] == 270 || direction[6] == 90){
				seen[8] = true;
				seen[7] = true;
				break;
			}
			else{
				seen[8] = true;
				seen[7] = true;
				seen[6] = true;
				break;
			}
		case 7:
			if(direction[8] ==180)break;
			else if(direction[8] ==0||direction[5] ==180){
				seen[8] = true;
				break;
			}
			else if(direction[5] == 0|| direction[2] ==180){
				seen[8] = true;
				seen[5] = true;
				break;
			}
			else {
				seen[8] = true;
				seen[5] = true;
				seen[2] = true;
				break;
			}
		case 8:
			if(direction[7] ==180)break;
			else if(direction[7] ==0||direction[4] ==180){
				seen[7] = true;
				break;
			}
			else if(direction[4] == 0|| direction[1] ==180){
				seen[7] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[7] = true;
				seen[4] = true;
				seen[1] = true;
				break;
			}
		case 9:
			if(direction[6] ==180)break;
			else if(direction[6] ==0||direction[3] ==180){
				seen[6] = true;
				break;
			}
			else if(direction[3] == 0|| direction[0] ==180){
				seen[6] = true;
				seen[3] = true;
				break;
			}
			else {
				seen[6] = true;
				seen[3] = true;
				seen[0] = true;
				break;
			}
		case 10:
			if(direction[6] ==270)break;
			else if(direction[6] ==90|| direction[7] ==270){
				seen[6] = true;
				break;
			}
			else if(direction[7] ==90|| direction[8] ==270){
				seen[6] = true;
				seen[7] = true;
				break;
			}
			else {
				seen[6] = true;
				seen[7] = true;
				seen[8] = true;
				break;
			}
		case 11:
			if(direction[3] ==270)break;
			else if(direction[3] ==90|| direction[4] ==270){
				seen[3] = true;
				break;
			}
			else if(direction[4] ==90|| direction[5] == 270){
				seen[3] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[3] = true;
				seen[4] = true;
				seen[5] = true;
				break;
			}
		case 12:
			if(direction[0] ==270)break;
			else if(direction[0] ==90||direction[1] ==270){
				seen[0] = true;
				break;
			}
			else if(direction[1] ==90||direction[2] ==270){
				seen[0] = true;
				seen[1] = true;
				break;
			}
			else {
				seen[0] = true;
				seen[1] = true;
				seen[2] = true;
				break;
			}
		default:
			cout<<"get_hol error in seen_check\n";
	}
	switch(dog_pos){
		case 1:
			if(direction[0] == 0)break;
			else if(direction[0] == 180||direction[3] == 0){
				seen[0]=true;
				break;
			}
			else if(direction[3] == 180||direction[6] == 0){
				seen[0] = true;
				seen[3] = true;
				break;
			}
			else {
				seen[0] = true;
				seen[3] = true;
				seen[6] = true;
				break;
			}
		case 2:
			if(direction[1] == 0)break;
			else if(direction[1] == 180||direction[4] == 0){
				seen[1]=true;
				break;
			}
			else if(direction[4] == 180||direction[7] == 0){
				seen[1] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[1] = true;
				seen[4] = true;
				seen[7] = true;
				break;
			}
		case 3:
			if(direction[2] == 0)break;
			else if(direction[2] == 180||direction[5] == 0){
				seen[2]=true;
				break;
			}
			else if(direction[5] == 180||direction[8] == 0){
				seen[2] = true;
				seen[5] = true;
				break;
			}
			else {
				seen[2] = true;
				seen[5] = true;
				seen[8] = true;
				break;
			}
		case 4:
			if(direction[2] ==90)break;
			else if(direction[2] == 270 || direction[1] == 90){
				seen[2] = true;
				break;
			}
			else if(direction[1] == 270 || direction[0] == 90){
				seen[2] = true;
				seen[1] = true;
				break;
			}
			else{
				seen[2] = true;
				seen[1] = true;
				seen[0] = true;
				break;
			}
		case 5:
			if(direction[5] ==90)break;
			else if(direction[5] == 270 || direction[4] == 90){
				seen[5] = true;
				break;
			}
			else if(direction[4] == 270 || direction[3] == 90){
				seen[5] = true;
				seen[4] = true;
				break;
			}
			else{
				seen[5] = true;
				seen[4] = true;
				seen[3] = true;
				break;
			}
		case 6:
			if(direction[8] ==90)break;
			else if(direction[8] == 270 || direction[7] == 90){
				seen[8] = true;
				break;
			}
			else if(direction[7] == 270 || direction[6] == 90){
				seen[8] = true;
				seen[7] = true;
				break;
			}
			else{
				seen[8] = true;
				seen[7] = true;
				seen[6] = true;
				break;
			}
		case 7:
			if(direction[8] ==180)break;
			else if(direction[8] ==0||direction[5] ==180){
				seen[8] = true;
				break;
			}
			else if(direction[5] == 0|| direction[2] ==180){
				seen[8] = true;
				seen[5] = true;
				break;
			}
			else {
				seen[8] = true;
				seen[5] = true;
				seen[2] = true;
				break;
			}
		case 8:
			if(direction[7] ==180)break;
			else if(direction[7] ==0||direction[4] ==180){
				seen[7] = true;
				break;
			}
			else if(direction[4] == 0|| direction[1] ==180){
				seen[7] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[7] = true;
				seen[4] = true;
				seen[1] = true;
				break;
			}
		case 9:
			if(direction[6] ==180)break;
			else if(direction[6] ==0||direction[3] ==180){
				seen[6] = true;
				break;
			}
			else if(direction[3] == 0|| direction[0] ==180){
				seen[6] = true;
				seen[3] = true;
				break;
			}
			else {
				seen[6] = true;
				seen[3] = true;
				seen[0] = true;
				break;
			}
		case 10:
			if(direction[6] ==270)break;
			else if(direction[6] ==90|| direction[7] ==270){
				seen[6] = true;
				break;
			}
			else if(direction[7] ==90|| direction[8] ==270){
				seen[6] = true;
				seen[7] = true;
				break;
			}
			else {
				seen[6] = true;
				seen[7] = true;
				seen[8] = true;
				break;
			}
		case 11:
			if(direction[3] ==270)break;
			else if(direction[3] ==90|| direction[4] ==270){
				seen[3] = true;
				break;
			}
			else if(direction[4] ==90|| direction[5] == 270){
				seen[3] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[3] = true;
				seen[4] = true;
				seen[5] = true;
				break;
			}
		case 12:
			if(direction[0] ==270)break;
			else if(direction[0] ==90||direction[1] ==270){
				seen[0] = true;
				break;
			}
			else if(direction[1] ==90||direction[2] ==270){
				seen[0] = true;
				seen[1] = true;
				break;
			}
			else {
				seen[0] = true;
				seen[1] = true;
				seen[2] = true;
				break;
			}
		default:
			cout<<"get_dog error in seen_check\n";
	}
	switch(wat_pos){
		case 1:
			if(direction[0] == 0)break;
			else if(direction[0] == 180||direction[3] == 0){
				seen[0]=true;
				break;
			}
			else if(direction[3] == 180||direction[6] == 0){
				seen[0] = true;
				seen[3] = true;
				break;
			}
			else {
				seen[0] = true;
				seen[3] = true;
				seen[6] = true;
				break;
			}
		case 2:
			if(direction[1] == 0)break;
			else if(direction[1] == 180||direction[4] == 0){
				seen[1]=true;
				break;
			}
			else if(direction[4] == 180||direction[7] == 0){
				seen[1] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[1] = true;
				seen[4] = true;
				seen[7] = true;
				break;
			}
		case 3:
			if(direction[2] == 0)break;
			else if(direction[2] == 180||direction[5] == 0){
				seen[2]=true;
				break;
			}
			else if(direction[5] == 180||direction[8] == 0){
				seen[2] = true;
				seen[5] = true;
				break;
			}
			else {
				seen[2] = true;
				seen[5] = true;
				seen[8] = true;
				break;
			}
		case 4:
			if(direction[2] ==90)break;
			else if(direction[2] == 270 || direction[1] == 90){
				seen[2] = true;
				break;
			}
			else if(direction[1] == 270 || direction[0] == 90){
				seen[2] = true;
				seen[1] = true;
				break;
			}
			else{
				seen[2] = true;
				seen[1] = true;
				seen[0] = true;
				break;
			}
		case 5:
			if(direction[5] ==90)break;
			else if(direction[5] == 270 || direction[4] == 90){
				seen[5] = true;
				break;
			}
			else if(direction[4] == 270 || direction[3] == 90){
				seen[5] = true;
				seen[4] = true;
				break;
			}
			else{
				seen[5] = true;
				seen[4] = true;
				seen[3] = true;
				break;
			}
		case 6:
			if(direction[8] ==90)break;
			else if(direction[8] == 270 || direction[7] == 90){
				seen[8] = true;
				break;
			}
			else if(direction[7] == 270 || direction[6] == 90){
				seen[8] = true;
				seen[7] = true;
				break;
			}
			else{
				seen[8] = true;
				seen[7] = true;
				seen[6] = true;
				break;
			}
		case 7:
			if(direction[8] ==180)break;
			else if(direction[8] ==0||direction[5] ==180){
				seen[8] = true;
				break;
			}
			else if(direction[5] == 0|| direction[2] ==180){
				seen[8] = true;
				seen[5] = true;
				break;
			}
			else {
				seen[8] = true;
				seen[5] = true;
				seen[2] = true;
				break;
			}
		case 8:
			if(direction[7] ==180)break;
			else if(direction[7] ==0||direction[4] ==180){
				seen[7] = true;
				break;
			}
			else if(direction[4] == 0|| direction[1] ==180){
				seen[7] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[7] = true;
				seen[4] = true;
				seen[1] = true;
				break;
			}
		case 9:
			if(direction[6] ==180)break;
			else if(direction[6] ==0||direction[3] ==180){
				seen[6] = true;
				break;
			}
			else if(direction[3] == 0|| direction[0] ==180){
				seen[6] = true;
				seen[3] = true;
				break;
			}
			else {
				seen[6] = true;
				seen[3] = true;
				seen[0] = true;
				break;
			}
		case 10:
			if(direction[6] ==270)break;
			else if(direction[6] ==90|| direction[7] ==270){
				seen[6] = true;
				break;
			}
			else if(direction[7] ==90|| direction[8] ==270){
				seen[6] = true;
				seen[7] = true;
				break;
			}
			else {
				seen[6] = true;
				seen[7] = true;
				seen[8] = true;
				break;
			}
		case 11:
			if(direction[3] ==270)break;
			else if(direction[3] ==90|| direction[4] ==270){
				seen[3] = true;
				break;
			}
			else if(direction[4] ==90|| direction[5] == 270){
				seen[3] = true;
				seen[4] = true;
				break;
			}
			else {
				seen[3] = true;
				seen[4] = true;
				seen[5] = true;
				break;
			}
		case 12:
			if(direction[0] ==270)break;
			else if(direction[0] ==90||direction[1] ==270){
				seen[0] = true;
				break;
			}
			else if(direction[1] ==90||direction[2] ==270){
				seen[0] = true;
				seen[1] = true;
				break;
			}
			else {
				seen[0] = true;
				seen[1] = true;
				seen[2] = true;
				break;
			}
		default:
			cout<<"get_hol error in seen_check\n";
	}
	for(int i = 0; i < 9; i++){
		if(dead[i]);
		else {
			if(seen[i])num_seen ++;
		}
	}
	return num_seen;
}
int choose(int* num_seen, int num_dead, int num_of_option)
{
	float optimal = (9-(float)num_dead)/2;
	float best = 10;
	int tmp = -1;

	for(int i = 0; i < num_of_option; i++){
		if(abs((float)num_seen[i]-optimal)<best){
			best = abs((float)num_seen[i]-optimal);
			tmp = i;
		}
	}
	return tmp;
}