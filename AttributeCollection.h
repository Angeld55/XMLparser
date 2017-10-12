#pragma once

#include "Attribute.h"
#pragma once
class AttributeCollection
{
private:
	Attribute** attributes;
	char* string;
	int stringCapacity;
	int count;
	int capacity;
	void Resize();
	void Free();
	void CopyFrom(const AttributeCollection& other);
	int GetAttributeStringLength(int);
	void Add(Attribute* attribute);
	void CreateString();
	
public:
	AttributeCollection();
	AttributeCollection(const AttributeCollection& other);
	AttributeCollection& operator= (const AttributeCollection& other);
	~AttributeCollection();



	void Add(const char* type,const char* text);
	char* ToString();
	int GetCount();
	bool SetAttributeValue(const char* key, const char* value);
	bool DeleteAttribute(const char* key);
	int FindAttribute(const char* key);
	const char* GetAttributeValue(const char* key);
	
};
