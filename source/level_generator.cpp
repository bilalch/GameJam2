#include "level_generator.h"
#include "stdlib.h"

LevelGenerator::LevelGenerator(int number)
{
	tilesToGenerate = 1000;
}

LevelGenerator::~LevelGenerator()
{

}

void LevelGenerator::Generate()
{
	levelArray = new int[tilesToGenerate];

	for (int i = 0; i < tilesToGenerate; i++) {
		
		int _number = rand()%3 + 1;
		levelArray[i] = _number;
	}
}

int LevelGenerator::getTypeAtIndex(int _index)
{
	if ( _index > 0 && _index < tilesToGenerate ) {

		return levelArray[_index];
	} else {

		return 1;
	}
}