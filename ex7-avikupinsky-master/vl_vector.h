//
// Created by aviku on 31/12/2021.
//


#ifndef VL_VECTOR_H
#define VL_VECTOR_H
#include <iostream>
#include <cmath>
#include <iterator>
#define STATIC_CAPACITY 16
#define NUMBER_2 2
#define NUMBER_3 3
#define ERROR_OUT_RANGE "the item is out of range"



template <typename T, size_t StaticCapacity = STATIC_CAPACITY >
class vl_vector{
private:
    T static_memory[StaticCapacity];
    T * heap_memory = nullptr;
    size_t size_vec = 0;
    size_t size_cap = StaticCapacity;
    size_t new_cap = 0;

public:
    // we creat all the necessary items for the iterator
    typedef T * iterator;
    typedef const T * const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    //we creat the begins and ends of the iterator
    iterator begin (){if (this->new_cap == 0){return {this->static_memory};}return{this->heap_memory};}
    iterator end (){ return begin()+ this->size_vec; }
    const_iterator begin () const{if (this->new_cap == 0){return {this->static_memory};}return{this->heap_memory};}
    const_iterator end () const{ return cbegin()+ this->size_vec;}
    const_iterator cbegin () const{if (this->new_cap == 0){return {this->static_memory};}return{this->heap_memory};}
    const_iterator cend () const{ return cbegin()+ this->size_vec; }
    reverse_iterator rbegin(){return reverse_iterator(end());}
    reverse_iterator rend(){return reverse_iterator(begin());}
    const_reverse_iterator rbegin()  const{return const_reverse_iterator(end());}
    const_reverse_iterator rend()const{return const_reverse_iterator(begin());}
    const_reverse_iterator crbegin()  const{return const_reverse_iterator(end());}
    const_reverse_iterator crend()const{return const_reverse_iterator(begin());}


    /**
     * a function to calculate the new capacity
     * @param num1
     * @param num2
     * @return the new capacity
     */
    size_t calculating_new_cap(size_t num1, size_t num2){
        return (NUMBER_3*(num1+num2)/NUMBER_2);
    }

    /**
     * the default constructor
     */
    vl_vector() {
    }

    /**
     * the constructor to copy from another vl
     * @param other
     */
    vl_vector(const vl_vector& other){
        this->size_vec = other.size_vec;
        this->size_cap = other.size_cap;
        this->new_cap = other.new_cap;
        if (other.new_cap){
            this->heap_memory = new T[other.new_cap];
        }
        std::copy (other.begin(), other.end(), this->begin());
    }


    /**
     * the constructor to copy data from an iterator
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    vl_vector(InputIterator first, InputIterator last) {
        size_t count = std::distance (first, last);
        if (count > this->size_cap) {
            size_t num = calculating_new_cap(this->size_vec,count);
            this->new_cap = num;
            this->heap_memory = new T[num];
        }
        this->size_vec += count;
        std::copy(first, last, this->begin());
    }


    /**
     * a constructor to begin with count item with the same value
     * @param count
     * @param v
     */
    vl_vector(size_t count, T v) {
        int num = 0;
        size_t check = calculating_new_cap(this->size_vec,count);
        if (check > this->size_cap) {
            this->heap_memory = new T[check];
            this->new_cap = check;
        }
        while (num != count) {
            if (this->new_cap != 0) {
                this->heap_memory[num] = v;
            } else{
                this->static_memory[num] = v;
            }
            num++;
        }
        this->size_vec += num;
    }

    /**
     * the destructor if we use heap memory we delete it
     */
    ~vl_vector(){
        if (this->new_cap){
            delete[] this->heap_memory;
        }
    }


    /**
     * getting the size of the vector
     * @return vector size
     */
    size_t size() const
    {
        return this->size_vec;
    }

    /**
     * getting the cap of the vector
     * @return cap size
     */
    size_t capacity() const
    {
        if (this->new_cap){
            return this->new_cap;
        }
        return this->size_cap;
    }

