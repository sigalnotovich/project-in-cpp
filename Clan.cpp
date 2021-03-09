#include <unordered_map>
#include "exceptions.h"
#include "Clan.h"
#include "MtmSet.h"
#include <string>
#include <algorithm>

using std::endl;

using namespace mtm;

//if (name.empty()) {
//	throw ClanEmptyName();
//}
//this->name = name;
//this->members = MtmSet<GroupPointer>();
//this->friends = std::list<Clan>();
Clan::Clan(const std::string& name) : clan_name(name), groups_set(), friends_set() {
	if (name .empty()==true) {
		throw ClanEmptyName();
	}
	this->clan_name = name;
	this->groups_set = MtmSet<GroupPointer>();
	this->friends_set = MtmSet<std::string>();
}
//if (name.empty()) {
//	throw ClanEmptyName();
//}
//this->name = name;
//this->members = MtmSet<GroupPointer>();
//this->friends = std::list<Clan>();

/**
* Copy constructor.
*/
Clan::Clan(const Clan& other) : clan_name(other.clan_name), groups_set(other.groups_set), friends_set(other.friends_set) {
	//clan_name = other.clan_name;
	//groups_set.~MtmSet();  //destroy this.group set;
	//groups_set = other.groups_set; //copy ctor
	////friends_set.~MtmSet();   changed when change get friend
	//friends_set = other.friends_set;
}

Clan::~Clan() = default;

/**
* Add a group (copy of it) to the clan
* @param group The group to add to the clan
* @throws ClanGroupIsEmpty if the group has no people (empty)
* @throws ClanGroupNameAlreadyTaken if there is already a group
* with the same name in the clan.
*/
void Clan::addGroup(const Group& group) {  //not shure about it
	if (group.getSize() == 0) {
		throw ClanGroupIsEmpty();
	}
	if (doesContain(group.getName()) == true) {
		throw ClanGroupNameAlreadyTaken();
	}
	Group new_group = group; // copy group to new_group
	new_group.changeClan(std::string(this->clan_name)); //change clan of new_group
	GroupPointer new_group_pointer(new Group(new_group)); //shared pointer to a copy of new_group
	groups_set.insert(new_group_pointer); //insert the group to the set
}

/**
* Get a group from the clan, with a given name
* @param group_name The name of the group the return
* @return A reference to the group with the given name
* @throws ClanGroupNotFound if there is no group in the clan with the
* given name.
*/
const GroupPointer& Clan::getGroup(const std::string& group_name) const {
	for (MtmSet<GroupPointer>::const_iterator i = this->groups_set.begin(); i != groups_set.end(); ++i) {
		if ((**i).getName() == group_name) {
			return *i;
		};
	}
	throw  ClanGroupNotFound();
}

//check if there is a group with the param group_name in the set
//if yes return true, otherwise return false
bool Clan::doesContain(const std::string& group_name) const {
	for (MtmSet<GroupPointer>::const_iterator i = this->groups_set.begin(); i != groups_set.end(); ++i) {
		if ((**i).getName() == group_name) {
			return true;
		};
	}
	return false;
}


/**
* The function returns the amount of people in the clan.
* A person belongs to the clan, if he belongs to a group, that
* belongs to the clan.
* @return The amount of people in the clan.
*/
int Clan::getSize() const {
	int amount_of_peaple = 0;
	for (MtmSet<GroupPointer>::const_iterator i = this->groups_set.begin(); i != groups_set.end(); ++i) {
		amount_of_peaple = amount_of_peaple + (**i).getSize();
	}
	return amount_of_peaple;
}


/**
* Make two clans unite, to form a new clan, with a new name.


*All the groups of each clan will change their clan.

* The friends of the new clan are all the friends of either one of
* the old 2 clans.

* The new clan will replace this clan, and the other clan (received
* by an argument) will become empty (i.e no groups).
*
* If One of the exception is thrown, both clan shouldn't change.
* @param other The clan to unite with
* @param new_name The name of the new clan. If the name is of one of
*  the uniting clans (assume to clan A), that means the other clan,
*  joined clan A, and the groups of the clan A, don't change their
*  clan.
* @return A reference to the new clan (this).
* @throws ClanEmptyName new_name is empty.
* @throws ClanCantUnite If other is the same clan as this or if
*  there is a group in one of the clans, that has the same name as a
*  group in the other clan.
*/
Clan& Clan::unite(Clan& other, const std::string& new_name) {
	if (new_name.empty() == true) {
		throw ClanEmptyName();
	}
	//is caln the same
	if (this->isClanAreTheSame(other) == true) {
		throw ClanCantUnite();
	}
	if (this->isThereIsGroupsWithTheSameNameInBothClans(other) == true) {
		throw ClanCantUnite();
	}
	//every thing is okay - make union
	//change clane name for all groups
	for (MtmSet<GroupPointer>::const_iterator i = groups_set.begin(); i != groups_set.end(); ++i) {
		(**i).changeClan(new_name);
	}
	for (MtmSet<GroupPointer>::const_iterator j = other.groups_set.begin(); j != other.groups_set.end(); ++j) {
		(**j).changeClan(new_name);
	}
	//unite clans friends
	friends_set.unite(other.friends_set);
	groups_set.unite(other.groups_set);
	clan_name = new_name;
	other.friends_set.clear();
	other.groups_set.clear();
	other.clan_name = "";
	return *this;
}

