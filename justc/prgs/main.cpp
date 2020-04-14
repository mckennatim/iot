#include <iostream>
#include <string>
#define sizeOf(a) (sizeof(a) / sizeof(a[0]))

using namespace std;

/*prg data structure declarations*/  
struct prg_t{
  int sr;
  int aid;
  int ev;
  int numdata;
  int prg[11][4];//max 11 events [hr,min,max,min]  
  int port;
  int hms;
};
struct prgs_t{
  int numprgs;
  prg_t prg[5];
};
extern prgs_t prgs;

// void sortArray(Pairs array[], int size);
void showArray(const prg_t prg[], int size);
void sortPrgsHms(prg_t prg[], int size);

int  main(){
  const int SIZE =4;
  // Pairs values[SIZE];

  // values[0].number = 7;
  // values[0].name ="seven";
  // values[1].number = 5;
  // values[1].name ="five";
  // values[2].number = 1;
  // values[2].name ="one";
  // values[3].number = 3;
  // values[3].name ="three";

  prgs_t prgs{
    3,//numprgs
    { //sr,aid,ev,numdata,prg[[]],port
      {2,255,1,2,{{0,0,61,59}},6,29002}, 
      {6,255,1,1,{{0,0,1}},7,29006},
      {7,255,1,1,{{0,0,0}},8,29001}
    }
  };

  showArray(prgs.prg, prgs.numprgs);
  sortPrgsHms(prgs.prg, prgs.numprgs);
  showArray(prgs.prg, prgs.numprgs);
}

void showArray(const prg_t prg[], int size){
  cout << endl;
  for (int i=0;i<size;i++){
    cout << prg[i].sr <<" " << prg[i].hms << "  ";
    cout << endl;
  }
}

void sortPrgsHms(prg_t prg[], int size){
  bool swapped;
  do{
    swapped=false;
    for (int i=0;i<size -1 ;i++){
      if(prg[i].hms > prg[i+1].hms ){
        prg_t temp = prg[i];
        prg[i] = prg[i+1];
        prg[i+1] = temp;
        swapped = true;
      }
    }    
  }while(swapped);
}

