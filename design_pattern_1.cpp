#include <iostream>
#include <string>
#include <vector>


using namespace std;


enum class Color { Red, Green, Blue};
enum class Size { Small, Medium, Large};

struct Product {
    string name;
    Color color;
    Size size;
};


struct ProductFilter {
    typedef vector<Product*> Items;

    static Items by_color(Items items, Color color) {
        Items result;

        for(auto &i : items ) {
            if(i->color == color)
                result.push_back(i);
        }
        return result;
    }

};

template <typename T> struct ISpecification {
    virtual bool is_satisfied(T* items) = 0;
};

template <typename T> struct IFilter {
    virtual vector <T*> filter (vector<T*> items, ISpecification<T> &spec)  = 0;
};



struct BetterFilter: IFilter <Product> {
    typedef vector<Product*> Items;
    virtual Items filter(Items items, ISpecification<Product> &spec) {
        Items result;
        for(auto &i: items) {
            if(spec.is_satisfied(i)) {
                result.push_back(i);
            }
        }
        return result;
    }

};

struct ColorSpecification: ISpecification<Product> {
    Color color;
    explicit ColorSpecification (const Color color): color(color) {

    }

    bool is_satisfied(Product* items) {
        return items->color  == color;
    }
};

struct SizeSpecification: ISpecification<Product> {
    Size size;
    explicit SizeSpecification (const Size size): size(size) {

    }

    bool is_satisfied(Product* items) {
        return items->size  == size;
    }
};
template <typename T> struct AndSpecification: ISpecification <T> {
    ISpecification<T> &first;
    ISpecification<T> &second;

    explicit AndSpecification ( ISpecification<T> &first,   ISpecification<T> &second)
    : first(first), second(second) {

    }

    bool is_satisfied(Product* items) {
        return first.is_satisfied(items) && second.is_satisfied(items);
    }
};

int main() {
    Product apple{"Apple", Color::Green, Size::Small};
    Product Tree{"Tree", Color::Red, Size::Large};
    Product House{"House", Color::Blue, Size::Medium};
    Product mango{"Mango", Color::Green, Size::Medium};

    vector<Product *> all = {&apple,&Tree, &House, &mango};

    BetterFilter bf;
    ColorSpecification color(Color::Green);
    SizeSpecification size(Size::Medium);
    AndSpecification<Product> as {color, size};
    auto green = bf.filter(all,color);

    for(auto &x: green) {
        cout<<x->name<<" is green"<<endl;
    }

    auto andResult = bf.filter(all ,as);
    for(auto &x: andResult) {
        cout<<x->name<<" is green"<<endl;
    }
    return 0;
}