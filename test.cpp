#include <iostream>
using std::cout;
using std::endl;
#include <cstdint>
using std::uint32_t;

class Base{
public:
	Base(uint32_t num)/* : num_(170)*/{
		//cout << "The number is " << num_ << endl;
	};
	virtual ~Base() = default;

	virtual uint32_t number() = 0;
/*private:
	uint32_t num_;*/
};

class Derived : public Base/*<number>*/ {
public:
	Derived(uint32_t num) : Base(num), num_(num) {};
	virtual ~Derived() = default;

	virtual uint32_t number() override;

private:
	uint32_t num_;
};

// template<uint32_t number>
// Derived<number>::Derived(){
//
// }


// template<uint32_t number>
// Derived<number>::~Derived(){}
uint32_t Derived::number() { return num_;}

class test : public Derived {
		public:
			test(uint32_t num) : Derived(num), num_(21), num1_(14) {};
			virtual ~test(){};
		 	uint32_t number(bool cond){
			 if(cond == true){
				 return num_;
			 } else {
				 return num1_;
			 }
		 };

	 private:
		 uint32_t num_;
		 uint32_t num1_;
};

int main(){
	test foo(15);
	Derived *test1 = &foo;
	cout << test1->number();
	return 1;
}