    /**
     * checking if vector is empty
     * @return true ar false
     */
    bool empty() const
    {
        return this->size_vec == 0;
    }


    /**
     * checking what the value is in certain index
     * @param y
     * @return the value at that index
     */
    T& at(size_t y) noexcept(false)
    {
        if (y >= this->size_vec || y < 0){
            throw std::out_of_range(ERROR_OUT_RANGE);
        }
        if (this->new_cap == 0){
            return this->static_memory[y];
        } else{
            return this->heap_memory[y];
        }
    }

    /**
     * checking what the value is in certain index
     * @param y
     * @return the value at that index
     */
    T at(size_t y) const noexcept(false)
    {
        if (y >= this->size_vec || y < 0){
            throw std::out_of_range(ERROR_OUT_RANGE);
        }
        if (this->new_cap == 0){
            return this->static_memory[y];
        } else{
            return this->heap_memory[y];
        }
    }


    /**
     * we push a new item to the vector
     * @param elem
     */
    void push_back(const T & elem) {
        if(((this->size_vec + 1 > this->new_cap) && this->new_cap != 0) ||
           (this->size_vec + 1> this->size_cap && this->new_cap ==0)) {
            allocating_memory(1);
        }
        if (this->new_cap != 0){
            this->heap_memory[this->size_vec] = elem;
        } else{
            this->static_memory[this->size_vec] = elem;
        }
        this->size_vec++;
    }

    /**
     * we allocate memory for the vector
     * @param i
     */
    void allocating_memory(int i) {
        size_t sum = calculating_new_cap(this->size_vec,i);
        T * new_x = new T [sum];
        for (size_t j = 0; j < this->size_vec; ++j) {
            if (this->new_cap == 0) {
                new_x[j] = this->static_memory[j];
            } else{
                new_x[j] = this->heap_memory[j];
            }
        }
        if (this->new_cap !=0){
            delete[] this->heap_memory;
        }
        this->heap_memory  = new_x;
        this->new_cap = sum;
    }


    /**
     * we insert one item in to the vector before the current
     * @param current
     * @param item
     * @return the current iterator
     */
    iterator insert(iterator current, const T& item) {
        size_t dist = std::distance (this->begin(), current);
        if(((this->size_vec + 1 > this->new_cap) && this->new_cap != 0) ||
           (this->size_vec + 1> this->size_cap && this->new_cap ==0)) {
            allocating_memory(1);
        }
        std::move_backward(begin() + dist, end(), end() + 1);
        *(begin()+dist)=item;
        this->size_vec++;
        return begin()+dist;
    }


    /**
     * insert a list of iterator from first to last
     * @tparam InputIterator
     * @param current
     * @param first
     * @param last
     * @return were the list begins for the iterator now in the vector
     */
    template<class InputIterator>
    iterator insert(iterator current,InputIterator first,InputIterator last){
        size_t count1 = std::distance (first, last);
        size_t count2 = std::distance (this->begin(), current);
        if(((this->size_vec + count1 > this->new_cap) && this->new_cap != 0) ||
           (this->size_vec + count1> this->size_cap && this->new_cap ==0)) {
            allocating_memory(count1);
        }
        std::copy (begin()+count2, end(), begin()+count1+count2);
        for (size_t i=0; i<count1; i++)
        {
            *(begin()+count2+i)=*first;
            first++;
        }
        this->size_vec+= count1;
        return begin() + count2;
    }


    /**
     * popping the last item
     */
    void pop_back(){
        if (this->size_vec > 0) {
            this->size_vec--;
            if (this->size_vec == this->size_cap) {
                for (size_t i = 0; i < this->size_vec; ++i) {
                    this->static_memory[i] = this->heap_memory[i];
                }
                this->new_cap = 0;
                delete[] this->heap_memory;
            }
        }
    }


