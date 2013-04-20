#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <vector>

using namespace std;

//Receivers

class Light{
private:
	string location;
public:
	Light(const string location):location(location){}
	void turnOn() const{cout<<location<<" light is on"<<endl;}
	void turnOff() const{cout<<location<<" light is off"<<endl;}
	void changeBulb () const{cout<< "change the bulb of"<<location<<"'s light!"<<endl;}
};

class Camera{
private:
	string location;
	int rotation;
public:
	Camera(string location,int rotation):location(location),rotation(rotation){}
	void turnOn() const{cout<<location<<" camera is on"<<endl;
	rotate();}
	void turnOff() const{cout<<location<<" camera is off"<<endl;}
	void rotate() const{cout<<location<<" camera is rotating with"<<rotation<<" degrees"<<endl;}};

class Alarm{
private:
	string location;
public:
	Alarm(string location):location(location){}
	void activate() const {cout<<location<<" alarm activated"<<endl;
	ring();}
	void deactivate() const{cout<<location<<" alarm deactivated"<<endl;
	stopRing();}
	void ring() const{cout<<location<<" alarm is ringing"<<endl;}
	void stopRing() const{cout<<location<<" is stop ringing"<<endl;}
};

class PIRSensor{
private:
	string location;
	bool sensor; //if there is a person, sensor is true. initially sensor is false
public:
	PIRSensor(string location,bool sensor):location(location),sensor(false){}
	void activate()const{cout<<location<< " pir sensor is activated"<<endl;}
	void deactivate()const{cout<<location<< " pir sensor is deactivated"<<endl;}
	void trigger()const{
		if(sensor)
		   activate();
		else
		   deactivate();}
};

//Command

class Command{
private:
	Command(const Command&);
	void operator=(const Command&);
protected:
	Command(){}
public:
	virtual ~Command()=0{}
	virtual void execute() const=0; };

//Concrete Command
class CameraOnCommand:public Command{
private:
	const Camera* camera;
public:
	CameraOnCommand(const Camera* camera) : camera(camera){
	assert(camera);}
	void execute()const{camera->turnOn();}
};

class CameraOffCommand:public Command{
private:
	const Camera* camera;
public:
	CameraOffCommand(const Camera* camera) : camera(camera){
	assert(camera);}
	void execute()const{camera->turnOff();}
};

/*class CameraRotateCommand: public Command{
private:
	const Camera* camera;
public:
	CameraRotateCommand(const Camera* camera) : camera(camera){
		assert(camera);}
	void execute()const{camera->rotate();}
};
*/
class LightOnCommand:public Command{
private:
	const Light* light;
public:
	LightOnCommand(const Light* light): light(light){
		assert(light);}
	void execute()const{light->turnOn();}
};

class LightOffCommand:public Command{
private:
	const Light* light;
public:
	LightOffCommand(const Light* light): light(light){
		assert(light);}
	void execute()const{light->turnOff();}
};

/*class LightChangeCommand:public Command{
private:
	const Light* light;
public:
	LightChangeCommand(const Light* light): light(light){
		assert(light);}
	void execute()const{light->changeBulb();}
};*/

class AlarmActivateCommand:public Command{
private:
	const Alarm* alarm;
public:
	AlarmActivateCommand(const Alarm* alarm):alarm(alarm){
		assert(alarm);}
	void execute()const{alarm->activate();}
};


class AlarmDeactivateCommand:public Command{
private:
	const Alarm* alarm;
public:
	AlarmDeactivateCommand(const Alarm* alarm):alarm(alarm){
		assert(alarm);}
	void execute()const{alarm->deactivate();}
};


class PIRSensorActivateCommand:public Command{
private:
	const PIRSensor* pir;
public:
	PIRSensorActivateCommand(const PIRSensor* pir):pir(pir){
		assert(pir);}
	void execute()const{pir->activate();}
};

