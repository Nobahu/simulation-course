#pragma once


namespace Rules {

	const float FIRE_PROBABILITY = 0.01;
	const float SPAWN_PROBABILITY = 0.01;

}

enum WindDirection {

	North = 0,
	East = 1,
	South = 2,
	West = 3,

};

enum CellCondition {

	Land = 0,
	Tree = 1,
	Fire = 2,
	Water = 3

};