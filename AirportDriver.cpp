/***********************************************
************CSCI-311-PROJECT-2-V-2071***********
************************************************
*******CODE-CHECKER-STARTING-ALIGNMENT**********
************************************************
*************CONTROL-NUMBER-XA-72***************
************************************************
**REPORT-GENERATION-MODE-AUTO_SYNC-EXCEPTION-2**
************************************************
*****************DATETIME-SYS*******************
************************************************/

//G1_EXCEPTION: Only produce your code as directed in Section A, B, C, and D1_EXCEPTION.
//G2_EXCEPTION: Do not write anything at the other places in this file.
//D1_EXCEPTION: Put you names here (on this line):_Lindsey_Lydon______________

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
//SECTION_A_START: put your header files here using the include directive.
//G3_EXCEPTION: You can also declare using standard namespace if you like, but do not use any global variable or method.




//SECTION_A_END: Section A ends here. 
/***********************************************
*************SECTION-A-HEADERS-END**************
************************************************/

/***********************************************
*************SECTION-B-CLASSES******************
************************************************/
//SECTION_B_START: put all your classes definitions here.





//SECTION_B_END: Section B ends here. 
/***********************************************
*************SECTION-B-CLASSES-END**************
************************************************/


/***********************************************
*************SECTION-C-MAIN-FUNCTION************
************************************************/
//SECTION_C_START: write your main function here.

//After no more printing the time should increment.



//SECTION_C_END: Section C ends here. 
/***********************************************
************SECTION-C-MAIN-FUNCTION-END*********
************************************************/

/***********************************************
**************PLAGIARISM-RTNG-PRTCL-C***********
****************GEN-AI-RTNG-PRTCL-K*************
*********LOOP-CS_SEC-CS_CHR-STU_R_R_RFR*********
*****************DICT-A-ENTRY-2071**************
***************ORI-KTIAN@CSUCHICO.EDU***********
************************************************/

/***********************************************
*********CODE-CHECKER-ENDING-ALIGNMENT**********
************************************************/
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>
using namespace std;

class Plane{
  public:
  
    int enterTime; 
    int planeId;
    string comeGo; //SHort for Coming or Going for departure or arrival.
    int priority;
    /*Keep track of this for the priority queuing based off of the test cases.
    Seems to be organized priority number, then if the same tie breaker is time entered, and then if
    that's the same the tie breaker is the plane id. Since they come in in ascending order I can use that
    to break up ties. Then it is simply pop depatures off to A and arrivals off to B until it is just
    one type left to pop off. */  
    Plane::Plane();
    Plane::Plane(int, int, string, int);

    //Getter functions
    int getPlaneId();
    int getPriority();
    string getComeGo();
    int getEnterTime();
    //Overloaded Operator< to allow comparsion between planes for the tie breakers in when heapifying.
    bool operator<(const Plane&);
    friend std::ostream& operator<<(std::ostream& stream, const Plane& p);
};

//Default contructor
Plane::Plane() {
  enterTime = -1;
  planeId = -1;
  comeGo = "";
  priority = -1;
}

//Initalizes a new plane object from the test file. 
Plane::Plane(int t, int id, string type, int p){
  enterTime = t;
  planeId = id;
  comeGo = type;
  priority = p;
}

int Plane::getPlaneId() {
  return planeId;
}
int Plane::getPriority() {
  return priority;
}
string Plane::getComeGo() {
  return comeGo;
}
int Plane::getEnterTime() {
  return enterTime;
}

bool Plane::operator<(const Plane &newP) {
  //checks to return the lower priority as first check.
  if (priority != newP.priority) {
    return priority < newP.priority;
  }
  //Then if needed it checks and returns the earlier time entered into the simulation.
  if (enterTime != newP.enterTime) {
    return enterTime < newP.enterTime;
  }
  //As a last resort for tie breaks, it will compare the plane ID numbers and return the lower one. 
  return planeId < newP.planeId;
}

std::ostream& operator<<(std::ostream& stream, const Plane& p) {
  stream << p.enterTime << " " << p.planeId << " " << p.comeGo << " " << p.priority;
  return stream;
}

class priorityQ{
  public:

  bool oneType;
  priorityQ::priorityQ();
  bool getOneType();
  void upheapify(int);
  void dwheapify(int);
  bool empty();
  int size();
  void push(Plane&);
  Plane pop(); //removes and returns the first element in the queue
  Plane peek(); //just returns the first element of the queue but doesn't remove like pop. 
  void isOneType(); //Checks the heap to see if there is only "arriving" or "departing" left.

  std::vector<Plane> minHeap; //Holds all the planes. 
};

bool priorityQ::getOneType() {
  return oneType;
}

void priorityQ::upheapify(int heapIndex) {
  int parentIndex = (heapIndex - 1) / 2;
  while( heapIndex > 0 && minHeap[heapIndex] < minHeap[parentIndex]) {
    swap(minHeap[heapIndex], minHeap[parentIndex]);
    heapIndex = parentIndex;
    //Rest since it is first initalized outside of while loop. 
    parentIndex = (heapIndex - 1) / 2;
  }
}
void priorityQ::dwheapify(int heapIndex) {
  int LIndex = 2 * heapIndex + 1;
  int RIndex = 2 * heapIndex + 2;
  int min = heapIndex;
  if (LIndex < minHeap.size() && minHeap[LIndex] < minHeap[min]) {
    min = LIndex;
  }
  if (RIndex < minHeap.size() && minHeap[RIndex] < minHeap[min]) {
    min = RIndex;
  }
  if (min != heapIndex) {
    swap(minHeap[heapIndex], minHeap[min]);
     dwheapify(min);
  }
}

bool priorityQ::empty() {
 if (minHeap.size() == 0) {
  return true;
 }
 return false;
}

