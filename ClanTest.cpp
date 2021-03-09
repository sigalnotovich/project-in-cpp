#include "testMacros.h"
#include "../Group.h"
#include "../Clan.h"
#include "../exceptions.h"

using namespace mtm;

bool ClanConstractorTest() {
	ASSERT_NO_EXCEPTION(Clan("Notovich"));
	ASSERT_EXCEPTION(Clan(""), ClanEmptyName);
	return true;
}

bool ClanAddGroupTest() {
	Clan Notovich("Notovich");
	Group group1("lena", "", 1, 0, 900, 900, 100);
	Group group2("lena", "ilushin", 3, 9, 55, 55, 82);
	Group group3("karin", 4, 5);
	Group group4("vadim", "ilushin",3, 9, 55, 55, 82);
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group1));
	ASSERT_EXCEPTION(Notovich.addGroup(group2), ClanGroupNameAlreadyTaken);
	ASSERT_TRUE(group2.getClan() == "ilushin");
	ASSERT_TRUE(group4.getClan() == "ilushin");
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group3));
	return true;
}

bool ClanDoesContainTest() {
		Clan Notovich("Notovich");
		Group group1("lena", "", 1, 0, 900, 900, 100);
		Group group3("karin", 4, 5);
		Group group4("vadim", "ilushin", 3, 9, 55, 55, 82);
		ASSERT_NO_EXCEPTION(Notovich.addGroup(group1));
		ASSERT_NO_EXCEPTION(Notovich.addGroup(group3));
		ASSERT_NO_EXCEPTION(Notovich.addGroup(group4));
		ASSERT_TRUE(Notovich.doesContain("lena"));
		ASSERT_TRUE(Notovich.doesContain("karin"));
		ASSERT_TRUE(Notovich.doesContain("vadim"));


	return true;
}

bool ClanGetSizetest() {
	Clan Notovich("Notovich");
	Group group1("lena", "", 1, 0, 900, 900, 100);
	Group group3("karin", 4, 5);
	Group group4("vadim", "ilushin", 3, 9, 55, 55, 82);
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group1));
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group3));
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group4));
	ASSERT_TRUE(Notovich.getSize() == 22);
	return true;
}

bool ClanIsFriendTest() {
	Clan clan1("a");
	Clan clan2("b");
	Clan clan3("b");
	Clan clan4("b");
	ASSERT_TRUE(clan1.isFriend(clan1));
	ASSERT_FALSE(clan1.isFriend(clan3));
	clan1.makeFriend(clan3);
	ASSERT_TRUE(clan1.isFriend(clan3));
	return true;
}

bool ClanPrintTest() {
	Clan Notovich("Notovich");
	Group group1("lena", "", 1, 0, 900, 900, 100);
	Group group3("karin", 4, 5);
	Group group4("vadim", "ilushin", 3, 9, 55, 55, 82);
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group1));
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group3));
	ASSERT_NO_EXCEPTION(Notovich.addGroup(group4));
	ostringstream os;
	ASSERT_NO_EXCEPTION(os << Notovich);
	ASSERT_TRUE(VerifyOutput(os, "Clan's name: Notovich\n"
		"Clan's groups:\n"
		"vadim\n"
		"lena\n"
		"karin\n"));
	return true;
}

int main() {
	RUN_TEST(ClanConstractorTest);
	RUN_TEST(ClanAddGroupTest);
	RUN_TEST(ClanDoesContainTest);
	RUN_TEST(ClanGetSizetest);
	RUN_TEST(ClanIsFriendTest);
	RUN_TEST(ClanPrintTest);
	return 0;
 }