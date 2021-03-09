#ifndef MTM4_SET_H
#define MTM4_SET_H

#include <stddef.h>
#include "exceptions.h"

namespace mtm {

	/**
	* A set
	* @tparam Type The type of an element on the group.
	*      Required to implement:
	*                             - operator ==
	*                             - copy constructor
	*/
	template<typename Type>
	class MtmSet {

		/**
		* A node in the set
		*/

		class Node {

			Type data;
			Node* next;

		public:
			friend MtmSet;
			Node(Type new_data) {
				data = new_data;
				next = NULL;
			}

			~Node() {}
		};

		int set_size;
		//Type* p_data;
		Node* first;


	public:

		//Forward declaration
		class const_iterator;

		/**
		* A iterator for Set
		*/
		class iterator {
			Node* node;

		public:
			/**
			* Empty constructor. Should not be dereferenced.
			* Same as MtmSet::end()
			*/
			iterator() {
				node = NULL;
			}

			/**
			* Constructor of Set iterator
			* @param node The node the iterator points to
			*/
			explicit iterator(Node *p_node) {
				node = p_node;
			}

			/**
			* Copy constructor
			* @param it The iterator to copy
			*/
			iterator(const iterator& it) {
				this->node = it.node;   //fixed: node = it.node
			}

			/**
			* Destructor
			*/
			~iterator() {
				if (node == NULL) {
					delete node;
				}
			}

			/**
			* Copy assignment operator.
			* @param rhs The iterator to copy.
			* @return A reference to this iterator.
			*/
			iterator& operator=(const iterator& rhs) {
				node = rhs.node;
				return *this;
			}

			/**
			* Dereference operator * .
			* Used like dereference of a pointer with * .
			* @return A reference of the data in the node the iterator
			*  points to.
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			const Type& operator*() const {
				if (node == NULL) {
					throw NodeIsEndException();
				}
				const Type *tmp = &node->data;
				return *tmp;
			}

			/**
			* Dereference operator -> .
			* Used like dereference of a pointer with -> .
			* @return A pointer to the data in the node the iterator
			*  points to.
			* C++ use the -> operator on the returned pointer,
			* this allows the user to treat the iterator like a pointer.
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			const Type *operator->() const {
				return &(node->data);
			}

			/**
			* Prefix increment operator (++i)
			* @return a reference to the iterator;
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			iterator& operator++() {
				if (node == NULL) {
					throw NodeIsEndException();
				}
				node = node->next;
				return *this; //fixed
			}

			/**
			* Postfix increment operator (i++)
			* @return iterator that points to the same node as this before
			* the increment
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			iterator operator++(int) {
				if (node == NULL) {
					throw NodeIsEndException();
				}
				iterator tmp(node);
				node = node->next;
				return tmp;
			}

			/**
			* Compare an iterator with const_iterator. (when there is a
			*  regular iterator on the left.
			* @param rhs the right const_iterator.
			* @return true if the two iterators point to the same node
			*/
			bool operator==(const const_iterator& rhs) const {
				//need to think about the option that thay are Null==and
				if (node == NULL && rhs.node == NULL) {
					return true;
				}
				Type p = *(rhs);

				Type f = node->data;
				return  (f == p);
			}

			/**
			* Compare an iterator with const_iterator. (when there is a
			*  regular iterator on the left.
			* @param rhs the right const_iterator.
			* @return true if the two iterators don't point to the same node
			*/
			bool operator!=(const const_iterator& rhs) const {
				return !(node == rhs.node); //fixed: return !(this == rhs);? //fixed2: return !(*this = rhs)
			}

			friend class const_iterator;
		};

		/**
		* A const_iterator for Set
		*/
		class const_iterator {
			const Node*  node;
			friend class iterator;
		public:
			/**
			* Empty constructor. Should not be dereferenced.
			* Same as MtmSet::end()
			*/
			const_iterator() {
				node = NULL;
			}

			/**
			* Constructor of Set const_iterator
			* @param node The node the const_iterator points to
			*/
			explicit const_iterator(Node *node) {
				this->node = node;  //fix: // this->node = node ?
			}

			/**
			* Copy constructor
			* @param it The const_iterator to copy
			*/
			const_iterator(const const_iterator& it) {
				this->node = it.node;
			}

