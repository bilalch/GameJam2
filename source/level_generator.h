/*
 * this class defines an object of level generator
 * which will be used to generate a level based on
 * certain difficulty parameters
 */

#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

class LevelGenerator
{
public:
	LevelGenerator(int number);
	~LevelGenerator();

	void Generate();
	int getTypeAtIndex(int);
private:
	int tilesToGenerate;
	int * levelArray;
};

#endif