#include "Area.h"
#include "Clan.h"

namespace mtm {
  
	class Mountain : public Area {
		GroupPointer ruller;
	public:
		//constructor
		Mountain(const std::string& name); 
		//distractor
		~Mountain();
		void groupArrive(const string& group_name, const string& clan,
			map<string, Clan>& clan_map);//override
		void groupLeave(const std::string& group_name); //ovveride
		friend bool group_pointer_compare_function_mountain(GroupPointer pointer1, GroupPointer pointer2);
	};
}
