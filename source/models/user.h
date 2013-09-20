#ifndef USER_H
#define USER_H

#include "model.h"
#include "powers.h"

class UserModel: public Model {
public:
	UserModel();
	~UserModel();

	int getID() { return ID; };
	void setID(int _id) { ID = _id; };
	string getName() { return name; };
	void setName(string _name) { name = _name; };
	string getUDID() { return udid; };
	void setUDID(string _udid) { udid = _udid; };
	double getTotalDistance() { return totalDistance; };
	void setTotalDistance(double _distance) { totalDistance = _distance; };
	double getTotalTime() { return totalTime; };
	void setTotalTime(double _time) { totalTime= _time; };
	PowersModel * getArmour() { return armour; };
	void setArmour(PowersModel *_armour) { armour->copy(_armour); };
	PowersModel * getGunPowder() { return gunPowder; };
	void setGunPowder(PowersModel *_armour) { gunPowder->copy(_armour); };
	PowersModel * getGunRecoil() { return gunRecoil; };
	void setGunRecoil(PowersModel *_armour) { gunRecoil->copy(_armour); };
	PowersModel * getForceField() { return forceField; };
	void setForceField(PowersModel *_armour) { forceField->copy(_armour); };
	PowersModel * getNoReload() { return noReload; };
	void setNoReload(PowersModel *_armour) { noReload->copy(_armour); };
	PowersModel * getInvincible() { return invincible; };
	void setInvincible(PowersModel *_armour) { invincible->copy(_armour); };
	PowersModel * getBribeACop() { return bribeACop; };
	void setBribeACop(PowersModel *_armour) { bribeACop->copy(_armour); };
	PowersModel * getBribeADeveloper() { return bribeADeveloper; };
	void setBribeADeveloper(PowersModel *_armour) { bribeADeveloper->copy(_armour); };
	PowersModel * getPullAHoudini() { return pullAHoudini; };
	void setPullAHoudini(PowersModel *_armour) { pullAHoudini->copy(_armour); };

	//http
	void receivedHTTPResponse();
	void httpMeta();
	void modelMeta();

private:
	int ID;
	string name;
	string udid;
	double totalTime;
	double totalDistance;
	PowersModel *armour;
	PowersModel *gunPowder;
	PowersModel *gunRecoil;
	PowersModel *forceField;
	PowersModel *noReload;
	PowersModel *invincible;
	PowersModel *bribeACop;
	PowersModel *bribeADeveloper;
	PowersModel *pullAHoudini;
};

#endif