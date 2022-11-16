#include "Towers.h"

//Initializers
Towers::Towers() {
	this->populateTowers();
}

Towers::Towers(int towers_) {
	if (towers_ > 2) {
		this->towerCount = towers_;
	} else {
		this->failFlag = true;
		this->errorType = this->notEnoughTowers;
	}

	this->populateTowers();
}

Towers::Towers(int towers_, int rings_) {
	if (towers_ > 2) {
		this->towerCount = towers_;
	} else {
		this->failFlag = true;
		this->errorType = this->notEnoughTowers;
	}

	if (rings_ > 1) {
		if (rings_ < 10) {
			this->rings = rings_;
		} else {
			this->rings = this->colorDepth;
			this->failFlag = true;
			this->errorType = this->tooManyRings;
		}
	} else {
		this->failFlag = true;
		this->errorType = this->notEnoughRings;
	}

	this->populateTowers();
}

//Deinitializer
Towers::~Towers() {
	//Empty individual towers
	for (int x = 0; x < this->towerCount; x++) {
		this->towers[x].clear();
	}

	//Empty the board
	this->towers.clear();
}

//Private Utilities
bool Towers::populateTowers() {
	for (int y = 0; y < this->towerCount; y++) {
		//Populate a new tower
		std::vector<int> newTower = {};

		for (int x = this->rings; x > 0; x--) {
			if (y < this->towerCount - 1) {
				newTower.push_back(x);
			} else {
				newTower.push_back(this->towerColor);
			}
		}

		//Add populated new tower to linked-list of towers
		this->towers.push_back(newTower);
	}

	return false;
}

int Towers::towerState(std::vector<int> tower) {
	int spaceCount = 0;
	int code = -2;

	for (int x = 0; x < signed(tower.size()); x++) {
		if (tower[x] == this->towerMarker) {
			spaceCount++;
		}
	}

	if (spaceCount == this->rings) {
		code = 0;
	} else if (spaceCount == 0) {
		code = -1;
	} else {
		code = 1;
	}

	return code;
}

int Towers::countRings(std::vector<int> tower) {
	int rings = 0;

	for (int x = 0; x < signed(tower.size()); x++) {
		if (tower[x] != this->towerMarker) {
			rings++;
		}
	}

	return rings;
}

//Public Utilities
bool Towers::shuffle() {
	bool shuffled = false;
	int source = 0;
	int destination = 0;
	int moved = 0;

	//Seed RNG
	srand((unsigned int)time(NULL));

	for (int x = 0; x < (this->towerCount * 16); x++) {
		do {
			source = rand() % this->towerCount + 1;
			destination = rand() % this->towerCount + 1;

			moved = this->move(source, destination);
		} while (moved != 0);
	}

	if (this->isSolved() == false) {
		shuffled = true;
	}

	return shuffled;
}

int Towers::move(int source, int destination) {
	int return_code = 0;
	int temp = 0;

	int sourceState = 0;
	int destinationState = 0;

	//Create copies for redundancy / easy identification
	std::vector<int> sourceTower = {};
	std::vector<int> destinationTower = {};

	if (source > 0 && source <= this->towerCount) {
		sourceTower = this->towers[source - 1];
	} else {
		//Source is Out-Of-Bounds
		return_code = -3;
	}

	if (return_code == 0) {
		if (destination > 0 && destination <= this->towerCount) {
			destinationTower = this->towers[destination - 1];
		} else {
			//Destination is Out-Of-Bounds
			return_code = -4;
		}
	}

	//If copies were made
	if (return_code == 0) {
		if (source == destination) {
			//Destination & Source cannot be the same
			return_code = -4;

		} else if (this->towerState(sourceTower) == 0) {
			//Source is empty
			return_code = -1;

		} else if (this->towerState(destinationTower) == -1) {
			//Destination is full
			return_code = -2;

		} else {
			destinationTower[this->countRings(destinationTower)] = sourceTower[this->countRings(sourceTower) - 1];
			sourceTower[this->countRings(sourceTower) - 1] = this->towerMarker;

			this->towers[source - 1] = sourceTower;
			this->towers[destination - 1] = destinationTower;

			//Memory Management
			sourceTower.clear();
			destinationTower.clear();
		}
	}

	return return_code;
}

void Towers::printRaw() {
	for (int tower = 0; tower < this->towerCount; tower++) {
		for (int ring = 0; ring < this->rings; ring++) {
			std::cout << this->towers[tower][ring] << ",";
		}

		std::cout << std::endl;
	}
}

void Towers::draw() {
	SetConsoleTextAttribute(this->consoleHandle, this->defaultColor);
	int colorConstant = int(this->colorDepth / this->rings);

	for (int tower = 0; tower < this->towerCount; tower++) {
		std::cout << "Tower " << tower + 1 << ": ";
		for (int ring = 0; ring < this->rings; ring++) {
			if (this->towers[tower][ring] == this->towerMarker) {
				SetConsoleTextAttribute(this->consoleHandle, this->towerColor);
				std::cout << std::setfill('-') << std::setw(2) << this->towerChar << std::setfill(' ');
			} else {
				SetConsoleTextAttribute(this->consoleHandle, this->towers[tower][ring] * colorConstant);
				std::cout << std::setfill(this->towerChar) << std::left << std::setw(2) << this->towers[tower][ring] << std::setfill(' ') << std::right;
			}
		}

		std::cout << std::endl;

		//Reset Console Color
		SetConsoleTextAttribute(this->consoleHandle, this->defaultColor);
	}
}

//Getters
int Towers::getTowerCount() {
	return this->towerCount;
}

int Towers::getTowerSize() {
	return this->rings;
}

int Towers::getMaxRings() {
	return this->colorDepth;
}

bool Towers::fail() {
	return this->failFlag;
}

int Towers::error() {
	return this->errorType;
}

bool Towers::isSolved() {
	bool solved = false;



	return solved;
}

//Overloads
std::ostream& operator<<(std::ostream& stream, Towers& towers) {
	int errorCode = towers.error();

	switch (errorCode) {
		case 2:
			stream << "Not Enough Towers";
			break;
		case 3:
			stream << "Too Many Rings.";
			break;
		case 4:
			stream << "Not Enough Rings.";
			break;
		case 6:
			stream << "Not Enough Towers and Too Many Rings";
			break;
		case 8:
			stream << "Not Enough Towers and Not Enough Rings";
			break;
		default:
			stream << "None";
			break;
	}

	return stream;
}