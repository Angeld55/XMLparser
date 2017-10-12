#include "ElementsCollection.h"

ElementsCollection::ElementsCollection()
{
	count = 0;
	elementCapacity = 8;
	
	elements = new Element*[8];

	stringCapacity = 10000;
	string = nullptr;
}
ElementsCollection::ElementsCollection(const ElementsCollection& other)
{
	CopyFrom(other);
}
ElementsCollection& ElementsCollection::operator=(const ElementsCollection& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
ElementsCollection::~ElementsCollection()
{
	Free();
}
void ElementsCollection::CopyFrom(const ElementsCollection& other)
{
	elements = new Element*[other.elementCapacity];
	elementCapacity = other.elementCapacity;
	stringCapacity = other.stringCapacity;
	
	for (int i = 0; i < other.count; i++)
	{
		elements[i] = new Element(*other.elements[i]);

	}
	count = other.count;
}
void ElementsCollection::Free()
{
	
	for (int i = 0; i < count; i++)
	{
		
		delete elements[i];
	}
	delete[] elements;
	delete[] string;
}
void ElementsCollection::Resize(Element** collcection,int& capacity)
{
	Element** temp = new Element*[capacity * 2];
	for (int i = 0; i < count; i++)
	{
		temp[i] = collcection[i];
	}
	capacity *= 2;
	delete[] collcection;
	elements = temp;
}
void ElementsCollection::AddТоCurrentCollection(Element* element)
{
	if (count == elementCapacity)
		Resize(elements, elementCapacity);
	elements[count] = element;
	count++;
}
void ElementsCollection::AddТоCurrentCollection(const char*type,const char* text)
{
	Element* element = new Element(type, text);
	AddТоCurrentCollection(element);
}
void ElementsCollection::AddТоCurrentCollection(const char*type)
{
	Element* element = new Element(type);
	AddТоCurrentCollection(element);
}
void ElementsCollection::Add(const char*type, const char* text,int parents)
{
	if (count>0)
	{
		if (getElement(count - 1)->IsElementClosed())
		{
			AddТоCurrentCollection(type, text);
			getElement(count - 1)->SetNumberOfParents(parents);//взимаме последно добавения елемент и му казваме кое "дете" е
			
			
		}
		else
		{
		getElement(count - 1)->getElementsCollection()->Add(type, text, parents + 1);
		
		}
	}
	else
	{
		AddТоCurrentCollection(type, text);
		getElement(count - 1)->SetNumberOfParents(parents);
		
	}

}

void ElementsCollection::Add(const char*type)
{
	Add(type, "");

}
void ElementsCollection::AddAttributeToLastUnclosedEl(const char*type,const char* value)
{
	if (count>0)
	{
		if (!getElement(count - 1)->IsElementClosed())
		{
			if (getElement(count - 1)->getElementsCollection()->count != 0)
			{
				getElement(count - 1)->getElementsCollection()->AddAttributeToLastUnclosedEl(type, value);
			}
			else
				getElement(count - 1)->AddAttribute(type, value);
			

		}
		else
		{
			//error
		}
	}
	else
	{
	//error

	}

}
void ElementsCollection::AddTextToLastUnclosedEl(const char*text)
{
	if (count>0)
	{
		if (!getElement(count - 1)->IsElementClosed())
		{
			if (getElement(count - 1)->getElementsCollection()->count != 0)
			{
				getElement(count - 1)->getElementsCollection()->AddTextToLastUnclosedEl(text);
			}
			else
				getElement(count - 1)->AddText(text);


		}
		else
		{
			//error
		}
	}
	else
	{
		//error

	}

}
bool ElementsCollection::CloseLast(const char* type)
{

	if (isLastElementClosed())
	{
		return false;
	}
	else
	{
		if (!getElement(count - 1)->getElementsCollection()->isLastElementClosed())
		{
			return getElement(count - 1)->getElementsCollection()->CloseLast(type);
		}
		else
		{
			if (strcmp(getElement(count-1)->GetKey(),type)==0)///проверява дали името на затварящия таг отговаря на името на последния не затворен елемент.
			{
				getElement(count - 1)->CloseElement();
				return true;
			}
			else 
				return false;
		}
	}
	
	
}
const char* ElementsCollection::ToString()
{
		delete[] string;
		CreateString();
		return string;
}
void ElementsCollection::CreateString()
{
	stringCapacity = 10000;
	string = new char[stringCapacity];
	int cursor = 0;
	for (int i = 0; i < GetCount(); i++)
	{
		cursor = copyToString(elements[i]->ToString(), cursor);///взима стринга на всеки елемент и го конкатенира към своя.
		
	}
	string[cursor] = '\0';
}
int ElementsCollection::copyToString(const char* strOther, int cursor)
{
	int strLenght = strlen(strOther);
	for (int i = 0; i < strLenght;cursor++, i++)
	{
		
		if (cursor == stringCapacity)
			string = XmlObject::ResizeString(string, stringCapacity);
		string[cursor] = strOther[i];
	}
	return cursor;
}

int ElementsCollection::GetCount()
{
	return count;
}
Element* ElementsCollection::getElement(int position)
{
	if (position >= GetCount())
		throw "Invalid index";
	return elements[position];
}
/*Element* ElementsCollection::getElement(char* type)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(elements[i]->GetValue(),type)==0)
		{
			return elements[i];
		}
		else
		{
			for (int i = 0; i < length; i++)
			{
				elements[i]->GetChild(i)->
			}
		}
	}*/
//}
bool ElementsCollection::isLastElementClosed()
{
	return (count == 0 || getElement(count - 1)->IsElementClosed());
	
}

Element* ElementsCollection::findElementByAttribute(const char* key, const char* value)
{
	Element* el;
	if (count == 0)
		return nullptr;
	for (int i = 0; i < count; i++)
	{
		const char* k = elements[i]->GetAttributeValue(key);
		if (strcmp(k, value) == 0)
			return elements[i];
		else
			el = elements[i]->getElementsCollection()->findElementByAttribute(key, value);
		if (el != nullptr)
			return el;
	}
	return nullptr;
}
const char* ElementsCollection::GetAttributeValueByOtherAttribute(const char* attrKey,const  char* attrValue,const char* keySearched)
{
	Element* searched= findElementByAttribute(attrKey, attrValue);
	if (searched == nullptr)
		return nullptr;
	return searched->GetAttributeValue(keySearched);

}
bool ElementsCollection::SetAttributeValueByOtherAttribute(const char* attrKey, const char* attrValue, const char* attrNameToChangeValue, const char* attrValueToChangeValue)
{
	Element* searched = findElementByAttribute(attrKey, attrValue);
	if (searched == nullptr)
		return false;
	searched->SetAttributeValue(attrNameToChangeValue, attrValueToChangeValue);
	return true;
}
const char* ElementsCollection::GetElementTextByAttribute(const char* attrKey, const char* attrValue)
{
	Element* searched = findElementByAttribute(attrKey, attrValue);
	if (searched == nullptr)
		return "";
	return searched->GetValue();
}
bool ElementsCollection::DeleteAttributeByAttribute(const char* attrKey, const  char* attrValue, const char* keySearched)
{
	Element* searched = findElementByAttribute(attrKey, attrValue);
	
	if (searched == nullptr)
		return false;
	return searched->DeleteAttribute(keySearched);
	

}
bool ElementsCollection::AddChildToElement(const char* attrKey, const  char* attrValue, const char* elementName, const char* elementText)
{
	Element* searched = findElementByAttribute(attrKey, attrValue);
	if (searched == nullptr)
		return false;
	searched->getElementsCollection()->Add(elementName, elementText, searched->NumberOfParents() + 1);
	searched->getElementsCollection()->CloseLast(elementName);
	return true;
}
const char* ElementsCollection::GetChildrenString(const char* attrKey, const char* attrValue)
{
	Element* searched = findElementByAttribute(attrKey, attrValue);
	if (searched == nullptr)
		return nullptr;
	return searched->getElementsCollection()->ToString();
}
const char* ElementsCollection::GetNthChildString(const char* attrKey, const char* attrValue, const int n)
{
	Element* searched = findElementByAttribute(attrKey, attrValue);
	if ((searched == nullptr)||(searched->getElementsCollection()->GetCount()<n))
		return nullptr;
	return searched->getElementsCollection()->elements[n]->ToString();

}