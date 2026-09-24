#include "CrewMember.hpp"
using std::string;
using std::ostream;


int currentid = 25220000;
// 1. Constructor implementation
CrewMember::CrewMember(string first, string last, float score, int aptitude)
    : firstName(first), lastName(last), trainingScore(score), missionAptitude(aptitude), id(currentid++)
{
   
}

// 1 means put a after b, -1 means put a before b, 0 means put them together

int compareFirstName(const CrewMember& a, const CrewMember& b) {
    
    
    
    
    
    if(a.firstName > b.firstName) return 1;
    
    
    if(a.firstName < b.firstName) return -1;
    
    
    return 0;
}

int compareLastName(const CrewMember& a, const CrewMember& b) {
    if(a.lastName > b.lastName) return 1;
    
    
    if(a.lastName < b.lastName) return -1;
    
    
    return 0;
}

// a?b, ? could be >, <, ==
int compareTrainingScore(const CrewMember& a, const CrewMember& b) {
    
    // a>b return 1, put a before
    if(a.trainingScore > b.trainingScore) return -1;
    
    //a<b return -1, put a after
    if(a.trainingScore < b.trainingScore) return 1;
    
    //a==b return 0
    return 0;
}

// a?b, ? could be >, <, ==
int compareMissionAptitude(const CrewMember& a, const CrewMember& b) {
    
    // a>b return 1, put a before
    if(a.missionAptitude > b.missionAptitude) return -1;
    
    //a<b return -1, put a after
    if(a.missionAptitude < b.missionAptitude) return 1;
    
    //a==b return 0
    return 0;
}

//crewmember pair

string CrewMember::getFirstName() const {
    return firstName;
}

void CrewMember::setFirstName(string newFirstName){
    firstName= newFirstName;
};


// lastName pair
string CrewMember::getLastName() const {
    return lastName;
}

void CrewMember::setLastName(string newLastName) {
    lastName = newLastName;
}

// trainingScore pair
float CrewMember::getTrainingScore() const {
    return trainingScore;
}

void CrewMember::setTrainingScore(float newScore) {
    trainingScore = newScore;
}

// MissionAptitude pair
int CrewMember::getMissionAptitude() const {
    return missionAptitude;
}

void CrewMember::setMissionAptitude(int newAptitude) {
    missionAptitude = newAptitude;
}

// ID pair
int CrewMember::getId() const {
    return id;
}

void CrewMember::setId(int newId) {
    id = newId;
}