int priorityQ::size() {
  return minHeap.size();
}

//This will work as an insert function to push planes to the heap. 
void priorityQ::push(Plane &p) {
  minHeap.push_back(p);
  //The newest plane is added to the end of the heap so only need upward heapify.
  upheapify(minHeap.size() -1);
}

Plane priorityQ::pop() {
  if (minHeap.empty()) {
    return Plane();
  }
  //Pop off the plane at the top of the heap so at the end of the vector.
  Plane top = minHeap[0];
  //Now need to treat it like a delete function and pull the last element to be root.
  minHeap[0] = minHeap.back();
  minHeap.pop_back();
  if (!minHeap.empty()) {
    //Heapify starting from root.
    dwheapify(0);
  }
  return top;
}

Plane priorityQ::peek() {
  if (minHeap.empty()) {
    return Plane();
  }
  Plane peek = minHeap[0]; //Finds the value at the top of the heap and returns the 
  return peek;
}

void priorityQ::isOneType() {
  int depCount = 0;
  int arrCount = 0;
  for (int i = 0; i < minHeap.size(); i++) {
    if (minHeap[i].comeGo == "departing") {
      depCount++;
    } else if ( minHeap[i].comeGo == "arriving") {
      arrCount++;
    }
  }
  if (depCount == 0 || arrCount == 0) {
    oneType = true;
  } else {
    oneType = false;
  }
}

class Runway{
  public:

    string rwId; //Runway ID that holds either A or B
    bool isFull; //Holds the value of if the runway is occupied or not. So empty or not.
    //List of Plane information that arrived or departed during that time stamp 
    Plane runway; //This will be the priority queue for either A or B. 

    Runway::Runway();
    string getId();
    bool getIsFull(); //Checks to see if the Runways are empty or not.  
    void assignPlane(Plane&);
    void clear();
};

Runway::Runway() {
  rwId =' ';
  isFull = false;
}

string Runway::getId(){
  return rwId;
}

bool Runway::getIsFull() {
  return isFull;
} 

void Runway::assignPlane(Plane &p) {
  runway = p;
  isFull = true;
}

void Runway::clear() {
  runway = Plane();
  isFull = false;
}
//total time = last plane to enter simulation 

//time function that checks for any of the three actions and prints them, if none found do not print
//either way time will increment by one and then loop again until i > total time. 
// for (int )

//Ends when the heap and the queues are both empty.

void print();

//Plane overloaded constructor

void print(int time, vector<Plane> enterList, Runway rwA, Runway rwB) { 
  //this function should print out the time stamps and corresponding plane and runway info
  //Check to see if any actions take place on either run way at each time stamp. So maybe a bool check for activity?
  //I'm going to put the check in main so it will only call print when activity happens.
  cout << "Time step " << time << "\n";
  cout << "\tEntering simulation\n";
  for (int i = 0; i <enterList.size()-1; i++) {
    cout << enterList[i] << "\n";
  }
  cout << enterList.back() << "\n";
  //Any plane info that entered the simulation during that time register. Unsure of how to do the cout of this
  //since it could be many cases.
  cout << "Runway A\n";
  if (rwA.getIsFull()) {
    cout << rwA.runway.enterTime;
    cout << rwA.runway.planeId;
    cout << rwA.runway.comeGo;
    cout << rwA.runway.priority << "\n";
  }
  //Same this should print out out the plane info that's on this run way. Should only be one each.
  cout << "Runway B\n";
    if (rwB.getIsFull()) {
    cout << rwB.runway.enterTime;
    cout << rwB.runway.planeId;
    cout << rwB.runway.comeGo;
    cout << rwB.runway.priority << "\n";
  }
  //Same as above  
  rwA.clear();
  rwB.clear();
}

int main() {
  //while the all three are not empty run program.
  //After all the printing has happened time needs to increment. Maybe a while loop to keep us in the 
  //print function and just before leaving have time increment. 
  int currentTime = 0; //This will be used to track the in real time for the simulation.
  priorityQ minHeap;
  Runway runwayA;
  runwayA.rwId = "A";
  Runway runwayB; 
  runwayB.rwId = "B";
  int t = 0;
  int id = 0;
  int p =0;
  string type;
  std::vector<Plane> enterList = {};

  ifstream testFile("test.txt"); //Need to rewor this so I can maybe use a command line arguement.
  if (testFile.is_open() == false) {
    cout << "Error: Test file not read.\n"; //Error check for testing. Will drop once all tests pass.
  }
  string testLine = "";
  string firstLine;
  getline(testFile, firstLine);
  while (getline(testFile, testLine)) {
    stringstream ss(testLine);
    ss >> t >> id >> type >> p;
    Plane newPlane(t, id, type, p);
    minHeap.push(newPlane);
  }
  testFile.close();

  while (!minHeap.empty() || runwayA.getIsFull() || runwayB.getIsFull()) {
    enterList.clear();
    while(!minHeap.empty() && minHeap.peek().getEnterTime() <= currentTime) {
      if (minHeap.oneType == false) {
       for (int i = 0; i < minHeap.size(); i++) {
        if(runwayA.isFull == false || runwayB.isFull == false) {
          if (minHeap[i].getComeGo() == "departing") {
            runwayA.assignPlane(p)
          } else if (minHeap[i].getComeGo() == "arriving") {
            runwayB.assignPlane(p);
          }
        }
       }
      } else if (minHeap.oneType == true) {
        if (runwayA.isFull == false) {
          runwayA.assignPlane(minHeap.peek());
        } else if (runwayB.isFull == false) {
          runwayB.assignPlane(minHeap.peek());
        }
      }
      enterList.push_back(minHeap);
    }
    print(currentTime, enterList, runwayA, runwayB);
    currentTime += 1;
  }
  return 0;
}

