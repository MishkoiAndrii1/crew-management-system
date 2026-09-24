#include "AlienCrew.hpp"

AlienCrew::AlienCrew(string first, string last, float score, int aptitude,
                     string world, const TelepathicLinkTest& test)
    : CrewMember(first, last, score, aptitude), homeworld(world), telepathicTest(test)
{
}

string AlienCrew::getHomeworld() const {
    return homeworld;
}

void AlienCrew::setHomeworld(string newHomeworld) {
    homeworld = newHomeworld;
}

TelepathicLinkTest AlienCrew::getTelepathicTest() const {
    return telepathicTest;
}

void AlienCrew::setTelepathicTest(const TelepathicLinkTest& test) {
    telepathicTest = test;
}

void AlienCrew::print(ostream& os) const {
    os << "ID: " << getId() << " | Name: " << getFirstName()  
       << " " << getLastName() << " | Training: " << getTrainingScore()
       << " | Aptitude: " << getMissionAptitude() << " | Homeworld: " << getHomeworld()
       << " | Telepathic Total: " << telepathicTest.getTotal();
}