			/**
			* Constructor from iterator (not const_iterator)
			* Allows casting from iterator to const_iterator
			* @param it The iterator to "copy" to a const_iterator
			*/
			const_iterator(const iterator& it) {
				const Node* tmp = it.node;
				node = tmp;

			}

			/**
			* Destructor
			*/
			~const_iterator() {}

			/**
			* Copy assignment operator.
			* @param rhs The iterator to copy.
			* @return A reference to this const_iterator.
			*/

			const_iterator& operator=(const const_iterator& rhs) {
				node = rhs.node;  //fixed 26.1 14:00
				return *this; //fixed 26.1 14:00
			}

			/**
			* Dereference operator * .
			* Used like dereference of a pointer with * .
			* @return A reference of the data in the node the const_iterator
			*  points to.
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			const Type& operator*() const {
				if (node == NULL) {
					throw NodeIsEndException();
				}
				const Type *tmp = &node->data;
				return *tmp;
			}

			/**
			* Dereference operator -> .
			* Used like dereference of a pointer with -> .
			* @return A pointer to the data in the node the const_iterator
			*  points to.
			*  C++ use the -> operator on the returned pointer,
			*  this allows the user to treat the const_iterator like a pointer.
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			const Type *operator->() const {
				return &node->data;
			}

			/**
			* Prefix increment operator (++i)
			* @return a reference to the iterator;
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			const_iterator& operator++() {
				if (node == NULL) {
					throw NodeIsEndException();
				}
				node = node->next;
				return *this;
			}

			/**
			* Postfix increment operator (i++)
			* @return const_iterator that points to the same node as this
			* before the increment
			* @throws NodeIsEndException if the iterator doesn't point to
			* an element in the set (end())
			*/
			const_iterator operator++(int) {
				if (node == NULL) {
					throw NodeIsEndException();
				}
				const_iterator tmp(*this); //fixed 26.1 14:00
				node = node->next;
				return tmp;
			}

			/**
			* Compare two const_iterators.
			* @param rhs the right const_iterator
			* @return true if the two const_iterators point to the same node
			*/
			bool operator==(const const_iterator& rhs) const {
				if (node == NULL && rhs.node == NULL) {
					return true;
				}
				return (rhs.node == node);               //fixed 26.1 14:00                      ???????????????????????????????????
			}

			/**
			* Compare two const_iterators.
			* @param rhs the right const_iterator
			* @return true if the two const_iterators don't point to the same
			* node
			*/
			bool operator!=(const const_iterator& rhs) const {
				if (node == NULL && rhs.node == NULL) {
					return false;
				}
				if (node != NULL && rhs.node == NULL) { //fixed:added
					return true;
				}
				if (node == NULL && rhs.node != NULL) {//fixed: added 
					return true;
				}
				return !(rhs.node->data == node->data);
			}
		};

		/**
		* Empty constructor
		* Creates an empty set
		*/
		MtmSet() {
			set_size = 0;
		}

		/**
		* Copy constructor
		* @param set the Set to copy
		*/
		MtmSet(const MtmSet& set) {
			set_size = 0;
			Node* tmp = set.first;
			for (int i = 0; i < set.set_size; i++) {
				insert(tmp->data);       //???????????????????
				tmp = tmp->next;
			}
		}

		/**
		* Destructor
		* Free all allocated memory in the set.
		*/
		~MtmSet() {
			for (int i = 0; i < set_size; i++) {
				Node* node;
				node = first;
				first = first->next;
				delete node;
			}
			set_size = 0;  //fixed :new
		}

		//~MtmSet() {
		//	Node* node;
		//	node = first;
		//	for (int i = 0; i < set_size; i++) {
		//		node = node->next;
		//		delete node;
		//	}
		//	set_size = 0;  //fixed :new
		//}

		/**
		* Insert a new element to the set, doesn't insert if there is already
		*  an equal element in the set.
		* If an element was't inserted, all iterators should stay valid.
		* @param elem The element to insert to the set
		* @return An iterator to the inserted element, or to the equal
		* element if the element wasn't inserted.
		*/
		iterator insert(const Type& elem) {

			if (set_size == 0) {
				Node* node = new Node(elem);
				iterator new_iterator(node);
				first = node;
				set_size++;
				return new_iterator;
			}
			Node* node;
			node = first;
			for (int i = 0; i < set_size; i++) {
				if (node->data == elem) {
					iterator new_iterator(node);
					return new_iterator;
				}
				if (i != set_size - 1) {
					node = node->next;
				}
			}

			Node* new_node = new Node(elem);

			iterator new_iterator(new_node);
			node->next = new_node;
			set_size++;

			return new_iterator;
		}

