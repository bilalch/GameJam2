#ifndef HTTP_TEST_INTERFACE
#define HTTP_TEST_INTERFACE

#include "http.h"
#include "model.h"
#include "json_parser.h"
#include <string>

using namespace std;

class HttpTest : public Http, public Model {
public:
	string name;
	int age;
	double grade;
	bool active;
	int64 ID;

	HttpTest();
	~HttpTest();

	void receivedHTTPResponse();
	void httpMeta();
	void modelMeta();
};

#endif