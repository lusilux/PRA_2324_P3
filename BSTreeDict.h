#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:

        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>;
        } 

        ~BSTreeDict(){
            delete tree;
        } 

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            out << bs.tree;
            return out;
        } 

        V operator[](std::string key){
            return search(key);
        } 

        //Metodos Dict.h

        void insert(string key, V value) override{
            tree->insert(key);
        } 
		
        V search(string key) override{
            return tree->search(key);
        } 
		
        V remove(string key) override{
            V value = tree->search(key);
            tree->remove(key);
            return value;
        } 

		int entries() override{
            return tree.nelem;
        }
        
};

#endif
