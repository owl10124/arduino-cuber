//lame program to generate test cases for the kociemba thingy, 
//set input as UUUUUUUUUFFFFFFFFFDDDDDDDDDRRRRRRRRRBBBBBBBBBLLLLLLLLL first for the normal cube
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <cstring>
#include <queue>
using namespace std;
char apple[54];
void back_turn_c(){
    char temp = apple[42];
  apple[42] = apple[44];
  apple[44] = apple[38];
  apple[38] = apple[36];
  apple[36] = temp;
  temp = apple[39];
  apple[39] = apple[43];
  apple[43] = apple[41];
  apple[41] = apple[37];
  apple[37] = temp;
  temp = apple[32];
  apple[32] = apple[25];
  apple[25] = apple[48];
  apple[48] = apple[1];
  apple[1] = temp;
  temp = apple[29];
  apple[29] = apple[26];
  apple[26] = apple[51];
  apple[51] = apple[0];
  apple[0] = temp;
  temp = apple[35];
  apple[35] = apple[24];
  apple[24] = apple[45];
  apple[45] = apple[2];
  apple[2] = temp;
}
void back_turn_ac(){
    back_turn_c();
    back_turn_c();
    back_turn_c();

}
void down_turn_c(){
    char temp = apple[21];
  apple[21] = apple[25];
  apple[25] = apple[23];
  apple[23] = apple[19];
  apple[19] = temp;
  temp = apple[24];
  apple[24] = apple[26];
  apple[26] = apple[20];
  apple[20] = apple[18];
  apple[18] = temp;
  temp = apple[52];
  apple[52] = apple[43];
  apple[43] = apple[34];
  apple[34] = apple[16];
  apple[16] = temp;
  temp = apple[44];
  apple[44] = apple[35];
  apple[35] = apple[17];
  apple[17] = apple[53];
  apple[53] = temp;
  temp = apple[42];
  apple[42] = apple[33];
  apple[33] = apple[15];
  apple[15] = apple[51];
  apple[51] = temp;

}
void down_turn_ac(){
    down_turn_c();
    down_turn_c();
    down_turn_c();
}
void left_turn_c(){


    char temp = apple[48];
  apple[48] = apple[52];
  apple[52] = apple[50];
  apple[50] = apple[46];
  apple[46] = temp;
  temp = apple[51];
  apple[51] = apple[53];
  apple[53] = apple[47];
  apple[47] = apple[45];
  apple[45] = temp;
  temp = apple[44];
  apple[44] = apple[18];
  apple[18] = apple[9];
  apple[9] = apple[0];
  apple[0] = temp;
  temp = apple[41];
  apple[41] = apple[21];
  apple[21] = apple[12];
  apple[12] = apple[3];
  apple[3] = temp;
  temp = apple[38];
  apple[38] = apple[24];
  apple[24] = apple[15];
  apple[15] = apple[6];
  apple[6] = temp;

}
void left_turn_ac(){
    left_turn_c();
    left_turn_c();
    left_turn_c();
}
void up_turn_c(){
    char temp = apple[0];
  apple[0] = apple[6];
  apple[6] = apple[8];
  apple[8] = apple[2];
  apple[2] = temp;
  temp = apple[1];
  apple[1] = apple[3];
  apple[3] = apple[7];
  apple[7] = apple[5];
  apple[5] = temp;
  temp = apple[9];
  apple[9] = apple[27];
  apple[27] = apple[36];
  apple[36] = apple[45];
  apple[45] = temp;
  temp = apple[10];
  apple[10] = apple[28];
  apple[28] = apple[37];
  apple[37] = apple[46];
  apple[46] = temp;
  temp = apple[11];
  apple[11] = apple[29];
  apple[29] = apple[38];
  apple[38] = apple[47];
  apple[47] = temp;
}
void up_turn_ac(){
    up_turn_c();
    up_turn_c();
    up_turn_c();

}
void right_turn_c(){
  char temp = apple[27];
  apple[27] = apple[33];
  apple[33] = apple[35];
  apple[35] = apple[29];
  apple[29] = temp;
  temp = apple[28];
  apple[28] = apple[30];
  apple[30] = apple[34];
  apple[34] = apple[32];
  apple[32] = temp;
  temp = apple[8];
  apple[8] = apple[17];
  apple[17] = apple[26];
  apple[26] = apple[36];
  apple[36] = temp;
  temp = apple[5];
  apple[5] = apple[14];
  apple[14] = apple[23];
  apple[23] = apple[39];
  apple[39] = temp;
  temp = apple[2];
  apple[2] = apple[11];
  apple[11] = apple[20];
  apple[20] = apple[42];
  apple[42] = temp;

}
void right_turn_ac(){
    right_turn_c();
    right_turn_c();
    right_turn_c();

}
void front_turn_c(){
  char temp = apple[9];
  apple[9] = apple[15];
  apple[15] = apple[17];
  apple[17] = apple[11];
  apple[11] = temp;
  temp = apple[10];
  apple[10] = apple[12];
  apple[12] = apple[16];
  apple[16] = apple[14];
  apple[14] = temp;
  temp = apple[8];
  apple[8] = apple[47];
  apple[47] = apple[18];
  apple[18] = apple[33];
  apple[33] = temp;
  temp = apple[6];
  apple[6] = apple[53];
  apple[53] = apple[20];
  apple[20] = apple[27];
  apple[27] = temp;
  temp = apple[7];
  apple[7] = apple[50];
  apple[50] = apple[19];
  apple[19] = apple[30];
  apple[30] = temp;

}
void front_turn_ac(){
    front_turn_c();
    front_turn_c();
    front_turn_c();


}

