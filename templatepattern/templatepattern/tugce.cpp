#include <iostream>
#include <string>

using namespace std;

class PatternRecognizer{
public:
	virtual void Recognize(){
		capture();
		resize();
		filtering();
		matching();
		detectingPattern();}
protected:
	virtual void capture()=0;
	virtual void filtering()=0;
private:
	void resize(){cout<<"image resizing..."<<endl;}
	void matching(){cout<<"image matching..."<<endl;}
	void detectingPattern(){cout<<"pattern detecting..."<<endl;}
};

class GrayImage:public PatternRecognizer{
public:
	void capture(){
		cout<<"gray image capturing..."<<endl;}
	void filtering(){
		cout<<"gray image filtering..."<<endl;}
};

class ColorImage:public PatternRecognizer{
public:
	void capture(){
		cout<<"color image capturing..."<<endl;}
	void filtering(){
		cout<<"color image filtering..."<<endl;}
};

int main(){

	GrayImage *gray=new GrayImage();
	cout<<"Gray Image Recognizing:"<<endl<<"___________________________"<<endl;
	gray->Recognize();

	cout<<endl<<endl;

	ColorImage *color=new ColorImage();
	cout<<"Color Image Recognizing:"<<endl<<"___________________________"<<endl;
	color->Recognize();

	system("pause");
	return 0;
}
		