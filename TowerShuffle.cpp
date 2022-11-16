#pragma warning(disable : 6031)

#include <iostream>
#include <conio.h>
#include <windows.h>

#include "Towers.h"

using namespace std;

int main();

void clear();

int main() {
	bool looping = true;
	bool valid = true;
	bool customSetup = false;

	bool playing = true;
	bool settingDest = true;

	int source = 0;
	int destination = 0;
	int returnCode = 0;
	
	int towers = 0;
	int rings = 0;

	char input = ' ';

	//Main Menu
	do {
		cout << "Welcome to the Vector Tower Jump." << endl;
		cout << "Would you like a custom setup? (y/n)" << endl;
		cout << ">>";

		input = _getch();

		if (input == 'Y' || input == 'y') {
			valid = true;
			customSetup = true;
		} else if (input == 'N' || input == 'n') {
			looping = false;
			valid = true;
		}
	} while (valid == false);

	while (looping == true) {
		valid = false;

		while (valid == false) {
			clear();

			cout << "Welcome to the Vector Tower Jump." << endl;
			cout << "Please enter the amount of towers you would like." << endl;
			cout << ">>";
			cin >> towers;

			if (cin.fail() == true) {
				//refresh cin
				cin.clear();
				rewind(stdin);

				cout << "Warning! Invalid input." << endl;
				cout << "Your input must be a real number" << endl;
				cout << "Press any key to try again" << endl << ">>";
				_getch();

			} else if (towers < 2) {
				cout << "Warning!" << endl << "There must be at least 2 towers." << endl;
				cout << "Press any key to try again..." << endl << ">>";
				_getch();

			} else if (towers > 9) {
				cout << "Warning!" << endl << "There must be no more than 9 towers." << endl;
				cout << "Press any key to try again..." << endl << ">>";
				_getch();

			} else {
				valid = true;
			}
		}

		valid = false;
		while (valid == false) {
			clear();
			cout << "Welcome to the Vector Tower Jump." << endl;
			cout << "There are " << towers << " towers" << endl;
			cout << "Please enter the amount of rings you would like per tower." << endl;
			cout << ">>";
			cin >> rings;

			if (cin.fail() == true) {
				//refresh cin
				cin.clear();
				rewind(stdin);

				cout << "Warning! Invalid input." << endl;
				cout << "Your input must be a real number" << endl;
				cout << "Press any key to try again" << endl << ">>";
				_getch();

			} else if (rings < 2) {
				cout << "Warning!" << endl << "There must be at least 2 rings per tower." << endl;
				cout << "Press any key to try again..." << endl << ">>";
				_getch();

			} else if (rings > 9) {
				cout << "Warning!" << endl << "There must be no more than 9 rings." << endl;
				cout << "Press any key to try again..." << endl << ">>";
				_getch();

			} else {
				valid = true;
			}
		}

		Towers example(towers, rings);

		if (example.fail() == false) {
			valid = false;

			while (valid == false) {
				clear();
				cout << "This is what you entered..." << endl;
				example.draw();

				cout << "Please confirm if this is correct (y/n)..." << endl;
				cout << ">>";
				input = _getch();

				if (input == 'Y' || input == 'y') {
					looping = false;
					valid = true;
				} else if (input == 'N' || input == 'n') {
					valid = true;
				}
			}

		} else {
			clear();
			cout << "Warning! Failed to generate game." << endl;
			cout << example;
			cout << endl << "Press any key to try again..." << endl;
			cout << ">>";
			_getch();
		}
	}

	//Generate official board
	clear();
	Towers game = (customSetup == false) ? Towers() : Towers(towers, rings);

	//Shuffle
	game.shuffle();

	//Play Game
	do {
		clear();
		game.draw();
		cout << "Please select a source tower or 'X' to quit..." << endl;
		cout << ">>";
		source = _getch();

		if (source == 120) {
			playing = false;

		} else {
			source -= 48;
			settingDest = true;

			do {
				clear();
				game.draw();
				cout << "Source: " << source << endl;
				cout << "Please select a destination tower or 'X' to quit, 'B' to go back..." << endl;
				cout << ">>";
				destination = _getch();

				if (destination == 120) {
					playing = false;
					settingDest = false;

				} else if (destination == 98) {
					settingDest = false;

				} else {
					destination -= 48;

					returnCode = game.move(source, destination);

					switch (returnCode) {
						case invalidMove:
							cout << "\n\nMove invalid. Press any key to try again..." << endl;
							cout << ">>";
							_getch();
							break;

						case noSpaceInDestination:
							cout << "\n\nDestination has no space. Press any key to try again..." << endl;
							cout << ">>";
							_getch();
							break;

						case invalidDestination:
							cout << "\n\nInvalid destination. Press any key to try again..." << endl;
							cout << ">>";
							_getch();
							break;

						case noRingsInSource:
							cout << "\n\nSource has no rings. Press any key to try again..." << endl;
							cout << ">>";
							_getch();

							settingDest = false;
							break;

						case invalidSource:
							cout << "\n\nInvalid source. Press any key to try again..." << endl;
							cout << ">>";
							_getch();

							settingDest = false;
							break;

						default:
							settingDest = false;
							break;
					}
				}

			} while (settingDest == true);
		}

	} while (playing == true);

	clear();
	cout << "Thanks for playing. Press any key to exit..." << endl;
	cout << ">>";
	_getch();
	return 0;
}

void clear() {
	system("cls");
}