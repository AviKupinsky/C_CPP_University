//
// Created by aviku on 22/12/2021.
//

#include "Stack.h"
#define EMPTY_ERROR "ERROR: the list of vector we have gotten is empty"
using std::make_pair;


/**
 * Default constructor, constructs an empty stack
 */
Stack::Stack() = default;

/**
 * Constructor that gets vector of pairs, and pushes them as apartments to the stack, when the first pair is pushed first.
 * @param coordinates vector of pairs
 */
Stack::Stack(std::vector<std::pair<double, double>> coordinates) {
    if (coordinates.empty()){
        std::cerr<< EMPTY_ERROR << std::endl;
    }
    for (auto value:coordinates){
        Apartment new_apt(value);
        this->data.insert(this->data.begin(),new_apt);
    }
}

/**
 * Pushes an apartment to the top of the stack
 * @param apartment
 */
void Stack::push(const Apartment &apartment) {
    this->data.insert(this->data.begin(),apartment);
}

/**
 * A method that deletes the item from the top of the stack.
 * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
 */
void Stack::pop() {
    if (this->data.empty()){
        std::cerr<< EMPTY_ERROR << std::endl;
    }
    this->data.erase(this->data.begin());
}

/**
*A method that returns true if the stack is empty and otherwise false.
*/
bool Stack::empty() const {
    bool last = false;
    if (this->data.empty()) {
        last = true;
    }
    return last;
}

/**
*A method that returns how many items are inside the stack.
*/
size_t Stack::size() const {
    return this->data.size();
}

/**
 * Method that return the item from the top of the stack, but do not remove it from it.
 * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
 * @return refernce to the top most item
 */
Apartment &Stack::top() {
    /// you need to fix this
    if (this->data.empty()){
        std::cerr<< EMPTY_ERROR << std::endl;
    }
    return this->data.front();
}

/**
 * Method that return the item from the top of the stack, but do not remove it from it.
 * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
 * @return copy to the top most item
 */
Apartment Stack::top() const {
    if (this->data.empty()){
        std::cerr<< EMPTY_ERROR << std::endl;
    }
    return this->data.front();
}

/**
 * iterator to begin
 * @return  first data
 */
Stack::iterator Stack::begin() {
    return this->data.begin();
}

/**
 * iterator to end
 * @return  last data = null
 */
Stack::iterator Stack::end() {
    return this->data.end();
}

/**
 * iterator to begin const
 * @return  first data
 */
Stack::const_iterator Stack::begin() const {
    return this->data.begin();
}

/**
 * iterator to begin const
 * @return  first data
 */
Stack::const_iterator Stack::cbegin() const {
    return this->data.begin();
}

/**
 * iterator to end const
 * @return  last data = null
 */
Stack::const_iterator Stack::end() const {
    return this->data.end();
}

/**
 * iterator to end const
 * @return  last data = null
 */
Stack::const_iterator Stack::cend() const {
    return this->data.end();
}


