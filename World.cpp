#include "Group.h"
#include "Clan.h"
#include "Area.h"
#include "Plain.h"
#include "Mountain.h"
#include "River.h"
#include "World.h"
#include <string>
#include "MtmSet.h"
#include <assert.h>


using namespace mtm;

/**
* Empty constructor
*/
World::World() : areas_names() { //to check!(try the default constractur with brakepoints to see what it does
}


World::~World() = default;

/**
* Add a new clan to the world.
* @param new_clan The name of the new clan
* @throws WorldInvalidArgument If new_clan is empty
* @throws WorldClanNameIsTaken If there is or was a clan with the
*  given name.
*/
void World::addClan(const string& new_clan) { //lookes like work good
	if (new_clan.empty() == true) {
		throw WorldInvalidArgument();
	}
	if (clans_names.contains(new_clan) == true) {//if there is a clan with the givven name
		throw WorldClanNameIsTaken();
	}
	clans_names.insert(new_clan);
	Clan clan(new_clan);
	clan_map.insert(std::pair<string, mtm::Clan>(new_clan, clan)); //to check
}

/**
* Add a new area to the world.
* @param area_name The name of the area
* @param type The type of the area (PLAIN, MOUNTAIN, RIVER)
* @throws WorldInvalidArgument If area_name is empty
* @throws WorldAreaNameIsTaken If there is already an area with the
*  given name.
*/
void World::addArea(const string& area_name, AreaType type) { //lookes like work good
	if (area_name.empty() == true) {
		throw WorldInvalidArgument();
	}
	if (areas_names.contains(area_name) == true) {
		throw WorldAreaNameIsTaken();
	}
	areas_names.insert(area_name);
	if (type == PLAIN) {
		AreaPtr new_area_pointer(new Plain(area_name));
		areas_map.insert(std::pair<string, AreaPtr>(area_name, new_area_pointer));
		//areas_set.insert(new_area_pointer);
	}
	if (type == MOUNTAIN) {
		AreaPtr new_area_pointer(new Mountain(area_name));
		areas_map.insert(std::pair<string, AreaPtr>(area_name, new_area_pointer));
		//areas_set.insert(new_area_pointer);
	}
	if (type == RIVER) {
		AreaPtr new_area_pointer(new River(area_name));
		areas_map.insert(std::pair<string, AreaPtr>(area_name, new_area_pointer));
		//areas_set.insert(new_area_pointer);
	}
}

/**
* Add a new group to the world, with given size, clan, and starting
*  area (the group "arrives" to the area).
*  The group should have 77 morale when entering the area.
* @param group_name The name of the new group
* @param clan_name The name of the clan of the group.
* @param num_children Number of children in the group.
* @param num_adults Number of the adults in the group.
* @param area_name The name of the area the group starts in (arrives
*  to it first)
* @throws WorldInvalidArgument If group_name is empty, or at least
* one of num_children and num_adults is negative, or both are 0.
* @throws WorldGroupNameIsTaken If there is already a group with the
*  given name in the world.
* @throws WorldClanNotFound If there is no clan with the given name
*  in the world.
* @throws WorldAreaNotFound If there is no area with the given name
*  in the world.
*/
void World::addGroup(const string& group_name, const string& clan_name, int
	num_children, int num_adults, const string& area_name) { //work good i thing chacked
	//exeptions
	if ((group_name.empty() == true) || (num_children < 0) || (num_adults < 0) || (num_children == 0 && num_adults == 0)) {
		throw WorldInvalidArgument();
	}
	//if (groups_clans_names.find(group_name) != groups_clans_names.end()) {
	//	throw WorldGroupNameIsTaken();
	//}
	for (MtmSet<std::string>::const_iterator i = clans_names.begin(); i != clans_names.end(); ++i) {
		if (clan_map.at(*i).doesContain(group_name) == true) {
			throw WorldGroupNameIsTaken();
		}
	}
	if (clan_map.find(clan_name) == clan_map.end()) {
		throw WorldClanNotFound();
	}
	if (areas_map.find(area_name) == areas_map.end()) {
		throw WorldAreaNotFound();
	}

	
	//if (groups_names.contains(group_name) == true) {
	//	throw WorldGroupNameIsTaken();
	//}

	//add group to clan
	//groups_clans_names.insert(std::pair<string,string>(group_name,clan_name));
	//groups_names.insert(group_name);
	
	Group new_group(group_name, num_children, num_adults);
	clan_map.at(clan_name).addGroup(new_group); //add the new group to the clan
	//add group to area
	(*areas_map.at(area_name)).groupArrive(group_name, clan_name, clan_map);
}


/**
* Make that an area reachable from another area.
* (make 'to' reachable from 'from')
* @param from The name of the area that the other area will be
* reachable from.
* @param to The name of the area that should be reachable from the
* other area.
* @throws WorldAreaNotFound If at least one of the areas isn't in
*  the world.
*/
void World::makeReachable(const string& from, const string& to) {
	if (areas_map.find(from) == areas_map.end()) {
		throw WorldAreaNotFound();
	}
	if (areas_map.find(to) == areas_map.end()) {
		throw WorldAreaNotFound();
	}
		//exeptions
	AreaPtr area_from = areas_map.at(from);
	//AreaPtr area_to = areas_map.at(to);
	(*area_from).addReachableArea(to);
	//(*area_to).addReachableArea(from);
}

