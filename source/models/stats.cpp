#include "stats.h"

StatsModel::StatsModel(){
	ID = 0;
	timePlayed = 0;
	distanceCovered = 0;
	score = 0;
	carsDestroyed = 0;
	prepareModel();
}

StatsModel::~StatsModel(){

}

void StatsModel::modelMeta(){
	bindModelAttribute("id", ID);
	bindModelAttribute("time_played", timePlayed);
	bindModelAttribute("distance_covered", distanceCovered);
	bindModelAttribute("score", score);
	bindModelAttribute("cars_destroyed", carsDestroyed);
	setModelMetaKey("id");
	setModelMetaTableName("stats");
}