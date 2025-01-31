//
// Created by aviku on 23/12/2021.
//

#include "AVL.h"


/**
 * Constructor. Constructs an empty AVL tree
 */
AVL::AVL(){
    this->root_ = nullptr;
}

/**
 * getting the height of the node
 * @param check
 * @return height
 */
int AVL::check_height(AVL::node *check) {
    if (check == nullptr)
        return 0;
    return check->height;
}

/**
 * getting the different in height between the left and the right
 * @param node
 * @return height different
 */
int AVL::getting_balance(AVL::node *node) {
    if (node == NULL)
        return 0;
    return check_height(node->left_) -
           check_height(node->right_);
}

/**
 * gitiing max
 * @param a
 * @param b
 * @return max
 */
int AVL::max(int a, int b) {
    return (a > b)? a : b;
}


/**
 * The function inserts the new apartment into the tree so that it maintains
 * the legality of the tree.
 * @param apartment
 */
void AVL::insert(const Apartment &apartment) {
    this->root_ = finding_place_node_insert(this->root_, apartment);
}

/**
 * we creat and allocate memory for a new node
 * @param new_node
 * @param apartment
 * @return new node
 */
AVL::node *AVL::allocating_new_node(AVL::node *new_node, const Apartment &apartment) {
    new_node = new node(apartment, nullptr, nullptr);
    new_node->data_ = apartment;
    new_node->right_ = nullptr;
    new_node->left_ = nullptr;
    new_node->height = 1;
    return new_node;
}


/**
 * this is a rec to find were to insert the data of the apartment
 * @param node
 * @param apartment
 * @return updated root
 */
AVL::node *AVL::finding_place_node_insert( AVL::node *node, const Apartment &apartment) {
    if (node == nullptr) {
        return allocating_new_node(node,apartment);
    }
    if (apartment < node->data_){
        node->left_ = finding_place_node_insert(node->left_,apartment);
    } else if(apartment > node->data_){
        node->right_ = finding_place_node_insert(node->right_,apartment);
    } else{
        return node;
    }
    node->height = 1 + max(check_height(node->left_), check_height(node->right_));
    return balancing_tree(node,apartment);
}

/**
 * if the tree is not even we fix it to be even again when insert
 * @param node
 * @param apartment
 * @return updated node
 */
AVL::node *AVL::balancing_tree(AVL::node *node, const Apartment &apartment) {
    if (abs(node->height) <= 1){
        return node;
    }
    int check = getting_balance(node);

    // Left Left Case
    if((check > 1) && apartment < node->left_->data_){
        return right_rotate(node);
    }

    // Left Right Case
    if((check > 1) && apartment > node->left_->data_){
        node->left_ = left_rotate(node->left_);
        return right_rotate(node);
    }

    // Right Right Case
    if ((check < -1) && apartment > node->right_->data_) {
        return left_rotate(node);
    }

    // Right Left Case
    if ((check < -1) && apartment < node->right_->data_)
    {
        node->right_= right_rotate(node->right_);
        return left_rotate(node);
    }
    return node;
}


/**
 * erasing a Apartment
 * @param apartment
 */
void AVL::erase(const Apartment &apartment) {
    if (this->root_ == nullptr){
    }
    this->root_ = finding_place_node_delete(this->root_, apartment);
}

/**
 * if the tree is not even we fix it to be even again when delete
 * @param node
 * @param apartment
 * @return updated node
 */
AVL::node *AVL::balancing_tree_delete(AVL::node *node) {
    int check = getting_balance(node);

    // Left Left Case
    if (check > 1 && getting_balance(node->left_) >= 0)
        return right_rotate(node);

    // Left Right Case
    if (check > 1 && getting_balance(node->left_) < 0)
    {
        node->left_ = left_rotate(node->left_);
        return right_rotate(node);
    }

    // Right Right Case
    if (check < -1 && getting_balance(node->right_) <= 0)
        return left_rotate(node);

    // Right Left Case
    if (check < -1 && getting_balance(node->right_) > 0)
    {
        node->right_ = right_rotate(node->right_);
        return left_rotate(node);
    }

    return node;
}

/**
 * in case we need to right rotate
 * @param new_node
 * @return updated node
 */
