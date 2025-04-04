#include <algorithm>
#include <iostream>
#include <ctime>
#include <string>
#include "clui.h"
#include <fstream>
using namespace std;
int tableasli[9][9];
int tablehalnashode[9][9];
void timer(){

  for(int i=1;i<=100;i++){
    cursor_to_pos(get_window_rows() /2 , get_window_cols() /2);
    change_color_rgb(237, 66, 14);
    cout<<i<<endl;
    delay(1000);
    clear_screen();
  }
  cursor_to_pos(get_window_rows() /2 , get_window_cols() /2);
  cout<<"you lost";
}
string username;
void menu();
void menu2(string name);
void level();
/*bool issolved() {
  bool solved = false;
  for(int i=1;i<9;i++) {
    for(int j=1;j<9;j++) {
      if(tablehalnashode[i][j]!=tableasli[i][j]) {
        solved = false;
      }
      else {
        solved = true;
      }
    }
  }
  return solved;
}*/
void generate(int table[9][9]) {
  //first line
  {
    srand(time(nullptr));
    for(int i = 0; i < 9; i++){
      bool rpt = true;
      //اول اینجا %10 گذاشته بودم ولی اشتباه بود چون از 0 عددارو میاورد
      int num = rand() % 9 + 1;
      for(int j = 0; j < i; j++){
        if (num==table[0][j])
          rpt = false;
      }
      if(rpt == true) {
        table[0][i] = num;
      }
      else {
        i--;
      }
    }
  }
  //line2
  {
    for(int i = 3; i < 9; i++) {
      table[1][i-3]=table[0][i];
    }
    for(int i = 0; i < 3; i++) {
      table[1][i+6]=table[0][i];
    }
  }
    //line3
  {
    for(int i = 3; i < 9; i++) {
      table[2][i-3]=table[1][i];
    }
    for(int i = 0; i < 3; i++) {
      table[2][i+6]=table[1][i];
    }
  }
  //line4
  {
    for(int i = 0; i < 9; i++) {
      if (i==4 || i==7) {
        table[3][i-4] = table[2][i];
        table[3][i-4+1] = table[2][i+1];
        table[3][i-4+2] = table[2][i-1];

      }

      else if (i==1) {
        table[3][i+5] = table[2][i];
        table[3][i+5+1] = table[2][i+1];
        table[3][i+5+2] = table[2][i-1];

      }
      else
        continue;
    }
  }
  //line5
  {
    for(int i = 3; i < 9; i++) {
      table[4][i-3]=table[3][i];
    }
    for(int i = 0; i < 3; i++) {
      table[4][i+6]=table[3][i];
    }
  }
  //line6
  {
    for(int i = 3; i < 9; i++) {
      table[5][i-3]=table[4][i];
    }
    for(int i = 0; i < 3; i++) {
      table[5][i+6]=table[4][i];
    }
  }
  //line7
  {
    for(int i = 0; i < 9; i++) {
      if (i==4 || i==7) {
        table[6][i-4] = table[5][i];
        table[6][i-4+1] = table[5][i+1];
        table[6][i-4+2] = table[5][i-1];

      }

      else if (i==1) {
        table[6][i+5] = table[5][i];
        table[6][i+5+1] = table[5][i+1];
        table[6][i+5+2] = table[5][i-1];

      }
      else
        continue;
    }
  }
  //line8
  {
    for(int i = 3; i < 9; i++) {
      table[7][i-3]=table[6][i];
    }
    for(int i = 0; i < 3; i++) {
      table[7][i+6]=table[6][i];
    }
  }
  //line9
  {
    for(int i = 3; i < 9; i++) {
      table[8][i-3]=table[7][i];
    }
    for(int i = 0; i < 3; i++) {
      table[8][i+6]=table[7][i];
    }
  }

}

void make_game_table(int table1[9][9] , int table2[9][9]) {
  generate(table1);
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      table2[i][j] = table1[i][j];
      tableasli[i][j] = table1[i][j];
      tablehalnashode[i][j] = table1[i][j];
    }
  }
  int remove=40 , i , j;
  while(remove) {
    i=rand()%9;
    j=rand()%9;

    if (table2[i][j]!=0) {
      table2[i][j]=0;
      tablehalnashode[i][j]=0;
      remove--;
    }
  }

}
// void print(int table[9][9]){
//
//   for(int i = 0; i < 9; i++) {
//     for(int j = 0; j < 9; j++) {
//
//       cout <<"["<< tablehalnashode[i][j]<<"]";
//
//
//     }
//     cout << endl;
//   }