void print_faces(){
    printf("%c %c %c\n",apple[0],apple[1],apple[2]);
    printf("%c %c %c\n",apple[3],apple[4],apple[5]);
    printf("%c %c %c\n",apple[6],apple[7],apple[8]);
    printf("%c %c %c %c %c %c %c %c %c %c %c %c\n",apple[9],apple[10],apple[11],apple[27],apple[28],apple[29],apple[36],apple[37],apple[38],apple[45],apple[46],apple[47]);
    printf("%c %c %c %c %c %c %c %c %c %c %c %c\n",apple[12],apple[13],apple[14],apple[30],apple[31],apple[32],apple[39],apple[40],apple[41],apple[48],apple[49],apple[50]);
    printf("%c %c %c %c %c %c %c %c %c %c %c %c\n",apple[15],apple[16],apple[17],apple[33],apple[34],apple[35],apple[42],apple[43],apple[44],apple[51],apple[52],apple[53]);
    printf("%c %c %c\n",apple[18],apple[19],apple[20]);
    printf("%c %c %c\n",apple[21],apple[22],apple[23]);
    printf("%c %c %c\n\n\n",apple[24],apple[25],apple[26]);





}
void turn_cube(int order){
        if (order == 5) {front_turn_c(); printf("F");}
        if (order == 6) {front_turn_ac(); printf("f");}
        if (order == 11) {right_turn_c(); printf("R");}
        if (order == 12) {right_turn_ac(); printf("r");}
        if (order == 1) {up_turn_c(); printf("U");}
        if (order == 2) {up_turn_ac(); printf("u");}
        if (order == 9) {left_turn_c(); printf("L");}
        if (order == 10) {left_turn_ac(); printf("l");}
        if (order == 3) {down_turn_c(); printf("D");}
        if (order == 4) {down_turn_ac(); printf("d");}
        if (order == 7) {back_turn_c(); printf("B");}
        if (order == 8) {back_turn_ac(); printf("b");}
        //printf("%s\n",apple);


}
bool check_cube(){
    //printf("%d\n",sizeof(apple));
    char current;
    for (int i=  0; i < sizeof(apple); i++){
        int color = i/9;
        switch(color){
            case 0: current = 'Y'; break;
            case 1: current = 'O'; break;
            case 2: current = 'W'; break;
            case 3: current = 'B'; break;
            case 4: current = 'R'; break;
            case 5: current = 'G'; break;
        }
            if (apple[i] != current) {
                    //printf("%c (apple[%d]) does not match %c,false\n",apple[i],i,current);
                    return false;
            }
        }
        printf("YAY ^_^\n");
        return true;


    }


