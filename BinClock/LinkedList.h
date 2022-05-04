#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<typename K, typename V>
/*
*   Obj definition for a linked list designed to contain all LEDs in the binary clock in a liner format
*/
class LinkedList {
    public:
        LinkedList();

        LinkedList(const LinkedList<K, V>& rhs);

        ~LinkedList();

        void ins(const K& search_led_pos, const V& new_led_idx);

        bool find(const K& search_led_pos, const V& result_led_idx) const;

        // void outputPositionOrder() const;

        void clear() const;

        int size() const;

    private:
        struct Node {
            //  Position in clock array (eg. "0")
            K led_pos;
            V led_idx;
            Node<T>* next;
            Node<T>* prev;
        };

        int length;
        Node* head;
        Node* tail;
};

template<typename K, typename V>
LinkedList<K, V>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<typename K, typename V>
LinkedList<K, V>::LinkedList(const LinkedList<K, V>& rhs) {
    //  Make sure two items aren't the same
    if (this == &rhs)
        return *this;

    Node* temp = rhs.head;
    while(temp != nullptr) {
    }
}

template<typename K, typename V>
LinkedList<K, V>::~LinkedList() {
    Node* curr_head = head;
    while (curr_head != nullptr) {
        Node* new_head = next;
        delete curr_head;
        curr_head = new_head;
    }

    curr_head = nullptr;
}

template<typename K, typename V>
void LinkedList<K, V>::ins(const K& search_led_pos, const V& new_led_idx) {
    Node* new_ins = new Node;
    new_ins->led_pos = search_led_pos;
    new_ins->led_idx = new_led_idx;
    new_ins->next = nullptr;

    //  Empty list -> set new node as the head and tail of the list
    if (length == 0) {
        head = new_ins;
        tail = new_ins;
        length++;
        return;
    }

    tail->next = new_ins;
    tail = new_ins;
    length++;
}

template<typename K, typename V>
bool LinkedList<K, V>::find(const K& search_led_pos, const V& result_led_idx) const {
    Node* iter = head;
    while (iter->next != null) {
        if (iter->led_pos == search_led_pos) {
            result_led_idx = iter->led_idx;
            return true;
        }

        iter = iter->next;
    }

    result_led_idx = -1;
    return false;
}

template<typename K, typename V>
int LinkedList<K, V>::size() const { return this->length; }

#endif