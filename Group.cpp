#include "exceptions.h"
#include "Group.h"
#include <cmath>
#include <iostream>
using std::endl;

using namespace mtm;

/**
* Constructor
* @param name The group's name. Can't be empty.
* @param clan The clan which the group belongs to.
*  empty string means no clan.
* @param children The amount of children in the group. Must be
*  non-negative.
* @param adults Bigger number means more tools. Must be non-negative.
* @param tools Bigger number means more tools. Must be non-negative.
* @param food Bigger number means more food. Must be non-negative.
* @param morale Bigger number means higher morale.
*  Must be between 0 to 100.
* @throws GroupInvalidArgs If at least one of the arguments is
*  invalid, or both adults and children are 0.
*/
Group::Group(const std::string& name, const std::string& clan, int children,
	int adults, int tools, int food, int morale) //: name(name), clan(clan), children(children)
//	, adults(adults), tools(tools), food(food), morale(morale)
{
	if ((name.empty() == true) || (children < 0) || (adults < 0) || (tools < 0)
		|| (food < 0) || (morale < 0) || (morale > 100) ||
		((adults == 0) && (children == 0))) {
		throw GroupInvalidArgs();
	}
	this->name = name;
	this->clan = clan;
	this->children = children;
	this->adults = adults;
	this->tools = tools;
	this->food = food;
	this->morale = morale;
}


/**
* Constructor.
* - The group will not belong to any clan.
* - The group will have 4 tools for every adult.
* - The group will have 3 food for every adult,
*      and 2 food for every child
* - The group will have 70 morale.
* @param name The group's name. Can't be empty.
* @param children The amount of children in the group. Must be
*  non-negative.
* @param adults Bigger number means more tools. Must be non-negative.
* @throws GroupInvalidArgs If at least one of the arguments is
*  invalid, or both adults and children are 0.
*/
Group::Group(const std::string& name, int children, int adults)// : name(name), children(children)
//, adults(adults), tools(4 * adults), food(3 * adults + 2 * children), morale(70) 
{
	if ((name == "") || (children < 0) || (adults < 0) || ((adults == 0) && (children == 0))) {
		throw GroupInvalidArgs();
	}
	this->name = name;
	this->children = children;
	this->adults = adults;
	this->tools = 4 * adults;
	this->food = 3 * adults + 2 * children;
	this->morale = 70;
	this->clan = "";
}


///**
//* Copy constructor
//* @param other The group to copy
//*/
Group::Group(const Group& other) {
	name = other.name;
	clan = other.clan;
	children = other.children;
	adults = other.adults;
	tools = other.tools;
	food = other.food;
	morale = other.morale;
}

///** Destructor
//*/
//onst std::string& name, const std::string& clan, int children,
//int adults, int tools, int food, int morale)
Group::~Group() = default;



/**
* Get the name of the group
* @return The name of the group
*/
const std::string& Group::getName() const {
	return name;
}

/**
* Get the amount of people (children + adults) in the group.
* @return  Amount of people in the group
*/
int Group::getSize() const {
	return children + adults;
}

/**
* @return The name of the clan that the group belongs to.
*/
const std::string& Group::getClan() const {
	return clan;
}


/**
* Change the clan of the group.
* If the group had a different clan before, reduce morale by 10%.
* If the group's clan was the same as the given one, do nothing.
* Otherwise, increase morale by 10%. (floor in both cases)
*
* floor: 0.5 -> 0, 1.5 -> 1 etc...
* @param clan The name of the new clan that the groups will belong to.
*/
void Group::changeClan(const std::string& clan) {
	if (this->clan != clan) {
		if (this->clan == "") {
			//increase morale by 10%
			morale = morale + (morale * 10) / 100;
		}
		else {
			//reduce morale by 10%.
			morale = morale - (morale * 10) / 100;
		}
	}
	this->clan = clan;
}

