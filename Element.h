#pragma once
#include <iostream>

class ElementsCollection;
#include "AttributeCollection.h"
#include "ElementsCollection.h"
class Element :public XmlObject
{
private:
	AttributeCollection attributeCollection;
	ElementsCollection* elementColletion;
	int stringCapacity;
	int numberOfParents;
	bool isElementClosed;

	int SetWhiteSpaces(int);
	void CopyElementsCollection(const Element& other);
	Element* getElement(char* type);
	bool SetAttributeValue(char* key, char* value);
	void CreateString();
	int addKey(bool, int);
	int copyStrToStr(const char*, int);

public:
	Element(const char*,const char*);
	Element(const char*);
	~Element();
	Element(const Element& other);
	Element& operator=(const Element& other);
	void AddAttribute(const char* type,const char* text);
	Element* GetLastChild();
	void SetNumberOfParents(int);
	int NumberOfParents();
	void AddText(const char* text);
	const char* GetAttributeValue(const char* key);
	bool IsElementClosed();
	void CloseElement();
    ElementsCollection* getElementsCollection();
	bool ContainsAttribute(const char* key);
	void SetAttributeValue(const char* key, const char* value);
	bool DeleteAttribute(const char* key);
	
};
