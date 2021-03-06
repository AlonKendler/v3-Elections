#include <iostream>
#include <string>
#include "Elections.h"

using namespace std;
using namespace elc;

#define MAX_SIZE 50

void mainMenu(Elections& e, bool& doneVoting);
void inputDateAndElectionRound(Elections& e);
void inputScreenPage1();
void inputScreenPage2(Elections& e);

void save(Elections& e,bool& doneVoting);
void load(Elections* e,bool& doneVoting);

void addDistric(Elections& e);
void addCitizen(Elections& e);
void addParty(Elections& e);
void addPartyCandidates(Elections& e);

void results(Elections& e, bool& doneVoting);
void simpleResults(Elections& e);
void openVotingMenu(Elections& e);
bool handleErrors(int ctrl, Elections& e);

template<class T>
void printObjects(T& objList)
{
	cout << objList;
}

enum menu { ADDdistrict = 1, ADDcitizen = 2, ADDparty = 3, ADDrep = 4,
	PRINTdistrict = 5, PRINTcitizen = 6, PRINTparty = 7, VOTE = 8, 
	RESULTS = 9, EXIT = 10, SAVE = 11, LOAD = 12 };

enum firstMenu { CREATE=1, LOADD=2, EXITT =3 };

void inputScreenPage1()
{
	std::cout << "--------intput screen--------" << endl;
	std::cout
		<< " 1 - Create new election round. " << endl
		<< " 2 - Load Existing election round from file." << endl
		<< " 3 - Exit program." << endl
		<< "waiting for input..." << endl;
}
void inputScreenPage2(Elections& e)
{
	
	std::cout << endl << "--------intput screen--------" << endl;
	(e.getRoundType()) ? cout << "   Simple Election Round" << endl : cout << "   Normal Election Round" << endl;
	std::cout << "   Election Date:" << e.getDate() << endl;
	std::cout << "--------intput screen--------" << endl << endl;
	std::cout << "what would you like to add? " << endl
		<< " 1 - Add District. " << endl
		<< " 2 - Add Citizen." << endl
		<< " 3 - Add Party." << endl
		<< " 4 - Add representitive for a party. " << endl
		<< " 5 - print ALL districts." << endl
		<< " 6 - print ALL citizens." << endl
		<< " 7 - print ALL parties." << endl
		<< " 8 - VOTE!!" << endl
		<< " 9 - show results." << endl
		<< " 10 - exit this menu." << endl
		<< " 11 - Save Elections Round." << endl
		<< " 12 - Load Elections Round." << endl
		<< "waiting for input..." << endl;
}

void openingMenu(Elections& e)
{
	int ctrl;
	bool doneVoting = false;
	inputScreenPage1();
	cin >> ctrl;

	while (ctrl < 1 || ctrl>4) //handle inputs
	{
		std::cout << "wrong input!!" << endl;
		cin >> ctrl;
	}
	switch (ctrl)
	{
	case CREATE: { system("CLS"); inputDateAndElectionRound(e); mainMenu(e,doneVoting); break; }
	case LOADD: { load(&e, doneVoting) ; break; }
	case EXITT: { std::cout << "Exit menu was chosen, byebye!" << endl; break; }
	}
}

