#pragma once

#include <cstdint>
#include <iterator>
#include <ostream>

namespace Saber {

struct ListNode {
    ListNode *prev = nullptr;
    ListNode *next = nullptr;
    ListNode *rand = nullptr;
    std::string data;
};

class List {
  public:
    class Iterator : public std::iterator<std::forward_iterator_tag,
                                          typename Saber::ListNode> {
      public:
        Iterator(ListNode *ptr);
        ListNode &operator*() const;
        ListNode *operator->();
        Iterator &operator++();
        Iterator operator++(int);
        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.m_ptr != b.m_ptr;
        }

  ListNode       *get_ptr();

      private:
        ListNode *m_ptr;
    };

    ListNode &push_front(const std::string &data);
    ListNode &push_back(const std::string &data);
    List::Iterator find(const std::string &data);
    size_t size() const;

    List::Iterator begin();
    List::Iterator end();

    void serialize(FILE *file);
    void deserialize(FILE *file);

    void free();
    ~List();

  private:
    ListNode *m_Head = nullptr;
    ListNode *m_Tail = nullptr;
    size_t m_Count = 0;
};

} // namespace Saber