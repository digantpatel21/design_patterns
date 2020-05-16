#include <iostream>

using namespace std;


class pizza {
    private:
        string base;
        int price;

    public:
        void printPizzaConfig() {
            cout<<"base type is: "<<base<< " and prie is : "<<price<<endl;
        }

        virtual void setbase(string) = 0;
        virtual void setprice(int) = 0;
};

class frenhPizza : public pizza {
    public:

        void setbase(string base) override { this->base = base;}
        void setprice(sring base) override { this->base = base;}
};