
#include"Votes.h"
#include <vector>



using namespace std;
namespace elc
{
	Votes::Votes(int _numOfParties, int _numOfDistricts) 
		: after_calcs(false), numOfParties(_numOfParties), numOfDistricts(_numOfDistricts), vote_buffer()
	{
		setVotes_table(_numOfDistricts, _numOfParties);
		setElectors_table(_numOfDistricts, _numOfParties);
	}


	void Votes::setVotes_table(const unsigned int& numOfDistricts, const unsigned int& numOfParties)
	{
		while (votes_table.size() < numOfDistricts)
		{
			vector<int> temp;
			while (temp.size() < numOfParties)
			{
				temp.push_back(0);
			}
			votes_table.push_back(temp);
		}
	}

	void Votes::setElectors_table(const unsigned int& numOfDistricts, const unsigned int& numOfParties)
	{
		while (electors.size() < numOfDistricts)
		{
			vector<int> temp;
			while (temp.size() < numOfParties)
			{
				temp.push_back(0);
			}
			electors.push_back(temp);
		}
	}

	void Votes::updateVotesTable()
	{
		auto itr = vote_buffer.begin();
		while (itr != vote_buffer.end())
		{
			votes_table[itr->first][itr->second]++;
			++itr;
		}
	}

	void Votes::setVote(Citizen& voter, int PartyID)
	{
		vote_buffer.push_back(pair<int, int>(voter.getDistrict().getDistID(), PartyID));
		voter.setVote(true);
	}

	const int Votes::getTotalPartyVotes(const int& partyID) const
	{
		int sum = 0;

		for (auto itr = votes_table.begin(); itr != votes_table.end(); ++itr)
		{
			sum += (*itr).at(partyID);
		}
		return sum;
	}

	const int Votes::getTotalVotesInDistrict(const int& DistID) const
	{
		int sum = 0;

		for (auto itr = votes_table[DistID].begin(); itr != votes_table[DistID].end(); ++itr)
		{
			sum += *itr;
		}
		return sum;
	}

	const int Votes::getPartyVotesInDist(const int& PartyID, const int& distID) const
	{
		return votes_table[distID][PartyID];
	}

	const float& Votes::getPartyVotesPrecentageInDist(const int& PartyID, const int& distID) const
	{
		int totalDistVotes = getTotalVotesInDistrict(distID);
		if (totalDistVotes != 0)
			return ((100 * (static_cast<float>(getPartyVotesInDist(PartyID, distID))) / totalDistVotes));
		else
			return 0;
	}

	const float& Votes::getTotalVotesPrecentage(const CitizensList& list)const
	{
		unsigned int i, citizens = list.getList().size();
		float totalVotes = 0;

		for (i = 0; i < votes_table.size(); i++)
		{
			totalVotes += getTotalVotesInDistrict(i);
		}

		return (100 * (totalVotes / citizens));

	}

	const float& Votes::getDistVotesPrecantage(const District& dist)const
	{
		int citizens = dist.GetDistCitizens().size();
		float votes = getTotalVotesInDistrict(dist.getDistID());

		return (100 * (votes / citizens));
	}


	const vector<pair<Party&,int>> Votes::getSortedElectorResults(const PartyList& parties)const
	{
		vector<pair<Party&,int>> results;
		unsigned int i, j, elecs;

		for (i = 0; i < parties.getList().size(); i++)
		{
			Party& prt = *(parties.getList()[i]);
			elecs = getTotalPartyElectors(prt.getpartyID());
			
			results.push_back(pair<Party&, int>(prt, elecs));
		}

		//bubbleSort for array of <part,int> pairs
		//sort by the int value
		for (i = 0; i < results.size() - 1; i++)
		{
			for (j = 0; j < results.size() - i - 1; j++)
			{
				if (results.at(j).second > results.at(j + 1).second)
				{
					results.at(j).swap(results.at(j + 1));
				}
			}
		}

		return results;
	}

	const vector<pair<Party&, int>> Votes::getSortedVotesResults(const PartyList& parties)const
	{
		vector<pair<Party&, int>> results;
		unsigned int i, j;
		int votes;

		for (i = 0; i < parties.getList().size(); i++)
		{
			Party& prt = *(parties.getList()[i]);
			votes = getTotalPartyVotes(prt.getpartyID());

			results.push_back(pair<Party&, int>(prt, votes));
		}

		//bubbleSort for array of <part,int> pairs
		//sort by the int value
		for (i = 0; i < results.size() - 1; i++)
		{
			for (j = 0; j < results.size() - i - 1; j++)
			{
				if (results.at(j).second > results.at(j + 1).second)
				{
					results.at(j).swap(results.at(j + 1));
				}
			}
		}

		return results;
	}

	
	
