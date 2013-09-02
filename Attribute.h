#include <stdio.h>
#include <string.h>
using namespace std;

template <class type>
type Attribute{
		type value;
		//Do we need a domain member?
	public:
		type get_value();
		Attribute(type value); //contructor
		~Attribute(); //destructor
};