AVL::node *AVL::right_rotate(AVL::node *new_node) {

    node * temp1 = new_node->left_;
    node *temp2 = temp1->right_;
    temp1->right_ = new_node;
    new_node->left_ = temp2;

    new_node->height = max(check_height(new_node->left_),
                           check_height(new_node->right_)) + 1;
    temp1->height = max(check_height(temp1->left_),
                        check_height(temp1->right_)) + 1;

    return temp1;
}

/**
 * in case we need to left rotate
 * @param new_node
 * @return updated node
 */
AVL::node *AVL::left_rotate(AVL::node *new_node) {
    node *temp1 = new_node->right_;
    node *temp2 = temp1->left_;

    temp1->left_ = new_node;
    new_node->right_ = temp2;

    new_node->height = max(check_height(new_node->left_),
                           check_height(new_node->right_)) + 1;
    temp1->height = max(check_height(temp1->left_),
                        check_height(temp1->right_)) + 1;
    return temp1;
}



/**
 * A constructor that receives a vector of a pairs. Each such pair is an
 * apartment that will inserted to the tree. Insert can be used to insert the
 * apartments a vector of a pairs
 * @param coordinates
 */
AVL::AVL(std::vector<std::pair<double, double>> coordinates) {
    this->root_ = nullptr;
    for (auto value:coordinates){
        Apartment new_apartment(value);
        insert(new_apartment);
    }
}

/**
 * a copy constructor
 * @param other
 */
AVL::AVL(const AVL &other) {
    this->root_ = copy_tree(other.root_);
}

/**
 * the =operator when there is memory allocated
 * @param other
 * @return this
 */
AVL &AVL::operator=(const AVL &other) {
    order_delete(this->root_);
    this->root_ = copy_tree(other.root_);
    return *this;
}


/**
 * copying between one tree and onother
 * @param other
 * @return copied root
 */
AVL::node *AVL::copy_tree(const node  *other) {
    if (other == nullptr){
        return nullptr;
    }
    node* new_node = nullptr;
    new_node = allocating_new_node(new_node,other->data_);
    new_node->left_ = copy_tree(other->left_);
    new_node->right_ = copy_tree(other->right_);
    return new_node;
}

/**
 * finding the in value
 * @param new_node
 * @return min value
 */
Apartment AVL::finding_min(AVL::node *new_node) {
    Apartment  * tmp;
    node * check = new_node;
    while (check->left_ != nullptr){
        check = check->left_;
    }
    tmp = &check->data_;
    return *tmp;
}

/**
 * finding were do delete the the apartmen and were is it
 * @param node
 * @param apartment
 * @return updated root
 */
AVL::node *AVL::finding_place_node_delete(AVL::node *node, const Apartment &apartment) {
    if (node == nullptr){
        return node;
    }
    if (apartment < node->data_){
        node->left_ = finding_place_node_delete(node->left_, apartment);
    } else if(apartment > node->data_){
        node->right_ = finding_place_node_delete(node->right_, apartment);
    }
    else{
        if( (node->left_ == nullptr) ||
            (node->right_ == nullptr) ){
            if ((node->left_ == nullptr) &&
                (node->right_ == nullptr )){
                delete node;
                node = nullptr;
            } else{
                if(node->left_ == nullptr) {
                    node->data_ = node->right_->data_;
                    delete node->right_;
                    node->right_ = nullptr;
                } else{
                    node->data_ = node->left_->data_;
                    delete node->left_;
                    node->left_ = nullptr;
                }
            }
        } else{
            node->data_ = finding_min(node->right_);
            finding_place_node_delete(node->right_,node->data_);
        }
    }
    if (node == nullptr)
        return node;
    node->height = 1 + max(check_height(node->left_), check_height(node->right_));
    return balancing_tree_delete(node);
}


/**
 * delete in rec the tree
 * @param node
 */
void AVL::order_delete(AVL::node *node) {
    if (node != nullptr){
        order_delete(node->left_);
        order_delete(node->right_);
        delete node;
        node = nullptr;
    }
}

/**
 * the destructor
 */
AVL::~AVL() {
    order_delete(this->root_);
    root_ = nullptr;
}

/**
 * a function to find throw an iter the data
 * @param data
 * @return the iter were the data is
 */
AVL::iterator AVL::find(const Apartment &data) {
    node *temp = root_;
    while (temp != nullptr && !(temp->data_ == data)) {
        if (data < temp->data_) {
            temp = temp->left_;
        } else if (data > temp->data_) {
            temp = temp->right_;
        }
    }
    if (temp == nullptr){
        return end();
    }
    if (temp->data_ == data){
        return {temp};
    }
    return end();
}

