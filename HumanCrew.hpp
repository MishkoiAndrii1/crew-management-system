#ifndef HUMANCREW_HPP
#define HUMANCREW_HPP

#include "CrewMember.hpp"


class HumanCrew : public CrewMember {
private:
	string homeSector;

public:
	HumanCrew(string first, string last, float score, int aptitude, string sector);
	string getHomeSector() const;
	void setHomeSector(string newHomeSector);
	 string getType() const override { return "Human"; }
	 void print(ostream& os) const;
	
};

























#endif