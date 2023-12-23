#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

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

        void insert(string key, V value) override { 
            TableEntry<V> *t = new TableEntry<V>(key, value);
            tree->insert(*t);
            delete t;
        } 

		V search(string key) override { return (tree->search(key)).value; } 

		V remove(string key) override {
            V val = (tree->search(key)).value;
            tree->remove(key); // return (tree->remove(key)).value
            return val;
        } 

		int entries() override { return tree->size();} 

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
            out << *bs.tree;
            return out;
        } 

        V operator[](std::string key){
            return search(key);
        } 

        
};

#endif