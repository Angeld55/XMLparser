#include "XmlFile.h"
#include "Element.h"
#include <iostream>
#include <fstream>
void printMenu()
{
	std::cout << "0 -> Open" << std::endl;
	
		std::cout << "1 -> Save" << std::endl;
		std::cout << "2 -> Save as" << std::endl;
		std::cout << "3 -> Print" << std::endl;
		std::cout << "4 -> Select" << std::endl;
		std::cout << "5 -> Set" << std::endl;
		std::cout << "6 -> Children" << std::endl;
		std::cout << "7 -> Child" << std::endl;
		std::cout << "8 -> Text" << std::endl;
		std::cout << "9 -> Delete" << std::endl;
		std::cout << "10 -> NewChild" << std::endl;
		std::cout << "11 -> Exit without saving" << std::endl;
	
}
int main()
{

	//char d[30];
	//char c[30];
	//std::cin >> d >> c;
	//
	int input=-1;
	/*std::cin >> input;*/
	XmlFile* file = nullptr;

	bool working = true;
	bool openedFile = false;
	printMenu();
	while (working)
	{
	
		std::cout << "Your command:" << std::endl;
		std::cin.clear();
		std::cin >> input;
	
		
		switch (input)
		{
		case 0:
		{
				  char fileName[50];
				  std::cout << "Enter the name of the file:" << std::endl;
				  std::cin.clear();
				  std::cin >> fileName;
				  if (file != nullptr)
					  delete file;
				  file = new XmlFile(fileName);
				  if (file->isFailed())
					  std::cout << "Error while opening file" << std::endl;
				  else
				  {
					  std::cout << "File succesfully opened" << std::endl;
					  openedFile = true;
				  }
				  break;
		}

		case 1:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }

				  bool isSucces = file->Save();
				  isSucces = file->Save();
				  if (isSucces)
					  std::cout << "File was succesfully saved" << std::endl;
				  else
					  std::cout << "Error saving file" << std::endl;


				  break;
		}
		case 2:
		{

				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  char fileName[50];
				  std::cout << "Please enter the destination file:" << std::endl;
				  std::cin.clear();
				  std::cin >> fileName;
				  bool isSucces = file->Save(fileName);
				  if (isSucces)
					  std::cout << "File was succesfully saved" << std::endl;
				  else
					  std::cout << "Error saving file" << std::endl;
				  break;
		}
		case 3:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  const char* text = file->ToString();
				  std::cout << text << std::endl;
				  printMenu();
				  break;
		}
		case 4:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  std::cout << "Enter ID of element and attribute key:" << std::endl;
				  char id[50];
				  char key[50];
				  std::cin.clear();
				  std::cin >> id >> key;
				  std::cout << std::endl;
				  const char* select = file->Select(id, key);
				  if (strcmp(select, "") == 0)
					  std::cout << "No matches";
				  else
						std::cout << select << std::endl;
				  break;
		}
		case 5:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  std::cout << "Enter ID of element and attribute key and the new attribute value:" << std::endl;
				  char id[50];
				  char key[50];
				  char value[50];
				  std::cin.clear();
				  std::cin >> id >> key >> value;
				  bool isSucces = file->Set(id, key, value);
				  if (isSucces)
					  std::cout << "Attribute value succesfully changed" << std::endl;
				  else
					  std::cout << "No such element/attribute found!" << std::endl;
				  break;
		}
		case 6:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  char id[50];
				  std::cout << "Enter ID the of element:" << std::endl;
				  std::cin.clear();
				  std::cin >> id;
				  const char* children = file->Children(id);
				  if (strcmp(children, "")==0)
				  {
					  std::cout << "No such element found/The element have no childen" << std::endl;
				  }
				  else
				  {
					  std::cout << children << std::endl;
				  }
				  break;
		}
		case 7:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  char id[50];
				  int n;
				  std::cout << "Enter ID of the element and the child number:" << std::endl;
				  std::cin.clear();
				  std::cin >> id >> n;
				  const char* child = file->Child(id, n);
				  if (strcmp(child, "")==0)
				  {
					  std::cout << "No such element found" << std::endl;
				  }
				  else
				  {
					  std::cout << child << std::endl;
				  }
				  break;
		}
		case 8:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  std::cout << "Enter ID of the element:" << std::endl;
				  char id[50];
				  std::cin.clear();
				  std::cin >> id;
				  const char* text = file->Text(id);
				  if (strcmp(text, "")==0)
				  {
					  std::cout << "No such element found" << std::endl;
				  }
				  else
				  {
					  std::cout << text << std::endl;
				  }
				  break;
		}
		case 9:
		{
				  if (!openedFile)
				  {
					  std::cout << "No file is opened" << std::endl;
					  break;
				  }
				  std::cout << "Enter ID  the of element and the key of the attribute to be deleted:" << std::endl;
				  char id[50];
				  char key[50];
				  std::cin.clear();
				  std::cin >> id >> key;
				  bool isSucces = file->Delete(id, key);
				  if (isSucces)
					  std::cout << "Attribute succesfully deleted" << std::endl;
				  else
					  std::cout << "No such element found" << std::endl;
				  break;
		}
		case 10:
		{
				   if (!openedFile)
				   {
					   std::cout << "No file is opened" << std::endl;
					   break;
				   }
				   char id[50];
				   char name[50];
				   char text[50];
				   std::cout << "Enter ID  the of element and the key and the text to the new element:" << std::endl;
				   std::cin.clear();
				   std::cin >> id >> name >> text;
				   bool isSucces = file->AddChild(id, name, text);
				   if (isSucces)
					   std::cout << "Element succesfully added!" << std::endl;
				   else
					   std::cout << "Error while adding new element!" << std::endl;
				   break;
		}
		case 11:
		{
				   working = false;
				   break;
		}
		default:
		{std::cout << "Invalid operation" << std::endl;
		break;
		}
		}
	}








	// TODO fix reading 

}