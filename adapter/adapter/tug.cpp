#include <iostream>
#include <string>
using namespace std;


class Network{
public:
	Network(){str="network";}
	virtual void open()=0;
	virtual void close()=0;
	virtual void send(string)=0;
	virtual string receive()=0;
protected:
	string str;};


class Ethernet:public Network{
public:
	Ethernet(){str="ethernet";}
	void open(){
	cout<<"ethernet is opened"<<endl;}
	void close(){
	cout<<"ethernet is closed"<<endl;}
	void send(string st){
	cout<<"ethernet sending <"<<st<<"> "<<endl;}
	string receive(){
	return str;}
};

class WaveLAN{
public:
	WaveLAN(){str="waveLAN";}
	void open(){
		cout<<"WaveLAN is opened"<<endl;}
	void write(string st){
		cout<<"WaveLAN writing<"<<st<<">"<<endl;}
	string read(){
		return str;}
private:
	string str;
};

class NetworkAdapter:public Network{
private:
	WaveLAN* wavelan;
public:
	NetworkAdapter(WaveLAN* wave){
		wavelan=wave;}
	void open(){} 
	void close(){}
	void send(string str){
		wavelan->write(str);}
	string receive(){
		return wavelan->read();}
};

class NetworkConnection{
public:
	void setNetwork(Network* network,string type){
		if(type=="ethernet")
			network=new Ethernet();
		if(type=="wavelan")
			network=new NetworkAdapter(wave);}
	void send(string str){cout<<"sending...  "<<str;}
	string receive(){
		return "network connection";}
private:
	WaveLAN *wave;
};

int main(){

	NetworkConnection nc;
	WaveLAN *wave=new WaveLAN();
	Network *net= new NetworkAdapter(wave);
	
	nc.setNetwork(net,"wavelan");
	net->send("tugce");
	cout<<net->receive()<<endl;

	cout<<endl;
	Network *netw=new Ethernet();
	netw->send("hello");
	cout<<netw->receive()<<endl;

	system("pause");
	return 0;
}


