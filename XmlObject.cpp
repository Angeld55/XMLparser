#include "XmlObject.h"
#include <iostream>
XmlObject::XmlObject(const char* type,const char* text)
{
	
	int lenght = strlen(type) + 1;
	this->type = new char[lenght];
	strcpy(this->type, type);
	lenght = strlen(text) + 1;
	this->text = new char[lenght];
	strcpy(this->text, text);
	string = nullptr;
	
}
XmlObject::XmlObject(const XmlObject& other)
{
	CopyFrom(other);
	
}
const char* XmlObject::ToString()
{
	delete[] string;
	CreateString();
	
	return string;
}

XmlObject& XmlObject::operator=(const XmlObject& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
		
	}
	return *this;
}
XmlObject::~XmlObject()
{
	Free();
}
void XmlObject::CopyFrom(const XmlObject& other)
{
	//std::cout << "puska se we";
	
	int lenght = strlen(other.text) + 1;
	type = new char[lenght];
	strcpy(type, other.type);
	lenght = strlen(other.text) + 1;
	text = new char[lenght];
	strcpy(text, other.text);
	

	//lenght = strlen(other.string) + 1;
	//text = new char[lenght];
	//strcpy(string, other.string);
}
void XmlObject::Free()
{
	delete[] type, text;
	delete[] string;
}

const char* XmlObject::GetKey()
{
	return type;
}
const char* XmlObject::GetValue()
{
	return text;
}
char*  XmlObject::ResizeString(char* input, int& capacity)
{
	char* str = new char[capacity * 2];
	

	for (int i = 0; i < capacity; i++)
	{
		str[i] = input[i];
	}
	capacity *= 2;
	delete[] input;
	return str;
}