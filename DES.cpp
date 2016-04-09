
#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
  struct Node{
double data;
Node* next;

};
struct Item{
double arrival_time;
double flqueue_time;//when it leaves first level queue
double unit1_time;//when it leaves first level unit
double slqueue_time;//when it leaves second level queue
double unit2_time;//when it leaves second level unit
};
Node* head;//events head,smallest t;
double t=0;
std::queue<Item> items;
std::queue<Item> flq;
std::queue<Item> slq;
std::vector<std::queue<Item> > slqs;
std::queue<Item> finals;

void addEvent(double data){//chronological linked list
Node* x=new Node;
x->data=data;
x->next=NULL;
if(head==NULL){
head=x;
return;
}
if(head->data>data){
x->next=head;
head=x;
return;
}
Node* temp=head;
if(temp->next==NULL){
head->next=x;
return;
}
while(temp->next->data<data){
if(temp->next->next==NULL){
temp->next->next=x;
return;
}
temp=temp->next;
}
x->next=temp->next;
temp->next=x;

}

double getEvent(){//gets smallest t which is at node then removes it
double x=head->data;
head=head->next;
return x;

}

void printEvents(){//print list of all events, for testing purposes
Node *temp=head;
while(temp!=NULL){

cout << temp->data << " ";
temp=temp->next;
}
}

struct Unit{//first level unit, as linked list
double proc_time;//how long it takes to process
double busy_till;//until this time, this unit is busy with a package, if -1 it's not busy
int index;//the number of unit, useful for arranging which second level queue it's operating with for multiple slq layout
Item i;//item this unit is currently processing
Unit* next=NULL;
void work(double t){//telling unit to do it's job at time t for single second level queue layout

if(busy_till==t){//if job is done, give package to slq
busy_till=-1;
slq.push(i);
}

if(busy_till==-1){//if not busy, take a package and add timestamps, then update busytill
if(flq.empty()){

return;
}
i=flq.front();
flq.pop();
i.flqueue_time=t;
busy_till=t+proc_time;
i.unit1_time=busy_till;
addEvent(busy_till);
}
}


void work2(double t){//telling unit to do it's job at time t for multiple second level queue layout, mostly same as work()

if(busy_till==t){
busy_till=-1;
slqs[(this->index+1)/2].push(i);//we want unit 3-4 to operate with slqs[2], 1-2 to 1, 5-6 to 3...;
}

if(busy_till==-1){
if(flq.empty()){

return;
}
i=flq.front();
flq.pop();
i.flqueue_time=t;
busy_till=t+proc_time;
i.unit1_time=busy_till;
addEvent(busy_till);
}
}


};
struct Unit2{//second level unit as linked list, very similar to Unit other taking item from slq and adding it to finals vector when the work is done
double proc_time;
double busy_till;
int index;
Unit2* next=NULL;
Item i;

void work(double t){
if(busy_till==t){
busy_till=-1;
finals.push(i);

}

if(busy_till==-1){
if(slq.empty()){
return;
}
i=slq.front();
slq.pop();
i.slqueue_time=t;
busy_till=t+proc_time;
i.unit2_time=busy_till;
addEvent(busy_till);
return;




}
}


void work2(double t){
if(busy_till==t){
busy_till=-1;
finals.push(i);

}

if(busy_till==-1){
if(slqs[this->index].empty()){
return;
}
i=slqs[this->index].front();
slqs[this->index].pop();
i.slqueue_time=t;
busy_till=t+proc_time;
i.unit2_time=busy_till;
addEvent(busy_till);
return;




}
}
};








Unit* u1head;// public variables for both unit's heads
Unit2* u2head;
void add_FLU(double ptime){//self explaining function name
Unit* u=new Unit;
u->proc_time=ptime;
u->busy_till=-1;
if(u1head==NULL){
u->index=1;
u1head=u;
return;
}

Unit* temp= u1head;
while(temp->next!=NULL){
temp=temp->next;
}
u->index=temp->index+1;
temp->next= u;

}


void add_SLU(double ptime){//self explaining function name
Unit2* u=new Unit2;
u->proc_time=ptime;
u->busy_till=-1;
if(u2head==NULL){
u->index=1;

u2head=u;
return;
}

Unit2* temp= u2head;
while(temp->next!=NULL){

temp=temp->next;

}
u->index=temp->index+1;

temp->next= u;

}