void inputDateAndElectionRound(Elections& e)
{
	Date _date;
	int day, month, year;
	int type = 0, reps = 0;
	char distName[20] = "system-District";

	cout << " Welcome to Roy & Alon Election program!" << endl;
	while(_date.getYear() == 1970) // default year is 1970
	{
		cout << "please enter the date fot this run in 'DD/MM/YYYY' format: " << endl;
		cout << "Enter Day: "; cin >> day;	   
		cout << "Enter Month: "; cin >> month; 
		cout << "Enter Year: "; cin >> year;   

		try { _date =  Date(day, month, year); }
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
	e.setDate(_date); //sets e.date after handle input

	
	std::cout << "choose Election round type (0 - normal) , (1 - simple) : "; cin >> type;
	if (type != 0 && type != 1) cout << "That imput was not a choice... ill make it a Simple round.." << endl;
	if (type)
	{
		while (true)
		{
			e.setRoundType(type);
			std::cout << "Enter number of Representitives: "; cin >> reps;
			try {
				e.handleSimpleRound(distName, reps);
				break;
			}
			catch (exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
	}
}

void mainMenu(Elections& e, bool& doneVoting)
{
	int ctrl;
	bool done = false; //flag for while loop
	char* date = new char[MAX_SIZE];
	
	system("CLS");
	while (!done)
	{
		inputScreenPage2(e);
		//cin.ignore();
			cin >> ctrl;
		while (ctrl < 1 || ctrl>12) //handle inputs
		{
			std::cout << "wrong input!!" << endl;
			cin >> ctrl;
		}
		while (handleErrors(ctrl, e)) //handle logical errors
		{
			cin >> ctrl;
		}

		system("CLS");
		switch (ctrl)
		{
		case ADDdistrict:	{if (!doneVoting && !e.getRoundType()) addDistric(e); 
						    else cout << "function not avilable in a Simple Election round" << endl;break; }
		case ADDcitizen:	{if (!doneVoting) { addCitizen(e); }break; }
		case ADDparty:		{if (!doneVoting) { addParty(e); }break; }
		case ADDrep:		{if (!doneVoting) { addPartyCandidates(e); }break; }
		case PRINTdistrict: {printObjects(e.getDistList()); break; }
		case PRINTcitizen:  {printObjects(e.getCitizensList()); break; }
		case PRINTparty:    {printObjects(e.getPartyList()); break; }
		case VOTE:			{if (!doneVoting) openVotingMenu(e); break; }
		case RESULTS:		{try { results(e, doneVoting); }
							catch (exception& ex) { cout << ex.what() << endl; } break; }
		case EXIT:			{ done = true; break; }
		case SAVE:			{ save(e, doneVoting); break; }
		case LOAD:			{ load(&e, doneVoting) ; break; }
		}
	}
	system("CLS");
	std::cout << "Exit menu was chosen, byebye!" << endl;
}


void save(Elections& e, bool& doneVoting)
{
	char name[MAX_SIZE];
	std::cout << "enter name of file" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);

	ofstream outfile(name, ios::binary | ios::trunc);
	if (!outfile) {
		cout << "error opening file for write" << endl;
		exit(-1);
	}
	outfile.write(rcastcc(&doneVoting), sizeof(doneVoting));
	e.save(outfile);

	cout << "data was saved to file: " << name << endl;
	outfile.close();
}


void load(Elections* e, bool& doneVoting )
{
	char name[MAX_SIZE];
	std::cout << "enter name of file" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);

	ifstream infile(name, ios::binary);
		if (!infile)
		{
			cout << "error opening file for read" << endl;
			exit(-1);
		}
		infile.read(rcastc(&doneVoting), sizeof(doneVoting));
		e = new Elections(infile);
		mainMenu(*e, doneVoting);
		infile.close();
}


void addDistric(Elections& e)
{
	string name;
	int num, type;
	

	std::cout << "enter name of district:" << endl;
	cin.ignore();
	cin >> name;
	std::cout << "enter number of representitves:" << endl; cin >> num;
	std::cout << "enter type of district: (0 - normal, 1 - divided):" << endl; cin >> type;

	try {
		e.addDistrict(name, num, type); 
	}
	catch (std::exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

bool validateCitizenAge(Elections& e, int yob)
{
	int electionYear = e.getDate().getYear();
	if (electionYear - yob > 18)
		return true;
	else
		return false;
}

void addCitizen(Elections& e)
{
	string name, idStr;
	int id, yob, distID;
	District * temp;
	bool flag = true;
	std::cout << "enter name" << endl;			cin >> name;
	std::cout << "enter id" << endl;			cin >> idStr;
	while (!(std::all_of(idStr.begin(), idStr.end(), ::isdigit)) || idStr.size()!=9)
	{
		//validates id cotains only digits, and is of size == 9
		cout << "invalid id, 9 digits require: "; cin >> idStr; cout << endl;
	}
	id = stoi(idStr); //converts string to int

	std::cout << "enter year of birth" << endl; cin >> yob;
	while (!validateCitizenAge(e, yob))
	{
		cout << "age smaller than 18, compared to election date:"
			<< e.getDate() << endl <<  " enter year of birth: "; cin >> yob;
	}
	//Handle simple round
	try {

		if (!e.getRoundType())
		{
			while (flag)
			{
				std::cout << "enter district from avilable: ";
				e.printDistrictsNameAndID(); std::cout << endl;
				cin >> distID;
				try {
					temp = e.getDistrictPtr(distID);
					e.addCitizen(name, id, *temp, yob);
					flag = false;
				}
				catch (out_of_range& ex) {
					cout << ex.what() << endl;
				}
			}
		}
		else // if simple, we want to pass add citizen function without district
		{
				e.addCitizen(name, id,e.getDistrict(0),yob); //in simple round, 0 is default id
		}
	}
	catch (std::exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

void addParty(Elections& e)
{
	string name;
	int id;
	bool flag = false;
	const Citizen* temp;

	while (!flag)
	{
		std::cout << "enter name of the party:" << endl;		cin >> name;
		std::cout << "enter id of president" << endl;			cin >> id;

		try {
			temp = e.getCitizenPtr(id);
			if (temp == nullptr)
			{
				throw (invalid_argument("ID did not match to an existing citizen."));
			}
			
			e.addParty(name, *temp); //party ctor throws
			flag = true; //success, break loop
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}
	std::cout << "all good, passed input" << endl;
}

void addPartyCandidates(Elections& e)
{
	int id, partyID, distID;
	const Citizen* temp;
	std::cout << "please enter the ID of the Candidate" << endl;
	cin >> id;
	temp = e.getCitizenPtr(id);
	while (temp == nullptr)
	{
		std::cout << "id did not match to an existing citizen." << endl
			<< "please enter a valid id: " << endl;
		cin >> id;
		temp = e.getCitizenPtr(id);
	}

	std::cout << "enter Party from avilable: ";
	e.printPartiesNameAndID(); std::cout << endl;
	cin >> partyID;

	if (e.getRoundType())
		distID = 0;
	else
	{
		std::cout << "enter District from avilable: ";
		e.printDistrictsNameAndID(); std::cout << endl;
		cin >> distID;
	}
	try {
		e.addPartyCandidate(*temp, partyID, distID);
	}
	catch (out_of_range& ex)
	{
		cout << ex.what() << endl;
		cout << "Representative object not added, procced" << endl;
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
}

void openVotingMenu(Elections& e)
{
	char ctl = '0';
	int id, partyID;
	Citizen* temp;
	system("CLS");

	while (ctl != 'q' && ctl != 'Q')
	{
		std::cout << "Welcome to voting proccess!" << endl
			<< "Please enter ID to vote." << endl;
		cin >> id;
		temp = e.getCitizenPtr(id);
		while (temp == nullptr)
		{
			system("CLS");
			std::cout << "ID was not found, please enter Valid ID" << endl;
			cin >> id;
			temp = e.getCitizenPtr(id);
		}
		if (temp->getVote())
		{
			std::cout << "why like this... you already Voted!" << endl;
		}
		else
		{
			system("CLS");
			std::cout << "plese enter the number of the party you would like to vote for. " << endl;
			std::cout << "enter Party from avilable: " << endl;
			e.printPartiesNameAndID(); std::cout << endl;
			cin >> partyID;
			try {
				e.setVote(*temp, partyID);
				std::cout << "Thank You very much for participating in the Voting Proccess!" << endl;
			}
			catch (out_of_range& ex)
			{
				cout << ex.what() << endl;
				cout << "please try again." << endl;
			}
		}
		std::cout << "please press any key other then 'Q'and then 'Enter' to finish, and clear your place for the next Voter," << endl
			<< "Or press 'Q' then 'Enter' to terminate voting proccess " << endl;
		cin.ignore();
		cin >> ctl;
		system("CLS");
	}

	return;
}


void results(Elections& e, bool& doneVoting)
{
	if (e.isVotesEmpty() )
		throw(invalid_argument("No votes submited. Please start voting proccess first"));
	if (!e.enoughReps())
		throw(invalid_argument("there are not enough Representatives in a party"));

	doneVoting = true;
	e.setResults();

	if (e.getRoundType())
	{
		simpleResults(e);
		return;
	}

	int winnerIdDist;
	int party_id, numOfReps;
	int numOfDistricts = e.getDistrictsLength(), numOfParties = e.getPartiesLength();
	vector<pair<Party&, int>> party_order = e.getVotes().getSortedElectorResults(e.getPartyList());
	string partyName;
	const District* dist;


	cout << "for Elections " << e.getDate() << ", The elections results are as follow: " << endl << endl;

	for (int i = 0; i < numOfDistricts; i++)
	{
		dist = &e.getDistrict(i);
		winnerIdDist = e.getVotes().getWinnerIDInDist(i);
		partyName = e.getParty(winnerIdDist)->getPartyName();
		numOfReps = e.getDistrict(i).getDistReps();
		std::cout << " --- In District " << dist->getDistName() << " --- " << endl
			<< "number of representative in the district: " << numOfReps << endl;
		if (typeid(*dist) == typeid(Divided))
		{
			cout << "District "<< dist->getDistName() << " is a divided district" << endl << endl;
			for (int j = numOfParties-1; j >= 0; j--)
			{
				party_id = party_order[j].first.getpartyID();
				partyName = party_order[j].first.getPartyName();
				numOfReps = e.getVotes().getElectorsforPartyInDist(party_id, i);

				if (numOfReps > 0)
				{
					cout << numOfReps << " Electors from the district choose " << e.getParty(j)->getBoss().getName()
						<< ", of party " << partyName << endl;
				}
				else
				{
					cout << "party " << partyName << " has no representatives" << endl;
				}
			}
			cout << endl;
		}
		else
			cout << "The district gives all of its representatives to: " << partyName << endl << endl
			<< "voting precantage in the District: " << e.getVotes().getDistVotesPrecantage(*dist) <<"%"<< endl << endl;

		for (int j = numOfParties-1; j >= 0; j--)
		{
			party_id = party_order[j].first.getpartyID();
			partyName = party_order[j].first.getPartyName();
			numOfReps = e.getVotes().getElectorsforPartyInDist(party_id, i);

			cout << "  - For party " << partyName << " -" << endl
				<< "number of votes won in the district: " << e.getVotes().getPartyVotesInDist(party_id, i) << endl
				<< "precentage of votes: " << e.getVotes().getPartyVotesPrecentageInDist(party_id, i) << "%" << endl
				<< "number of representatives won: " << numOfReps << endl;
			if (numOfReps > 0)
			{
				cout << "party representatives: " << endl;
				e.getDistrict(i).printPartyRepsNames(party_id);
			}
			cout << endl << endl;
		}

	}

	cout << " -- Election results for each party --  " << endl << endl;
	for (int i = numOfParties - 1; i >= 0; i--)
	{
		party_id = party_order[i].first.getpartyID();
		partyName = e.getParty(party_id)->getPartyName();
		int partyVotes = e.getVotes().getTotalPartyVotes(party_id);

		cout << "  - For party " << partyName << " - " << endl
			<< "Party candidate for prime minister: " << e.getParty(party_id)->getBoss().getName() << endl
			<< "Total party electors won: " << party_order[i].second << endl
			<< "Total party votes: " << partyVotes << endl << endl;
	}
	return;

}


void simpleResults(Elections& e)
{
	const CitizensList& citizens = e.getCitizensList();
	int i, numOfReps, party_id, partyVotes, numOfParties = e.getPartiesLength();
	vector<pair<Party&, int>> party_order = e.getVotes().getSortedVotesResults(e.getPartyList());
	string partyName;

	cout << "for Elections " << e.getDate() << ", The elections results are as follow: " << endl << endl
		<< "With a total of " << e.getVotes().getTotalVotesPrecentage(citizens) << "% votes precentage:" << endl;
	
	for (i = numOfParties-1; i >= 0; i--)
	{
		party_id = party_order[i].first.getpartyID();
		partyName = e.getParty(party_id)->getPartyName();
		numOfReps = e.getVotes().getElectorsforPartyInDist(party_id, 0);
		partyVotes = e.getVotes().getTotalPartyVotes(party_id);
		
		cout << "  - For party " << partyName << "-" << endl
			<< "party candidate for prime minister: " << e.getParty(party_id)->getBoss().getName() << endl
			<< "number of votes won: " << partyVotes << endl
			<< "precentage of votes: " << e.getVotes().getPartyVotesPrecentageInDist(party_id, 0) << "%" << endl
			<< "number of representatives won: " << numOfReps << endl;
			if (numOfReps > 0)
			{
				cout << "party representatives: " << endl;
				e.getDistrict(0).printPartyRepsNames(party_id);
			}
		cout << endl << endl;
	}
	cout << endl;
}


bool handleErrors(int ctrl, Elections& e)
{
	if (ctrl == 2 && e.getDistrictsLength() == 0)
	{
		std::cout << "no districts avilable" << endl;
		return true;
	}

	if (ctrl == 3 && e.getCitizensLength() == 0)
	{
		std::cout << "no citizens avilable" << endl;
		return true;
	}

	if (ctrl == 4 && e.getPartiesLength() == 0)
	{
		std::cout << "no parties avilable" << endl;
		return true;
	}

	if (ctrl == 4 && e.getCitizensLength() == 0)
	{
		std::cout << "no citizens avilable" << endl;
		return true;
	}
	if (ctrl == 8 && e.getCitizensLength() == 0)
	{
		std::cout << "no citizens avilable" << endl;
		return true;
	}	
	return false;
}



