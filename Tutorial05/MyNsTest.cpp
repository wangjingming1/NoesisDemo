#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include <string>
#include "Include\NsGui\Style.h"
#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\ColumnDefinition.h"

using namespace Noesis;

MyNsTest::MyNsTest(){
	Noesis::GUI::LoadComponent(this, "wangjingming.xaml");
	std::string str = "title";
	for (int i = 0; i < 20; i++) {
		gridTopData_.push_back(str + std::to_string(i));
	}
	reloadView();
}
//https://msdn.microsoft.com/zh-cn/library/vs/alm/ms752271(v=vs.110).aspx
void MyNsTest::reloadView(){
	picPanel_ = FindName<StackPanel>("PicPanel");
	Noesis::Gui::UIElementCollection* collection = picPanel_->GetChildren();
	Style *style = GetResources()->FindName<Style>("ImageCellStyle");

	for (int i = 0; i < gridTopData_.size(); i++) {
		Ptr<Button> btn = *new Button();
		btn->SetStyle(style);
		btn->MouseDown() += MakeDelegate(this, &MyNsTest::myMouseButtonDown);
		btn->MouseUp() += MakeDelegate(this, &MyNsTest::myMouseButtonUp);
		btn->MouseMove() += MakeDelegate(this, &MyNsTest::myMouseButtonMove);
		collection->Add(btn.GetPtr());
	}
	Button *btn = FindName<Button>("Button1");
	
}

void MyNsTest::myMouseButtonDown(Noesis::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e) {
	canvas_ = FindName<Canvas>("movableButtonCanvas");
	//Noesis::Point p = canvas->PointFromScreen(e.position);
	Button *btn = (Button *)sender;
	originPoint_ = Point(canvas_->GetLeft(btn), canvas_->GetTop(btn));
	canvas_->SetLeft(btn, e.position.x - btn->GetWidth());
	canvas_->SetTop(btn, e.position.y - btn->GetHeight());
	
	Button *movableButton = FindName<Button>("movableButton");
	movableButton->SetOpacity(1.0);
	canvas_->SetLeft(movableButton, e.position.x - movableButton->GetWidth());
	canvas_->SetBottom(movableButton, e.position.y - btn->GetHeight() / 2 - 20 - movableButton->GetHeight());
	//btn->transfrm
}

void MyNsTest::myMouseButtonMove(BaseComponent* sender, const  Noesis::Gui::MouseEventArgs& e) {


	Button *btn = (Button *)sender;
	canvas_->SetLeft(btn, e.position.x - btn->GetWidth());
	canvas_->SetTop(btn, e.position.y - btn->GetHeight());

	Button *movableButton = FindName<Button>("movableButton");
	canvas_->SetLeft(movableButton, e.position.x - movableButton->GetWidth());
	canvas_->SetBottom(movableButton, e.position.y - btn->GetHeight() / 2 - 20 - movableButton->GetHeight());
}

void MyNsTest::myMouseButtonUp(BaseComponent* sender, const  Noesis::Gui::MouseButtonEventArgs& e){
	Button *btn = (Button *)sender;
	canvas_->SetLeft(btn, originPoint_.x);
	canvas_->SetTop(btn, originPoint_.y);

	Button *movableButton = FindName<Button>("movableButton");
	movableButton->SetOpacity(0);
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