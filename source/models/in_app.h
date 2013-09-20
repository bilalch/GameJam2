#ifndef IN_APP_H
#define IN_APP_H

#include "http.h"
#include "model.h"

class InAppModel: public Http, public Model {
public:
	InAppModel();
	~InAppModel();

	int getID() { return ID; };
	void setID(int _id) { ID = _id; };
	string getName() { return name; };
	void setID(string _name) { name = _name; };
	string getPackageID() { return packageID; };
	void setPackageID(string _packageID) { packageID = _packageID; };
	double getPrice() { return price; };
	void setPrice(double _price) { price = _price; };
	int getType() { return type; };
	void setType(int _type) { type = _type; };
	int getValue() { return value; };
	void setValue(int _value) { value = _value; };

	//http
	void receivedHTTPResponse();
	void httpMeta();
	void modelMeta();

private:
	int ID;
	string name;
	string packageID;
	double price;
	int type;
	double value;
};

#endif