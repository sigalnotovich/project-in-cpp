#include <iostream>
#include "../Plain.h"
#include "../River.h"
#include "testMacros.h"
#include "../Area.h"
#include "../exceptions.h"
#include "../Mountain.h"
#include "../World.h"
using namespace mtm;

std::map<std::string, Clan> makeClanMap() {
	std::map<std::string, Clan> clan_map;
	clan_map.insert(std::pair<std::string, Clan>("Beta", Clan("Beta")));
	clan_map.insert(std::pair<std::string, Clan>("Gamma", Clan("Gamma")));
	clan_map.at("Beta").addGroup(Group("Alpha1", 10, 10));
	clan_map.at("Beta").addGroup(Group("Alpha2", "", 10, 10, 40, 0, 70));
	clan_map.at("Gamma").addGroup(Group("Lambda1", 10, 10));
	clan_map.at("Gamma").addGroup(Group("Lambda2", 5, 5));
	clan_map.at("Gamma").addGroup(Group("Lambda3", 100, 100));
	return clan_map;
}

bool plainTest() {
	ASSERT_EXCEPTION(Plain(""), AreaInvalidArguments);
	AreaPtr area1(new Plain("area1"));  
	AreaPtr area2(new Plain("area2")); 
	AreaPtr area3(new Plain("area3")); 
	ASSERT_NO_EXCEPTION(area1->addReachableArea("area2"));
	ASSERT_FALSE(area2->isReachable("area1"));
	ASSERT_TRUE(area1->isReachable("area2"));
	std::map<std::string, Clan> clan_map = makeClanMap();
	ASSERT_NO_EXCEPTION(area1->groupArrive("Alpha2", "Beta", clan_map));
	ASSERT_NO_EXCEPTION(area1->groupArrive("Lambda1", "Gamma", clan_map));
	ASSERT_TRUE(area1->getGroupsNames().contains("Alpha2"));
	ASSERT_FALSE(area2->getGroupsNames().contains("Alpha2"));
	ASSERT_EXCEPTION(area1->groupLeave(""), AreaGroupNotFound);
	ASSERT_EXCEPTION(area1->groupLeave("Alpha5"), AreaGroupNotFound);
	ASSERT_EXCEPTION(area2->groupLeave("Alpha2"), AreaGroupNotFound);
	ASSERT_NO_EXCEPTION(area1->groupLeave("Alpha2"));
	ostringstream os;
	ASSERT_NO_EXCEPTION(os << clan_map.at("Gamma"));
	ASSERT_TRUE(VerifyOutput(os, "Clan's name: Gamma\n"
		"Clan's groups:\n"
		"Lambda3\n"
		"Lambda1\n"
		"Lambda2\n"));
	return true;
}

bool testMountain() {
	ASSERT_EXCEPTION(Mountain(""), AreaInvalidArguments);
	AreaPtr area1(new Mountain("area1"));
	AreaPtr area2(new Mountain("area2"));
	AreaPtr area3(new Mountain("area3"));
	ASSERT_NO_EXCEPTION(area1->addReachableArea("area2"));
	ASSERT_TRUE(area1->isReachable("area2"));
	ASSERT_FALSE(area3->isReachable("area2"));
	ASSERT_FALSE(area3->isReachable("area1"));
	std::map<std::string, Clan> clan_map = makeClanMap();
	ASSERT_NO_EXCEPTION(area1->groupArrive("Lambda1", "Gamma", clan_map));
	ASSERT_TRUE(area1->getGroupsNames().contains("Lambda1"));
	ASSERT_FALSE(area1->getGroupsNames().contains("Lambda2"));
	ASSERT_FALSE(area2->getGroupsNames().contains("Lambda2"));
	ASSERT_NO_EXCEPTION(area1->groupLeave("Lambda1"));
	ASSERT_EXCEPTION(area1->groupLeave("Lambda1"), AreaGroupNotFound);
	ASSERT_NO_EXCEPTION(area1->groupArrive("Lambda2", "Gamma", clan_map));
	ostringstream os;
	ASSERT_NO_EXCEPTION(os << clan_map.at("Gamma"));
	ASSERT_TRUE(VerifyOutput(os, "Clan's name: Gamma\n"
		"Clan's groups:\n"
		"Lambda3\n"
		"Lambda1\n"
		"Lambda2\n"));
	return true;
}

bool RiverTest() {
	ASSERT_EXCEPTION(River(""), AreaInvalidArguments);
	AreaPtr area1(new River("area1"));
	AreaPtr area2(new River("area2"));
	AreaPtr area3(new River("area3"));
	ASSERT_NO_EXCEPTION(area1->addReachableArea("area2"));
	ASSERT_TRUE(area1->isReachable("area2"));
	ASSERT_FALSE(area3->isReachable("area2"));
	ASSERT_FALSE(area3->isReachable("area1"));
	std::map<std::string, Clan> clan_map = makeClanMap();
	ASSERT_NO_EXCEPTION(area1->groupArrive("Lambda1", "Gamma", clan_map));
	ASSERT_TRUE(area1->getGroupsNames().contains("Lambda1"));
	ASSERT_FALSE(area1->getGroupsNames().contains("Lambda2"));
	ASSERT_FALSE(area2->getGroupsNames().contains("Lambda2"));
	ASSERT_NO_EXCEPTION(area1->groupLeave("Lambda1"));
	ASSERT_EXCEPTION(area1->groupLeave("Lambda1"), AreaGroupNotFound);
	ASSERT_NO_EXCEPTION(area1->groupArrive("Lambda2", "Gamma", clan_map));
	ostringstream os;
	ASSERT_NO_EXCEPTION(os << clan_map.at("Gamma"));
	ASSERT_TRUE(VerifyOutput(os, "Clan's name: Gamma\n"
		"Clan's groups:\n"
		"Lambda3\n"
		"Lambda1\n"
		"Lambda2\n"));
	return true;

	
}

int main() {
	RUN_TEST(plainTest);
	RUN_TEST(testMountain);
	RUN_TEST(RiverTest);

	return 0;
}