		/**
		* Remove an element from the set. If there is no element equal to
		*  elem in the set, does nothing.
		* If an element wasn't removed, all iterators should stay valid.
		* @param elem the element to remove.
		*/
		void erase(const Type& elem) {
			Node* node = first;
			for (int i = 0; i < set_size; i++) {
				if (node->data == elem) {
					if (i == 0) {
						first = node->next;
						delete node;
						set_size--;
						return;
					}

					Node* node2 = first;
					for (int k = 0; k < i - 1; k++) {
						//find the node befor the one we want to remove
						node2 = node2->next;
					}
					//change the next pointer so we skip the one to remove
					node2->next = node->next;
					//remove node
					delete node;
					set_size--;
					return;
				}
				node = node->next;
			}
			return;
		}

		/**
		* Remove the element the iterator points to from the set.
		* Iterator to another set is undefined.
		* @param it The iterator to the element to the set.
		*/
		void erase(const iterator& it) {
			erase(*(it));
		}

		/**
		* Get the amount of elements in the set.
		* @return The amount of elements in the set.
		*/
		int size() const {
			return set_size;
		}

		/**
		* Check if the set is empty.
		* @return true is the set is empty.
		*/
		bool empty() const {
			if (set_size == 0) {
				return true;
			}
			return false;
		}

		/**
		* Empty the set, free all allocated memory in the set.
		*/
		void clear() {
			Node* node = first;
			for (int i = 0; i < set_size; i++) {
				Node* tmp = node;
				node = node->next;
				delete tmp;
			}
			first = NULL;
			set_size = 0;
		}

		/**
		* Get an iterator to the first element in the set.
		* If set is empty, return the same as end.
		* @return
		*/
		iterator begin() {
			if (set_size == 0) {
				iterator tmp(NULL);
				return tmp;
			}
			iterator iterator(first);
			return  iterator;

		}

		/**
		* Get a const_iterator to the first element in the set.
		* If set is empty, return the same as end.
		* @return
		*/
		const_iterator begin() const {

			if (set_size == 0) {
				const_iterator tmp(NULL);
				return tmp;
			}
			const_iterator iterator(first);
			return  iterator;

		}

		/**
		* Returns an iterator referring to the past-the-end element in the set.
		* The past-the-end element is the theoretical element that would follow
		* the last element in the set. It does not point to any element, and
		* thus should not be dereferenced.
		* @return Iterator to past-the-end element.
		*/
		iterator end() {

			iterator tmp(NULL);
			return tmp;
		}

		/**
		* Returns a const_iterator referring to the past-the-end element in
		* the set.
		* The past-the-end element is the theoretical element that would follow
		* the last element in the set. It does not point to any element, and
		* thus should not be dereferenced.
		* @return const_iterator to past-the-end element.
		*/
		const_iterator end() const {
			const_iterator tmp(NULL);
			return tmp;
		}

		/**
		* Find an element in the set.
		* @param elem The element to find
		* @return An iterator that points to the elem.
		*/
		iterator find(const Type& elem) {
			Node* node = first;
			for (int i = 0; i < set_size; i++) {
				if (node->data == elem) {
					iterator tmp(node);
					return tmp;
				}
				node = node->next;
			}
			iterator tmp(NULL);
			return tmp;
		}

		/**
		* Find an element in the set.
		* @param elem The element to find
		* @return A const_iterator that points to the elem.
		*/
		const_iterator find(const Type& elem) const {
			Node* node = first;
			for (int i = 0; i < set_size; i++) {
				if (node->data == elem) {
					const_iterator tmp(node);
					return tmp;
				}
				node = node->next;
			}
			const_iterator tmp(NULL);
			return tmp;
		}

		/**
		* Check if an element is in the set.
		* @param elem The element to check if it's in the set.
		* @return True if the element is in the set, false otherwise.
		*/
		bool contains(const Type& elem) const {
			Node* node = first;
			for (int i = 0; i < set_size; i++) {
				if (node->data == elem) {
					return true;
				}
				node = node->next;
			}
			return false;
		}

