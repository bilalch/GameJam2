#ifndef STATS_H
#define STATS_H

#include "model.h"

class StatsModel: public Model {
public:
	StatsModel();
	~StatsModel();

	int getID() { return ID; };
	void setID(int _id) { ID = _id; };
	int getCarsDestroyed() { return carsDestroyed; };
	void setCarsDestroyed(int _cars) { carsDestroyed = _cars; };
	double getTimePlayed() { return timePlayed; };
	void setTimePlayed(double _time) { timePlayed = _time; };
	double getDistanceCovered() { return distanceCovered; };
	void setDistanceCovered(double _distance) { distanceCovered = _distance; };
	int getScore() { return score; };
	void setScore(int _score) { score = _score; };

	void modelMeta();

private:
	int ID;
	int carsDestroyed;
	double timePlayed;
	double distanceCovered;
	int score;
};

#endif