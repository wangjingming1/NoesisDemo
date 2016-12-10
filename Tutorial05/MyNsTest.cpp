﻿#pragma once
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
	Button *btn = FindName<Button>("Button1");
	btn->MouseDown() += MakeDelegate(this, &MyNsTest::myMouseButtonDown);
	btn->MouseUp() += MakeDelegate(this, &MyNsTest::myMouseButtonUp);
	btn->MouseMove() += MakeDelegate(this, &MyNsTest::myMouseButtonMove);
}

void MyNsTest::myMouseButtonDown(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e) {
	Canvas* canvas;
	Noesis::Point p = canvas->PointFromScreen(e.position);
	
	printf("aaaaaa");
}

void MyNsTest::myMouseButtonUp(BaseComponent* sender, const  Noesis::Gui::MouseButtonEventArgs& e){

}

void MyNsTest::myMouseButtonMove(BaseComponent* sender, const  Noesis::Gui::MouseEventArgs& e) {

}


MyNsTest::~MyNsTest(){
}
//MARK：/////////////////////////////////////////////////
DataObj::DataObj(NsString text, NsString pic) :
	text_(text), pic_(pic)
{	
	Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("image/1.jpg");
	auto x = image->GetDpiX();
	auto y = image->GetDpiY();
	auto width = image->GetWidth();
	auto height = image->GetHeight();
	FILE *f;
	fopen_s(&f, "resource/image/1.jpg", "rb");
	auto buffer_size = fseek(f, 0, SEEK_END);
	rewind(f);
	NsByte * buffer = static_cast<NsByte *>(malloc(sizeof(unsigned char)*buffer_size));
	fread(buffer, 1, buffer_size, f);
	//Noesis::Ptr<Noesis::BitmapSource> source = Noesis::BitmapSource::Create(
		//width, height, x, y, buffer, buffer_size, width / 8);
	brush_ = *new Noesis::ImageBrush(image.GetPtr()/*source.GetPtr()*/);
};

DataModel3::~DataModel3() {
	
}