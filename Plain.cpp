#include "Plain.h"
#include "Area.h"
#include "Clan.h"
#include <algorithm>
#include <string>

using namespace mtm;

Plain::Plain(const std::string& name) : Area(name) {

}

Plain::~Plain() = default;


namespace mtm {
	bool group_pointer_compare_function_plain(GroupPointer pointer1, GroupPointer pointer2) {
		return *pointer1 > *pointer2;
	}
}

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
void Plain::groupArrive(const string& group_name, const string& clan,
	map<string, Clan>& clan_map) { //override   //to check!!
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
	std::sort(groups.begin(), groups.end(), group_pointer_compare_function_plain);//sorting .result:the most pawerful group first, the less powerful group in the end
	//אם יש בקבוצה פחות משליש מכמות האנשים בשבט, היא מתאחדת עם
		//הקבוצה החזקה ביותר באזור )לפי אופרטורי ההשוואה(, השייכת לאותו
	//	השבט, וביחד אין להן יותר משליש מכמות האנשים בשבט, אם יש כזאת.
	int clan_size = clan_map.at(clan).getSize();
	int group_size = (*pointer_to_arrived_group).getSize();
	int indicator = 0;
	int curent_group_size = -1;
	if (group_size < (clan_size / 3)) {
		for (std::vector<GroupPointer>::iterator it = groups.begin(); it != groups.end(); ++it) { //run over the sorted groups
			curent_group_size = (**it).getSize();
			if ((group_size + curent_group_size) < (clan_size / 3)) { //check condition
				bool is_unite;
				is_unite = ((**it).unite(*pointer_to_arrived_group, clan_size / 3));
				if (is_unite == true) { //unite
					indicator = 1; //if unite success
					break;
				}
			}
		}
		if (indicator == 0) { //if not united with any group add to arrea
			//GroupPointer new_group_pointer1(new Group(*pointer_to_arrived_group));
			//groups.insert(groups.begin(), new_group_pointer1);
			groups.insert(groups.begin(), pointer_to_arrived_group);
		}
	}
	/*אם יש בקבוצה יותר משליש מכמות האנשים בשבט, ולפחות 10 אנשים,
		הקבוצה מתפצלת, כאשר שם הקבוצה החדשה נקבע ע"י הוספת "_" לשם
		הקבוצה ומיד לאחריו המספר הקטן ביותר שגדול שווה ל2, שאין חבורה
		בשם זה באף אחד מהשבטים ממילון השבטים שהתקבל כפרמטר.יש
		להוסיף את שתי הקבוצות לאזור*/
	else if ((group_size > (clan_size / 3)) && (group_size >= 10)) {
		std::string new_name;
		std::string arrived_group_name = (*pointer_to_arrived_group).getName();
		int counter = 0;
		int l = 2;
		bool k = false;
		while (k == false) {
			counter = 0;
			new_name = arrived_group_name + "_" + std::to_string(l);
			for (map<string, Clan>::iterator i = clan_map.begin(); i != clan_map.end(); i++) {
				if (clan_map.at(i->first).doesContain(new_name) == true) { //if there 
					counter++;
					//k = true;
				}
			}
			if (counter == 0) {
				k = true;
			}
			l++; //increase the name index
		}
		Group new_group = (*pointer_to_arrived_group).divide(new_name);
		clan_map.at(clan).addGroup(new_group); //new 26.1 26.1
		groups.insert(groups.begin(), pointer_to_arrived_group); //insert arived group after dividing
		GroupPointer new_group_pointer(new Group(new_group));
		groups.insert(groups.begin(), new_group_pointer);
		
	}
	else {
		//if no one of cndition is true
		//GroupPointer new_group_pointer2(new Group(*pointer_to_arrived_group));
		//groups.insert(groups.begin(), new_group_pointer2);
		groups.insert(groups.begin(), pointer_to_arrived_group);
	}
}



//void Plain::groupLeave(const std::string& group_name) {
//	int distance = 0;
//	for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) {
//		if ((**i).getName() == group_name) {
//			distance = std::distance(groups.begin(), i);
//			break;
//		}
//	}
//	groups.erase(groups.begin() + distance);
//}