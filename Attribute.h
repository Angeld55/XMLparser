#pragma once
#include <iostream>
#include "XmlObject.h"
 class Attribute:public XmlObject
{

private:
	void CreateString();
public:
	Attribute(const char*,const char*);
	//Attribute(const Attribute& other);
	//Attribute& operator=(const Attribute& other);
	void SetValue(const char* text);
};