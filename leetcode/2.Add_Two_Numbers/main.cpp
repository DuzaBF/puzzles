#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "../../utilities/linked_list.hpp"
#include "../../utilities/utils.hpp"

using ListNode = linked_list::ListNode<int>;
using LinkedList = linked_list::LinkedList<int>;

struct NumberAsList : LinkedList {
    using LinkedList::LinkedList;
};

std::ostream& operator<<(std::ostream& out, const NumberAsList& list) {
    const ListNode* cur = list.head;
    const ListNode* last_printed = nullptr;
    while (last_printed != list.head) {
        const ListNode* cur = list.head;
        while (cur->next != last_printed) {
            cur = cur->next;
        }
        out << cur->val;
        last_printed = cur;
    }
    return out;
}

class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result_head = new ListNode(0);
        ListNode* cur = result_head;
        while ((l1 != nullptr) || (l2 != nullptr)) {
            int sum = cur->val + ((l1 == nullptr) ? 0 : l1->val) +
                      ((l2 == nullptr) ? 0 : l2->val);
            int digit = sum % 10;
            int carry = sum / 10;
            cur->val = digit;

            if (l1 != nullptr) {
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                l2 = l2->next;
            }

            if ((l1 != nullptr) || (l2 != nullptr) || (carry > 0)) {
                cur->next = new ListNode(carry);
            }

            cur = cur->next;
        }

        return result_head;
    }
};

int main(void) {
    const std::vector<
        std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>>
        test_cases = {
            {{2, 4, 3}, {5, 6, 4}, {7, 0, 8}},
            {{0}, {0}, {0}},
            {{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}, {8, 9, 9, 9, 0, 0, 0, 1}},
            {{0, 0, 1}, {0}, {0, 0, 1}},
            {{0, 0, 1}, {0, 1}, {0, 1, 1}},
        };

    for (const auto& test : test_cases) {
        std::vector<int> va = std::get<0>(test);
        std::reverse(va.begin(), va.end());
        std::vector<int> vb = std::get<1>(test);
        std::reverse(vb.begin(), vb.end());
        std::vector<int> ve = std::get<2>(test);
        std::reverse(ve.begin(), ve.end());
        NumberAsList la = NumberAsList(va);
        NumberAsList lb = NumberAsList(vb);
        NumberAsList le = NumberAsList(ve);

        ListNode* a = la.head;
        ListNode* b = lb.head;

        const ListNode* expected = le.head;
        ListNode* answer = Solution().addTwoNumbers(a, b);
        NumberAsList lans = NumberAsList(answer);

        std::cout << std::get<0>(test) << " + " << std::get<1>(test) << std::endl;
        std::cout << *((LinkedList*)&la) << " + " << *((LinkedList*)&lb)
                  << std::endl;
        std::cout << la << " + " << lb << std::endl;
        std::cout << utils::CheckAnswer<NumberAsList>(lans, le) << std::endl;
        ;
    }

    return 0;
}
