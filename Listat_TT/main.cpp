#include "XMLparser.h"

int main() {
	try {
		XMLparser test_xml("test.xml");
		test_xml.parse();
		test_xml.printParsed();
		test_xml.makeIntervals();
		test_xml.printInervals();
	}
	catch (const descriptive_exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}