void add_item(double arrival_time){//self explaining function name
addEvent(arrival_time);
Item *i=new Item;
i->arrival_time=arrival_time;
items.push(*i);
}


void input(char* infileName){//function to read file
 ifstream myfile(infileName);//start file stream
	 string line;
	 getline(myfile, line);
	 stringstream data(line);

	 double K;
	 int N;
data >> N;


for(int i=0; i<N; i++){
	getline(myfile, line);
	stringstream data(line);

data >> K;

add_FLU(K);


}

getline(myfile, line);
data.clear();
stringstream data2(line);
data2 >> N;

for(int i=0; i<N; i++){
	getline(myfile, line);
stringstream	 data(line);

data >> K;
add_SLU(K);

std::queue<Item> a;
slqs.push_back(a);//create slqs equal to number of second level units for multiple slq layout

}

getline(myfile, line);
	stringstream data3(line);
data3 >> N;


for(int i=0; i<N; i++){
	getline(myfile, line);
stringstream	 data(line);

data >> K;
add_item(K);

}



}
int main(int argc, char *argv[]){
if(argc!=3){
		printf("Usage: ./DES infile outfile\n");
		return 0;
	}
size_t maxq1l=0;
size_t maxq2l=0;
size_t maxq1l2=0;
size_t maxq2l2=0;
input(argv[1]);



double it=head->data;
double lt;

while(head!=NULL){
t=getEvent();
lt=t;
if(!items.empty()){
if(items.front().arrival_time==t){
flq.push(items.front());
items.pop();
}}

Unit* temp=u1head;
while(temp!=NULL){
temp->work(t);
temp=temp->next;
}
Unit2* temp2=u2head;
while(temp2!=NULL){

temp2->work(t);
temp2=temp2->next;

}

if(maxq1l<flq.size()){
maxq1l=flq.size();
}

if(maxq2l<slq.size()){
maxq2l=slq.size();
}


}



ofstream myfile;//start file stream
myfile.open (argv[2]);

  myfile.precision(3);
 myfile.setf( std::ios::fixed, std:: ios::floatfield );
double total =0;
int itemc=0;
double lw=0;
double wttotal;
while (!finals.empty()){
total += finals.front().unit2_time - finals.front().arrival_time;
wttotal+=finals.front().flqueue_time-finals.front().arrival_time+finals.front().slqueue_time-finals.front().unit1_time;
if(finals.front().flqueue_time-finals.front().arrival_time+finals.front().slqueue_time-finals.front().unit1_time>lw){

lw=finals.front().flqueue_time-finals.front().arrival_time+finals.front().slqueue_time-finals.front().unit1_time;
}
itemc++;
finals.pop();
}
myfile << total/itemc << endl;
myfile << maxq1l << endl;
myfile << maxq2l << endl;
myfile << wttotal/itemc << endl;
myfile << lw<< endl;
myfile << lt-it << endl << endl;




u1head=NULL;
u2head=NULL;
input(argv[1]);

while(head!=NULL){
t=getEvent();
lt=t;
if(!items.empty()){
if(items.front().arrival_time==t){
flq.push(items.front());
items.pop();
}}

Unit* temp=u1head;
while(temp!=NULL){

temp->work2(t);
temp=temp->next;
}
Unit2* temp2=u2head;
while(temp2!=NULL){

temp2->work2(t);
temp2=temp2->next;

}

if(maxq1l2<flq.size()){
maxq1l2=flq.size();
}

for(size_t i=0;i<slqs.size();i++)
if(maxq2l2<slqs[i].size()){
maxq2l2=slqs[i].size();
}


}

total=0;
itemc=0;
lw=0;
wttotal=0;
while (!finals.empty()){
total += finals.front().unit2_time - finals.front().arrival_time;
wttotal+=finals.front().flqueue_time-finals.front().arrival_time+finals.front().slqueue_time-finals.front().unit1_time;
if(finals.front().flqueue_time-finals.front().arrival_time+finals.front().slqueue_time-finals.front().unit1_time>lw){

lw=finals.front().flqueue_time-finals.front().arrival_time+finals.front().slqueue_time-finals.front().unit1_time;
}
itemc++;
finals.pop();
}
myfile << total/itemc << endl;
myfile << maxq1l2 << endl;
myfile << maxq2l2 << endl;
myfile << wttotal/itemc << endl;
myfile << lw<< endl;
myfile << lt-it << endl;


return 0;
}
