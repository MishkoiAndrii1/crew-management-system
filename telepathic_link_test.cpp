#include "telepathic_link_test.hpp"

// Constructor
TelepathicLinkTest::TelepathicLinkTest(int signalStrength, int cognitiveLink, int empathicOverlay, int cognitiveResistance)
	: signalStrength(signalStrength), cognitiveLink(cognitiveLink),
	  empathicOverlay(empathicOverlay), cognitiveResistance(cognitiveResistance) {
	total = signalStrength + cognitiveLink + empathicOverlay + cognitiveResistance;
}

// Getters and Setters
int TelepathicLinkTest::getSignalStrength() const {
	return signalStrength;
}
void TelepathicLinkTest::setSignalStrength(int value) {
	signalStrength = value;
	total = signalStrength + cognitiveLink + empathicOverlay + cognitiveResistance;
}

int TelepathicLinkTest::getCognitiveLink() const {
	return cognitiveLink;
}
void TelepathicLinkTest::setCognitiveLink(int value) {
	cognitiveLink = value;
	total = signalStrength + cognitiveLink + empathicOverlay + cognitiveResistance;
}

int TelepathicLinkTest::getEmpathicOverlay() const {
	return empathicOverlay;
}
void TelepathicLinkTest::setEmpathicOverlay(int value) {
	empathicOverlay = value;
	total = signalStrength + cognitiveLink + empathicOverlay + cognitiveResistance;
}

int TelepathicLinkTest::getCognitiveResistance() const {
	return cognitiveResistance;
}
void TelepathicLinkTest::setCognitiveResistance(int value) {
	cognitiveResistance = value;
	total = signalStrength + cognitiveLink + empathicOverlay + cognitiveResistance;
}

int TelepathicLinkTest::getTotal() const {
	return total;
}

// Output operator
ostream& operator<<(ostream& os, const TelepathicLinkTest& t) {
	os << "Signal Strength: " << t.signalStrength
	   << ", Cognitive Link: " << t.cognitiveLink
	   << ", Empathic Overlay: " << t.empathicOverlay
	   << ", Cognitive Resistance: " << t.cognitiveResistance
	   << ", Total: " << t.total;
	return os;
}
