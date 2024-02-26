#include <iostream>
#include <vector>

template <typename T>
class ValueContainer {
    private:
        T content;
    public:
        ValueContainer* next = nullptr;

        ValueContainer(T data) {
            content = data;
        }

        void addNext(T data) {
            auto newContainer = new ValueContainer<T>(data);

            if (next != nullptr)
                newContainer->addNext(data);

            next = newContainer;
        }

        T getValue() {
            return content;
        }
};


template <typename KeyType, typename ValueType>
class Node {
    private:
        KeyType key;
        ValueContainer<ValueType>* container;
        std::pair<Node*, Node*> next = {nullptr, nullptr};

    public:
        Node(KeyType _key, ValueType _value) {
            key = _key;
            container = new ValueContainer<ValueType>(_value);
        }

        KeyType getKey() {
            return key;
        }

        void addValue(ValueType value) {
            container->addNext(value);
        }

        std::vector<ValueType> getValue() {
            std::vector<ValueType> result;
            auto current = container;

            while (current != nullptr) {
                result.push_back(current->getValue());
                current = current->next;
            }

            return result;
        }

        Node left() {
            return *next.first;
        }

        Node right() {
            return *next.second;
        }

        void addLeft(Node<KeyType, ValueType>* data) {
            next.first = data;
        }
};


int main() {
    Node<std::string, int> test("flex", 1);
    test.addValue(3);

    Node<std::string, int> test2("flex", 2);
    test2.addValue(8);
    test2.addValue(8);
    Node<std::string, int> test5("flex", 5);

    test.addLeft(&test2);
    std::cout << test.left().getKey() << std::endl;

    for (auto data : test.left().getValue()) {
        std::cout << data << " ";
    }

    return 0;
}