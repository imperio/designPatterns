#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Graphic{
public:
	
	virtual void draw(){cout<<"---"<<endl;}
	virtual void add(Graphic *){cout<<"---"<<endl;}
	virtual void remove(Graphic *){cout<<"---"<<endl;}
	virtual Graphic* getChild(int){cout<<"---"<<endl; return NULL;}
};

class Line:public Graphic{
public:
	void draw(){cout<<"A Line is drawn"<<endl;}

};

class Rectangle:public Graphic{
public:
	void draw(){cout<<"A Rectangle is drawn"<<endl;}
};

class Text:public Graphic{
public:
	void draw(){cout<<"A Text is drawn"<<endl;}
};

class Picture:public Graphic{
private:
	vector<Graphic*> graphics;
public:
	void draw(){
		cout<<"Picture:"<<endl;
		for(vector<Graphic*>::iterator iter=graphics.begin();graphics.end()!=iter;iter++){
         Graphic *gr=*iter;
		 gr->draw();}
	}
    void add( Graphic * gr){
		graphics.push_back(gr);
	}
	void remove(Graphic * gr){
		/*vector<Graphic*>::iterator i=
			std::remove(mylist.begin(),mylist.end(),gr);
		mylist.erase(i,mylist.end());*/
	}
	Graphic* getChild(int t){
		return graphics[t];
	}

};


int main(){
	Graphic *picture=new Picture();
	Graphic *line=new Line();
	Graphic *rectangle= new Rectangle();
	Graphic *text=new Text();

	picture->add(line);
	picture->add(rectangle);
	picture->add(text);
    
	picture->draw();

	system("pause");
	return 0;
}