/**
* Compare two groups. according to power (defined here), and name.
*
* Power: ((10*number_of_adults + 3 * number_of_children) *
* (10 * number_of_tools + number_of_food)*morale)/100 (floor)
*
* @param rhs
* @return true, if power(this) < power(rhs), or if they're equal and
*  this group's name is smaller (lexicographic) than rhs's name.
*  false otherwise.
*/

int Group::getPower(const Group& group) const {
	int power_group = ((10 * group.adults + 3 * group.children) *
		(10 * group.tools + group.food)*group.morale) / 100;
	return power_group;
}

bool Group::operator<(const Group& rhs) const {
	int power_rhs = Group::getPower(rhs);
	int power_this = Group::getPower(*this); //is it okay? ask oren

	if (power_this < power_rhs) {
		return true;
	}

	if ((power_this == power_rhs) && (std::string(this->name) < std::string(rhs.name))) {
		return true;
	}
	return false;
}


/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) > power(rhs), or if they're equal and
*  this group's name is bigger (lexicographic) than rhs's name.
*  false otherwise.
*/
bool Group::operator>(const Group& rhs) const {
	int power_rhs = Group::getPower(rhs);

	int power_this = Group::getPower(*this);

	if (power_this > power_rhs) {
		return true;
	}
	if ((power_this == power_rhs) && (std::string(this->name)> std::string(rhs.name))) {
		return true;
	}
	return false;
}

/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) < power(rhs), or if they're equal and
*  this group's name is not bigger (lexicographic) than rhs's name.
*  false otherwise.
*/
bool Group::operator<=(const Group& rhs) const { //try to write it with < if there is time
	int power_rhs = Group::getPower(rhs);
	int power_this = Group::getPower(*this); //is it okay? ask oren

	if (power_this < power_rhs) {
		return true;
	}

	if ((power_this == power_rhs) && (std::string(this->name) <= std::string(rhs.name))) {
		return true;
	}
	return false;
}

/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) > power(rhs), or if they're equal and
*  this group's name is not smaller (lexicographic) than rhs's name.
*  false otherwise.
*/
bool Group::operator>=(const Group& rhs) const { //try to write it with > if there is time
	int power_rhs = Group::getPower(rhs);
	int power_this = Group::getPower(*this);

	if (power_this > power_rhs) {
		return true;
	}

	if ((power_this == power_rhs) && (std::string(this->name) >= std::string(rhs.name))) {
		return true;
	}
	return false;
}

/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) == power(rhs), and this group's name is
* equal to rhs's name.
* false otherwise.
*/
bool Group::operator== (const Group& rhs) const {
	int power_rhs = Group::getPower(rhs);
	int power_this = Group::getPower(*this);

	if ((power_this == power_rhs) && (std::string(this->name) == std::string(rhs.name))) {
		return true;
	}
	return false;
}

/**
* Compare two groups. according to power, and name.
* @param rhs
* @return true, if power(this) != power(rhs), and this group's name
* isn't equal to rhs's name.
* false otherwise.
*/
bool Group::operator!=(const Group& rhs) const {
	return !(*this == rhs);
	/*int power_rhs = Group::getPower(rhs);
	int power_this = Group::getPower(*this);

	if ((power_this != power_rhs) && (std::string(this->name) != std::string(rhs.name))) {
		return true;
	}
	return false;*/
}


//compare by all parameters
//return true if is the same group
//else return false
bool Group::checkIsTwoGroupAreTheSame(Group& other) {
	if ((this->name == other.name) && (this->clan == other.clan) && (this->children == other.children)
		&& (this->adults == other.adults) && (this->tools == other.tools) && (this->food == other.food)
		&& (this->morale == other.morale)) {
		return true;
	}
	return false;
}



