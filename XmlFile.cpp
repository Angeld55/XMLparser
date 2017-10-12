#include "XmlFile.h"


XmlFile::XmlFile(char* fileName)
{

	std::ifstream str;
	str.open(fileName);
	if (str.fail())
	{
		file = nullptr;
		ids = nullptr;
		string = nullptr;
		isFail = true;
		return;
	}
	

	int len = strlen(fileName);
	contentFileSource = new char[len + 1];
	strcpy(contentFileSource, fileName);
	contentFileSource[len] = '\0';

	idsCapacity = 5;
	ids = new char*[idsCapacity];
	ReadFile(str);
	AddFileContentToCollection();
	string = nullptr;
	isModified = true;
	str.close();
}
XmlFile::XmlFile(const XmlFile& other)
{
	CopyFrom(other);
}
XmlFile& XmlFile::operator=(const XmlFile& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
void XmlFile::addId(char* id)
{
	if (idsCapacity==idsCount)
	{
		char ** temp = new char*[idsCapacity*2];
		
		for (int i = 0; i < idsCount; i++)
		{
			temp[i] = ids[i];
		}
		idsCapacity *= 2;
		delete ids;
		ids = temp;
	}
	int length = strlen(id);
	char* tempStr = new char[length+ 1];
	strcpy(tempStr, id);
	tempStr[length] = '\0';
	ids[idsCount] = tempStr;
	idsCount++;
}
void XmlFile::ReadFile(std::ifstream& str)
{
	int capacity = 10000;
	file = new char[capacity];
	char c;
	int cursor = 0;
	str.get(c);
	while (!str.eof())
	{
		


		if (cursor == capacity)
		{
			file = XmlObject::ResizeString(file, capacity);
		
		}
		file[cursor++] = c;
		str.get(c);
	}
	fileStringLength = cursor;
	file[cursor] = '\0';
}
void XmlFile::Free()
{
	delete[] contentFileSource;
	delete[] file;
	delete[] string;
	
	for (int i = 0; i < idsCount; i++)
	{
		delete[] ids[i];
	}
	delete[] ids;
}
void XmlFile::CopyFrom(const XmlFile& other)
{
	int len = strlen(other.contentFileSource);
	contentFileSource = new char[len + 1];
	strcpy(contentFileSource, other.contentFileSource);
	elements = other.elements;
	ids = new char*[other.idsCount];
	for (int i = 0; i < other.idsCount; i++)
	{
		int l = strlen(other.ids[i]);
		ids[i] = new char[l + 1];
		strcpy(ids[i], other.ids[i]);
	}
	isFail = other.isFail;
	isModified = other.isModified;
	len = strlen(other.string);
	string = new char[len + 1];
	strcpy(string, other.string);
	file = nullptr;
	/// no need for copy of char* file (no need in keeping it for that matter...).
}
bool XmlFile::isIdTaken(const char* id)
{
	for (int i = 0; i < idsCount; i++)
	{
		if (strcmp(id,ids[i])==0)
		{
			return true;
		}
	}
	return false;

}
char* XmlFile::GenerateAutoId(int num)
{
	int digits = 0;
	int tempNum = num;
	while (tempNum) {
		tempNum /= 10;
		digits++;
	}
	char* generetedId = new char[7 + digits + 1];
	generetedId[0] = 'a';
	generetedId[1] = 'u';
	generetedId[2] = 't';
	generetedId[3] = 'o';
	generetedId[4] = 'I';
	generetedId[5] = 'D';
	generetedId[6] = '_';

	int cursor = 7;
	cursor += -1 + digits;
	while (true)
	{
		
		int temp = num % 10;

		if (num == 0)
		{
			generetedId[6 + 1 + digits] = '\0';
			break;
		}
		num /= 10;
		generetedId[cursor--] = temp + 48;///вървим на обратно за да запишем числото в правилен ред
	}
	return generetedId;
}
char* XmlFile::ConcatinateUniqeCharsToId(char* id,int num)
{
	int len = strlen(id);
	int digits = 0;
	int tempNum = num;
	while (tempNum) {
		tempNum /= 10;
		digits++;
	}
	char* newId = new char[len + 2+digits];
	for (int i = 0; i <len; i++)
	{
		newId[i] = id[i];
	}
	int cursor = len;

	newId[cursor] = '_';
	cursor += digits;
	

	while (true) 
	{
		int temp = num % 10;
		
		if (num == 0)
		{
			newId[len + 1 + digits] = '\0';
			break;
		}
		num /= 10;
		newId[cursor--] = temp + 48;///вървим на обратно за да запишем числото в правилен ред
	}
	return newId;

}

XmlFile::~XmlFile()
{
	Free();
	
}
void XmlFile::AddFileContentToCollection()
{
	if (isFailed())
	{
		return;
	}
	char* elementName=nullptr;
	char* elementText=nullptr;
	char* attributeName=nullptr;
	char* attributeValue=nullptr;
	
	int textLenghtCapacity = 30;
	
	
	bool isGettingElementName=0;
	bool isGettingAtrName=0;
	bool isGettingAtrValue = 0;
	bool isGettingElementText=0;
	bool elementHaveId = false;
	int cursor = 0;
	char c;
	for (int i = 0; i < fileStringLength; i++)
	{
		
		c = file[i];
		if (isGettingElementName)
		{
			if (c == '>')
			{
				elementName[cursor] = '\0';
				if (elementName[0]=='/')///ако е затварящ , шифтваме всичко на ляво.
				{
					int tempCursor = 0;
					while (elementName[tempCursor]!='\0')
					{
						elementName[tempCursor] = elementName[tempCursor + 1];
						tempCursor++;
					}

					elements.CloseLast(elementName);
				}
				else
				{
				elements.Add(elementName);

				if (!elementHaveId)
				{
					int uniqeNum = 1;
					while (true)
					{
						char* temp = GenerateAutoId(uniqeNum);
						if (!isIdTaken(temp))
						{
							elements.AddAttributeToLastUnclosedEl("id", temp);
							addId(temp);
							delete[] temp;
							break;
						}
						uniqeNum++;
						delete[] temp;
					}

				}

				elementHaveId = false;
				}
				isGettingElementName = false;
				cursor = 0;
				textLenghtCapacity = 30;
				delete[] elementName;
				continue;
			}
			else if (c == ' ')
			{
				elementName[cursor] = '\0';
				isGettingElementName = false;
				elements.Add(elementName);
				
				textLenghtCapacity = 30;
				cursor = 0;
				isGettingAtrName = true;
				attributeName = new char[textLenghtCapacity];
				delete[] elementName;
				continue;
			}

			if (cursor == textLenghtCapacity)
				elementName=XmlObject::ResizeString(elementName, textLenghtCapacity);
			elementName[cursor] = c;
			cursor++;
			continue;
			
		}
		else if (isGettingAtrName)
		{

			if (c=='=')
			{
				attributeName[cursor] = '\0';
				isGettingAtrName = false;
				
				isGettingAtrValue = true;
				textLenghtCapacity = 30;
				cursor = 0;
				attributeValue = new char[textLenghtCapacity];
				i++;//за да пропуснем кавичката " 
				continue;
			}

			if (cursor == textLenghtCapacity)
				attributeName = XmlObject::ResizeString(attributeName, textLenghtCapacity);
			attributeName[cursor] = c;
			cursor++;

		}
		else if (isGettingAtrValue)
		{
			if (c == '"')
			{
				attributeValue[cursor] = '\0';
				///повтарящи се id-та;
				if (strcmp(attributeName,"id")==0)
				{
					elementHaveId = true;
					if (isIdTaken(attributeValue))
					{
						int uniqeNum = 1;
						while (true)
						{
							char* temp = ConcatinateUniqeCharsToId(attributeValue,uniqeNum);
							if (!isIdTaken(temp))
							{
								delete[] attributeValue;
								attributeValue = temp;
								break;
							}
							uniqeNum++;
							delete[] temp;
						}
					}
					addId(attributeValue);
				}
				
					elements.AddAttributeToLastUnclosedEl(attributeName, attributeValue);
					i++;//за да пропуснем кавичката
				
			
				if (file[i]==' ')
				{
					isGettingAtrName = true;
				}
				if (!isGettingAtrName)
				{

					if (!elementHaveId)
					{
						int uniqeNum = 1;
						while (true)
						{
							char* temp = GenerateAutoId(uniqeNum);
							if (!isIdTaken(temp))
							{
								elements.AddAttributeToLastUnclosedEl("id", temp);
								addId(temp);
								delete[] temp;
								break;
							}
							uniqeNum++;
							delete[] temp;
						}
					}

					elementHaveId = false;
				}
				
				isGettingAtrValue = false;
				cursor = 0;
				textLenghtCapacity = 30;
				delete[] attributeName;
				delete[] attributeValue;
				if (isGettingAtrName)
				{
					textLenghtCapacity = 30;
					attributeName = new char[textLenghtCapacity];
				}
				continue;
			}
			if (cursor == textLenghtCapacity)
				attributeValue = XmlObject::ResizeString(attributeValue, textLenghtCapacity);
			attributeValue[cursor] = c;
			cursor++;
		}
		else if (isGettingElementText)
		{
			if (c=='<')
			{
				elementText[cursor] = '\0';
				elements.AddTextToLastUnclosedEl(elementText);
				delete[] elementText;
				cursor = 0;
				textLenghtCapacity = 30;
				isGettingElementText = false;
				i--;// за да хванем скобката;
				continue;
			}
			if (cursor == textLenghtCapacity)
				elementText = XmlObject::ResizeString(elementText, textLenghtCapacity);
			elementText[cursor] = c;
			cursor++;
		}
		else
		{


			if (c == '<')
			{
				elementName = new char[textLenghtCapacity];
				isGettingElementName = true;
			}
			else if (isalpha(c) || isdigit(c))
			{
				isGettingElementText = true;
				elementText = new char[textLenghtCapacity];
				i--; //при слеващото влизане в цикъла да хванем и този символ
			}
		}
	}
}
bool XmlFile::isFailed()
{
	return isFail;
}
const char* XmlFile::ToString()
{
	if (isModified)
	{
		CreateString();
	}
	isModified = false;
	return string;
}
void XmlFile::CreateString()
{
	delete[] string;
	const char* temp = elements.ToString();
	int len = strlen(temp);
	string = new char[len + 1];
	strcpy(string, temp);
	string[len] = '\0';
}
const char* XmlFile::Select(const char* id, const char* key)
{
	const char* result = elements.GetAttributeValueByOtherAttribute("id", id, key);
	if (result == nullptr)
		return "";
	
	return result;
}
bool XmlFile::Set(const char* id, const char* key, const char* value)
{
	
	bool isSuccesfull= elements.SetAttributeValueByOtherAttribute("id", id,key, value);
	if (isSuccesfull)
		isModified = true;
	return isSuccesfull;
}
const char* XmlFile::Text(const char* id)
{
return elements.GetElementTextByAttribute("id", id);
}
bool XmlFile::Delete(const char* id, const char* key)
{

	bool isSuccesfull = elements.DeleteAttributeByAttribute("id", id, key);
	if (isSuccesfull)
		isModified = true;
	return isSuccesfull;
}
bool XmlFile::Save(const char* fileName)
{
	std::ofstream fileToOutPut(fileName);
	if (!fileToOutPut.is_open()) {
		
		return false;
	}
	fileToOutPut << ToString();

	if (fileToOutPut.good())
	{
		fileToOutPut.close();
		return true;
	}

	else 
	{
		fileToOutPut.close();
		return false;
	}
}
bool XmlFile::Save()
{
	return Save(contentFileSource);
}
bool XmlFile::AddChild(const char* id, const char*name, const char* text)
{
	bool isSuccesfull = elements.AddChildToElement("id", id, name, text);
	if (isSuccesfull)
		isModified = true;
	return isSuccesfull;
}
const char* XmlFile::Children(const char* id)
{
	const char* result = elements.GetChildrenString("id", id);
	if (result == nullptr)
		return ""; // or messege for error ?
	return result;
}
const char* XmlFile::Child(const char* id,const int n)
{
	const char* result = elements.GetNthChildString("id", id,n);
	if (result == nullptr)
		return ""; // or messege  again...
	return result;
}