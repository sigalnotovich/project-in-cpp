#include "Area.h"
#include "Clan.h"

namespace mtm {

	class River : public Area {

	public:
		//constructor
		River(const std::string& name);
		//distractor
		~River();
		void groupArrive(const string& group_name, const string& clan,
			map<string, Clan>& clan_map); //override
	//	void groupArrive2(const string& group_name, const string& clan,
	//		map<string, Clan>& clan_map);//for now
		friend bool group_pointer_compare_function_river(GroupPointer pointer1, GroupPointer pointer2);
		};
}