/**
* Try to unite two groups, this group, and given group.
* Will succeed only if the two groups are not the same group, //
* belong to the same clan, both have at least 70 morale, and they
* don't surpass together a given amount of people.
* Should the union succeed, this group will change according to:
* - name = name of the more powerful group
* - clan = old clan
* - children = sum of the children in the two groups
* - adults = sum of the adults in the two groups
* - tools = sum of the tools in the two groups
* - food = sum of the food in the two groups
* - morale = average of the morales, counting the amount of people
* (floor)
*
* The other group will become empty.
* @param other The group to unite with.
* @param max_amount If the two groups have more people combined then
*  max_amount, then the union fails.
* @return True if Unite was successful, false otherwise.
*/

void Group::emptyGroup(Group& other) {
	other.name = "";
	other.clan = "";
	other.adults = 0;
	other.children = 0;
	other.tools = 0;
	other.food = 0;
	other.morale = 0;
}


bool Group::unite(Group& other, int max_amount) {
	//check if the same group
	//if (checkIsTwoGroupAreTheSame(other) == true) {
	if(this == &other){
	return false;
	}
	if (std::string(this->clan) != std::string(other.clan)) {
		return false;
	}
	if (((this->morale) <= 70) || (other.morale <= 70)) {
		return false;
	}
	if (this->children + this->adults + other.children + other.adults > max_amount) {
		return false;
	}
	if (operator<(other)){ //if other sronger then this
		this->name = other.name; // this name is changed to the athers name							 //clan name stey the same
	}
	//this will have the parameters of the united group
	int this_size = this->children + this->adults;
	int other_size = other.children + other.adults;
	this->morale = ((this_size)*this->morale + (other_size)*other.morale)
		/ (this_size + other_size);
	this->children = this->children + other.children;
	this->adults = this->adults + other.adults;
	this->tools = this->tools + other.tools;
	this->food = this->food + other.food;
	//other group will become empty:
	emptyGroup(other);
	return true;
}

/**
* Divide the group.
*
* After the division this group will have the same
*  name, clan, morale. And ceiling of half of children , adults ,
*  tools, food
*
* The other group will have a new name, same clan, same morale,
*  and floor of half of children , adults, tools, food.
*
* Ceiling: 0.5 -> 1, 1.5 -> 2 etc...
*
* floor: 0.5 -> 0, 1.5 -> 1 etc...
* @param name The name of the new group.
* @return The new group, that divided from this group.
* @throws GroupInvalidArgs If name is empty.
* @throws GroupCantDivide If the divided group Would be empty (can
* only happen of this group has no more than 1 child and 1 adult).
*/
Group Group::divide(const std::string& name) {
	if (name == "") {
		throw GroupInvalidArgs();
	}
	if ((this->children <= 1) || (this->adults <= 1)) {
		throw GroupCantDivide();
	}

	Group new_group(name, this->clan, this->children / 2, this->adults / 2
		, this->tools / 2, this->food / 2, this->morale);

	//ceil(a/b) = (a + b - 1)/b :
	this->children = (this->children + 2 - 1) / 2;
	this->adults = (this->adults + 2 - 1) / 2;
	this->tools = (this->tools + 2 - 1) / 2;
	this->food = (this->food + 2 - 1) / 2;

	return new_group;
}


Group& Group::addToLoser(Group& other) {
	other.children = ceil((2 * other.children) / 3);
	other.adults = ceil((2 * other.adults) / 3);
	other.tools = ceil((1 * other.tools) / 2);
	other.food = ceil((1 * other.food) / 2);
	other.morale = ((80 * other.morale) / 100);
	if (other.morale > 100) {
		other.morale = 100;
	}
	if (other.morale < 0) {
		other.morale = 0;
	}
	return other;
}

//loser_food is the food the losing group had before the fight
Group& Group::addToWinner(Group& other, int loser_food) {
	other.adults = other.adults - other.adults / 4; //((3 * other.adults)/4);
	other.tools = other.tools - other.tools / 4;
	other.food = other.food + ceil(loser_food / 2) / 2;
	other.morale = other.morale + ceil(other.morale*0.20);//ceil((120 * other.morale)/100);
	if (other.morale > 100) {
		other.morale = 100;
	}
	if (other.morale < 0) {
		other.morale = 0;
	}
	return other;
}