bool check(int val , int y , int x){
  bool flag = false;
  if(tableasli[y][x] == val) {
    flag = true;
  }
  return flag;

}
int count_wrong = 0;
void control() {
  int count=40;
  int y=0,x=0;
  cursor_to_pos(1,3);
  while(true) {
    int botton=getch();
    switch(botton) {

      case 27: {
        clear_screen();
        cursor_to_pos(get_window_rows() /2 , get_window_cols() /2);
        cout<<"the game stopted";
      }
      break;
      case 77:
        if(x<8) {
          cursor_forward(5);
          x++;
        }
      break;
      case 75:
        if(x>0) {
          cursor_backward(5);
          x--;
        }
      break;
      case 80:
        if(y<8) {
          cursor_down(1);
          y++;
        }
      break;
      case 72:
        if(y>0) {
          cursor_up(1);
          y--;
        }
      break;


      default:
        if (botton >= '0' && botton <= '9') {
          int val = botton - '0';
          if (tablehalnashode[y][x] == 0 && check(val, y, x)) {
            //cursor_to_pos(y+1, x*5+3);
            cout << val;
            tablehalnashode[y][x] = val;
            count--;
            if (count==0) {
              clear_screen();
              cursor_to_pos(get_window_rows() /2 , get_window_cols() /2);
              change_color_rgb(4, 143, 14);
              cout<<"you won the game";
              delay(1000);
              reset_color();
              menu2(username);
            }
            cursor_to_pos(y+1, x*5+3);
          }
          else if (check(val, y, x)==false && tablehalnashode[y][x] == 0) {
            cursor_to_pos(1, 50);
            count_wrong--;
            cout<<"Remaining Chances: "<<count_wrong<<"  ";
            cursor_to_pos(y+1, x*5+3);
            if (count_wrong == 0) {
              clear_screen();
              cursor_to_pos(get_window_rows() /2 , get_window_cols() /2);
              change_color_rgb(173, 9, 9);
              cout<<"You Have Lost!";
              delay(1000);
              reset_color();
              menu2(username);
          }
        }
        }
    }
  }
}

void play() {

  clear_screen();
  int table[9][9];
  int game_table[9][9];

  make_game_table(table, game_table);
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {

      cout <<"[ "<< tablehalnashode[i][j]<<" ]";


    }
    cout << endl;
  }
  cursor_to_pos(1,50);
  cout<<"Remaining Chances: "<<count_wrong;
  control();

}
void level(int input2){
          clear_screen();
          if(input2 == 1) {
            count_wrong=10;
          play();
        }
        else if(input2 == 2) {
          count_wrong=5;
          play();
        }
        else if (input2==3)
        {
          count_wrong=1;
          timer();
          play();

        }
        
}
void menu2(string name) {
  cursor_to_pos(get_window_rows()/2-1 ,get_window_cols()/2-2);
  cout<<"* * * * * * * * * * * * *"<<endl;

  cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2-2);
  cout<<"* ";
  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2-2);
  cout<<"* ";

  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2-2);
  cout<<"* ";
  cursor_to_pos(get_window_rows()/2+5 ,get_window_cols()/2-2);
  cout<<"* * * * * * * * * * * * *"<<endl;

  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2+21);
  cout<<" * ";

  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2+21);
  cout<<" * ";
    clear_screen();
    change_color_rgb(245, 122, 56);
  cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2);
    cout<<"hello  ";
  reset_color();
  change_color_rgb(255, 240, 71);

  cout<<name<<endl;
  reset_color();
    int input1;
  change_color_rgb(245, 122, 56);
  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2);
    cout<<"1.start a game"<<endl;
  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2);

    cout<<"2.exit"<<endl;
  cursor_to_pos(get_window_rows()/2+3 ,get_window_cols()/2);

    cout<<"press a number: ";
  reset_color();

  change_color_rgb(255, 240, 71);
    cin>>input1;
  reset_color();
    if(input1 == 1) {
      clear_screen();
        change_color_rgb(219, 20, 153);
      cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2);
        cout<<"1.easy mode"<<endl;
    reset_color();
      change_color_rgb(176, 14, 122);
      cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2);
        cout<<"2.normal mode"<<endl;
      change_color_rgb(133, 11, 92);

      cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2);
        cout<<"3.hard mode"<<endl;
      reset_color();
      change_color_rgb(79, 5, 52);

      cursor_to_pos(get_window_rows()/2+3 ,get_window_cols()/2);
        cout<<"what level do you want?"<<endl;
        int input2;
      cursor_to_pos(get_window_rows()/2+4 ,get_window_cols()/2);
        cin>>input2;
      reset_color();
        level(input2);


    }
  else if(input1 == 2) {
    exit(0);
  }






}
bool usernameExists(const string& username) {
  ifstream infile("usernames.txt" , ios::in | ios::app);
  string line;
  while (getline(infile, line)) {
    if (line == username) {
      return true;
    }
  }
  return false;
}
void singup() {

  change_color_rgb(59, 209, 79);
  string username;
  cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2-2);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2-2);
  cout<<"| ";

  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2-2);
  cout<<"| ";
  cursor_to_pos(get_window_rows()/2+3 ,get_window_cols()/2-2);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2+21);
  cout<<"| ";

  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2+21);
  cout<<"| ";
  change_color_rgb(46, 73, 191);
  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2);
    cout<<"make an user:"<<endl;
    cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2);
  cin.ignore();
  getline(cin,username);
  if(usernameExists(username)) {
    clear_screen();
    cursor_to_pos(get_window_rows()/2,get_window_cols()/2);
    cout<<"username already exist";
    delay(1000);
    menu();
  }
  else {
    ofstream file("usernames.txt" , ios::app | ios::in);
    file<<username<<endl;
    file.close();
    menu2(username);
    reset_color();
  }
}

