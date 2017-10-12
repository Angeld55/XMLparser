#pragma once
#include "Element.h"
class Element;
class ElementsCollection
{
public:
	ElementsCollection();
	ElementsCollection(const ElementsCollection& other);
	ElementsCollection& operator=(const ElementsCollection&);
	~ElementsCollection();



	void CreateString();
	const char* ToString();
	int GetCount();
	Element* getElement(int position);
	void Add(const char*type,const  char* text,const int parents=0);
	void Add(const char* type);
	void AddAttributeToLastUnclosedEl(const char* type,const char* value);//��� ������ �� ����, ������ ������� � �� ������ ��� �������� �������;
	void AddTextToLastUnclosedEl(const char*text);
	Element* getElement(char* type);
	bool CloseLast(const char* type);// ������� �� ��� �������� ���;
	void AddElementToCollectionOfAllElementsInFile(Element*);
	const char* GetAttributeValueByOtherAttribute(const char*,const  char*,const char* );
	bool SetAttributeValueByOtherAttribute(const char* ,const char*,const char*,const char*);
	const char* GetElementTextByAttribute(const char*, const char*);
	bool DeleteAttributeByAttribute(const char* ,const char*, const char*);
	Element* findElementByAttribute(const char* key, const char* value);//private
	bool AddChildToElement(const char*,const char*, const char*, const char*);
	const char* GetChildrenString(const char* key, const char* value);
	const char* GetNthChildString(const char* key, const char* value, const int n);
private:
	Element** elements;
	
	bool isLastElementClosed();
	char* string;
	int count;
	int elementCapacity;
	int stringCapacity;
	void Resize(Element**,int&);
	void Free();
	void CopyFrom(const ElementsCollection& other);
	int copyToString(const char*,int);
	void Add��CurrentCollection(const char* type,const char* text);
	void Add��CurrentCollection(const char*);
	void Add��CurrentCollection(Element* element);
	
};	