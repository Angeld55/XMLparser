class XmlObject
{
protected:
	char* type; /// �� ������� -> <person>Ivan</person> person  ,�� ������� id="1" ->id
	char* text; /// �� ������� -> <person>Ivan</person> Ivan  ,�� ������� id="1" ->1
	char* string; //������ �� ������ � XmlObject
	int stringLenght;
	void Free();
	void CopyFrom(const XmlObject&);
	
public:
	XmlObject(const char*,const char*);
	XmlObject(const XmlObject&);
	virtual ~XmlObject();
	XmlObject& operator=(const XmlObject&);
	const char* ToString();
	const char* GetKey();
	const char* GetValue();
	virtual void CreateString()= 0;
	//int getStringLenght();
	static char* ResizeString(char*, int& capacity);

};