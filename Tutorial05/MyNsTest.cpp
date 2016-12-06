#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include <string>
#include "Include\NsGui\Style.h"
#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\ColumnDefinition.h"

using namespace Noesis;

MyNsTest::MyNsTest(){
	Noesis::GUI::LoadComponent(this, "addChuguiView2.xaml");
	std::string str = "title";
	for (int i = 0; i < 20; i++) {
		gridTopData_.push_back(str + std::to_string(i));
	}
	reloadView();
}
//https://msdn.microsoft.com/zh-cn/library/vs/alm/ms752271(v=vs.110).aspx
void MyNsTest::reloadView(){
	gridTop_ = FindName<Grid>("GridTop");
	gridTop_->GetRowDefinitions()->Clear();
	gridTop_->GetColumnDefinitions()->Clear();
	
	Style *style = GetResources()->FindName<Style>("ButtonStyle");
	Ptr<RowDefinition> row = *new RowDefinition();
	row->SetHeight(45);
	gridTop_->GetRowDefinitions()->Add(row.GetPtr());

	for (int i = 0; i < gridTopData_.size(); i++) {
		Ptr<ColumnDefinition> column = *new ColumnDefinition();
		column->SetWidth(80);
		gridTop_->GetColumnDefinitions()->Add(column.GetPtr());

		Ptr<Button> btn = *new Button();
		btn->SetStyle(style);
		btn->SetContent(gridTopData_[i].c_str());

		gridTop_->SetRow(btn.GetPtr(), 0);
		gridTop_->SetColumn(btn.GetPtr(), i);
		
		gridTop_->GetChildren()->Add(btn.GetPtr());
	}

}

MyNsTest::~MyNsTest(){
}
//MARK：/////////////////////////////////////////////////
DataObj::DataObj(NsString text, NsString pic) :
	text_(text), pic_(pic)
{	
	FILE *fp = fopen(pic_.c_str(), "r");
	if (fp) {
		Ptr<FileStream> fs = *new FileStream(fp);// File::OpenStream(pic_.c_str());
		unsigned char *byData;
		//NsChar *byData = "";
		fs->Read(byData, fs->GetLength());
		image_ = *new BitmapImage(byData);
	
		//delete []byData;
		fclose(fp);
	}
};

DataModel3::~DataModel3() {
	
}