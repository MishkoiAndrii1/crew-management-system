#include "HumanCrew.hpp"

HumanCrew::HumanCrew(string first, string last, float score, int aptitude, string sector)
	: CrewMember(first, last, score, aptitude), homeSector(sector)
{
}

string HumanCrew::getHomeSector() const {
	return homeSector;
}

void HumanCrew::setHomeSector(string newHomeSector) {
	homeSector= newHomeSector;
}


void HumanCrew::print(ostream& os) const {
    os << "ID: " << getId() << " | Name: " << getFirstName()  // ← Remove "human."
       << " " << getLastName() << " | Training: " << getTrainingScore()
       << " | Aptitude: " << getMissionAptitude() << " | Sector: " << getHomeSector();
}