		/**
		* Check if this set is a superset of a given set.
		* Superset: A superset of B if B is a subset of A, that mean's that
		*  A contains all the elements in B.
		* @param subset The set to check if it's a subset.
		* @return True if the given set is a subset of this set.
		*/
		bool isSuperSetOf(const MtmSet& subset) const {
			Node* node1 = first;
			Node* node2 = subset.first;
			int sum = 0;
			for (int i = 0; i < subset.set_size; i++) {
				for (int k = 0; k < set_size; k++) {
					if (node2->data == node1->data) {
						sum++;
						break;
					}
					node1 = node1->next;
				}
				node1 = first;
				node2 = node2->next;
			}
			if (sum == subset.set_size) {
				return true;
			}
			return false;
		}

		/**
		* Check if two set are equal, meaning, they contain the same elements.
		* @param rhs The set right of the == operator.
		* @return true if thw two set conatain the same elements, false
		*  otherwise.
		*/
		bool operator==(const MtmSet& rhs) const {
			return !(this->operator!=(rhs));
		}

		/**
		* Check if two set are equal, meaning, they contain the same elements.
		* @param rhs The set right of the != operator.
		* @return false if thw two set conatain the same elements, true
		*  otherwise.
		*/
		bool operator!=(const MtmSet& rhs) const {
			if (isSuperSetOf(rhs) == true) {
				MtmSet<Type> set(rhs);
				if (set.isSuperSetOf(*this) == true) {
					return false;
				}
			}
			return true;
		}

		/**
		* Insert all the elements in the given set to this set (union).
		* @param set The set to insert all the elements from.
		* @return A reference to this set.
		*/
		MtmSet& unite(const MtmSet& set) {
			Node* node_set = set.first;
			for (int i = 0; i < set.set_size; i++) {
				insert(node_set->data);
				node_set = node_set->next;
			}
			MtmSet* tmp;
			tmp = this;
			return *tmp;
		}

		/**
		* Returns a new set that is an union of this set, and a given set.
		* @param set The other set (other than this) to be in the union.
		* @return The new set.
		*/
		MtmSet unite(const MtmSet& set) const {
			MtmSet new_set(*this); //fixed 26.1 14:00
			new_set.unite(set);
			return new_set;
		}

		/**
		* Remove all the elements from this set, that are in the given set
		* (intersection).
		* @param set The other set in the intersection.
		* @return A reference to this set.
		*/
		MtmSet& intersect(const MtmSet& set) {
			Node* node_set = first;
			for (int i = 0; i < set_size; i++) {
				if (!set.contains(node_set->data)) {
					Node* tmp2 = node_set;
					node_set = node_set->next;
					erase(tmp2->data);
					i--;
					continue;
				}
				node_set = node_set->next;
			}
			MtmSet* tmp;
			tmp = this;
			return *tmp;
		}

		/**
		* Returns a new set that is an intersection of this set,
		*  and a given set.
		* @param set The other set (other than this) to be in the intersection.
		* @return The new set.
		*/
		MtmSet intersect(const MtmSet& set) const {
			MtmSet new_set(*this); //fixed 26.1 14:00
			new_set.intersect(set);
			return new_set;
		}

		/**
		* Remove all the elements in the set, that doesn't meet a given
		*  condition.
		* @tparam func - A function of an object-function that receive 1
		*  argument, of the same type as an element in the set, and returns
		*  a bool.
		* @param condition - function (or object-function) that returns true
		* if the element is meeting the condition and false otherwise.
		* @return A reference to this set.
		*/
		template<typename func>
		MtmSet& getSubSet(func condition) {
			Node* node = first;
			for (int i = 0; i < set_size; i++) {
				if (condition(node->data)) {
					node = node->next;
					continue;
				}
				//doesn't meet a given condition
				Node* tmp_node = node;
				node = node->next;
				erase(tmp_node->data);
				i--;

			}
			MtmSet* tmp;
			tmp = this;
			return *tmp;
		}

		/**
		* Get a subset of this set, that contains all the elements in the set,
		* that doesn't meet a given condition.
		* @tparam func - A function of an object-function that receive 1
		*  argument, of the same type as an element in the set, and returns
		*  a bool.
		* @param condition - function (or object-function) that returns true
		* if the element is meeting the condition and false otherwise.
		* @return A the new set.
		*/
		template<typename func>
		MtmSet getSubSet(func condition) const {
			MtmSet new_set(*this);
			new_set.getSubSet(condition);
			return new_set;
		}
	};
} // namespace mtm

#endif //MTM4_SET_H