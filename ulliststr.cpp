#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

/**
 * Adds a new value to the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::push_back(const std::string& val)
{
  if (tail_ == nullptr || tail_->last == ARRSIZE)
  {
    Item* temp = new Item();
    if (empty()) {
      head_ = temp;
      tail_ = temp;
    } else {
      temp->prev = tail_;
      tail_->next = temp;
      tail_ = temp;
    }
    temp->first = 0;
    temp->last = 0;
  }
  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;

}

/**
 * Removes a value from the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_back()
{
  if (!empty()) {
    tail_->last--;
    size_--;

    if (tail_->first == tail_->last) //item is empty
    {
      if (tail_->prev == nullptr) //only one item in list
      {
        delete tail_;
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        tail_ = tail_->prev;
        delete tail_->next;
        tail_->next = nullptr;
      }
    }
  }
}

/**
 * Adds a new value to the front of the list.
 * If there is room before the 'first' value in
 * the head node add it there, otherwise, 
 * allocate a new head node.
 *   - MUST RUN in O(1)
 */
void ULListStr::push_front(const std::string& val)
{
  if (head_ == nullptr || head_->first == 0)
  {
    Item* temp = new Item();
    if (empty()) {
      head_ = temp;
      tail_ = temp;
    } else {
      temp->next = head_;
      head_->prev = temp;
      head_ = temp;
    }
    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }
  head_->first--;
  head_->val[head_->first] = val;
  size_++;
}

/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front()
{
  if (!empty()) {
    head_->first++;
    size_--;

    if (head_->first == head_->last)
    {
      if (head_->next == nullptr) //only one element in list
      {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        head_ = head_->next;
        delete head_->prev;
        head_->prev = nullptr;
      }
    }
  }
}

/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::back() const
{
  if(!empty())
  {
    return tail_->val[tail_->last-1];
  }
}

/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::front() const
{
  if(!empty())
  {
    return head_->val[head_->first];
  }
}

/** 
 * Returns a pointer to the item at index, loc,
 *  if loc is valid and NULL otherwise
 *   - MUST RUN in O(n) 
 */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc < size_)
  {
    Item *curr = head_;
    size_t totalIndex = 0;
    while(curr != nullptr)
    {
      size_t arrIndex = curr->first;
      while(arrIndex < curr->last)
      {
        if(totalIndex == loc)
        {
          return &curr->val[arrIndex];
        }
        totalIndex++;
        arrIndex++;
      }
      curr = curr->next;
    }
  }
  return nullptr;
}
