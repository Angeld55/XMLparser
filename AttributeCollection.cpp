#include "AttributeCollection.h"
#include <iostream>

AttributeCollection::AttributeCollection()
{
	count = 0;
	capacity = 8;
	attributes = new Attribute*[8];
	string = nullptr; 
	stringCapacity = 300;
}
AttributeCollection::AttributeCollection(const AttributeCollection& other)
{
	CopyFrom(other);
}
AttributeCollection& AttributeCollection::operator=(const AttributeCollection& other)
{
	if (this!=&other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
AttributeCollection::~AttributeCollection()
{
	Free();
}
void AttributeCollection::CopyFrom(const AttributeCollection& other)
{
	attributes = new Attribute*[other.capacity];
	capacity = other.capacity;
	for (int i = 0; i < other.count; i++)
	{
		attributes[i] = new Attribute(*other.attributes[i]);
			
	}
	count = other.count;
}
void AttributeCollection::Free()
{
	for (int i = 0; i < count; i++)
	{
		delete attributes[i];
	}
	delete[] attributes;
	delete[] string;
}
void AttributeCollection::Resize()
{
	Attribute** temp = new Attribute*[capacity * 2];
	for (int i = 0; i < count; i++)
	{
		temp[i] = attributes[i];
	}
	capacity *= 2;
	delete[] attributes;
	attributes = temp;
}
void AttributeCollection::Add(Attribute* attribute)
{
	//std::cout << "Dobawqm " << attribute->GetKey() << std::endl;
	if (count == capacity)
		Resize();
	attributes[count] = attribute;
	count++;
}
void AttributeCollection::Add(const char*type,const char* text)
{
	
	Attribute* attribute = new Attribute(type, text);
	Add(attribute);
}
void AttributeCollection::CreateString()//С точна дължина!
{
	if (count == 0)
	{
		string = "";
		return;
	}
	
	char* str = new char[stringCapacity];
	int cursor = 0;
	for (int i = 0; i < count; i++)
	{
		
		for (int j = 0; j< GetAttributeStringLength(i); cursor++, j++)
		{
			if (cursor==stringCapacity)
				str = XmlObject::ResizeString(str, stringCapacity);
			str[cursor] = attributes[i]->ToString()[j];
		}
		if (i != count - 1)
		{
			str[cursor] = ' ';
			cursor++;
		}
		
	}
	str[cursor] = '\0';
	string = str;
	
}
int AttributeCollection::GetCount()
{
	return count;
}
int AttributeCollection::GetAttributeStringLength(int index)
{
	if (index > count)
		return -1;
	const char* str = attributes[index]->ToString();
	return strlen(str);
}
char* AttributeCollection::ToString()
{
	
	CreateString();
	return string;
}
bool AttributeCollection::SetAttributeValue(const char* key,const char* value)
{
	for (int i = 0; i < count; i++)
	{
		if (_stricmp(attributes[i]->GetKey(),key)==0)
		{
			attributes[i]->SetValue(value);
			return true;
		}
	}
	return false;
}
int AttributeCollection::FindAttribute(const char* key)
{
	for (int i = 0; i < count; i++)
	{
		if (_stricmp(attributes[i]->GetKey(),key)==0)
		{
			return i;
		}
	}
	return -1;
}
bool AttributeCollection::DeleteAttribute(const char* key)
{
	int index = FindAttribute(key);
	if (index == -1)
		return false;

	delete attributes[index];
	for (int i = index; i < count-1; i++)
	{
		attributes[i] = attributes[i + 1];///местим всички атрибути с една позиция назад
	}
	count--;
	return true;
}
const char* AttributeCollection::GetAttributeValue(const char* key)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(attributes[i]->GetKey(), key) == 0)
		{
			return attributes[i]->GetValue();
		}
	}
	return "";
}
