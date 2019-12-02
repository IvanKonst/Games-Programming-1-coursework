#pragma once
#include <string>
#include <vector>

using namespace std;

class cHighScoreTable
{
private:
	struct Item {
		string Name = "";
		int score = 0;

		bool operator < ( const Item& rhs) const
		{
			return rhs.score < score;
		}
	};

	int tableSize = 0;
	bool fileEmpty = false;
	int MAX_SIZE = 10;

	Item tableEntry;

	vector<Item*> tableEntries;
	vector<Item*>::iterator row;

	string userName = "";
	
public:
	cHighScoreTable();
	cHighScoreTable(int maxSize);

	bool loadFromFile(string highScoreFile);
	bool saveToFile(string highScoreFile);

	int  addItem(Item entry);
	int  addItem(string name, int score);

	Item getItem(int theRow);
	void clearTable();
	string convertToString();
	int getTableSize();
	void setTableSize(int theSize);

	bool getIsFileEmpty();
	void setIsFileEmpty(bool flag);

	void getUserName();

	virtual ~cHighScoreTable();
};

