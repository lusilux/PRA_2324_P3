#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "PRA_2324_P1/ListLinked.h"
using namespace std;

template <typename V> class HashTable : public Dict<V> {
    
    private:

        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(string h) {
            int res = 0;
            int size = h.length();
            for(int i = 0; i < size; i++)res += int(h.at(i));
            return res%max;
        } 

    public:

        HashTable(int size) {
            table = new ListLinked<TableEntry<V>>[size];
            max = size;
            n = 0;  
        } 

        ~HashTable() {
            delete[] table; 
        }

        int capacity() {
            return max;
        } 
        
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
            out << "==============" << endl << endl;
            for(int i = 0; i < th.max; i++){
                out << "== Cubeta " << i << " =="<< endl << endl;
                out << "List => ";
                for(int j = 0; j < th.table[i].size(); j++){
                    out <<	"[" << th.table[i][j].key << ":" << th.table[i][j].value << "] ";
                } 
                out << endl << endl;
            }  
            out << "==============" << endl << endl;
			return out;
	    }

        V operator[](string key) {
            V kValue = search(key);
            return kValue;
        }

        void insert(string key, V value) override {
            int pos = h(key); 
            for(int i = 0; i < table[pos].size(); i++) {
                if(table[pos][i].key == key) throw runtime_error("Key alredy exists!");
            } 
            TableEntry newEntry(key, value);
            table[pos].append(newEntry); 
        }

        V search(string key) override { //Duda: puedo usar la sobrecarga del operador dentro de la misma clase? V kValue = table[key] 
            int pos = h(key);
            V kValue = -1;
            for(int i = 0; i < table[pos].size(); i++){
                if(table[pos][i].key == key){
                    kValue = table[pos][i].value;
                    break; 
                } 
            } 
            if(kValue == -1)throw runtime_error("Key not found!");
            return kValue;
        }    

        V remove(string key) override {
            int i;
            int pos = h(key);
            for(i = 0; i < table[pos].size(); i++) {
                if(table[pos][i].key == key) break;
            }
            if(i == (table[pos].size())) throw runtime_error("Key not found!");
            V returnValue = (table[pos].remove(i)).value; 

            return returnValue; 
        }

        int entries() override {
            return n;
        } 

}; 

#endif
