#include <bits/std_thread.h>
#include <bits/stdc++.h>
#include <chrono>
#include <cstdlib>
#include <raylib.h>
#include <thread>
#include <vector>

using namespace std;

const int SCREEN_WIDTH=900;
const int SCREEN_HEIGHT=600;

const int NUM_BARS=150;

void DrawBars(const vector<int>& arr, int highlight1=-1,int highlight2=-1){
  int barWidth=SCREEN_WIDTH/NUM_BARS;
  for (int i=0;i<NUM_BARS;i++){
    int height=arr[i];
    Color color=GRAY;
    if(i==highlight1){
      color=RED;
      height=arr[i];
    }
    if(i==highlight2){
      color=YELLOW;
      height=arr[i];
    }
    DrawRectangle(i*barWidth,SCREEN_HEIGHT-height+20,barWidth-1,height,color);
  }
}
void DrawBlocks(const vector<int>& arr){
  
}

// Algorithms ------------------------------------------------------------

// Bubblesort ---------------------------------------------------------
void BubbleSort(vector<int>& arr){
  BeginDrawing();

  for (int i=0;i<NUM_BARS;i++){
    for(int j=0;j<NUM_BARS-i-1;j++){
      if(arr[j]>arr[j+1]){
        ClearBackground(BLACK);
        DrawText("Bubble Sort", 20, 10, 20, GREEN);
        DrawBars(arr,j+1,j);
        swap(arr[j],arr[j+1]);
        this_thread::sleep_for(chrono::milliseconds(10));
      }
      EndDrawing();
    }
  }
}

// Insertion sort --------------------------------------------- 

void InsertionSort(vector<int>& array){
  BeginDrawing();
  for (int i=1;i<NUM_BARS;i++) {
    int temp = array[i];
    int j=i-1;
    while(j>=0 && array[j]>temp){
      ClearBackground(BLACK);
      DrawText("Insertion Sort", 20, 10, 20, GREEN);
      DrawBars(array,j-1,j);
      array[j+1]=array[j];
      j--;
      this_thread::sleep_for(chrono::milliseconds(10));
      EndDrawing();
    }
    array[j+1]=temp;
  }
}
// Custom Sort ---------------------------------------------------

void CustomSort(vector<int>& array){
 
  
}

// Selection sort ------------------------------------------------

void selectionSort(vector<int>& array) {
  BeginDrawing();
  for (int i=0;i<NUM_BARS-1;i++) {
    int min=i;
    for (int j=i+1;j<NUM_BARS;j++) {
      if(array[min]>array[j]) {
        min=j;
      }
    }
    swap(array[i],array[min]);
    ClearBackground(BLACK);
    DrawText("Selection Sort", 20 , 10, 20, GREEN);
    DrawBars(array,i,min);
    EndDrawing();
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}

// Mergesort ------------------------------------------------

void merger(vector<int>& array,int l, int mid,int r){
  int n1=mid-l+1;
  int n2=r-mid;
  //int *L=new int[n1];
  //int *R=new int[n2];
  vector<int> L(n1);
  vector<int> R(n2);
  
  BeginDrawing();
  
  for(int i=0;i<n1;i++){
    L[i]=array[l+i];
  }
  for(int j=0;j<n2;j++){
    R[j]=array[mid+1+j];
  }

  int i=0,j=0,k=l;
  while(i<n1 && j<n2){
    ClearBackground(BLACK);
    if(L[i]<=R[j]){
      DrawBars(array,k,i);
      array[k++]=L[i++];
    }
    else{
      DrawBars(array,k,j);
      array[k++]=R[j++];
    }
  }
  while(i<n1){
    ClearBackground(BLACK);
    DrawBars(array,k,i);
    array[k++]=L[i++];
  }
  while(j<n2){
    ClearBackground(BLACK);
    DrawBars(array,k,j);
    array[k++]=R[j++];
  }
  DrawText("Merge Sort", 20 , 10, 20, GREEN);
  EndDrawing();
  this_thread::sleep_for(chrono::milliseconds(10));
}

void mergeSort(vector<int>& array,int first,int last){
  int mid;
  if(first<last){
    mid=first+(last-first)/2;
    mergeSort(array,first,mid);
    mergeSort(array,mid+1,last);
    merger(array,first,mid,last);
  }
}

// Quicksort ------------------------------------------------

int partition(vector<int>& array, int start, int end){
  int pivot=array[end];
  int i=start-1;

  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("Quick Sort", 30, 10, 20, GREEN);

  for(int j=start;j<=end-1;j++){
    if(array[j]<pivot){
      i++;
      swap(array[i],array[j]);
      ClearBackground(BLACK);
      DrawBars(array,i,j);
    }
  }
  i++;
  swap(array[i],array[end]);
  ClearBackground(BLACK);
  DrawBars(array,i,end);
  this_thread::sleep_for(chrono::milliseconds(10));
  EndDrawing();
  return i;
}

void quickSort(vector<int>& array,int start,int end){
  if(end<=start) return;
  int pivot=partition(array,start,end);
  quickSort(array,start,pivot-1);
  quickSort(array,pivot+1,end);
}

void Randomize(vector<int>& arr){
    for(int i=0;i<NUM_BARS;i++)
    arr[i]=GetRandomValue(60,SCREEN_HEIGHT-10);
}

int main(void) {

  InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Sorting Visualizer");
  SetTargetFPS(160);
  
  vector<int> arr(NUM_BARS);

  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
  
  Randomize(arr);
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawBars(arr);
    DrawText("Sorting Visualizer",40,40,40,GREEN);
    DrawText("Press:",50,SCREEN_HEIGHT/6+50,35,BLUE);
    DrawText("B -> Bubble Sort",60,SCREEN_HEIGHT/6+100,30,ORANGE);
    DrawText("I  -> Insertion Sort",60,SCREEN_HEIGHT/6+130,30,ORANGE);
    DrawText("S -> Selection Sort",60,SCREEN_HEIGHT/6+160,30,ORANGE);
    DrawText("M -> Merge Sort",60,SCREEN_HEIGHT/6+190,30,ORANGE);
    DrawText("Q -> Quick Sort",60,SCREEN_HEIGHT/6+220,30,ORANGE);
    DrawText("W -> Quit",60,SCREEN_HEIGHT/2+260,30,RED);
    EndDrawing();
    if(IsKeyPressed(KEY_Q)){
      Randomize(arr);
      this_thread::sleep_for(chrono::milliseconds(10));
      quickSort(arr, 0, NUM_BARS);
    }
    else if(IsKeyPressed(KEY_S)){
      Randomize(arr);
      this_thread::sleep_for(chrono::milliseconds(10));
      selectionSort(arr);
    }
    else if(IsKeyPressed(KEY_M)){
      Randomize(arr);
      this_thread::sleep_for(chrono::milliseconds(10));
      mergeSort(arr, 0, NUM_BARS-1);
    }
    else if(IsKeyPressed(KEY_I)){
      Randomize(arr);
      this_thread::sleep_for(chrono::milliseconds(10));
      InsertionSort(arr);
    }
    else if(IsKeyPressed(KEY_B)){
      Randomize(arr);
      this_thread::sleep_for(chrono::milliseconds(10));
      BubbleSort(arr);
    }
    else if(IsKeyPressed(KEY_W)){
      CloseWindow();
    }
    else if(IsKeyPressed(KEY_C)){
      Randomize(arr);
      this_thread::sleep_for(chrono::milliseconds(10));
      CustomSort(arr);
    }
    
  }
  CloseWindow();
 
}