class PIRSensorDeactivateCommand:public Command{
private:
	const PIRSensor* pir;
public:
	PIRSensorDeactivateCommand(const PIRSensor* pir):pir(pir){
		assert(pir);}
	void execute()const{pir->deactivate();}
};

class NoCommand:public Command{
public:
	void execute() const{} };

//Macro

class MacroCommand:public Command{
private:
	vector<Command*> commands;
public:
	MacroCommand(vector<Command*> command):commands(command){}
	void execute() const{
		for(int i=0;i< commands.size();i++){
			commands[i]->execute();}}
	};



//Invoker

class RemoteControl{
private:
	static const int SLOTS=4; 
	Command* onCommands[SLOTS];
	Command* offCommands[SLOTS];
	Command* noCommand;

	RemoteControl(const RemoteControl&);
	void operator=(const RemoteControl&);
public:
	RemoteControl(){
		noCommand= new NoCommand();
		for(int i=0;i<SLOTS;i++){
			onCommands[i]=noCommand;
			offCommands[i]=noCommand;}
	}

	~RemoteControl(){
		delete noCommand;}

	void setCommand(int slot,Command* onCommand,Command* offCommand){
		assert(slot<=SLOTS); assert(onCommand);assert(offCommand);
		onCommands[slot]=onCommand;
		offCommands[slot]=offCommand;}

	void onButtonWasPushed(int slot)const{
		assert(slot<=SLOTS);
		onCommands[slot]->execute();}

	void offButtonWasPushed(int slot)const{
		assert(slot<=SLOTS);
		offCommands[slot]->execute();}

    string toString()const {
		stringstream value;
		value<<endl<<"......................Control Panel......................"<<endl<<endl;
		for(int i=0;i<SLOTS;i++){
			value<<"{slot " <<i<<"} ";
			value<<typeid(*onCommands[i]).name();
			value<<"      ";
			value<<typeid(*offCommands[i]).name();
			value<<endl;
		}
		return value.str();
	}
};


	
//Client

int main(){
	RemoteControl *remoteControl=new RemoteControl();

	Light *light=new Light("Bed Room");
	Camera *camera=new Camera("Living Room",45);
	Alarm *alarm=new Alarm("Front Door");
	PIRSensor *pir=new PIRSensor("Bed Room",false);

	LightOnCommand *lightOn=new LightOnCommand(light);
	CameraOnCommand *cameraOn=new CameraOnCommand(camera);
	AlarmActivateCommand *alarmOn=new AlarmActivateCommand(alarm);
	PIRSensorActivateCommand *pirOn=new PIRSensorActivateCommand(pir);

	LightOffCommand *lightOff=new LightOffCommand(light);
	CameraOffCommand *cameraOff=new CameraOffCommand(camera);
	AlarmDeactivateCommand *alarmOff=new AlarmDeactivateCommand(alarm);
	PIRSensorDeactivateCommand *pirOff=new PIRSensorDeactivateCommand(pir);

	vector<Command*> imAtHome;
	imAtHome.push_back(lightOn);
	imAtHome.push_back(cameraOff);
	imAtHome.push_back(alarmOff);
	imAtHome.push_back(pirOff);

	vector<Command*> imNotAtHome;
	imNotAtHome.push_back(lightOff);
	imNotAtHome.push_back(cameraOn);
	imNotAtHome.push_back(alarmOn);
	imNotAtHome.push_back(pirOn);

	MacroCommand *imHomeMacro=new MacroCommand(imAtHome);
	MacroCommand *imNotHomeMacro=new MacroCommand(imNotAtHome);

	remoteControl->setCommand(0,imHomeMacro,imNotHomeMacro);

	cout << remoteControl->toString() << endl<<endl;
	cout<<"---- Pushing Macro on ----"<<endl<<endl;
	remoteControl->onButtonWasPushed(0);
	cout<<"\n---- Pushing Macro off ----"<<endl;
	remoteControl->offButtonWasPushed(0);


	system("pause");
	return 0;
}