/**
* This group fights an opponent group. The bigger group according to
*  the relational operators is the winner. If both groups are equal,
*  the groups will not fight.//
*
* Fights effects on the loser group:
* - Losing third of each of the children and adult population (ceiling)
* - Losing Half of the tools, and half of the food (ceiling)
* - Morale decreases by 20%. (ceiling)
* For example: if a group that had 5 adults and 3 tools lost and 50
* morale, it will have 3 adults, 1 tool, and 40 morale after the fight.
*
* Fights effects on the winner group:
* - Losing a quarter of the adults (floor) and no children.
* - Losing a quarter of the tools (floor).
* - gaining half of the food the loser group lost in the fight. (floor)
*      The gain is equal to ceiling(loser.food / 2) / 2, even if the
*      loser group lost all of it's people.
* - Morale increases by 20%. (ceiling)
* @param opponent The group to fight with.
* @return WON if this group won, LOST if this group lost, and DRAW
* in case the 2 groups are equal.
* @throws GroupCantFightWithItself if opponent is the same as this  //
* @throws GroupCantFightEmptyGroup if this group, or the other group //
*  is empty (i.e no people).
*/

FIGHT_RESULT Group::fight(Group& opponent) {
	//if (checkIsTwoGroupAreTheSame(other) == true) {
	if (this == &opponent) {
		throw GroupCantFightWithItself();
	}
	if ((this->children + this->adults == 0) || (opponent.children + opponent.adults == 0)) {
		throw GroupCantFightEmptyGroup();
	}
	if (operator==(opponent) == true) {//power(this) =  power(rhs) and names equal
		return DRAW;
	}

	if (operator>(opponent) == true) { //power(this) > power(rhs) or names this>rhs
		Group::addToWinner(*this, opponent.food);
		Group::addToLoser(opponent);
		return WON;
	}
	else { //(operator<(opponent) == true) {// power(this) < power(rhs) or names this<rhs
		Group::addToWinner(opponent, this->food);
		Group::addToLoser(*this);
		return LOST;
	}

}


/**
* Try to do a trade between the two groups.
* Each groups tries make its tools and food equal.
* To do that, each group offers |group's tools - group's food| / 2
* (ceiling) of the resource it has more of.
* If the other group offers the other resource, a trade is made.
* In the trade, each group gives the average of the offers [(offer1 +
* offer2)/2 (ceiling)], from the resource it has more of. A group
* can't give more tools or food than it has, and the two groups
* always trade the same amount of resources.
*
* If one of the groups has the same amount of tools as amount of
* food, or if both has more tools than food, or vice versa,
* the trade would not be made.
* @param other Group to trade with.
* @return true if a trade was made, false otherwise.
* @throws GroupCantTradeWithItself if other is the same as this
*/
void Group::makeTheTradeThisHasMoreTools(Group& other, int trade) {
	if ((this->tools < trade) || (other.food < trade)) {
		if (this->tools < other.food) {
			this->food = this->food + this->tools;  //other give to this same amount of food
			other.food = other.food - this->tools;
			other.tools = other.tools + this->tools; //this give to other the tools it have
			this->tools = 0;
		}
		if (other.food < this->tools) {
			other.tools = other.tools + other.food; //this give tools to other
			this->tools = this->tools - other.food;
			this->food = this->food + other.food; //other give food to this
			other.food = 0;
		}
	}
	else {
		other.tools = other.tools + trade;//this give tools to other
		this->tools = this->tools - trade;
		this->food = this->food + trade;//other give food to this
		other.food = other.food - trade;
	}


	//if (this->tools >= trade) {
	//	this->tools = this->tools - trade;
	//	other.tools = other.tools + trade;
	//}
	//else {
	//	other.tools = other.tools + this->tools;
	//	this->tools = 0;
	//}
	////other has more food
	//if (other.food >= trade) {
	//	other.food = other.food - trade;
	//	this->food = this->food + trade;
	//}
	//else {
	//	this->food = this->food + other.food;
	//	other.food = 0;
	//}
}

