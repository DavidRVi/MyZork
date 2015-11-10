#include <string>
#include <list>

//Nota: no poner tildes.
using namespace std;
enum Directions { NORTH, SOUTH, WEST, EAST };
class Room
{
private:
	string name;
	string description;

	list<string> items;
	list<Directions> doors;

public:
	Room(string aName);
	Room(string aName, string aDescription);
	void setDescription(string aDescription);
	void addItem(string item);		//Add a given item
	void addDoor(Directions door); //Add a door in a direction, and check there's no door before in that direction
	list<string> getItems();
	list<Directions> getDoors();

	string toString();
};