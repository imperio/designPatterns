#include <iostream>
#include <string>
#include <list>

using namespace std;

class Alarm{
public:
	Alarm(){
		description="Alarm";}
	void activate(){cout<<"alarm is activated"<<endl;}
	void deactive(){cout<<"alarm is deacticated"<<endl;}
	void ring(){cout<<"alarm ringing"<<endl;}
	void stopRing(){cout<<"alarm stop ringing"<<endl;}
private:
	string description;
};

class Camera{
public:
	Camera(){
		description="Camera";
}
	void rotate(int t){
		cout<<"camera is rotating with "<<t<<"degrees"<<endl;}
	void turnOff(){
		cout<<"camera off"<<endl;}
	void turnOn(){
		cout<<"cameras on"<<endl;}
private:
	string description;
};

class Light{
private:
	bool bulb;
	string description;
public:
    Light(){
		description="Light";
		bulb=true;}
    void ChangeBulb(){
		if(bulb==false)
			cout<<"change first bulb"<<endl;}
	void turnOff(){
		cout<<"light off"<<endl;}
	void turnOn(){
		cout<<"light on"<<endl;}

};
class PIRSensor{
public:
	PIRSensor(){
		description="PIR Sensor";}
	void activate(){
		cout<<"sensors are on"<<endl;}
	void deactivate(){
		cout<<"sensors are off"<<endl;}
	void trigger(){
		activate();}
private:
	string description;
	
};


class HomeSecurityFacade{
private:
	Alarm* alarm;
	Camera* camera;
	Light* light;
	PIRSensor* pirsensor;
public:
	HomeSecurityFacade(Alarm *a,Camera *c,Light *l,PIRSensor *p){
		alarm=a;
		camera=c;
		light=l;
		pirsensor=p;}

	void activeWholeSystem(){
		alarm->activate();
		camera->turnOn();
		light->turnOn();
		pirsensor->activate();}

	void deactiveWholeSystem(){
		alarm->deactive();
		camera->turnOff();
		light->turnOff();
		pirsensor->deactivate();}


};

int main(){
	/*ayrý ayrý idare etmek icin
	list<PIRSensor*> sensors[4];
	list<Light*> lights[3];
	list<Camera*> cameras[2];*/

	Alarm* a=new Alarm();
	Camera* c=new Camera();
	Light* l=new Light();
	PIRSensor* p=new PIRSensor();

	HomeSecurityFacade *homesecurity=new HomeSecurityFacade(a,c,l,p);

	homesecurity->activeWholeSystem();
	cout<<endl;
	homesecurity->deactiveWholeSystem();

	system("pause");
	return 0;
}