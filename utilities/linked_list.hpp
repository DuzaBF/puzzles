#include <iostream>
#include <vector>

namespace linked_list {

template <typename T>
struct ListNode {
   public:
    T val;
    ListNode* next;
    ListNode(T x) : val(x), next(nullptr){};
    ListNode(T x, ListNode* next) : val(x), next(next){};

   private:
    ListNode(){};
};

template <typename T>
struct LinkedList {
   private:
    LinkedList(){};

   public:
    ListNode<T>* head;
    LinkedList(const std::vector<T>& cvalues) {
        ListNode<T>* prev = nullptr;
        for (auto& v : cvalues) {
            ListNode<T>* cur = new ListNode<T>(v, prev);
            prev = cur;
        }

        head = prev;
    }

    LinkedList(ListNode<T>* head) : head(head){};
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list) {
    const ListNode<T>* cur = list.head;
    while (cur != nullptr) {
        out << cur->val;
        cur = cur->next;
        if (cur != nullptr) {
            out << "->";
        }
    }
    return out;
}

template <typename T>
bool operator==(const LinkedList<T>& lhs, const LinkedList<T>& rhs) {
    const ListNode<T>* cur_l = lhs.head;
    const ListNode<T>* cur_r = rhs.head;
    bool result = true;
    while ((cur_l != nullptr) && (cur_r != nullptr)) {
        if (cur_l->val != cur_r->val) {
            result = false;
        }

        cur_l = cur_l->next;
        cur_r = cur_r->next;
    }

    if ((cur_l != nullptr) || (cur_r != nullptr)) {
        result = false;
    }

    return result;
}
}  // namespace linked_list