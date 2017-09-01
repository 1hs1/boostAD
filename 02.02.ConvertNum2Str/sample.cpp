#include "stdafx.h"

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;


class JsonObj
{
public:
	virtual void steamOut(std::ostream& os) const = 0;
};

class JsonKey : public JsonObj
{
	//- key는 무조건 string 임
	string key_;

public:
	template <typename T>
	JsonKey(T key) {
		//- 물론 std::to_string 을 써도 되지만...
		key_ = boost::lexical_cast<string>(key);
	}

	void steamOut(std::ostream& os) const override {
		os << key_;
	}
};

class JsonValueInt : public JsonObj
{
	//- 어떤 필드는 무조건 int 형이여야만 함
	int value_;

public:
	template <typename TYPE_VALUE>
	JsonValueInt(TYPE_VALUE value)
	{
		value_ = boost::lexical_cast<int>(value);
	}

	void steamOut(std::ostream& os) const override {
		os << value_;
	}
};

std::ostream& operator << (std::ostream& os, const JsonObj& obj)
{
	obj.steamOut(os);
	return os;
}


void sample()
{
	try {
		JsonKey key(12345);
		JsonValueInt value("37282929");

		cout << "key:" << key << ", value:" << value << endl;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	
}
