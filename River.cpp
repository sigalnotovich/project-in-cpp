#include "River.h"
#include "Area.h"
#include "Clan.h"
#include <algorithm>
#include <string>

using namespace mtm;

River::River(const std::string& name) : Area(name) {

}

River::~River() = default;


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
//void River::groupArrive2(const string& group_name, const string& clan,
//	map<string, Clan>& clan_map) {  //nedd to check // wirking ecept when arriving one more group from the same clan as group that erived before and doesContain function failed in work
//	if (clan_map.find(clan) == clan_map.end()) {
//		throw AreaClanNotFoundInMap();
//	}
//	if (clan_map.at(clan).doesContain(group_name) == false) {
//		throw AreaGroupNotInClan();
//	}
//	GroupPointer pointer_to_arrived_group = clan_map.at(clan).getGroup(group_name);
//	for (std::vector<GroupPointer>::iterator m = groups.begin(); m != groups.end(); ++m) {//if a group with the same nae is allready in area
//		if ((**m).getName() == group_name) {
//			throw AreaGroupAlreadyIn();
//		}
//	}
//	//clan_map.at(clan).;
//	Clan clan_of_arived_group = clan_map.at(clan);
//	std::vector<GroupPointer> groups_to_trade_with;
//	for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) { //get the groups to trade with to a vector 
//		//Clan clan_of_i();
//		//((**i).getClan() == (*pointer_to_arrived_group).getClan()) //rempoved couse clan is friend of inself ..was iside the if here:
//		if ((clan_of_arived_group).isFriend((clan_map.at((**i).getClan()))) ==true) {  //i clan is the same as the arrived group//the group is from friend of the arrived group caan
//			groups_to_trade_with.insert(groups_to_trade_with.begin(), (*i));
//		}
//	}
//	std::sort(groups_to_trade_with.begin(), groups_to_trade_with.end(), group_pointer_compare_function_river);
//	for (std::vector<GroupPointer>::iterator j = groups_to_trade_with.begin(); j != groups_to_trade_with.end(); ++j) {
//		if (((*pointer_to_arrived_group).trade(**j)) == true) {
//			break;
//		}
//	}
//	GroupPointer new_group_pointer(new Group(*pointer_to_arrived_group));
//	groups.insert(groups.begin(), new_group_pointer);
//	//groups.insert(groups.begin(),pointer_to_arrived_group);
//}
namespace mtm {
	bool group_pointer_compare_function_river(GroupPointer pointer1, GroupPointer pointer2) {
		return *pointer1 > *pointer2;
	}
}

void River::groupArrive(const string& group_name, const string& clan,
	map<string, Clan>& clan_map) {
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
	Clan clan_of_arived_group(clan_map.at(clan));
	//add clan and friends clans to friend_clans vector
	//MtmSet<Clan> friend_clans;
	//friend_clans.insert(clan_of_arived_group);
	std::vector<GroupPointer> friend_groups;
	string clan_name;
	//Clan clan_clan();
	//clan_clan(clan_of_arived_group);
	//clan_clan = clan_of_arived_group;
	for (std::vector<GroupPointer>::iterator m = groups.begin(); m != groups.end(); ++m) {
		clan_name = (**m).getClan();
		Clan clan_clan(clan_map.at(clan_name));
		if (clan_clan.isFriend(clan_of_arived_group) == true) {
			friend_groups.push_back(*m);
			//friend_clans.insert(clan_map.at((**m).getClan()));
		}
	}
	//iteret over the groups and insert to vector the friend group (groups of friend clans)
	std::sort(friend_groups.begin(), friend_groups.end(), group_pointer_compare_function_river);
	for (std::vector<GroupPointer>::iterator k = friend_groups.begin(); k != friend_groups.end(); ++k) {
		if ((*pointer_to_arrived_group).trade(**k) == true) {
			break;
		}
	}
	//GroupPointer new_group_pointer(new Group(*pointer_to_arrived_group));
	//groups.insert(groups.begin(), new_group_pointer);
	groups.insert(groups.begin(), pointer_to_arrived_group);
}


