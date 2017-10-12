#include "Element.h"

Element::Element(const char* type,const char* text) :XmlObject(type, text)
{
	
	elementColletion = new ElementsCollection();
	numberOfParents = 0;
	isElementClosed = false;
	stringCapacity = 1000;
}

Element::Element(const char* type) :XmlObject(type, "")
{

	elementColletion = new ElementsCollection();
	numberOfParents = 0;
	isElementClosed = false;
}

Element::Element(const Element& other) : XmlObject(other)
{ CopyElementsCollection(other);
attributeCollection = other.attributeCollection;
numberOfParents = other.numberOfParents;
stringCapacity = other.stringCapacity;
isElementClosed = other.isElementClosed;

}
Element& Element::operator=(const Element& other)
{
	if (this != &other)
	{
		XmlObject::operator=(other);
		CopyElementsCollection(other);
		attributeCollection = other.attributeCollection;
		numberOfParents = other.numberOfParents;
		stringCapacity = other.stringCapacity;
		isElementClosed = other.isElementClosed;
		
	}
	return *this;
}
Element::~Element()
{
	delete elementColletion;

}
void Element::AddAttribute(const char*type, const char* text)
{
	attributeCollection.Add(type, text);
	
}
void Element::CreateString()
{
	
	if (strlen(text)!=0&&elementColletion->GetCount()==0)///ако елементът има само текст.
	{
		 
		int attLength = 0;
		
		int typeLenght = strlen(type);
		int textLenght = strlen(text);

		if (attributeCollection.ToString()!=nullptr)
			attLength = strlen(attributeCollection.ToString());
		

		int cursor = 0;
		string = new char[stringCapacity];
		cursor = SetWhiteSpaces(cursor);
		string[cursor++] = '<';
		for (int i = 0; i <typeLenght; i++,cursor++)
		{
			if (cursor == stringCapacity)
				string = XmlObject::ResizeString(string, stringCapacity);
			string[cursor] = type[i];
		}
		if (cursor == stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		if (attLength!=0)
		{
			string[cursor] = ' ';
			cursor++;
		}
		
		for (int i = 0; i < attLength; i++, cursor++)
		{
			if (cursor == stringCapacity)
				string = XmlObject::ResizeString(string, stringCapacity);
			string[cursor] = attributeCollection.ToString()[i];
		}
		if (cursor == stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor] = '>';
		cursor++;
		for (int i = 0; i < textLenght; i++, cursor++)
		{
			if (cursor == stringCapacity)
				string = XmlObject::ResizeString(string, stringCapacity);
			string[cursor] = text[i];
		}
		if (cursor + 5 > stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor] = '<';
		cursor++;
		string[cursor] = '/';
		cursor++;
		for (int i = 0; i <typeLenght; i++, cursor++)
		{
			if (cursor == stringCapacity)
				string = XmlObject::ResizeString(string, stringCapacity);
			string[cursor] = type[i];
		}
		if (cursor+6 >stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor++] = '>';
		string[cursor++] = '\n';
		string[cursor++] = '\0';
		
	}
	else if (strlen(text) == 0 && elementColletion->GetCount()> 0)//има само елементи
	{
		
		string = new char[stringCapacity];
		int cursor = 0;
		cursor = SetWhiteSpaces(cursor);
		cursor = addKey(true, cursor);
		string[cursor++] = '\n';
		cursor = copyStrToStr(elementColletion->ToString(), cursor);//добавя на стрингвете на всички вложени елементи 
	/*	for (int i = 0; i < elementColletion->getCount(); i++)
		{
			char* texttt = (elementColletion->getElement(i)->toString());
			copyStrToStr(texttt, cursor);
		}*/
		//string[cursor++] = '\n';
		cursor = SetWhiteSpaces(cursor);
		cursor = addKey(false, cursor);
		string[cursor++] = '\n';
		string[cursor++] = '\0';
	}
	else if (strlen(text) == 0 && elementColletion->GetCount() == 0)//няма нищо
	{
		string = new char[stringCapacity];
		int cursor = 0;
		cursor = SetWhiteSpaces(cursor);
		cursor = addKey(true, cursor);
		cursor = addKey(false, cursor);
		string[cursor++] = '\n';
		string[cursor++] = '\0';
	}
	else  //има и 2 те
	{
		int textLenght = strlen(text);
		string = new char[stringCapacity];
		int cursor = 0;
		cursor = SetWhiteSpaces(cursor);
		cursor = addKey(true, cursor);
		for (int i = 0; i < textLenght; i++, cursor++)
		{
			if (cursor == stringCapacity)
				string =XmlObject::ResizeString(string, stringCapacity);
			string[cursor] = text[i];
		}
		string[cursor++] = '\n';
		cursor = copyStrToStr(elementColletion->ToString(), cursor);//добавя на стрингвете на всички вложени елементи 
		/*	for (int i = 0; i < elementColletion->getCount(); i++)
		{
		char* texttt = (elementColletion->getElement(i)->toString());
		copyStrToStr(texttt, cursor);
		}*/
		//string[cursor++] = '\n';
		cursor = SetWhiteSpaces(cursor);
		cursor = addKey(false, cursor);
		string[cursor++] = '\n';
		string[cursor++] = '\0';
	}
	
}
int Element::addKey(bool isStart,int cursor)
{
	string[cursor++] = '<';
	if (!isStart)
		string[cursor++] = '/';
	int typeLenght = strlen(type);
	for (int i = 0; i < typeLenght;cursor++, i++)
	{
		if (cursor == stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor] = type[i];
	}
	if (isStart)
	{
		int attLength = 0;
		if (attributeCollection.ToString() != nullptr)
			attLength = strlen(attributeCollection.ToString());
		if (attLength != 0)
		{
			string[cursor] = ' ';
			cursor++;
		}
		for (int i = 0; i < attLength; i++, cursor++)
		{
			if (cursor == stringCapacity)
				string =XmlObject::ResizeString(string, stringCapacity);
			string[cursor] = attributeCollection.ToString()[i];
		}
		
	}
	string[cursor++] = '>';
	return cursor;
}
int Element::copyStrToStr(const char* txt, int cursor)
{
   int	elementTxtLenght = strlen(txt);
	for (int i = 0; i < elementTxtLenght;cursor++, i++)
	{
		if (cursor == stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor] = txt[i];
	}
	return cursor;
}



Element* Element::GetLastChild()
{
	if (getElementsCollection()->GetCount() == 0)
		return nullptr;
	return getElementsCollection()->getElement(getElementsCollection()->GetCount()-1);
}
void Element::CopyElementsCollection(const Element& other)
{
	elementColletion = new ElementsCollection(*other.elementColletion);
}
void Element::SetNumberOfParents(int num)
{
	if (num < 0)
		throw "Invalid value";
	numberOfParents = num;

}
int Element::SetWhiteSpaces(int cursor)///добавя интервали в зависимост, кое колко родители има
{
	for (int i = 0; i < numberOfParents*5;cursor++, i++)
	{
		if (cursor == stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor] = ' ';
	}
	return cursor;
}
bool Element::SetAttributeValue(char* key, char* value)
{
	bool isSucceed = attributeCollection.SetAttributeValue(key, value);
	if (!isSucceed)
	{
		for (int i = 0; i < elementColletion->GetCount()&&!isSucceed; i++)
		{
			isSucceed = elementColletion->getElement(i)->SetAttributeValue(key, value);
		}
		
	}
	

	return isSucceed;
}
//Element* Element::getElement(char* type)
//{
//	if (strcmp(type,GetKey()))
//	{
//
//	}
//}
void Element::AddText(const char* textToAdd)
{
	if (text != nullptr)
		delete[] text;
	int textToAddLenght = strlen(textToAdd);
	text = new char[textToAddLenght + 1];
	for (int i = 0; i < textToAddLenght; i++)
	{
		text[i] = textToAdd[i];
	}
	text[textToAddLenght] = '\0';

}
bool Element::IsElementClosed()
{
	return isElementClosed;
}
void Element::CloseElement()
{
	isElementClosed = true;
}
ElementsCollection* Element::getElementsCollection()
{
	return elementColletion;
}
bool Element::ContainsAttribute(const char* key)
{
	int result = attributeCollection.FindAttribute(key);
	if (result == -1)
		return false;
	return true;
}
const char* Element::GetAttributeValue(const char* key)
{
	return attributeCollection.GetAttributeValue(key);
}
void Element::SetAttributeValue(const char* key, const char* value)
{
	attributeCollection.SetAttributeValue(key, value);
}
bool Element::DeleteAttribute(const char* key)
{
	return attributeCollection.DeleteAttribute(key);
}
int Element::NumberOfParents()
{
	return numberOfParents;
}
