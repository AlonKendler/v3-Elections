#include <iostream>
#include "District.h"
#include "Citizen.h"
#include "Party.h"

using namespace std;
using namespace elc;

#define MAX_SIZE 50


//void mainMenu(Elections& e, bool& doneVoting);
//void inputDateAndElectionRound(Elections& e);
//void inputScreenPage1();
//void inputScreenPage2(Elections& e);
//
//void save(Elections& e, bool& doneVoting);
//void load(Elections* e, bool& doneVoting);
//
//void addDistric(Elections& e);
//void addCitizen(Elections& e);
//void addParty(Elections& e);
//void addPartyCandidates(Elections& e);
//
//void results(Elections& e);
//void simpleResults(Elections& e);
//void openVotingMenu(Elections& e, bool& doneVoting);
//bool handleErrors(int ctrl, Elections& e);
//

void inputScreenPage1()
{
	std::cout << "--------intput screen--------" << endl;
	std::cout
		<< " 1 - Create new election round. " << endl
		<< " 2 - Load Existing election round from file." << endl
		<< " 3 - Exit program." << endl
		<< "waiting for input..." << endl;
}
void inputScreenPage2()
{

	std::cout << endl << "--------intput screen--------" << endl;
	//(e.getRoundType()) ? cout << "   Simple Election Round" << endl : cout << "   Normal Election Round" << endl;
	std::cout << "   Election Date:" <<  endl;
	std::cout << "--------intput screen--------" << endl << endl;
	std::cout << "what would you like to add? " << endl
		<< " 1 - Add District. " << endl
		<< " 2 - Add Citizen." << endl
		<< " 3 - Add Party." << endl
		<< " 4 - Add representitive for a party. " << endl
		<< " 5 - print ALL districts." << endl
		<< " 6 - print ALL citizens." << endl
		<< " 7 - print ALL parties." << endl
		<< " 8 - VOTE!! (inputs will no longer be avilable)" << endl
		<< " 9 - show results." << endl
		<< " 10 - exit this menu." << endl
		<< " 11 - Save Elections Round." << endl
		<< " 12 - Load Elections Round." << endl
		<< "waiting for input..." << endl;
}

//void openingMenu()
//{
//	int ctrl;
//	bool doneVoting = false;
//	inputScreenPage1();
//	cin >> ctrl;
//
//	while (ctrl < 1 || ctrl>4) //handle inputs
//	{
//		std::cout << "wrong input!!" << endl;
//		cin >> ctrl;
//	}
//	switch (ctrl)
//	{
//	case 1: { }; break;
//	}
//	//case 2: { load(&e, doneVoting); break; }
//	//case 3: { std::cout << "Exit menu was chosen, byebye!" << endl; break; }
//	}
//}
//


int main()
{
	District d1("tlv", 5, 1);
	Divided d2("jaffa", 3, 2);

	District& p = d2;
	

	cout << d1 << endl;
	cout << d2 << endl;
	cout << p << endl;


}