    /**
     * erasing one item from the vector
     * @tparam InputIterator
     * @param x
     * @return the item the wasr removed
     */
    template<class InputIterator>
    InputIterator erase(InputIterator x)
    {
        if (!contains (*x))
            return nullptr;
        size_t num = std::distance (this->begin(), x);
        this->size_vec--;
        if (x!= this->end()){
            std::copy (this->begin() + num + 1, this->end () + 1, this->begin() + num);
        }
        if (this->size_vec== this->size_cap){
            for (size_t i = 0; i < this->size_vec; ++i) {
                this->static_memory[i] = this->heap_memory[i];
            }
            delete[] this->heap_memory;
            this->new_cap = 0;
            return &this->static_memory[num];
        }
        return x;
    }

    /**
     * removing a list of items from the vector
     * @tparam InputIterator
     * @param first
     * @param last
     * @return the list that was removed from its first item
     */
    template<class InputIterator>
    InputIterator erase(InputIterator first,InputIterator last)
    {
        size_t count = std::distance (first, last);
        size_t num = std::distance (this->begin(),first);
        if (last!= this->end())
            std::copy (this->begin()+num+count,this->end(), this->begin()+num);
        else
            first=last;
        this->size_vec-=count;
        if (this->size_vec== this->size_cap){
            for (size_t i = 0; i < this->size_vec; ++i) {
                this->static_memory[i] = this->heap_memory[i];
            }
            delete[] this->heap_memory;
            this->new_cap = 0;
            return &this->static_memory[num];
        }
        return first;
    }


    /**
     * removing all the items from the vector
     */
    void clear(){
        if (this->new_cap){
            delete[] this->heap_memory;
            this->new_cap = 0;
        }
        this->size_vec = 0;
    }

    /**
     * the data were the vector saved
     * @return heap or static
     */
    T * data(){
        if (this->new_cap == 0){
            return this->static_memory;
        }
        return this->heap_memory;
    }

    /**
     *checking id the item is in the vector
     * @param item
     * @return
     */
    bool contains(const T& item){
        int flag = 0;
        if (this->new_cap == 0){
            for (size_t i = 0; i < this->size_vec; ++i) {
                if (this->static_memory[i] == item){
                    flag = 1;
                }
            }
        } else{
            for (size_t i = 0; i < this->size_vec; ++i) {
                if (this->heap_memory[i] == item){
                    flag = 1;
                }
            }
        }
        return flag != 0;
    }

    /**
     * the equal operator
     * @param other
     * @return this
     */
    vl_vector& operator=(const vl_vector& other){
        if (this!= &other) {
            if (this->new_cap != 0) {
                delete[] this->heap_memory;
            }
            if (other.new_cap != 0){
                this->heap_memory = new T[other.new_cap];
                this->new_cap = other.new_cap;
            } else{
                this->new_cap = 0;
            }

            std::copy (other.begin (), other.end (), this->begin ());
            this->size_vec = other.size_vec;
            this->size_cap = other.size_cap;
        }
        return *this;
    }

    /**
     * finding index ope
     * @param idx
     * @return the value at that index
     */
    T& operator[](int idx)
    {
        if (this->new_cap == 0)
            return this->static_memory[idx];
        return this->heap_memory[idx];
    }

    /**
     * finding index ope
     * @param idx
     * @return the value at that index
     */
    T operator[](int idx) const
    {
        if (this->new_cap == 0)
            return this->static_memory[idx];
        return this->heap_memory[idx];
    }

    /**
     * checking if there equal
     * @param other
     * @return true are false
     */
    bool operator==(vl_vector& other)
    {
        if (this->size_vec!=other.size_vec)
            return false;
        iterator curr_this= this->begin();
        iterator curr_other= other.begin();
        while (curr_this!= this->end())
        {
            if (*curr_this!=*curr_other) {
                return false;
            }
            curr_this++;
            curr_other++;
        }
        return true;
    }

    /**
     * checking if there not equal
     * @param other
     * @return true ar false
     */
    bool operator!=(vl_vector& other)
    {
        return ! (*this== other);
    }

};

#endif //VL_VECTOR_H