void Group::makeTheTradeThisHasMoreFood(Group& other, int trade) {

	if ((this->tools < trade) || (other.food < trade)) {
		if (this->food < other.tools) {
			this->tools = this->tools + this->food; //other give this tools
			other.tools = other.tools - this->food;
			other.food = other.food + this->food; //this give other food
			this->food = 0;
		}
		if (other.tools < this->food) {
			other.food = other.food + other.tools;// this give other food
			this->food = this->food - other.tools;
			this->tools = this->tools + other.tools; //other give this tools
			other.tools = 0;
		}
	}
	else {
		other.food = other.food + trade; //this give other food
		this->food = this->food - trade;
		this->tools = this->tools + trade; //other give this tools
		other.tools = other.tools - trade;
	}

	//if (this->food >= trade) {
	//	this->food = this->food - trade;
	//	other.food = other.food + trade;
	//}
	//else {
	//	other.food = other.food + this->food;
	//	this->food = 0;
	//}
	////other has more tools
	//if (other.tools >= trade) {
	//	other.tools = other.tools - trade;
	//	this->tools = this->tools + trade;
	//}
	//else {
	//	this->tools = this->tools + other.tools;
	//	other.tools = 0;
	//}
}

bool Group::checkConditionsForTrade(Group& other) {
	if ((this->food == this->tools) || (other.food == other.tools)) {
		return false;
	}
	if ((this->food > this->tools) && (other.food > other.tools)) {
		return false;
	}
	if ((this->tools > this->food) && (other.tools > other.food)) {
		return false;
	}
	return true;
}

bool Group::trade(Group& other) {
	//if (checkIsTwoGroupAreTheSame(other) == true) {
	if (this == &other) {
	throw GroupCantTradeWithItself();
	}
	if (checkConditionsForTrade(other) == false) {
		return false;
	}
	int delta_this = 0, delta_other = 0;
	//double k = 0;
	if (this->tools > this->food) { //other.food >other.tools
		//k = (this->tools - this->food) / 2.0;
		//delta_this = ceil(k);
		delta_this = ceil((this->tools - this->food) / 2.0);
		delta_other = ceil((other.food - other.tools) / 2.0);
		int trade = ceil((delta_this + delta_other) / 2.0);
		makeTheTradeThisHasMoreTools(other, trade);
	}
	else { //this->food > this->tools // other.tools > other.food
		delta_this = ceil((this->food - this->tools) / 2.0);
		delta_other = ceil((other.tools - other.food) / 2.0);
		int trade = ceil((delta_this + delta_other) / 2.0);
		makeTheTradeThisHasMoreFood(other, trade);
	}
	return true;
}


/**
* Print the data of a given group. Output form:
*      Group's name: [group's name]
*      Group's clan: [group's clan]
*      Group's children: [group's children]
*      Group's adults: [group's adults]
*      Group's tools: [group's tools]
*      Group's food: [group's food]
*      Group's morale: [group's morale]
*
* @param os the output stream
* @param group The group to print
* @return the output stream
*/
namespace mtm {
	std::ostream& operator<<(std::ostream& os, const Group& group) {
		if (group.name != "") {
			os << "Group's name: " << group.name << endl;
		}
		else {
			os << "Group's name: " << endl;
		}
		if (group.clan != "") {
			os << "Group's clan: " << group.clan << endl;
		}
		else {
			os << "Group's clan: " << endl;
		}
		os << "Group's children: " << group.children << endl;
		os << "Group's adults: " << group.adults << endl;
		os << "Group's tools: " << group.tools << endl;
		os << "Group's food: " << group.food << endl;
		os << "Group's morale: " << group.morale << endl;
		return os;
	}
}