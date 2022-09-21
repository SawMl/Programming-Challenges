#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
//timer = 0 to start
//fetch car
//add arrival time to index of car
//inputs for fetching car: current time, street of last car, qA, qB
//output: car

vector<int> street_vector;

int get_st(pair<int,int> car){
  if (car.first==-1){
    return -1;
  }
  return street_vector[car.first];
}


//logic for pulling the next car
//-1 for empty last_street
pair<int,int> fetch_car(int curr_time,int last_street, queue<pair<int,int>> &first_ave, queue<pair<int,int>> &main_st){


  pair<int,int> car = make_pair(-1,-1);
  int next_main_arrival_time;
  int next_first_arrival_time;
  if (first_ave.empty()){
    next_main_arrival_time = (main_st.front()).second;
    if (next_main_arrival_time <= curr_time){
      car = main_st.front();
      main_st.pop();
      return car;
    }
    else{
      return car;
    }
  }
  else if(main_st.empty()){
    next_first_arrival_time = (first_ave.front()).second;
    if (next_first_arrival_time <= curr_time){
      car = first_ave.front();
      first_ave.pop();
      return car;
    }
    else{
      return car;
    }
  }
  next_main_arrival_time = (main_st.front()).second;
  next_first_arrival_time = (first_ave.front()).second;
  if (curr_time < min(next_main_arrival_time,next_first_arrival_time)){
    return car;
  }
  if (next_main_arrival_time==next_first_arrival_time){
    if (last_street==-1){
      car = first_ave.front();
      first_ave.pop();
    }
    else if(last_street==0){
      car = first_ave.front();
      first_ave.pop();
    }
    else{
      car = main_st.front();
      main_st.pop();
    }
  }
  else if (next_main_arrival_time<next_first_arrival_time){
    car = main_st.front();
    main_st.pop();
  }
  else{
    car = first_ave.front();
    first_ave.pop();
  }
  return car;
}


//the engine
vector<int> foo(int time, int last_st, queue<pair<int,int>> &first_ave,queue<pair<int,int>> &main_st, vector<int> &solution){
  if (!first_ave.empty() || !main_st.empty()){
    pair<int,int> next_car = fetch_car(time,last_st,first_ave,main_st);
    if (next_car.first!=-1){
      last_st = get_st(next_car);
      solution.push_back(time);
    }
    else{
      last_st=-1;
    }
    return foo(time+1,last_st,first_ave,main_st,solution);
  }
  return solution;
}




vector<int> getResult(vector<int> arrival, vector<int> street){
  street_vector = street;
  pair<int,int> car; //index, arrival time
  queue<pair<int,int>> first_street;
  queue<pair<int,int>> main_street;

  int size = arrival.size();
  for (int i=0;i<size;i++){
    if (street[i]==0){
      main_street.push(make_pair(i,arrival[i]));
    }
    else{
      first_street.push(make_pair(i,arrival[i]));
    }
  }


  vector<int> solution;
  return foo(0,-1,first_street,main_street,solution);
}




int main()
{

    vector<int> arrival = {1, 2, 35, 67};
    vector<int> street = {1, 0, 0, 1};
    vector<int> res = getResult(arrival, street);
    for (auto i : res)
    {
        cout << i << " ";
    }
}
