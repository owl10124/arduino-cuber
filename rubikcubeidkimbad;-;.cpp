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
	//REALLY 
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
	//SERIOUSLY, I EXPECTED MORE FROM YOU
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
	// I GIVE UP
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
	// I AUTHORISE YOU TO GET A CUBE ALGORITMN FORM SOMEWHERE
    // if you're doing this then at least use a tilapiaing for loop
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
	// BCOS THIS IS ABSOLUTE RUBBISH
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
	// JUST FRIGGIN GET A CODE ALREADY

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
int main(){

    for (int i =0 ; i < 54; i++){
        scanf(" %c",&apple[i]);
    }


    print_faces();
    /*
    char order;
    while (scanf(" %c",&order) != EOF){
        if (order == 'F') front_turn_c();
        if (order == 'f') front_turn_ac();
        if (order == 'R') right_turn_c();
        if (order == 'r') right_turn_ac();
        if (order == 'U') up_turn_c();
        if (order == 'u') up_turn_ac();
        if (order == 'L') left_turn_c();
        if (order == 'l') left_turn_ac();
        if (order == 'D') down_turn_c();
        if (order == 'd') down_turn_ac();
        if (order == 'B') back_turn_c();
        if (order == 'b') back_turn_ac();
        print_faces();
    }
     */
   // /*
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




 //*/
}
