#include "json_parser.h"
#include <string>

using namespace std;

class JsonTest : public JsonParser {
public:
	string name;
	int age;
	double grade;
	bool active;
	int64 ID;

	JsonTest(){
		name = "test";
		age = 10;
		grade = 2.35;
		active = true;
		ID = 1234568976454321354;

		bindJsonAttribute("name", name);
		bindJsonAttribute("age", age);
		bindJsonAttribute("grade", grade);
		bindJsonAttribute("active", active);
		bindJsonAttribute("id", ID);
	}
};