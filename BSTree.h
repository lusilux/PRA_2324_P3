#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T> *root;

        //Busqueda

        BSNode<T>* search(BSNode<T>* n, T e) const{
            if(n == nullptr)throw runtime_error("");
            else if(n.elem < e) return search(n.right, e);
            else if(n.elem > e) return search(n.left, e);
            else return n;
        } 

        //Insercion

        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n == nullptr) return new BSNode(e);
            else if(n.elem == e)throw runtime_error("");
            else if(n.elem < e) n.right = insert(n.right, e);
            else n.left = insert(n.left, e);
            return n;
        } 

        //Recorrido

        void print_inorder(std::ostream &out, BSNode<T> n) const{
            if(n != nullptr){
                print_inorder(n.left, out);
                out << n << " ";
                print_inorder(n.right, out);
            } 
        }

        //Eliminación

        BSNode<T>* remove(BSNode<T>* n, T e){
            if(n == nullptr)throw runtime_error("");
            else if(n.elem < e)n.right = remove(n.right,e);
            else if(n.elem > e)n.left = remove(n.left, e);
            else{
                if(n.left != nullptr && n.right != nullptr){
                    n.elem = max(n.left);
                    n.left = remove_max(n.left);
                } else{
                    n = (n.left != nullptr) ? n.left : n.right;
                } 
            } 
            return n;
        }  

        T max(BSNode<T>* n) const{
            if(n == nullptr)throw runtime_error("");
            else if(n.right != nullptr)return max(n.right);
            else return n.elem;
        } 

        BSNode<T>* remove_max(BSNode<T>* n){
            if(n.right == nullptr) return n.left;
            else{
                n.right = remove_max(n.right);
                return n;
            }  
        }

        //Destruccion
        void delete_cascade(BSNode<T>* n) {
            if(n == nullptr)return;
            delete_cascade(n.left);
            delete_cascade(n.right);
            delete n;
        } 


    public:

        BSTree(){
            nelem = 0;
            root = nullptr;
        } 

        int size() const{return nelem;}

        //Busqueda

        T search(T e) const{
            return search(root, e).elem;
        }

        T operator[](T e) const{
            return search(e);
        }   

        //Insercion

        void insert(T e){
            root = insert(root, e);
        } 

        //Recorrido

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            out << print_inorder(out, bst.root);
            return out;
        } 

        //Eliminacion

        void remove(T e){
            remove(root, e);
        }  

        //Destruccion

        ~BSTree(){
            delete_cascade(root);
        } 
};

#endif