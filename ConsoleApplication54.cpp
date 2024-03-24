#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class Priority_Queue {
private:
    vector<T> data;

public:
    Priority_Queue(){}
    Priority_Queue(const T& value) { data.push_back(value);};
    Priority_Queue(const Priority_Queue& other) : data(other.data) {}

    void push_back(const T& value) {
        data.push_back(value);
        int index = data.size() - 1;
        while (index > 0 && data[(index - 1) / 2] < data[index]) {
            swap(data[index], data[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    T pop_front() {
        if (empty())
            throw out_of_range("Queue is empty");

        T front_element = data[0];
        swap(data[0], data[data.size() - 1]);
        data.pop_back();

        int index = 0;
        while (true) {
            int left_child = 2 * index + 1;
            int right_child = 2 * index + 2;
            int largest_child = index;

            if (left_child < data.size() && data[left_child] > data[largest_child])
                largest_child = left_child;
            if (right_child < data.size() && data[right_child] > data[largest_child])
                largest_child = right_child;

            if (largest_child != index) {
                swap(data[index], data[largest_child]);
                index = largest_child;
            }
            else {
                break;
            }
        }
        return front_element;
    }

    T pop_back() {
        if (empty())
            throw out_of_range("Queue is empty");

        T back_element = data.back();
        data.pop_back();
        return back_element;
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    bool operator<(const Priority_Queue& other) const {
        return data < other.data;
    }

    bool operator>(const Priority_Queue& other) const {
        return data > other.data;
    }

    bool operator==(const Priority_Queue& other) const {
        return data == other.data;
    }
};


int main()
{
    Priority_Queue<int> pq;
    pq.push_back(10);
    pq.push_back(5);
    pq.push_back(20);

    cout << "Front element: " << pq.pop_front() << endl;
    cout << "Back element: " << pq.pop_back() << endl;
    cout << "Size: " << pq.size() << endl;
    cout << "Is empty? " << (pq.empty() ? "Yes" : "No") << endl;

    Priority_Queue<int> pq2(100);
    cout << "Is pq equal to pq2? " << (pq == pq2 ? "Yes" : "No") << endl;
}