int main(){
    vector<char> solution;
    int links[54];
    links[1] = 37;
    links[3] = 46;
    links[5] = 28;
    links[7] = 10;
    links[10] = 7;
    links[12] = 50;
    links[14] = 30;
    links[16] = 19;
    links[19] = 16;
    links[21] = 52;
    links[23] = 34;
    links[25] = 43;
    links[28] = 5;
    links[30] = 14;
    links[32] = 39;
    links[34] = 23;
    links[37] = 1;
    links[39] = 32;
    links[41] = 48;
    links[43] = 25;
    links[46] = 3;
    links[48] = 41;
    links[50] = 12;
    links[52] = 21;

    //queue<char> sequenceofmoves;
    for (int i =0 ; i < 54; i++){
        scanf(" %c",&apple[i]);
    }



    //print_faces();


    printf("\n");
    int k = 1;
    for (k = 1; k < 55; k++){
        //printf("%d\t",k);

        //if (/*apple[k] == apple[4] && */k % 9 % 2 == 1) printf("%d (%c) %d (%c)\n",k,apple[k],links[k],apple[links[k]]);
    }

    /*for (int i = 1; i <= 12; i++){

        if ((i) % 2 == 0){
            turn_cube(i);
            if (check_cube()) exit(0);
            turn_cube(i-1);
        }
        else{
             turn_cube(i);
             if (check_cube()) exit(0);
             turn_cube(i+1);
        }

    }*/
    // /*
    char order;
    while (scanf(" %c",&order) != EOF){
        if (order == 'F') {front_turn_c(); solution.push_back('F');solution.push_back('\'');}
        if (order == 'f') {front_turn_ac(); solution.push_back('F');}
        if (order == 'R') {right_turn_c(); solution.push_back('R');solution.push_back('\'');}
        if (order == 'r') {right_turn_ac(); solution.push_back('R');}
        if (order == 'U') {up_turn_c(); solution.push_back('U');solution.push_back('\'');}
        if (order == 'u') {up_turn_ac(); solution.push_back('U');}
        if (order == 'L') {left_turn_c(); solution.push_back('L');solution.push_back('\'');}
        if (order == 'l') {left_turn_ac(); solution.push_back('L');}
        if (order == 'D') {down_turn_c(); solution.push_back('D');solution.push_back('\'');}
        if (order == 'd') {down_turn_ac(); solution.push_back('D');}
        if (order == 'B') {back_turn_c(); solution.push_back('B');solution.push_back('\'');}
        if (order == 'b') {back_turn_ac(); solution.push_back('B');}
        for (int i = 0; i < 6; i++){
            int startpoint = 0;
            if (i == 0) startpoint = 0;
            if (i == 1) startpoint = 27;
            if (i == 2) startpoint = 9;
            if (i == 3) startpoint = 18;
            if (i == 4) startpoint = 45;
            if (i == 5) startpoint = 36;
            for (int j = startpoint; j < startpoint+9; j++){
                printf("%c",apple[j]);

            }
        }
            printf("\nsolution so far is: ");
            for (int i = 0; i < solution.size(); i++){
                printf("%c",solution[i]);
            }


        printf("\n");

    }
    // */
    /*
     int scramble;
    scanf("%d",&scramble);
    queue<int> moves;
    for (int i = 0; i < scramble; i++){
        int order = rand() % 12;
        moves.push(order);
        if (order == 1) front_turn_c();
        if (order == 2) front_turn_ac();
        if (order == 3) right_turn_c();
        if (order == 4) right_turn_ac();
        if (order == 5) up_turn_c();
        if (order == 6) up_turn_ac();
        if (order == 7) left_turn_c();
        if (order == 8) left_turn_ac();
        if (order == 9) down_turn_c();
        if (order == 10) down_turn_ac();
        if (order == 11) back_turn_c();
        if (order == 0) back_turn_ac();
        print_faces();
    }
    while (!moves.empty()){
        int order = moves.front();
        moves.pop();
        if (order == 1) printf("F");
        if (order == 2) printf("f");
        if (order == 3) printf("R");
        if (order == 4) printf("r");
        if (order == 5) printf("U");
        if (order == 6) printf("u");
        if (order == 7) printf("L");
        if (order == 8) printf("l");
        if (order == 9) printf("D");
        if (order == 10) printf("d");
        if (order == 11) printf("B");
        if (order == 0) printf("b");
    }




 */
}
