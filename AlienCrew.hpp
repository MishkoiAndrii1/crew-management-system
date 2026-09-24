#ifndef ALIENCREW_HPP
#define ALIENCREW_HPP

#include "CrewMember.hpp"
#include "telepathic_link_test.hpp"
#include <string>
#include <iostream>
using namespace std;

class AlienCrew : public CrewMember {
private:
    string homeworld;
    TelepathicLinkTest telepathicTest;

public:
    // Constructor
    AlienCrew(string first, string last, float score, int aptitude,
              string world, const TelepathicLinkTest& test);

    // Getters and Setters
    string getHomeworld() const;
    void setHomeworld(string newHomeworld);

    TelepathicLinkTest getTelepathicTest() const;
    void setTelepathicTest(const TelepathicLinkTest& test);

    // Output Operator
    string getType() const override { return "Alien"; }
    void print(ostream& os) const;
};

#endif
