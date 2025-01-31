//
// Created by rotem on 07/10/2021.
//

#ifndef _AVL_H_
#define _AVL_H_
#include <vector>
#include <stack>
#include "Apartment.h"
#include "Stack.h"

class AVL {
 public:
  /**
   * To manage the tree nodes, we use a nested struct. This struct contains the
   * apartment corresponding to the node, the left son and the right son of the
   * node, both of them Node type themselves.
   */
  struct node {
      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       */
      node (Apartment data, node *left, node *right)
          : data_ (data), left_ (left), right_ (right)
      {}
      /**
       *
       * @return the left child of this node
       */
      node *get_left () const
      {
        return left_;
      }
      /**
       *
       * @return the right child of this node
       */
      node *get_right () const
      {
        return right_;
      }

      /**
     *
     * @return the const reference apartment of this node
     */
      const Apartment &get_data () const
      {
        return data_;
      }
      size_t get_height () const
      {
          return height;
      }
      Apartment data_;
      node *left_, *right_;
      int height = 0;
  };
  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ();
  /**
   * Copy constructor
   * @param other
   */
  AVL (const AVL &other);
  /**
   * A constructor that receives a vector of a pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert the
   * apartments a vector of a pairs
   * @param coordinates
   */
  AVL (std::vector<std::pair<double, double>> coordinates);
  /**
   *
   * @return the root node of this tree
   */
  node *get_root () const{
    return root_;
  }
  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void insert (const Apartment &apartment);
  /**
   * The function deletes the apartment from the tree (if it is in that tree) so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  node *finding_place_node_insert(node* node, const Apartment &apartment);

  node *finding_place_node_delete(node* node, const Apartment &apartment);

  Apartment finding_min(node* new_node);

  int check_height(node * check);

  node * allocating_new_node(node* new_node, const Apartment &apartment);

  node * balancing_tree(node* node, const Apartment &apartment);

  node *  balancing_tree_delete(node* node);

  node * right_rotate(node * new_node);

  node * left_rotate(node * node);

  int getting_balance(node * node);

  int max(int a, int b);

  AVL &operator=(const AVL &other);

  node * copy_tree(const node *other);

  void order_delete(node * node);

  virtual ~AVL();

  void erase (const Apartment &apartment);
  /**
   * The class should support forward iterator. Don't forget to define the
   * iterator traits and all the actions required to support a forward iterator
   * The iterator will move in preorder.
   */
  class ConstIterator;
  class Iterator{
      std::stack<AVL::node*> node_stack;
      friend class ConstIterator;
  public:
      typedef Apartment value_type;
      typedef Apartment &reference;
      typedef Apartment *pointer;
      typedef std::forward_iterator_tag iterator_category;
      typedef Apartment difference_type;
      Iterator(node *cur) {
          node_stack.push(cur);
      }

      pointer operator-> ();
      reference operator* ();
      Iterator &operator++ ();
      Iterator operator++ (int);
      bool operator== (const Iterator &rhs) const;
      bool operator!= (const Iterator &rhs) const;
  };

    class ConstIterator{
        std::stack<AVL::node*> node_stack;
    public:
        typedef const Apartment value_type;
        typedef const Apartment &reference;
        typedef const Apartment *pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        ConstIterator (node *cur)
        {
            node_stack.push(cur);
        }

        const Apartment *operator-> () const;
        Apartment operator* () const;
        ConstIterator &operator++ ();
        ConstIterator operator++ (int);
        bool operator== (const ConstIterator &rhs) const;
        bool operator!= (const ConstIterator &rhs) const;
    };


  using iterator = Iterator;
  using const_iterator = ConstIterator;
    iterator begin ()
    {
       return {root_};
    }
    iterator end ()
    {
        return {nullptr};
    }
    const_iterator begin () const
    {
        return {root_};
    }
    const_iterator end () const
    {
        return {nullptr};
    }
    const_iterator cbegin () const
    {
        return {root_};
    }
    const_iterator cend () const
    {
        return {nullptr};
    }
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder traversal.
   * Each apartmnet will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);


 private:
  node *root_;
};

#endif //_AVL_H_
