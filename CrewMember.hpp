#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <string>
#include <iostream>
using std::string;
using std::ostream;


class CrewMember {
    private:
    string firstName, lastName;
    float trainingScore;
    int missionAptitude, id;
    
    public:
    CrewMember(string firstName, string lastName, float trainingScore, int missionAptitude);
    virtual ~CrewMember() = default;
    virtual string getType() const = 0;
    
    
     virtual void print(ostream& os) const = 0;
    
    // Friend operator<< that uses the virtual function
    friend ostream& operator<<(ostream& os, const CrewMember& cm) {
        cm.print(os);
        return os;
    }
    
    //friends
    friend int compareFirstName(const CrewMember& a, const CrewMember& b);
    friend int compareMissionAptitude(const CrewMember& a, const CrewMember& b);
    friend int compareLastName(const CrewMember& a, const CrewMember& b);
    friend int compareTrainingScore(const CrewMember& a, const CrewMember& b);
    
    //firstName pair
    string getFirstName() const;
    void setFirstName(string newFirstName);
    // LastName pair  
    string getLastName() const;
    void setLastName(string newLastName);
    
    // TrainingScore pair
    float getTrainingScore() const;
    void setTrainingScore(float newScore);
    
    // MissionAptitude pair
    int getMissionAptitude() const;
    void setMissionAptitude(int newAptitude);
    
    // ID pair
    int getId() const;
    void setId(int newId);  
    
    
};
































#endif