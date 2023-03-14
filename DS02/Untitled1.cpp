#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

class Animal{
	public:
		void getWeight(){
			printf("%d\n",weight);
		}
	protected:
		int weight = 5;
};

class Dog:public Animal{
	public:
		void getWeight(){
			printf("你家狗狗吃太多東西了，體重增加5\n");
			weight+=5;
			printf("%d\n",weight);
		}	
	
};

class Cat: public Animal{
	public:
		void getWeight(){
			printf("你家貓貓要餓死了，體重減7\n");
			weight-=7;
			printf("%d\n",weight); 
		}
};

int main(){
	Dog dog;
	Cat cat;
	dog.getWeight();
	cat.getWeight();
}
