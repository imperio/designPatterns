#include <iostream>
#include <string>
using namespace std;

class AbstractCheckIn{
public:
	AbstractCheckIn(){}
	virtual string getSuitableRooms()=0;
};

class ActualCheckIn:public AbstractCheckIn{
public:
	ActualCheckIn(){
	st="actual check in with the requirements:\n";}
	string getSuitableRooms(){
		return st;}
private:
	string st;
};

class CheckInDecorator:public AbstractCheckIn{
public:
	CheckInDecorator(){}
	virtual string getSuitableRooms()=0;
};

class AccessibilityCheckIn:public CheckInDecorator{
public:
	AccessibilityCheckIn(AbstractCheckIn *a,string need){
		aci=a;
		AccessibilityNeeds=need;}
	string getSuitableRooms(){
		return aci->getSuitableRooms()+" ,"+AccessibilityNeeds;}
private:
	AbstractCheckIn *aci;
	string AccessibilityNeeds /*blindness or wheelcahirs*/;};

class CommunicationCheckIn:public CheckInDecorator{
public:
	CommunicationCheckIn(AbstractCheckIn *a,string need){
		aci=a;
		CommunicationNeeds=need;}
	string getSuitableRooms(){
		return aci->getSuitableRooms()+" ,"+CommunicationNeeds;}
private:
	AbstractCheckIn *aci;
	string CommunicationNeeds /*internet or broadband*/;};

class FamilyCheckIn:public CheckInDecorator{
public:
	FamilyCheckIn(AbstractCheckIn *a){
		aci=a;
		Needs=",Family size";}
	string getSuitableRooms(){
		return aci->getSuitableRooms()+" "+Needs;}
private:
	AbstractCheckIn *aci;
	string Needs;};



int main(){

	AbstractCheckIn *aci=new ActualCheckIn;
	aci=new CommunicationCheckIn(aci,"Internet access");
	aci=new AccessibilityCheckIn(aci," Wheel chair");
	aci=new FamilyCheckIn(aci);

	cout<<aci->getSuitableRooms()<<endl;

	system("pause");
	return 0;

}






