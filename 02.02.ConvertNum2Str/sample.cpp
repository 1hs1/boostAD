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
	//- key�� ������ string ��
	string key_;

public:
	template <typename T>
	JsonKey(T key) {
		//- ���� std::to_string �� �ᵵ ������...
		key_ = boost::lexical_cast<string>(key);
	}

	void steamOut(std::ostream& os) const override {
		os << key_;
	}
};

class JsonValueInt : public JsonObj
{
	//- � �ʵ�� ������ int ���̿��߸� ��
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
