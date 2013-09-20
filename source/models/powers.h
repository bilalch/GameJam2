#ifndef POWERS_H
#define POWERS_H

#include "http.h"
#include "model.h"

class PowersModel: public Http, public Model {
public:
	PowersModel();
	~PowersModel();

	int getID() { return ID; };
	void setID(int _id) { ID = _id; };
	double getPrice() { return price; };
	void setPrice(double _price) { price = _price; };
	int getType() { return type; };
	void setType(int _type) { type = _type; };
	string getTypeName() { return typeName; };
	void setTypeName(string _type) { typeName = _type; };
	int getValue() { return value; };
	void setValue(int _value) { value = _value; };
	int getLevelNumber() { return levelNumber; };
	void setLevelNumber(int _number) { levelNumber = _number; };
	PowersModel *clone();
	void copy(PowersModel *_power);

	//http
	void receivedHTTPResponse();
	void httpMeta();
	void modelMeta();

private:
	int ID;
	int levelNumber;
	double price;
	int type;
	string typeName;
	double value;
};

#endif