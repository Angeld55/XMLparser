#include "ElementsCollection.h"
#include <iostream>
#include <fstream>
class XmlFile
{

//	char* id;
//public:
//	char* Select(char* id, char* key);///returns attribute by ID of element, key of attribute;
//
public:
	XmlFile(char*);
	XmlFile(const XmlFile& other);
	XmlFile& operator=(const XmlFile& other);
	~XmlFile();
	bool isFailed();
	const char* ToString();
	ElementsCollection elements;

	const char* Select(const char* id, const char* key);
	bool Set(const char* id, const char* key, const char* value);
	const char* Text(const char* id);
	bool Delete(const char* id, const char* key);
	bool Save();
	bool Save(const char*);
	bool AddChild(const char*, const char*, const char*);
	const char* Children(const char*);
	const char* Child(const char*,const int);
private:
	char* file;
	char* string;
	char* contentFileSource;
	char** ids;
	bool isFail;
	void Free();
	void CopyFrom(const XmlFile& other);
	void AddFileContentToCollection();
	void ReadFile(std::ifstream&);
	void CreateString();
	
	
	bool isIdTaken(const char*);
	bool isModified;

	char* ConcatinateUniqeCharsToId(char* id, int num);
	char* GenerateAutoId(int num);
	
	void addId(char* id);
	int idsCapacity;
	int idsCount;

	int fileStringLength;
	

};