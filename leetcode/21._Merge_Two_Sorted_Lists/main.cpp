#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "../../utilities/linked_list.hpp"
#include "../../utilities/utils.hpp"

using ListNode = linked_list::ListNode<int>;
using LinkedList = linked_list::LinkedList<int>;

class Solution {
   public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* cur_1 = list1;
        ListNode* cur_2 = list2;
        ListNode* head = nullptr;
        if ((cur_1 != nullptr) && (cur_2 != nullptr)) {
            if (cur_1->val > cur_2->val) {
                head = cur_2;
                if (cur_2 != nullptr) {
                    cur_2 = cur_2->next;
                }
            } else {
                head = cur_1;
                if (cur_1 != nullptr) {
                    cur_1 = cur_1->next;
                }
            }
        } else if (cur_1 == nullptr) {
            head = cur_2;
            cur_2 = nullptr;
        } else if (cur_2 == nullptr) {
            head = cur_1;
            cur_1 = nullptr;
        }

        ListNode* merged = head;

        while ((cur_1 != nullptr) || (cur_2 != nullptr)) {
            if ((cur_1 != nullptr) && (cur_2 != nullptr)) {
                if (cur_1->val > cur_2->val) {
                    merged->next = cur_2;
                    if (cur_2 != nullptr) {
                        cur_2 = cur_2->next;
                    }
                } else {
                    merged->next = cur_1;
                    if (cur_1 != nullptr) {
                        cur_1 = cur_1->next;
                    }
                }
            } else if (cur_1 == nullptr) {
                merged->next = cur_2;
                if (cur_2 != nullptr) {
                    cur_2 = cur_2->next;
                }
            } else if (cur_2 == nullptr) {
                merged->next = cur_1;
                if (cur_1 != nullptr) {
                    cur_1 = cur_1->next;
                }
            }

            merged = merged->next;
        }

        return head;
    }
};

int main(void) {
    const std::vector<
        std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>>
        test_cases = {
            {{1, 3, 5, 7}, {2, 3, 4, 6}, {1, 2, 3, 3, 4, 5, 6, 7}},
            {{1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4}},
            {{}, {}, {}},
            {{}, {0}, {0}},
        };

    for (const auto& test : test_cases) {
        std::vector<int> va = std::get<0>(test);
        std::sort(va.begin(), va.end(), std::greater<int>());
        std::vector<int> vb = std::get<1>(test);
        std::sort(vb.begin(), vb.end(), std::greater<int>());
        std::vector<int> ve = std::get<2>(test);
        std::sort(ve.begin(), ve.end(), std::greater<int>());
        LinkedList la = LinkedList(va);
        LinkedList lb = LinkedList(vb);
        LinkedList le = LinkedList(ve);

        ListNode* a = la.head;
        ListNode* b = lb.head;

        const ListNode* expected = le.head;
        ListNode* answer = Solution().mergeTwoLists(a, b);
        LinkedList lans = LinkedList(answer);

        std::cout << std::get<0>(test) << " + " << std::get<1>(test)
                  << std::endl;
        std::cout << la << " + " << lb << std::endl;
        std::cout << utils::CheckAnswer<LinkedList>(lans, le) << std::endl;
    }

    return 0;
}