/**
* Move a group to destination area.
* @param group_name The name of the group that should move
* @param destination The name of the area the group should move to.
* @throws WorldGroupNotFound If there is no group with the given
*  name in the world.
* @throws WorldAreaNotFound If there is no area with the given name
*  in the world.
* @throws WorldGroupAlreadyInArea If the group is already in the
*  destination area.
* @throws WorldAreaNotReachable If the destination area isn't
*  reachable from the area the group is currently in.
*/
void World::moveGroup(const string& group_name, const string& destination) {
	int indicator = 0;
	std::string clan_name;
	for (MtmSet<std::string>::const_iterator i = clans_names.begin(); i != clans_names.end(); ++i) {
		if (clan_map.at(*i).doesContain(group_name) == true) {
			GroupPointer p = clan_map.at(*i).getGroup(group_name);
			if ((*p).getSize() != 0) {
				indicator = indicator + 1;
				clan_name = *i;
			}
			break;
		}
	}
	if (indicator == 0) {
		throw WorldGroupNotFound();
	}
	/*if (groups_names.contains(group_name) == false) {
		throw WorldGroupNotFound();
	}*/
	if (areas_names.contains(destination) == false) {
		throw WorldAreaNotFound();
	}
	AreaPtr area_pointer1 = areas_map.at(destination);
	MtmSet<std::string> groups_names2 = (*area_pointer1).getGroupsNames();
	if (groups_names2.contains(group_name) == true) {
		throw WorldGroupAlreadyInArea();
	}
	AreaPtr area_pointer = NULL;
	for (MtmSet<std::string>::const_iterator i = areas_names.begin(); i != areas_names.end(); ++i) {
		area_pointer = areas_map.at(*i);
		if (((*area_pointer).getGroupsNames()).contains(group_name) == true) { //find the area of the 2group
			if ((*area_pointer).isReachable(destination) == false) {//check if reachable
				throw WorldAreaNotReachable();
			}
			else {
				break;//is reachable - one grope in the world with this name - no need to check anymore
			}
		}
	}
	assert(area_pointer != NULL);
	//string clan_name = groups_clans_names.at(group_name);
	//remove group from current area
	(*area_pointer).groupLeave(group_name);
	//move group to new area
	(*areas_map.at(destination)).groupArrive(group_name, clan_name, clan_map);
}

/**
* Make to clans friends.
* @param clan1 The name of one of the clans to become friends.
* @param clan2 The name of the other clan to become friends with.
* @throws WorldClanNotFound If at least one of the clans isn't in
* the world.
*/
void World::makeFriends(const string& clan1, const string& clan2) {
	if (clan_map.find(clan1) == clan_map.end()) {
		throw WorldClanNotFound();
	}
	if (clan_map.find(clan2) == clan_map.end()) {
		throw WorldClanNotFound();
	}
	clan_map.at(clan1).makeFriend(clan_map.at(clan2));
}


/**
* Unite to clans to a new clan with a new name.
* @param clan1 The name of one of the clan that need to unite.
* @param clan2 The name of the second clan that need to unite.
* @param new_name The name of the new clan.
* @throws WorldInvalidArgument If new_name is empty.
* @throws WorldClanNameIsTaken If new_name was already used for a
* clan that is not clan1 or clan2.
* @throws WorldClanNotFound If clan1 or clan2 are not in the world.
*/
void World::uniteClans(const string& clan1, const string& clan2, const
	string& new_name) {
	if (new_name.empty() == true) {
		throw WorldInvalidArgument();
	}
	if ((new_name != clan1) && (new_name != clan2)) {
		if (clans_names.contains(new_name)==true) {
			throw WorldClanNameIsTaken();
		}
	}
	if (clan_map.find(clan1) == clan_map.end()) {
		throw WorldClanNotFound();
	}
	if (clan_map.find(clan2) == clan_map.end()) {
		throw WorldClanNotFound();
	}
	//unite clans 
	Clan new_clan = clan_map.at(clan1).unite(clan_map.at(clan2), new_name);
	//erase clan1 and clan2 from dictionary couse key is not correct
	clan_map.erase(clan1);
	clan_map.erase(clan2);  //check that clan1 changed and clan 2 erased!!
	//insert the new clan to the map
	clan_map.insert(std::pair<string, mtm::Clan>(new_name, new_clan));
}


/**
* Print a group to the ostream, using the group output function (<<).
* Add to it another line (after the last one of a regular print) of
* the form:
*      Group's current area: [area name]
* That print the area which the group is in.
* @param os The ostream to print into.
* @param group_name The name of the group to print.
* @throws WorldGroupNotFound If there is no group in the world with
*  the given name.
*/
void World::printGroup(std::ostream& os, const string& group_name) const {
	int indicator = 0;
	std::string clan_name;
	for (MtmSet<std::string>::const_iterator i = clans_names.begin(); i != clans_names.end(); ++i) {
		if (clan_map.at(*i).doesContain(group_name) == true) {
			indicator = indicator + 1;
			clan_name = *i;
			break;
		}
	}
	if (indicator == 0) {
		throw WorldGroupNotFound();
	}
	//string clan_name = groups_clans_names.at(group_name);
	Clan clan1 = clan_map.at(clan_name);
	os << (*clan1.getGroup(group_name));
		//operator<<(os, clan_map.at(clan_name).getGroup(group_name));
		AreaPtr area_pointer = NULL;
	for (MtmSet<std::string>::const_iterator i = areas_names.begin(); i != areas_names.end(); ++i) {
		area_pointer = areas_map.at(*i);
		if (((*area_pointer).getGroupsNames()).contains(group_name) == true) {
			os << "Group's current area: " << (*i) << std::endl;
			break;
		}
	}
}

/**
* Print a clan to the ostream, using the clan output function.
* @param os The ostream to print into.
* @param clan_name The name of the clan to print.
* @throws WorldClanNotFound If there is no clan with the given name
*  in the world.
*/
void World::printClan(std::ostream& os, const string& clan_name) const {
	if (clan_map.find(clan_name) == clan_map.end()) {
		throw WorldClanNotFound();
	}
	os << clan_map.at(clan_name);
}