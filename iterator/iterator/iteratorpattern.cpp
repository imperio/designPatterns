#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Book;

template <class T>
class Iterator{
public:
	virtual bool hasNext()=0;
	virtual T* next()=0;
};

class ABookStoreIterator:public Iterator<Book>{
private:
	vector<Book*>books;
	int index;
public:
	ABookStoreIterator(vector<Book*> b):books(b),index(0){};
	Book* next(){
		Book* b=books[index];
		index++;
		return b;}
	bool hasNext(){
		if(index >= books.size() ) return false;
		else return true;}
};

class BBookStoreIterator:public Iterator<Book>{
private:
	vector<Book*>books;
	int index;
public:
	BBookStoreIterator(vector<Book*> b):books(b),index(0){};
	Book* next(){
		Book* b=books[index];
		index++;
		return b;}
	bool hasNext(){
		if(index>= books.size() ) return false;
		else return true;}
};

class Book{
private:
	string author;
	string title;
	double price;
public:
	Book(string a,string t,double p):author(a),title(t),price(p){}
	string getTitle(){return title;}
	void setTitle(string t){title=t;}
	string getAuthor(){return author;}
	void setAuthor(string a){author=a;}
	double getPrice(){return price;}
	void setPrice(double pr){price=pr;}
	void print(){
		cout<<"Title of the book: "<<title<<endl
			<<"Author of the book: "<<author<<endl
			<<"Price of the book: "<<price<<endl;}
};


class BookStore{
public:
	virtual void addBook(Book*)=0;
};


class ABookStore:public BookStore{
private:
	vector<Book*> books;
public:
	ABookStore(){
		Book *b1=new Book("Victor Hugo","Sefiller",4.99);
		Book *b2=new Book("Adam Fawer","Olasiliksiz",15.99);
		Book *b3=new Book("Stieg Larsson","Ejderha Dovmeli Kiz",25.99);

		addBook(b1);
		addBook(b2);
		addBook(b3);

	}
	void addBook(Book* book){
		books.push_back(book);}

	Iterator<Book>* createIterator(){
		return (Iterator<Book>*) (new ABookStoreIterator(books));}

};

class BBookStore:public BookStore{
private:
	vector<Book*> books;
public:
	BBookStore(){
		Book *b1=new Book("Dostoyevski","Ezilenler",5.99);
		Book *b2=new Book("J.K.Rowling","H.P. ve Felsefe Tasi",19.99);
		Book *b3=new Book("J.K.Rowling","H.P. ve Sirlar Odasi",19.99);

		addBook(b1);
		addBook(b2);
		addBook(b3);

	}
	void addBook(Book* book){
		books.push_back(book);}

	Iterator<Book>* createIterator(){
		return (Iterator<Book>*) (new BBookStoreIterator(books));}

};

class WebStore{
private:
	ABookStore* abook;
	BBookStore* bbook;
public:
	WebStore(ABookStore* a,BBookStore* b):abook(a),bbook(b){}
	void printBooks(){
		Iterator<Book>* aiterator=abook->createIterator();
		Iterator<Book>* biterator=bbook->createIterator();
		cout<<"...BOOKS..."<<endl<<"**A Book Store**"<<endl;
		printBooks(aiterator);
		cout<<endl;
		cout<<"**B Book Store**"<<endl;
		printBooks(biterator);
	}

	/*double getPrice(string tit){
		Iterator<Book>* aiterator=abook->createIterator();
		Iterator<Book>* biterator=bbook->createIterator();
		getPrice(aiterator,tit);
		getPrice(biterator,tit);}*/


private:
	void printBooks(Iterator<Book>* iter){
		while(iter->hasNext()){
			Book* bo=(Book*) (iter->next() );
			bo->print();
		    }
	}

  /*double getPrice(Iterator<Book>*iter,string titl){
		while(iter->hasNext()){
			Book *bo=(Book*)(iter->next());
			if(bo->getTitle()==titl)
				return bo->getPrice();}} */


};

int main(){

	ABookStore *abook=new ABookStore();
	BBookStore *bbook=new BBookStore();
	WebStore *web=new WebStore(abook,bbook);

	web->printBooks();

	//cout<<web->getPrice("Sefiller");

	system("pause");
	return 0;
}