void login() {
    change_color_rgb(59, 209, 79);
    string username;
    cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2-2);
    cout<<"* * * * * * * * * * * * *"<<endl;

    cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2-2);
  cout<<"* ";

  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2-2);
  cout<<"* ";
  cursor_to_pos(get_window_rows()/2+3 ,get_window_cols()/2-2);
  cout<<"* * * * * * * * * * * * *"<<endl;

  cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2+21);
  cout<<" * ";

  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2+21);
  cout<<" * ";


    reset_color();
    change_color_rgb(46, 73, 191);
    cursor_to_pos(get_window_rows()/2+1 ,get_window_cols()/2);
    cout<<"enter your username:"<<endl;
    cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2);
  cin.ignore();
  getline(cin,username);
  if (usernameExists(username)) {
    menu2(username);
    }
  else {
    clear_screen();
    change_color_rgb(143, 4, 4);
    cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2);
    cout<<"user doesn't exist"<<endl;
    delay(1000);
    menu();
  }
  }
void menu() {

    clear_screen();
 change_color_rgb(29, 87, 72);

  cursor_to_pos(get_window_rows()/2-2 ,get_window_cols()/2-4);
  cout<<"# # # # # # # # # # # # # # # # #"<<endl;
  reset_color();
  change_color_rgb(161, 22, 64);

  cursor_to_pos(get_window_rows()/2-2 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2-1 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+1,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+3 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+4 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+5 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+6 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+7 ,get_window_cols()/2-6);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2-1 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+1,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+2 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+3 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+4 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+5 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+6 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  cursor_to_pos(get_window_rows()/2+7 ,get_window_cols()/2+28);
  cout<<"# "<<endl;
  reset_color();
  change_color_rgb(29, 87, 72);

  cursor_to_pos(get_window_rows()/2+7 ,get_window_cols()/2-4);
  cout<<"# # # # # # # # # # # # # # # # #"<<endl;
  reset_color();
    cursor_to_pos(get_window_rows()/2 ,get_window_cols()/2+3);
    change_color_rgb( 21, 161, 128);
    cout<<"Welcome my friend!"<<endl<<endl;;
    reset_color();
  change_color_rgb(230, 80, 192);
    cursor_to_pos(get_window_rows()/2 + 2 ,get_window_cols()/2);
    cout<<"1.log in "<<endl;
    cursor_to_pos(get_window_rows()/2 + 3 ,get_window_cols()/2);
    cout<<"2.sing up "<<endl;
  cursor_to_pos(get_window_rows()/2 + 4 ,get_window_cols()/2);
  cout<<"What do you want to do? "<<endl;

    // change_color_rgb(191, 10, 10);
    int choice;
  cursor_to_pos(get_window_rows()/2 + 5 ,get_window_cols()/2);
    cout<<": ";
    cin>>choice;
    // reset_color();
    if (choice == 1) {
        clear_screen();
        login();
    }
    if (choice==2) {

        clear_screen();
        singup();


    }

    reset_color();
    

}

int main(){
    menu();

  return 0;
  }