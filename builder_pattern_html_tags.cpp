#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct HtmlElement {
    string name;
    string text;

    vector <HtmlElement> sub_elements;
    const size_t indent_size = 2;

    HtmlElement () { }
    HtmlElement(string name, string text): name(name), text(text) {

    }

    string str(int indent = 0) const {
        ostringstream oss;

        string i(indent_size*indent, ' ');

        oss<<i<<"<"<<name<<">"<<endl;

        if(text.size()>0) {
            oss<<string(indent_size*indent+1, ' ')<<text<<endl;
        }

        for (const auto &element : sub_elements) {
            oss<<element.str(indent+1)<<endl;
        }

        oss<<i<<"</"<<name<<">"<<endl;

        return oss.str();
    }
};


struct HtmlBuilder {
    HtmlElement root;

    HtmlBuilder() { }
    HtmlBuilder(string root_name)   {
        root.name = root_name;
    }

    void add_child(string child_name, string child_text) {
        HtmlElement e{child_name, child_text};

        root.sub_elements.emplace_back(e);
    }

    const string str () {return root.str().c_str();}
};


int main() {

    HtmlBuilder root{"ul"};

    root.add_child("li", "Hello");
    root.add_child("li", "world");


    cout<<root.str()<<endl;
    return 0;
}