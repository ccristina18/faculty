#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

class carti {
protected:
	string autor;
	string titlu;
	int imprumutat;
public:
	carti(string a, string t, int i)
	{
		autor = a;
		titlu = t;
		imprumutat = i;
	}

	virtual void display() {};
};


class tehnice : public carti {
	int nr_ex;
	string limba;
	int an_ap;
	tehnice *head;
	tehnice *next;
public:
	tehnice(string a, string t, int i, int nr, string l, int an) :carti(a, t, i) {
		head = NULL;
		nr_ex = nr;
		limba = l;
		an_ap = an;
	}

	void display();
	void adaugare();
};

void tehnice::adaugare()
{
	int imprumutat, nr_ex, an_ap;
	string autor, titlu, limba;

	cin.get();
	cout << "autor=";
	getline(cin, autor);
	cout << "titlu=";
	getline(cin, titlu);
	cout << "imprumutat: (0/1)";
	cin >> imprumutat;
	cout << "nr exemplare=";
	cin >> nr_ex;
	cin.get();
	cout << "limba=";
	getline(cin, limba);
	cout << "an aparitie=";
	cin >> an_ap;

	tehnice *p = new tehnice(autor, titlu, imprumutat, nr_ex, limba, an_ap);
	p->next = head;
	head = p;
}

void tehnice::display()
{
	tehnice *p = head;
	while (p != NULL)
	{
		cout << "Autor:" << p->autor << endl;
		cout << "Titlu:" << p->titlu << endl;
		cout << "Imprumutat:" << p->imprumutat << endl;
		cout << "Nr exemplare:" << p->nr_ex << endl;
		cout << "Limba:" << p->limba << endl;
		cout << "An aparitie:" << p->an_ap << endl;
		p = p->next;
	}
}

int main()
{
	int opt;
	tehnice *c = new tehnice("", "", 0, 0, "", 0);


	while (1)
	{
		cout << "1.Adaugare carte tehnica" << endl;
		cout << "2.Afisare carte tehnica" << endl;
		cout << "0.Iesire" << endl;
		cout << "dati optiune:";
		cin >> opt;

		switch (opt)
		{
		case 1:c->adaugare();
			break;

		case 2:c->display();
			break;

		case 0:exit(0);
			break;
		}
	}


	return 0;
}