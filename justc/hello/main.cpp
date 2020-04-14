#include <iostream>
#include <string>
#define sizeOf(a) (sizeof(a) / sizeof(a[0]))

using namespace std;

struct Pairs{
    int number;
    string name;
    int hms;
};

void sortArray(Pairs array[], int size);
void showArray(const Pairs array[], int size);

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

  Pairs values[] {{8, "eight"},{5, "five"},{1, "one"},{3, "three"}};

  int arr[6] ={6,5,4,3,2,1};
  cout<< sizeof(values) / sizeof(values[0]);
  cout<< sizeOf(values);

  cout << " the unsorted are\n";
  showArray(values, SIZE);

  sortArray(values,SIZE);

  cout << "the sorted are\n";
  showArray(values, SIZE);
}

void showArray(const Pairs array[], int size){
  cout << endl;
  for (int i=0;i<size;i++){
    cout << array[i].number <<" " << array[i].name << "  ";
    cout << endl;
  }
}

void sortArray(Pairs array[], int size){
  bool swapped;
  do{
    swapped = false;
    for (int i=0;i<size -1 ;i++){
      if(array[i].number > array[i+1].number ){
        swap(array[i], array[i+1]);
        swapped = true;
      }
    }
  } while(swapped);
}