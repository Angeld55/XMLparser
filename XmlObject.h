class XmlObject
{
protected:
	char* type; /// За елемент -> <person>Ivan</person> person  ,за атрибут id="1" ->id
	char* text; /// За елемент -> <person>Ivan</person> Ivan  ,за атрибут id="1" ->1
	char* string; //стринг на Обекта в XmlObject
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