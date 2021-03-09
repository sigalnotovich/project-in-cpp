#include "testMacros.h"
#include "../MtmSet.h"
#include "../exceptions.h"

using namespace mtm;

bool isEven(double n) {
	return (n>4);
}
bool setTest2() {
	MtmSet<string> set;
	ASSERT_NO_EXCEPTION(set.insert("had"));
	ASSERT_NO_EXCEPTION(set.insert("sig"));
	MtmSet<string>::iterator tmp = set.begin();
	MtmSet<string>::const_iterator tmp2 = set.begin();
	tmp2++;
	tmp++;
	ASSERT_TRUE(*tmp == *tmp2);
	return true;
}
bool setTest() {
	MtmSet<double> set;
	ASSERT_NO_EXCEPTION(set.insert(1.3));
	ASSERT_NO_EXCEPTION(set.insert(2.5));
	MtmSet<double> set2(set);
	ASSERT_TRUE(set.contains(1.3));
	ASSERT_FALSE(set.contains(1.1));
	ASSERT_NO_EXCEPTION(set.erase(1.3));
	ASSERT_FALSE(set.contains(1));
	ASSERT_TRUE(set.size() == 1);
	ASSERT_FALSE(set.size() == 6);
	ASSERT_FALSE(set.empty());
	MtmSet<double>::iterator tmp = set.begin(); //2.5
	ASSERT_TRUE(*(tmp++) == 2.5);
	ASSERT_TRUE(tmp == set.end());
	MtmSet<double>::const_iterator tmp2 = set.begin(); //2.5
	ASSERT_TRUE(*(tmp2++) == 2.5);
	ASSERT_TRUE(tmp2 == set.end());

	ASSERT_TRUE(set.begin() == set.find(2.5));
	ASSERT_TRUE(set2.isSuperSetOf(set));
	ASSERT_TRUE(set2 != set);
	ASSERT_TRUE(tmp == tmp2);

	ASSERT_NO_EXCEPTION(set.unite(set2));
	ASSERT_TRUE(set == set2);
	ASSERT_FALSE(set != set2);

	MtmSet<double> set3;
	MtmSet<double>::const_iterator tmp3 = set3.begin(); //2.5
	ASSERT_TRUE(tmp3 == set.end());
	ASSERT_NO_EXCEPTION(set3.insert(6));
	tmp3 = set3.begin();
	ASSERT_TRUE(tmp3 != tmp2);
	ASSERT_NO_EXCEPTION(set3.erase(6));
	ASSERT_NO_EXCEPTION(set.intersect(set3));
	ASSERT_TRUE(set.empty());
	ASSERT_NO_EXCEPTION(set2.clear());
	ASSERT_TRUE(set2.empty());
	ASSERT_NO_EXCEPTION(set.insert(7.5));
	ASSERT_NO_EXCEPTION(set.insert(6));
	ASSERT_TRUE(set.getSubSet(isEven).size() == 2);
	ASSERT_TRUE(set3.getSubSet(isEven).size() == 0);
	return true;
}

int main() {
	RUN_TEST(setTest);
	RUN_TEST(setTest2);
	return 0;
}
