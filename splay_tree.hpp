#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP


template<typename T>
struct sNode
{
  T data;
  sNode *left;
  sNode *right;
  sNode *parent;

};

template<typename T>
class sptree
{
private:
  sNode<T> *root = nullptr;
  void insert(sNode<T>*,  T );
  sNode<T>* rightrotate(sNode<T>*);
  sNode<T>* leftrotate(sNode<T>*);
  sNode<T>* splay(sNode<T> *);
  sNode<T>* findmax(sNode<T> *);
  void make_empty(sNode<T>*);


public:
  sptree(){};
  bool search(T );
  void remove(T );
  void insert(T );
  void print_tree(T);
  sNode<T>* insert2(sNode<T> *, T);
  void make_empty();
  void print_sorted(sNode<T> *);
  void print_sorted();


};
// ---------implementation-----------
template<typename T>
bool sptree<T>::search(T data)
{
  sNode<T>* node = root;
  sNode<T>* parent =nullptr;

  while (node)
  {
    parent = node;
    if (data > node->data)
      node = node->right;
    else if (data < node->data)
      node = node->left;
    else
        {
          root = splay(node);
          return true;
        }
  }
  root = splay(parent);
  return false;
}

template<typename T>
sNode<T>* sptree<T>::rightrotate(sNode<T> *node)
{
  sNode<T> *temp = node->left;
  node->left = temp->right;
  temp->right = node;

  if (node->left)
    node->left->parent = node;
  temp->parent = node->parent;
  if (node->parent)
  {
    if (node->parent->left == node)
      temp->parent->left = temp;
    else temp->parent->right = temp;
  }


  node->parent = temp;


  return temp;

}

template<typename T>
sNode<T>* sptree<T>::leftrotate(sNode<T> *node)
{
  sNode<T> *temp = node->right;
  node->right = temp->left;
  temp->left = node;

  if (node->right)
    node->right->parent = node;
  temp->parent = node->parent;
  if (node->parent)
  {
    if (node->parent->left == node)
      temp->parent->left = temp;
    else temp->parent->right = temp;
  }


  node->parent = temp;


  return temp;
}

template<typename T>
void sptree<T>::remove(T data)
{
  sNode<T> *temp = root;
  sNode<T> *parent = nullptr;
  if (!temp)
    return;

  while (temp)
  {
    parent = temp;
    if (data > temp->data)
      temp = temp->right;
    else if (data < temp->data)
      temp = temp->left;
    else
      break;
  }

    if (temp == nullptr)
      {
        root = splay(parent);
        return;
      }

    root = splay(temp);
    temp = root;

    if (root->left)
      {
        root->left->parent = nullptr;
        root = splay(findmax(root->left));
        root->right= temp->right;
        
        if(root->right)
          root->right->parent = root;
      }
      else
        {
          if (root->right)
           root = root->right;
        }

    root->parent = nullptr;
    delete temp;
    temp = nullptr;

}

template<typename T>
void sptree<T>::insert(sNode<T> *node, T data)
{

  sNode<T> *temp = root;
  sNode<T> *parent = nullptr;

  while (temp != nullptr)
  {
    parent = temp;
    if (data > temp->data)
       temp = temp->right;

    else if(data < temp->data)
        temp = temp->left;
    else {
           root = splay(temp);
           return;
        }
  }

  node = new sNode<T>{data, nullptr, nullptr, parent};
  if (parent == nullptr)
    root = node;
  else if (node->data < parent->data)
    parent->left = node;
  else if (node->data > parent->data)
    parent->right = node;


  root = splay(node);
}

template<typename T>
void sptree<T>::insert(T data)
{
  // sNode *p = nullptr;
  insert(root,  data);

}

template<typename T>
sNode<T>* sptree<T>::splay(sNode<T>* node)
{

  while (node->parent)
    {
      if (node->parent->parent == nullptr) // the root is the parent
        {if (node == node->parent->left)
            node = rightrotate(node->parent);
        else if (node == node->parent->right)
            node = leftrotate(node->parent);
        }
      else if (node == node->parent->left &&
               node->parent == node->parent->parent->left)
               {
                 node = rightrotate(node->parent->parent);//
                 node = rightrotate(node);
               }
      else if (node == node->parent->right &&
               node->parent == node->parent->parent->right)
               {
                node = leftrotate(node->parent->parent);//
                node = leftrotate(node);
               }
     else if (node == node->parent->right &&
              node->parent == node->parent->parent->left)
              {

               node = leftrotate(node->parent);
               node =rightrotate(node->parent); ///
              }

    else if (node == node->parent->left &&
             node->parent == node->parent->parent->right)
             {

              node = rightrotate(node->parent);
              node = leftrotate(node->parent);///
             }
    }

    return node;
}

template<typename T>
void sptree<T>::print_tree(T val)
{
  std::cout<<"----from root to leaf----"<<'\n';
  sNode<T> * temp;
  temp = root;

  while (temp!=nullptr)
    {
      if (val > temp->data)
        {
          std::cout<<temp->data<<" ";
          temp = temp->right;
        }
      else if(val < temp->data)
        {
          std::cout<<temp->data<<" ";
          temp= temp->left;
        }
      else
          {
            std::cout<<temp->data<<'\n';
            std::cout<<"this is the last line"<<'\n';
            std::cout<<"------------------------"<<'\n';
            break;
          }

    }

}

template<typename T>
sNode<T>* sptree<T>::findmax(sNode<T>* node)
{
  sNode<T>* temp;
  while (node)
  {
    temp = node;
    node = node->right;
  }
  return temp;
}

template<typename T>
void sptree<T>::make_empty()
{

  make_empty(root);
}

template<typename T>
void sptree<T>::make_empty(sNode<T> *node)
{
  if (node != nullptr)
  {
    make_empty(node->left);
    make_empty(node->right);
    delete node;
  }
  node = nullptr;

}
template<typename T>
void sptree<T>::print_sorted(sNode<T>* node)
{
  if (node->left)
  print_sorted(node->left);
  std::cout<<node->data<<std::endl;
  if (node->right)
  print_sorted(node->right);



}
template<typename T>
void sptree<T>::print_sorted()
{
  print_sorted(root);
}
#endif