bool Clan::isClanAreTheSame(Clan& other) {
	if ((this->clan_name == other.clan_name) && (this->friends_set == other.friends_set)
		&& (this->groups_set == other.groups_set)) {
		return true;
	}
	return false;
}

bool Clan::isThereIsGroupsWithTheSameNameInBothClans(Clan& other) {
	std::string this_name = "";
	std::string other_name = "";
	for (MtmSet<GroupPointer>::const_iterator i = groups_set.begin(); i != groups_set.end(); ++i) {
		this_name = (**i).getName();
		for (MtmSet<GroupPointer>::const_iterator j = other.groups_set.begin(); j != other.groups_set.end(); ++j) {
			other_name = (**j).getName();
			if (other_name == this_name) {
				return true;
			}
		}
	}
	return false;

	//MtmSet<GroupPointer> new_set = this->groups_set.intersect(other.groups_set);
	//if (new_set.empty() == true) {
	//	return false;   //intersect is empty wich mean that the groups in the clans are different
	//}
	//return true;
}


/**
* Make this clan, and a given clan, friends. If the two clans already
* were friends, does nothing.
* Assume that every clan has a unique name. (In copied clans, you
* can assume one of the copies will not be used again).
* @param other The clan to become a friend with.
*/
void Clan::makeFriend(Clan& other) { //done write
	if (isFriend(other) == true) {
		return;
	}
	friends_set.insert(other.clan_name);
	other.friends_set.insert(this->clan_name);
}

/**
* Check if a given clan is a friend of this clan.
* Every clan is a friend of itself.
* @param other The clan to check if is a friend.
* @return true, if the given clan is a friend of this clan, false
*  otherwise.
*/
bool Clan::isFriend(const Clan& other) const { //done writing
	if (this->clan_name == other.clan_name) {
		return true;
	}
	for (MtmSet<std::string>::const_iterator i = friends_set.begin(); i != friends_set.end(); ++i) {
		if ((*i) == other.clan_name) {
			return true;
		};
	}
	return false;
}

/**
* Print The clan name, and it groups, sorted by groups comparison
* operators, from strongest to weakest. In the next Format:
*
* Clan's name: [name]
*     [1'st group name]
*     [2'nd group name]
*     [3'rd group name]
*             *
*             *
*             *
*
* @param os The output stream
* @param clan The clan to print
* @return A reference to the output stream
*/


namespace mtm {
	bool group_pointer_compare_function_clan(GroupPointer pointer1, GroupPointer pointer2) {
		return *pointer1 > *pointer2;
	}

	std::ostream& operator<<(std::ostream& os, const Clan& clan) {
		os << "Clan's name: " << clan.clan_name << endl;
		os << "Clan's groups:" << endl;

		std::vector<GroupPointer> clan_vector;
		for (MtmSet<GroupPointer>::const_iterator i = clan.groups_set.begin(); i != clan.groups_set.end(); ++i) {
			clan_vector.push_back(*i);
		}
		std::sort(clan_vector.begin(), clan_vector.end(), group_pointer_compare_function_clan);
		//
		for (std::vector<GroupPointer>::const_iterator i = clan_vector.begin(); i != clan_vector.end(); ++i) {
			if (!(((**i).getClan() == "") && ((**i).getName() == "") && ((**i).getSize() == 0))) { //if group not empty print  //is it enought to check to know that group is empty?
				os << (**i).getName() << endl;
			}
		}
		return os;
	}
}

//std::ostream& Clan::returnSetOrganaizedByPowerFromStrongerToWeakest(std::ostream& os) {
//	std::vector<GroupPointer> clan_vector;
//	for (MtmSet<GroupPointer>::iterator i = groups_set.begin(); i != groups_set.end(); ++i) {
//		clan_vector.push_back(*i);
//	}
//	std::sort(clan_vector.begin(), clan_vector.end(), group_pointer_compare_function_clan);
//	//
//	for (std::vector<GroupPointer>::iterator i = clan_vector.begin(); i != clan_vector.end(); ++i) {
//		os << (**i).getName();
//	}
//
//}


//Clan& Clan::returnSetOrganaizedByPowerFromStrongerToWeakest() {
//	MtmSet<GroupPointer> copy_of_group_set(groups_set);
//	MtmSet<GroupPointer> empty_set;
//	MtmSet<GroupPointer>::iterator j = copy_of_group_set.begin();
//	while (copy_of_group_set.empty() == false) {
//		MtmSet<GroupPointer>::iterator n = copy_of_group_set.begin();
//		j = n;
//		for (MtmSet<GroupPointer>::iterator i = copy_of_group_set.begin(); i != copy_of_group_set.end(); ++i) {
//			if ((**j) > (**i)) { //insert the biggest first so after him you can push the 
//								 //smallest : push 4 ,push3 ,push 2 ,push 1 , outcome: 1,2,3,4
//				j = i;
//			}
//		}
//		empty_set.insert(*j);
//		copy_of_group_set.erase(*j);
//	}
//	this->groups_set.clear();
//	groups_set.unite(empty_set);
//	return *this;
//	/*MtmSet<std::string>::const_iterator j = this->friends_set.begin();
//	for (i = j+1; i != friends_set.end(); ++i) {
//	if
//	}*/
//	
//}