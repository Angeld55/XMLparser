#include "Attribute.h"
#include <iostream>
Attribute::Attribute(const char* type,const char* text) :XmlObject(type,text)
{
	ToString();
}
//Attribute::Attribute(const Attribute& other) : XmlObject(other){  }
//Attribute& Attribute::operator=(const Attribute& other)
//{
//	XmlObject::operator=(other);
//	//ToString();
//	return *this;
//}
void Attribute::CreateString()
{
	
	int typeLenght = strlen(type);
	int textLenght = strlen(text);
	char* XmlObjectString = new char[typeLenght + textLenght + 4];

	for (int i = 0; i < typeLenght; i++)
		XmlObjectString[i] = type[i];
	XmlObjectString[typeLenght] = '=';
	XmlObjectString[typeLenght + 1] = 34;
	for (int i = 0, j = typeLenght + 2; i < textLenght; i++, j++)
		XmlObjectString[j] = text[i];
	XmlObjectString[typeLenght + textLenght + 2] = 34;
	XmlObjectString[typeLenght + textLenght + 3] = '\0';
	string = XmlObjectString;

}
void Attribute::SetValue(const char* textToSet)
{
	delete[] this->text;
	int length = strlen(textToSet);
	char* temp = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		temp[i] = textToSet[i];
	}
	temp[length] = '\0';
	this->text = temp;

}
