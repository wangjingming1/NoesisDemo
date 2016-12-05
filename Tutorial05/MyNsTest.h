#include <NoesisGUI.h>
#include <vector>
class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	Noesis::Grid *gridTop_;
	std::vector<std::string> gridTopData_;
	void reloadView();
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};

class DataObj : public Noesis::BaseComponent
{
public:
	DataObj() {};
	~DataObj() {};
	DataObj(NsString text, NsString pic) :
		text_(text), pic_(pic) {};
private:
	NS_IMPLEMENT_INLINE_REFLECTION(DataObj, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataObj");
		NsProp("Text", &DataObj::text_);
		NsProp("Pic", &DataObj::pic_);
	}
	NsString text_;
	NsString pic_;
};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3() 
	{
		dataObjs_ = *new Noesis::ObservableCollection<DataObj>;
		NsString picName = "image/1.jpg";
		for (int i = 0; i < 20; i++) {
			Noesis::Ptr<DataObj> dataObj = *new DataObj("1", picName);
			dataObjs_->Add(dataObj.GetPtr());
		}
	};
	~DataModel3();
private:
	Noesis::Ptr<Noesis::ObservableCollection<DataObj>> dataObjs_;
	NS_IMPLEMENT_INLINE_REFLECTION(DataModel3, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel3");
		NsProp("DataObjs", &DataModel3::dataObjs_);
	}
};