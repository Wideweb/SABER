#include "list.hpp"

#include <unordered_map>
#include <vector>

namespace Saber {

List::Iterator::Iterator(ListNode *ptr) : m_ptr(ptr) {}

ListNode &List::Iterator::operator*() const { return *m_ptr; }

ListNode *List::Iterator::operator->() { return m_ptr; }

List::Iterator &List::Iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

List::Iterator List::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

ListNode *List::Iterator::get_ptr() { return m_ptr; }

struct SerializeNode {
    int64_t rand_idx = -1;
    int64_t data_size = -1;
};

void List::serialize(std::FILE *file) {
    if (!file)
        return;

    std::vector<SerializeNode> nodes(m_Count);
    std::unordered_map<intptr_t, size_t> index_map;
    index_map[0] = -1;

    auto list_ptr = m_Head;
    for (size_t i = 0; i < m_Count; i++, list_ptr = list_ptr->next) {
        auto key = reinterpret_cast<intptr_t>(list_ptr);
        index_map[key] = i;
    }

    std::fwrite(&m_Count, sizeof(m_Count), 1, file);

    list_ptr = m_Head;
    for (size_t i = 0; i < m_Count; i++, list_ptr = list_ptr->next) {
        nodes[i].data_size = list_ptr->data.size();

        auto rand_key = reinterpret_cast<intptr_t>(list_ptr->rand);
        nodes[i].rand_idx = index_map[rand_key];

        std::fwrite(&nodes[i], sizeof(SerializeNode), 1, file);
        std::fwrite(list_ptr->data.c_str(), list_ptr->data.size(), 1, file);
    }
}

void List::deserialize(std::FILE *file) {
    if (!file) {
        return;
    }

    free();

    std::fread(&m_Count, sizeof(m_Count), 1, file);

    auto nodes = std::vector<ListNode *>(m_Count);
    for (size_t i = 0; i < m_Count; i++) {
        nodes[i] = new ListNode;
    }

    SerializeNode serialized_node;
    for (int i = 0; i < m_Count; i++) {
        std::fread(&serialized_node, sizeof(SerializeNode), 1, file);
        std::vector<char> buffer(serialized_node.data_size);
        std::fread(buffer.data(), buffer.size(), 1, file);

        nodes[i]->prev = i - 1 < 0 ? nullptr : nodes[i - 1];
        nodes[i]->next = i == m_Count - 1 ? nullptr : nodes[i + 1];
        nodes[i]->rand = serialized_node.rand_idx == -1
                             ? nullptr
                             : nodes[serialized_node.rand_idx];
        nodes[i]->data = std::string(buffer.data(), buffer.size());
    }

    m_Head = nodes[0];
    m_Tail = nodes[m_Count - 1];
}

ListNode &List::push_front(const std::string &data) {
    auto it = new ListNode();
    it->data = data;
    it->prev = nullptr;
    it->next = m_Head;

    if (!m_Head) {
        m_Head = it;
        m_Tail = it;
    } else {
        m_Head->prev = it;
        m_Head = it;
    }

    ++m_Count;

    return *it;
}

ListNode &List::push_back(const std::string &data) {
    auto it = new ListNode();
    it->data = data;
    it->prev = m_Tail;
    it->next = nullptr;

    if (!m_Tail) {
        m_Tail = it;
        m_Head = it;
    } else {
        m_Tail->next = it;
        m_Tail = it;
    }

    ++m_Count;

    return *it;
}

List::Iterator List::find(const std::string &data) {
    return std::find_if(begin(), end(), [&data](const ListNode &node) {
        return data == node.data;
    });
}

size_t List::size() const { return m_Count; }

List::Iterator List::begin() { return {m_Head}; }

List::Iterator List::end() { return {nullptr}; }

void List::free() {
    auto *list_ptr = m_Head;
    while (list_ptr != nullptr) {
        auto *next = list_ptr->next;
        delete list_ptr;
        list_ptr = next;
    }
}

List::~List() { free(); }

} // namespace Saber