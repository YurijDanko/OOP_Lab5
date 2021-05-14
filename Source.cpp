#include <iostream>
#include <string>

using namespace std;

enum currency {
	Dollar = 2772,
	Euro = 3301,
};

class trip

{
protected:
	string name;
	int days;
public:
	trip() {
		name = "";
		days = 0;
	}

	trip(string str, int number) :name(str), days(number) {}
	~trip() {}
	string get_name() { return name; }
	int get_days() { return days; }
	virtual int total_price() { return 0; }
	virtual void output() { cout << "Name of city: " << this->get_name() << "\t\tAmount of days: " << this->get_days() << endl; }
};

class rest_abroad : public trip {
private:
	int one_day_price;
	int travel_price;
	currency cur;
public:
	rest_abroad() :trip(), one_day_price(0), travel_price(0), cur(Dollar) {}
	rest_abroad(string str1, int d, int price1, int price2, currency c) : trip(str1, d), one_day_price(price1), travel_price(price2), cur(c) {}
	~rest_abroad() {}
	int day_price() { return one_day_price; }
	int travel_pr() { return travel_price; }
	int total_price() { return ((travel_price + one_day_price * days) * cur / 100); }
	void output() {
		char c[5];
		switch (this->get_currency()) {
		case Dollar:
			strcpy_s(c, "USD");
			break;
		case Euro:
			strcpy_s(c, "EUR");
			break;
		default:
			break;
		}
		cout << "Name of city: " << this->get_name() << "\nDuration: " << this->get_days() << "\nOne day price: " << this->day_price() << " " << c << "\nTravel price: " << this->travel_pr()<< " " << c << "\nTotal price: " << this->total_price() << " UAH" << endl;
	}
	currency get_currency() { return cur; }

	rest_abroad operator=(rest_abroad& obj) {
		this->name = obj.name;
		this->days = obj.days;
		this->one_day_price = obj.one_day_price;
		this->travel_price = obj.travel_price;

		return *this;
	}
};

class bus_tour : public trip {
private:
	int bt_insideprice;
	int bt_insidedur;
	int bt_abroadprice;
	int bt_abroaddur;
	currency cur;
public:
	bus_tour() : trip(), bt_insideprice(0), bt_insidedur(0), bt_abroadprice(0), bt_abroaddur(0), cur(Dollar) {}
	bus_tour(string str1, int bti_price, int bta_price, int bti_dur, int bta_dur, currency c) : trip(str1, bti_dur + bta_dur), 
		bt_insideprice(bti_price), bt_abroadprice(bta_price), bt_insidedur(bti_dur), bt_abroaddur(bta_dur), cur(c){}
	~bus_tour() {}
	int total_price() { return ((bt_abroadprice * bt_abroaddur * cur / 100) + (bt_insideprice * bt_insidedur)); }
	int btin_price() { return bt_insideprice; }
	int btab_price() { return bt_abroadprice; }
	int btin_dur() { return bt_insidedur; }
	int btab_dur() { return bt_abroaddur; }
	currency get_currency() { return cur; }

	void output() {
		char c[5];
		switch (this->get_currency()) {
		case Dollar:
			strcpy_s(c, "USD");
			break;
		case Euro:
			strcpy_s(c, "EUR");
			break;
		default:
			break;
		}
		cout << "Name of city: " << this->get_name() << "\nDuration: " << this->get_days() << "\nOne day price in country: " << this->btin_price() << " UAH" << "\nAmount of days in country: " << this->btin_dur() << "\nOne day price abroad: " << this->btab_price() << " " << c << "\nAmount of days abroad: " << this->btab_dur() << "\nTotal price of bus tour: " << this->total_price() << " UAH" << endl;
	}

	bus_tour operator=(bus_tour& obj) {
		this->name = obj.name;
		this->days = obj.days;
		this->bt_insideprice = obj.bt_insideprice;
		this->bt_abroadprice = obj.bt_abroadprice;
		this->bt_insidedur = obj.bt_insidedur;
		this->bt_abroaddur = obj.bt_abroaddur;

		return *this;
	}
};

void input(trip** p, int n) {
	for (int i = 0; i < n; i++) {
		cout << "Enter City Number " << i + 1 << "\n\n";
		string n;
		int d, d_price, b_price, c, type_of_journey;
		currency cur;
		cout << "Choose type of journey(1 -- Typical Vacation, 2 -- Bus Tour): "; cin >> type_of_journey;
		cout << "Name of city: "; cin >> n;
		cout << "Choose type of currency(1 -- Dollar, 2 -- Euro): "; cin >> c;
		cout << "\n";
		switch (c) {
		case 1:
			cur = Dollar;
			break;
		case 2:
			cur = Euro;
			break;
		}
		if (type_of_journey == 1) {
			cout << "Amount of days: "; cin >> d;
			cout << "One day price: "; cin >> d_price;
			cout << "Bus cost: "; cin >> b_price;

			p[i] = new rest_abroad(n, d, d_price, b_price, cur);
		}
		else if (type_of_journey == 2) {
			int bti_price, bta_price, bti_dur, bta_dur;
			cout << "One day price in country: "; cin >> bti_price;
			cout << "Duration in country: "; cin >> bti_dur;
			cout << "One day price abroad: "; cin >> bta_price;
			cout << "Duration abroad: "; cin >> bta_dur;

			p[i] = new bus_tour(n, bti_price, bta_price, bti_dur, bta_dur, cur);
		}
	}
	cout << "\n\n";
}

void print(trip** a, int b) {
	for (int i = 0; i < b; i++) {
		cout << "City Number - " << i + 1 << ": " << endl;
		a[i]->output();
		cout << endl;
	}
}

void sort_by_price(trip** a, int b) {
	for (int i = 1; i < b; i++) {
		if (a[i]->total_price() > a[i - 1]->total_price()) {
			swap(a[i], a[i - 1]);
		}
	}
}

int main() {
	trip** p;
	int kst;
	cout << "Enter amounts of trips: ";cin >> kst;
	cout << endl;
	p = new trip * [kst];
	input(p, kst);
	cout << "\t\tList of journey:\n\n" << endl;
	print(p, kst);
	cout << "\n\n";
	sort_by_price(p, kst);
	cout << "\t\tSorted list by price:\n\n" << endl;
	print(p, kst);
	return 0;
}


/*Створити базовий клас ПУТІВКА (задаються пункт призначення та тривалість). 
Створити похідний клас ВІДПОЧИНОК ВСЕРЕДИНІ КРАЇНИ (задаються вартість за 1 добу, вартість проїзду). 
Для заданих прикладів путівок обчислити вартість кожної з них, 
впорядкувати путівки за спаданням вартості і обчислити сумарну вартість.*/