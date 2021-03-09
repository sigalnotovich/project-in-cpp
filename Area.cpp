#include "Area.h"
#include <string>
#include <vector>
#include "MtmSet.h"

using namespace mtm;

/**
* Constructor
* @param name The name of the area
* @throws AreaInvalidArguments If the name is empty
*/
 Area::Area(const std::string& name){ //: area_name(name) ,groups(), reachable_areas_set(){
	 if (name.empty() == true) {
		 throw AreaInvalidArguments();
	 }
	 this->area_name = name;
	 this->groups = std::vector<GroupPointer>();
	 this->reachable_areas_set = MtmSet<std::string>();
	 /*if (name == "") {
		 area_name.~basic_string();/
		 groups.~vector();
		 reachable_areas_set.~MtmSet();
		 throw AreaInvalidArguments();
	 }*/
}

 Area::~Area() = default;

 /**
 * Add an area, that can be reachable from this area.
 * Doesn't mean that this area is reachable from the area with the
 * given name.
 * @param area_name The name of the area that can be reachable from
 *  this are.
 */
 void Area::addReachableArea(const std::string& area_name) {
	 this->reachable_areas_set.insert(area_name);
 }

 /**
 * Check if an area is reachable from this area.
 * An area is always reachable from itself.
 * @param area_name The name of the area to check if it's reachable.
 * @return True if the area with the given name is reachable from
 * this area, and false otherwise.
 */
 bool Area::isReachable(const std::string& area_name) const {
	 if (this->area_name == area_name) {
		 return true;
	 }
	 if (this->reachable_areas_set.contains(area_name) == true) {
		 return true;
	 }
	 return false;
 }

 ///**
 //* Get a group into the area.
 //* @param group_name The name of the group that get into the area.
 //* @param clan The name of the clan that the group belongs to.
 //* @param clan_map The map of clans that contains the clan of the group
 //* @throws AreaClanNotFoundInMap If there is no clan with the given
 //* name in the map.
 //* @throws AreaGroupNotInClan If there is no group with the given name
 //* in the clan with the given name in the map.
 //* @throws AreaGroupAlreadyIn If group with same name already in the
 //*  area.
 //*
 //* Assert that the map does contain the clan that the group belongs to.
 //*/
 //virtual
 void Area::groupArrive(const string& group_name, const string& clan,
	 map<string, Clan>& clan_map) {

 }
 
 //virtual
 void Area::groupLeave(const std::string& group_name) {
	 int distance = 0;
	 int indeicator = 0;
	 for (std::vector<GroupPointer>::iterator i = groups.begin(); i != groups.end(); ++i) {
		 if ((**i).getName() == group_name) {
			 indeicator = 1;
			 distance = std::distance(groups.begin(), i);
			 break;
		 }
	 }
	 if (indeicator == 0) {
		 throw AreaGroupNotFound();
	 }
	 groups.erase(groups.begin() + distance);
 }




  /*std::string Area::getName() {
	  return this->area_name;
  }
  std::vector<GroupPointer>& Area::getGroupsInArea() {
	  return this->groups_in_the_area;
  }

  MtmSet<std::string>& Area::getReachableAreasSet() {
	  return this->reachable_areas_set;
  }*/
 /* MtmSet<std::string> Area::getGroupsNames() const {


  }*/


  /**
  * Get a set of the names of all the groups in the area.
  * @return A set that contains the names of all the groups in the area.
  */
  MtmSet<std::string> Area::getGroupsNames() const {
	  MtmSet<std::string> new_set;
	  std::string name;
	  for (std::vector<GroupPointer>::const_iterator i = groups.begin(); i != groups.end(); ++i){
		  name = (**i).getName();
		  new_set.insert(name);
	  }
	  return new_set;
  }