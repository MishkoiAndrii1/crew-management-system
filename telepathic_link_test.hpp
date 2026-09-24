#ifndef TELEPATHIC_LINK_TEST_HPP
#define TELEPATHIC_LINK_TEST_HPP

#include <iostream>
using std::ostream;

class TelepathicLinkTest {
private:
    int signalStrength;
    int cognitiveLink;
    int empathicOverlay;
    int cognitiveResistance;
    int total;

public:

    TelepathicLinkTest(int signalStrength = 0, int cognitiveLink = 0, int empathicOverlay = 0, int cognitiveResistance = 0);


    int getSignalStrength() const;
    void setSignalStrength(int value);

    int getCognitiveLink() const;
    void setCognitiveLink(int value);

    int getEmpathicOverlay() const;
    void setEmpathicOverlay(int value);

    int getCognitiveResistance() const;
    void setCognitiveResistance(int value);

    int getTotal() const; 


    friend ostream& operator<<(ostream& os, const TelepathicLinkTest& t);
};

#endif
