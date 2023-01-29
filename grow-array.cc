/*
	Write a GrowArray class that is templated, and that allows you to 
	allocate memory but not call the constructor for each element.
	To do this you will have to cast and use placement new syntax.

	See placementnew.cc, GrowArray.cc
	You are encouraged to write the class from scratch without looking at 
	my code, once you understand the fundamentals.

*/

#include <iostream>
#include "vector"
using namespace std;

class Person {
private:
	uint32_t len;
	char* name;
public:
	Person(const char n[]) : len(strlen(n)) {
		cout << "Person constructor\n";
		name = new char[len];
		memcpy(name, n, len);
	}
	Person(const Person& orig) : len(strlen(orig.name)){
		cout << "copying Person\n";
		name = new char[len];
		memcpy(name, orig.name, len);
	}
	~Person() {
		cout << "Destructor\n";
		delete [] name;
	}
};

//new Person[5]  --> Person()
/*
	You can write your code here
 */
template<typename T>
class GrowArray {
private:
	uint32_t capacity;
	void * operator new(size_t size, T* place){
	    return place;
	}
	uint32_t len;
	char* data;
	T* getAddr(int i) const {
	    return (T*)data + i;
	}
public:
	// new T[1000] --> calls constructor T::T() 1000 times
	GrowArray(uint32_t initialCapacity) : capacity(initialCapacity), len(0), data(new char[initialCapacity*sizeof(T)]) {}
	~GrowArray() {
		for (int i = 0; i < len; i++)
			(((T*)data)+i).~T();
		delete [] data;
	}
	// add copy constructor and operator =
    GrowArray(const GrowArray& orig) : capacity(orig.capacity), len(orig.len), data(new char[orig.capacity*sizeof(T)]){
	    for(int i = 0; i < len; i++){
            new (getAddr(i)) T( ((T*)orig.data) +i);
	    }
	}
	GrowArray& operator =(GrowArray orig){
	    capacity = orig.capacity;
	    len = orig.len;
	    swap(data, orig.data);
	    return *this;
	}
	void add(T& element){
	    T * old = (T*)data;
        data = new char[(len+1)*sizeof(T)];
        for(int i = 0; i < len; i++){
            new (getAddr(i)) T(move(old[i]));
        }
        ((T*)data)[len++] = element;
	}
};

int main() {
	GrowArray<Person> list(1000000); // should not call constructor for Person!
	list.add(Person("Test")); // Should call the constructor once and the copy once
	/*
		Destructor should be called twice for person (once for the temp, and once for 
		the object in the array. If the optimizer somehow can do it, it could be only once. 
		But most important, you must not call the destructor 1000000 times!
	*/
	GrowArray<Person> list2(list); // make a copy of the list
	list2 = list; // operator =
}