	void Votes::setElectorsInDist(PartyList& parties, District& dist)
	{
		unsigned int i;
		int partyElectors, chosen_counter = 0, remaining , distID=dist.getDistID();
		int totalVotes = getTotalVotesInDistrict(distID);
		float partyPrecent, approxElectors, avg;
		//const Senator* temp;

		for (i = 0; i < electors[distID].size(); i++) //calculating rough estimate of electors for each party
		{
			partyPrecent = getPartyVotesPrecentageInDist(i, distID);
			approxElectors = (partyPrecent / 100) * dist.getDistReps();
			partyElectors = (int)approxElectors;
			chosen_counter += partyElectors;

			electors[distID][i] = partyElectors;
		}

		remaining = dist.getDistReps() - chosen_counter;
		if (remaining > 0)
		{
			avg = static_cast<float>(remaining) / parties.getList().size();
			for (i = 0; i < electors[distID].size() && remaining > 0; i++)
			{
				partyPrecent = getPartyVotesPrecentageInDist(i, distID);
				approxElectors = (partyPrecent / 100) * dist.getDistReps();
				partyElectors = static_cast<int>(approxElectors);
				if (approxElectors - partyElectors >= avg)
				{
					//partyElectors += 1;
					electors[distID][i]++;
					remaining--;
				}
			}

			for (i = 0; remaining > 0; i++)
			{
				electors[distID][i]++;
				remaining--;
			}
		}

		for (i = 0; i < electors[distID].size(); i++)
		{
			for (int j = 0; j < electors[distID][i]; j++)
			{
				dist.addPartyRepToList(i, parties.getPartyRepInDist(i, distID, j));
			}
		}

	}
	
	const int Votes::getElectorsforPartyInDist(const int& partyID, const int& distID) const
	{
		return electors[distID][partyID];
	}

	const int Votes::getTotalPartyElectors(const int& partyID)const
	{
		int sum = 0;

		for (auto itr = electors.begin(); itr != electors.end(); ++itr)
		{
			sum += (*itr).at(partyID);
		}
		return sum;
	}

	const int Votes::getWinnerIDInDist(const int& distID) const
	{
		//-1 is for sanity check
		unsigned int i;
		int max = -1, winningPartyID = -1;

		for (i = 0; i < votes_table[distID].size(); i++)
		{
			if (votes_table[distID][i] > max)
			{
				winningPartyID = i;
				max = votes_table[distID][i];
			}
		}
		return winningPartyID;
	}

	const int Votes::getWinnerIDInDist(District* const dist) const
	{
		unsigned int i;
		int max = 0, winningPartyID = -1;

		if (typeid(dist) == typeid(Divided))
		{
			for (i = 0; i < votes_table[dist->getDistID()].size(); i++)
			{
				if (max < votes_table[dist->getDistID()][i])
				{
					winningPartyID = i;
					max = votes_table[dist->getDistID()][i];
				}
			}
		}
		return winningPartyID;

	}

	/************************* Seralization *********************************/

	void Votes::save(ofstream& out) const
	{
		bool temp = false;
		out.write(rcastcc(&temp), sizeof(temp));
		out.write(rcastcc(&numOfParties), sizeof(numOfParties));
		out.write(rcastcc(&numOfDistricts), sizeof(numOfDistricts));
		int flag1,flag2; // 0 if electors && votetable are null ptr, else flag ==1

		if (electors.size() == 0)
			flag1 = 0;
		else
			flag1 = 1;

		if (votes_table.size() == 0)
			flag2 = 0;
		else
			flag2 = 1;

		out.write(rcastcc(&flag1), sizeof(flag1));
		out.write(rcastcc(&flag2), sizeof(flag2));

		if (flag1)
		{
			for (int i = 0; i < numOfDistricts; i++)
			{
				for (int j = 0; j < numOfParties; j++)
				{
					out.write(rcastcc(&electors[i][j]), sizeof(int));
				}
			}
		}

		if (flag2)
		{
			for (int i = 0; i < numOfDistricts; i++)
			{
				for (int j = 0; j < numOfParties; j++)
				{
					out.write(rcastcc(&votes_table[i][j]), sizeof(int));
				}
			}
		}

		int bufferSize = vote_buffer.size();
		out.write(rcastcc(&bufferSize), sizeof(bufferSize));
		for (auto itr : vote_buffer)
		{
			out.write(rcastcc(&itr.first), sizeof(itr.first));
			out.write(rcastcc(&itr.second), sizeof(itr.second));
		}
	}

	void Votes::load(ifstream& in)
	{
		int flag1, flag2; // 0 if electors && votetable are null ptr, else flag ==1
		
		in.read(rcastc(&after_calcs), sizeof(after_calcs));
		in.read(rcastc(&numOfParties), sizeof(numOfParties));
		in.read(rcastc(&numOfDistricts), sizeof(numOfDistricts));
		in.read(rcastc(&flag1), sizeof(flag1));
		in.read(rcastc(&flag2), sizeof(flag2));


		if (flag1 == 1)
		{
			setElectors_table(numOfDistricts, numOfParties);
			for (int i = 0; i < numOfDistricts; i++)
			{
				for (int j = 0; j < numOfParties; j++)
				{
					in.read(rcastc(&electors[i][j]), sizeof(int));
				}
			}
		}

		if (flag2 ==1)
		{
			setVotes_table(numOfDistricts,numOfParties);
			for (int i = 0; i < numOfDistricts; i++)
			{
				for (int j = 0; j < numOfParties; j++)
				{
					in.read(rcastc(&votes_table[i][j]), sizeof(int));
				}
			}
		}

		int bufferSize;
		pair<int, int> temp;
		vote_buffer.clear();
		in.read(rcastc(&bufferSize), sizeof(bufferSize));
		for (int i = 0; i < bufferSize; i++)
		{
			in.read(rcastc(&temp.first), sizeof(temp.first));
			in.read(rcastc(&temp.second), sizeof(temp.second));
			vote_buffer.push_back(temp);
		}

	}
}