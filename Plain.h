#include "Area.h"
#include "Clan.h"

namespace mtm{

	class Plain : public Area {

	public:
		//constructor
		Plain(const std::string& name);
		//distractor
		~Plain();
		void groupArrive(const string& group_name, const string& clan,
			map<string, Clan>& clan_map); //override
		friend bool group_pointer_compare_function_plain(GroupPointer pointer1, GroupPointer pointer2);
	};
}