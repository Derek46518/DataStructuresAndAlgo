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
			printf("�A�a�����Y�Ӧh�F��F�A�魫�W�[5\n");
			weight+=5;
			printf("%d\n",weight);
		}	
	
};

class Cat: public Animal{
	public:
		void getWeight(){
			printf("�A�a�߿߭n�j���F�A�魫��7\n");
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