/**
 * a function to find throw an iter the const data
 * @param data
 * @return the iter were the data is
 */
AVL::const_iterator AVL::find(const Apartment &data) const {
    node *temp = root_;
    while (temp != nullptr && !(temp->data_ == data)) {
        if (data < temp->data_) {
            temp = temp->left_;
        } else if (data > temp->data_) {
            temp = temp->right_;
        }
    }
    if (temp == nullptr){
        return end();
    }
    if (temp->data_ == data){
        return {temp};
    }
    return end();
}

/**
 * operator->
 * @return getting the data in the nose
 */
Apartment * AVL::Iterator::operator->()
{
    return &node_stack.top()->data_;
}

/**
 * operator*
 * @return getting the data in the nose
 */
Apartment &AVL::Iterator::operator*() {
    return node_stack.top()->data_;
}


/**
 * getting the nest node
 * @return next node in preorder
 */
AVL::Iterator & AVL::Iterator::operator++() {
    node *curr_node = node_stack.top();
    node_stack.pop();
    if (curr_node->right_ != nullptr){
        node_stack.push(curr_node->right_);
    }
    if (curr_node->left_ != nullptr){
        node_stack.push(curr_node->left_);
    }
    if (node_stack.empty()){
        node_stack.push(nullptr);
    }
    return *this;
}

/**
 * getting the nest node
 * @return next node in preorder const
 */
AVL::Iterator AVL::Iterator::operator++(int ){
    Iterator it = *this;
    node *curr_node = node_stack.top();
    node_stack.pop();
    if (curr_node->right_ != nullptr){
        node_stack.push(curr_node->right_);
    }
    if (curr_node->left_ != nullptr){
        node_stack.push(curr_node->left_);
    }
    if (node_stack.empty()){
        node_stack.push(nullptr);
    }
    return it;
}

/**
 * the ==operator
 * @param rhs
 * @return true are false
 */
bool AVL::Iterator::operator==(const Iterator &rhs) const {
        return node_stack == rhs.node_stack;
}


/**
 * the !=operator
 * @param rhs
 * @return true are false
 */
bool AVL::Iterator::operator!=(const Iterator &rhs) const
{
    return !(rhs == *this);
}

/**
 * operator->
 * @return getting the data in the nose const
 */
const Apartment * AVL::ConstIterator::operator->() const
{
    return &node_stack.top()->data_;
}


/**
 * operator*
 * @return getting the data in the nose const
 */
Apartment  AVL::ConstIterator::operator*() const
{
    return node_stack.top()->data_;
}

/**
 * getting the nest node ConstIterator
 * @return next node in preorder const
 */
AVL::ConstIterator & AVL::ConstIterator::operator++()
{
    node *curr_node = node_stack.top();
    node_stack.pop();
    if (curr_node->right_ != nullptr){
        node_stack.push(curr_node->right_);
    }
    if (curr_node->left_ != nullptr){
        node_stack.push(curr_node->left_);
    }
    if (node_stack.empty()){
        node_stack.push(nullptr);
    }
    return *this;
}

/**
 * getting the nest node ConstIterator
 * @return next node in preorder const
 */
AVL::ConstIterator AVL::ConstIterator::operator++(int )
{
    ConstIterator it = *this;
    node *curr_node = node_stack.top();
    node_stack.pop();
    if (curr_node->right_ != nullptr){
        node_stack.push(curr_node->right_);
    }
    if (curr_node->left_ != nullptr){
        node_stack.push(curr_node->left_);
    }
    if (node_stack.empty()){
        node_stack.push(nullptr);
    }
    return it;
}

/**
 * the ==operator const
 * @param rhs
 * @return true are false
 */
bool AVL::ConstIterator::operator==(const ConstIterator &rhs) const
{
    return node_stack == rhs.node_stack;
}

/**
 * the !=operator const
 * @param rhs
 * @return true are false
 */
bool AVL::ConstIterator::operator!=(const ConstIterator &rhs) const
{
    return !(rhs == *this);
}


/**
 * we print all of the nodes in the root
 * @param os
 * @param avl
 * @return os
 */
std::ostream &operator<<(std::ostream &os, const AVL &avl) {
    AVL::node* curr = avl.root_;
    AVL::ConstIterator iterator(curr);
    while (iterator != avl.end()){
        os << *iterator<< std::endl;
        ++iterator;
    }
    return os;
}