#include "Area.h"
#include "Clan.h"
#include "Mountain.h"
#include <string>
#include <algorithm>

using namespace mtm;

Mountain::Mountain(const std::string& name) : Area(name) , ruller(NULL){  //? is null is okay?

}

Mountain::~Mountain() = default;



/**
* Get a group into the area.
* @param group_name The name of the group that get into the area.
* @param clan The name of the clan that the group belongs to.
* @param clan_map The map of clans that contains the clan of the group
* @throws AreaClanNotFoundInMap If there is no clan with the given
* name in the map.
* @throws AreaGroupNotInClan If there is no group with the given name
* in the clan with the given name in the map.
* @throws AreaGroupAlreadyIn If group with same name already in the
*  area.
*
* Assert that the map does contain the clan that the group belongs to.
*/
//every time that a new group arrived to the mountain it will be added to the map;
void Mountain::groupArrive(const string& group_name, const string& clan,
	map<string, Clan>& clan_map) {  //checked ->work perfect
	if (clan_map.find(clan) == clan_map.end()) {
		throw AreaClanNotFoundInMap();
	}
	if (clan_map.at(clan).doesContain(group_name) == false) {
		throw AreaGroupNotInClan();
	}
	GroupPointer pointer_to_arrived_group = clan_map.at(clan).getGroup(group_name); 
	for (std::vector<GroupPointer>::iterator m = groups.begin(); m != groups.end(); ++m) {//if a group with the same nae is allready in area
		if ((**m).getName() == group_name) {
			throw AreaGroupAlreadyIn();
		}
	}
	if (ruller == NULL) {
		//GroupPointer new_group_pointer(new Group(*pointer_to_arrived_group));
		//groups.insert(groups.begin(),new_group_pointer);
		groups.insert(groups.begin(), pointer_to_arrived_group);
		ruller = pointer_to_arrived_group;
	}
	else {
		if ((*ruller).getClan() == (*pointer_to_arrived_group).getClan()) { //if groups are from same clan:
			//GroupPointer new_group_pointer(new Group(*pointer_to_arrived_group));
			//groups.insert(groups.begin(), new_group_pointer);
			groups.insert(groups.begin(), pointer_to_arrived_group);
			if ((*pointer_to_arrived_group) > (*ruller)) {
				ruller = pointer_to_arrived_group;
			}
		}
		else { //groups are not in the same clan
			FIGHT_RESULT fight_result = (*ruller).fight(*(pointer_to_arrived_group));
			int distance = 0;
			if ((*ruller).getSize() == 0) {//delete ruller from groups
				for (std::vector<GroupPointer>::iterator b = groups.begin(); b != groups.end(); ++b) {
					if ((**b).getName() == (*ruller).getName()) {
						distance = std::distance(groups.begin(), b);
					}
				}
				groups.erase(groups.begin() + distance);
				fight_result = LOST;
			}
			if ((*pointer_to_arrived_group).getSize() != 0) { //if group empty->then it died->dont add!
				//GroupPointer new_group_pointer(new Group(*pointer_to_arrived_group));
				//groups.insert(groups.begin(), new_group_pointer);
				groups.insert(groups.begin(), pointer_to_arrived_group);
				//if draw??
				if (fight_result == LOST) {//ruller lost , new group is the ruller
					ruller = pointer_to_arrived_group;
				}
			}
			//else : ruller won and stays the ruller  (nothing to do)
		}
	}
}


/**
* Get a group out of the area.
* @param group_name The name of the leaving group.
* @throws AreaGroupNotFound If there is no group in the area with the
*  same name;
*/
//void Mountain::groupLeave(const std::string& group_name) {  //write again
//	int indicator = 0;
//	GroupPointer leaving_group;
//	for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) { //find the groupPointer of the leaving group in the groups vector
//		if ((**i).getName() == group_name) {
//			indicator = 1;
//			leaving_group = (*i);
//			break;
//		}
//	}
//	if (indicator == 0) {
//		throw AreaGroupNotFound();
//	}
//	//continue//
//	//or:if(ruller == pointer_to_arrived_group)//compare by address, need to be the same
//	std::vector<GroupPointer> groups_from_same_clan;
//	int indicator2 = 0;
//	if (ruller == leaving_group) { //the name is different for each group so if this group has the same name as the ruller they are the same group
//		for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) {
//			if ((**i).getClan() == (*ruller).getClan()) {
//				if (ruller != (*i)) {
//					groups_from_same_clan.insert(groups_from_same_clan.begin(), (*i));
//				}
//			}
//		}
//	}
//	if (groups_from_same_clan.empty() == false) { //if there is group from same clan
//		std::sort(groups_from_same_clan.begin(), groups_from_same_clan.end(), group_pointer_compare_function_mountain);
//		if (ruller != (*groups_from_same_clan.begin())) {
//			ruller = (*groups_from_same_clan.begin());
//		}
//		else {
//			ruller = (*(++groups_from_same_clan.begin()));//the next in the vector
//		}
//	}
//	else {
//		std::sort(groups.begin(), groups.end(), group_pointer_compare_function_mountain);
//		if (groups.empty() == true) {
//			ruller == NULL;
//		}
//		else if(ruller != (*groups.begin())) {
//			ruller = (*groups.begin());
//		}
//		else {
//			ruller = (*(++groups.begin()));//the next in the vector
//		}
//	}
//	//deliete the leaving group from the groups vector
//	int distance;
//	for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) {
//		if ((**i).getName() == group_name) {
//			distance = std::distance(v.begin(), i);
//			break;
//		}
//	}
//	groups.erase(groups.begin() + distance);
//}

namespace mtm {
	bool group_pointer_compare_function_mountain(GroupPointer pointer1, GroupPointer pointer2) {
		return *pointer1 > *pointer2;
	}
}

void Mountain::groupLeave(const std::string& group_name) { //checked work perfect
	int indicator = 0;
	int distance = 0;
	GroupPointer leaving_group;
	std::string clan_name;
	for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) { //find the groupPointer of the leaving group in the groups vector
		if ((**i).getName() == group_name) {
			distance = std::distance(groups.begin(), i); //fro earase
			indicator = 1; //to know i found
			clan_name = (**i).getClan(); //clan name for the continue
			break;
		}
	}
	if (indicator == 0) {
		throw AreaGroupNotFound();
	}
	groups.erase(groups.begin() + distance);
	std::vector<GroupPointer> groups_from_same_clan;
	if ((*ruller).getName() == group_name) { //the name is different for each group so if this group has the same name as the ruller they are the same group
		for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) {
			if ((**i).getClan() == clan_name) {
				groups_from_same_clan.insert(groups_from_same_clan.begin(), (*i));
			}
		}
		if (groups_from_same_clan.empty() == false) { //if there is group from same clan
			std::sort(groups_from_same_clan.begin(), groups_from_same_clan.end(), group_pointer_compare_function_mountain);
			ruller = (*groups_from_same_clan.begin());
		}
		else {
			std::sort(groups.begin(), groups.end(), group_pointer_compare_function_mountain);
			if (groups.empty() == false) {
				ruller = *(groups.begin());
			}
			else {
				ruller = NULL;
			}
		}
	}
}

