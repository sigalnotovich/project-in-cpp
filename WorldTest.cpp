#include <iostream>
#include "testMacros.h"
#include "../exceptions.h"
#include "../World.h"
using namespace mtm;

bool WorldAddClanTest() {
	World world;
	ASSERT_EXCEPTION(world.addClan(""), WorldInvalidArgument);
	ASSERT_NO_EXCEPTION(world.addClan("clan1"));
	ASSERT_EXCEPTION(world.addClan("clan1"), WorldClanNameIsTaken);
	ASSERT_NO_EXCEPTION(world.addClan("clan2"));
	ASSERT_EXCEPTION(world.addClan("clan2"), WorldClanNameIsTaken);
	return true;
}

bool WorldAddAreaTest() {
	World world;
	ASSERT_EXCEPTION(world.addArea("", RIVER), WorldInvalidArgument);
	ASSERT_NO_EXCEPTION(world.addArea("area1", MOUNTAIN));
	ASSERT_EXCEPTION(world.addArea("area1", PLAIN), WorldAreaNameIsTaken);
	ASSERT_EXCEPTION(world.addArea("area1", RIVER), WorldAreaNameIsTaken);
	ASSERT_NO_EXCEPTION(world.addArea("area2", RIVER));
	ASSERT_NO_EXCEPTION(world.addArea("area3", PLAIN));
	return true;
}

bool WorldMakeReachableTest() {
	World world;
	world.addArea("area1", PLAIN);
	world.addArea("area2", PLAIN);
	world.addArea("area3", MOUNTAIN);
	world.addArea("arae4", RIVER);
	world.addArea("area5", MOUNTAIN);
	ASSERT_NO_EXCEPTION(world.makeReachable("area1", "area2"));
	ASSERT_NO_EXCEPTION(world.makeReachable("area1", "area3"));
	ASSERT_NO_EXCEPTION(world.makeReachable("area2", "area3"));
	ASSERT_EXCEPTION(world.makeReachable("", ""), WorldAreaNotFound);
	ASSERT_EXCEPTION(world.makeReachable("area1", ""), WorldAreaNotFound);
	ASSERT_EXCEPTION(world.makeReachable("", "area1"), WorldAreaNotFound);
	return true;
}

bool WorldMoveGroupTest() {
	World world;
	world.addClan("clan1");
	world.addClan("clan2");
	world.addArea("area1", PLAIN);
	world.addArea("area2", PLAIN);
	world.addArea("area3", MOUNTAIN);
	world.addArea("arae4", RIVER);
	world.addArea("area5", MOUNTAIN);
	ASSERT_EXCEPTION(world.moveGroup("", ""), WorldGroupNotFound);
	ASSERT_EXCEPTION(world.moveGroup("", "area1"), WorldGroupNotFound);
	ASSERT_EXCEPTION(world.moveGroup("area1", ""), WorldGroupNotFound);
	ASSERT_NO_EXCEPTION(world.makeReachable("area1", "area2"));
	ASSERT_NO_EXCEPTION(world.makeReachable("area1", "area3"));
	ASSERT_NO_EXCEPTION(world.makeReachable("area2", "area3"));
	world.addGroup("group1", "clan1", 60, 12, "area1");
	world.addGroup("group2", "clan2", 17, 8, "area2");
	ASSERT_NO_EXCEPTION(world.moveGroup("group1", "area2"));
	ASSERT_EXCEPTION(world.moveGroup("group1", "area2"), WorldGroupAlreadyInArea);	
	return true;
}

bool WorldMakeFriendsTest() {
	World world;
	world.addClan("clan1");
	world.addClan("clan2");
	world.addClan("clan3");
	ASSERT_EXCEPTION(world.makeFriends("", ""), WorldClanNotFound);
	ASSERT_EXCEPTION(world.makeFriends("", "clan1"), WorldClanNotFound);
	ASSERT_EXCEPTION(world.makeFriends("clan1", ""), WorldClanNotFound);
	ASSERT_NO_EXCEPTION(world.makeFriends("clan1", "clan1"));
	ASSERT_NO_EXCEPTION(world.makeFriends("clan1", "clan2"));
	ASSERT_NO_EXCEPTION(world.makeFriends("clan2", "clan3"));
	return true;
}


int main() {
	RUN_TEST(WorldAddClanTest);
	RUN_TEST(WorldAddAreaTest);
	RUN_TEST(WorldMakeReachableTest);
	RUN_TEST(WorldMoveGroupTest);
	RUN_TEST(WorldMakeFriendsTest);
	return 0;
}