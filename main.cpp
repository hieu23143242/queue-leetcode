#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <vector>
#include <deque>

using namespace std;

class MyStack {
private:
    queue<int> q1;
    queue<int> q2;
public:
    MyStack() {
        // do nothing
    }
    void push(int x) {
        this->q1.push(x);
        while (!this->q2.empty()) {
            this->q1.push(this->q2.front());
            this->q2.pop();
        }
        swap(this->q1, this->q2);
    }
    int pop() {
        int res = this->q2.front();
        this->q2.pop();
        return res;
    }
    int top() {
        return this->q2.front();
    }
    bool empty() {
        return this->q2.empty();
    }
};

class MyQueue {
private:
    stack<int> s1;
    stack<int> s2;
public:
    MyQueue() {/*do nothing*/}

    void push(int x) {
        this->s1.push(x);
    }

    int pop() {
        if (!this->s2.empty()) {
            int res = this->s2.top();
            this->s2.pop();
            return res;
        }
        while (!this->s1.empty()) {
            this->s2.push(this->s1.top());
            this->s1.pop();
        }
        return this->pop();
    }

    int peek() {
        if (!this->s2.empty()) return this->s2.top();
        while (!this->s1.empty()) {
            this->s2.push(this->s1.top());
            this->s1.pop();
        }
        return this->peek();
    }

    bool empty() {
        return this->s1.empty() && this->s2.empty();
    }
};

int firstUniqChar(string s) {
    unordered_map<char, int> m;
    for (char c: s) {
        m[c] ++;
    }
    for (int i=0; i<s.length(); i++) {
        if (m[s[i]] == 1) {
            return i;
        }
    }
    return -1;
}

class MyCircularQueue {
private:
    vector<int> queue;
    int maxSize;
    int currentSize;
    int front;
    int rear;
public:
    MyCircularQueue(int k) {
        this->queue.resize(k);
        this->front = -1;
        this->rear = -1;
        this->maxSize = k;
        this->currentSize = 0;
    }
    bool isEmpty() {
        return this->currentSize == 0;
    }
    bool isFull() {
        return this->currentSize == this->maxSize;
    }
    bool enQueue(int value) {
        if (this->isFull()) return false;
        if (this->isEmpty()) {
            this->front = 0;
        }
        this->rear = (this->rear + 1) % this->maxSize;
        this->queue[this->rear] = value;
        this->currentSize ++;
        return true;
    }
    bool deQueue() {
        if (this->isEmpty()) return false;
        if (this->front == this->rear) {
            this->front = -1;
            this->rear = -1;
            this->currentSize --;
            return true;
        }
        this->front = (this->front + 1) % this->maxSize;
        this->currentSize --;
        return true;
    }
    int Front() {
        if (this->isEmpty()) return -1;
        return this->queue[this->front];
    }
    int Rear() {
        if (this->isEmpty()) return -1;
        return this->queue[this->rear];
    }
};

class MyCircularDeque {
private:
    vector<int> queue;
    int currentSize;
    int maxSize;
    int front;
    int rear;
public:
    MyCircularDeque(int k) {
        this->queue.resize(k);
        this->currentSize = 0;
        this->maxSize = k;
        this->front = -1;
        this->rear = -1;
    }

    bool insertFront(int value) {
        if (this->isFull()) return false;
        if (this->isEmpty()) {
            this->front = 0;
            this->rear = 0;
        } else {
            this->front = this->front == 0 ? this->maxSize-1 : this->front-1;
        }
        this->queue[this->front] = value;
        this->currentSize ++;
        return true;
    }

    bool insertLast(int value) {
        if (this->isFull()) return false;
        if (this->isEmpty()) {
            this->front = 0;
            this->rear = 0;
        } else {
            this->rear = (this->rear + 1) % this->maxSize;
        }
        this->queue[this->rear] = value;
        this->currentSize ++;
        return true;
    }

    bool deleteFront() {
        if (this->isEmpty()) return false;
        if (this->front == this->rear) {
            this->front = -1;
            this->rear = -1;
        } else {
            this->front = (this->front + 1) % this->maxSize;
        }
        this->currentSize --;
        return true;
    }

    bool deleteLast() {
        if (this->isEmpty()) return false;
        if (this->front == this->rear) {
            this->front = -1;
            this->rear = -1;
        } else {
            this->rear = this->rear == 0 ? this->maxSize-1 : this->rear-1;
        }
        this->currentSize --;
        return true;
    }

    int getFront() {
        if (this->isEmpty()) return -1;
        return this->queue[this->front];
    }

    int getRear() {
        if (this->isEmpty()) return -1;
        return this->queue[this->rear];
    }

    bool isEmpty() {
        return this->currentSize == 0;
    }

    bool isFull() {
        return this->currentSize == this->maxSize;
    }
};

class ProductOfNumbers {
private:
    vector<int> v;
public:
    ProductOfNumbers() {
        v.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            this->v.clear();
            this->v.push_back(1);
        } else {
            this->v.push_back(num * this->v.back());
        }
    }

    int getProduct(int k) {
        if (k >= this->v.size()) return 0;
        return this->v.back() / (this->v[this->v.size()-1-k]);
    }
};

class FrontMiddleBackQueue {
private:
    deque<int> left;
    deque<int> right;
public:
    FrontMiddleBackQueue() {}

    void pushFront(int val) {
        if (this->left.size() <= this->right.size()) {
            this->left.push_front(val);
        } else {
            this->right.push_front(this->left.back());
            this->left.pop_back();
            this->pushFront(val);
        }
    }
    void pushMiddle(int val) {
        if (this->left.size() <= this->right.size()) {
            this->left.push_back(val);
        } else {
            this->right.push_front(val);
        }
    }

    void pushBack(int val) {
        if (this->right.size() < this->left.size()) {
            this->right.push_back(val);
        } else {
            this->left.push_back(this->right.front());
            this->right.pop_front();
            this->pushBack(val);
        }
    }

    int popFront() {
        if (this->left.empty()) return -1;
        int res;
        if (this->left.size() >= this->right.size()) {
            res = this->left.front();
            this->left.pop_front();
        } else {
            this->left.push_back(this->right.front());
            this->right.pop_front();
            return this->popFront();
        }
        return res;
    }

    int popMiddle() {
        if (this->left.size() >= this->right.size()) {
            int res = this->left.back();
            this->left.pop_back();
            return res;
        } else {
            int res = this->right.front();
            this->right.pop_front();
            return res;
        }
    }

    int popBack() {
        if (this->right.empty()) return -1;
        int res;
        if (this->right.size() > this->left.size()) {
            res = this->right.back();
            this->right.pop_back();
        } else {
            this->right.push_front(this->left.back());
            this->left.pop_back();
            return this->popBack();
        }
        return res;
    }
};

int countStudents(vector<int>& students, vector<int>& sandwiches) {
    queue<int> studentQ;
    queue<int> sandwicheQ;
    int cnt = 0;
    for (int i=0; i<students.size(); i++) {
        studentQ.push(students[i]);
        sandwicheQ.push(sandwiches[i]);
    }
    while (!studentQ.empty() && !sandwicheQ.empty() && cnt < studentQ.size()) {
        int student = studentQ.front();
        studentQ.pop();
        int sandwiche = sandwicheQ.front();
        if (sandwiche == student) {
            sandwicheQ.pop();
            cnt = 0;
        } else {
            studentQ.push(student);
            cnt ++;
        }
    }
    return studentQ.size() == 0 ? 0 : studentQ.size();
}

int timeRequiredToBuy(vector<int>& tickets, int k) {
    queue<int> q;
    int wait = 0;
    for(int i=0; i<tickets.size(); i++) {
        q.push(i);
    }
    while (tickets[k] != 0) {
        int front = q.front();
        q.pop();
        if (tickets[front] != 0) {
            wait ++;
            tickets[front] --;
        }
        q.push(front);
    }
    return wait;
}

int findTheWinner(int n, int k) {
    queue<int> q;
    for (int i=1; i<=n; i++) {
        q.push(i);
    }
    int cnt = 0;
    while (q.size() != 1) {
        int front = q.front();
        q.pop();
        cnt ++;
        if (cnt == k) {
            cnt = 0;
        } else {
            q.push(front);
        }
    }
    return q.front();
}

int maxSumSubarray(const vector<int>& nums, int k) {
    int maxSum = 0;
    int currentSum = 0;
    for(int i=0; i<k; i++) {
        currentSum += nums[i];
    }
    maxSum = currentSum;
    for (int i=k; i<nums.size(); i++) {
        currentSum += nums[i] - nums[i-k];
        maxSum = max(currentSum, maxSum);
    }
    return maxSum;
};

long long continuousSubarrays(vector<int>& nums) {
    int left = 0;
    long long cnt;
    int size = nums.size();
    deque<int> mn;
    deque<int> mx;
    for(int i=0; i<size; i++) {
        while (!mn.empty() && nums[i] < mn.front()) {
            mn.pop_front();
        }
        mn.push_back(nums[i]);
        while (!mx.empty() && nums[i] > mx.front()) {
            mx.
        }
    }
}

class DataStream {
private:
    int cnt;
    int k;
    int value;
    queue<int> q;
public:
    DataStream(int value, int k) {
        this->cnt = 0;
        this->k = k;
        this->value = value;
    }

    bool consec(int num) {
        this->q.push(num);
        if (num == this->value) {
            this->cnt ++;
        }
        if (this->q.size() > this->k) {
            int front = this->q.front();
            this->q.pop();
            if (front == this->value) {
                this->cnt --;
            }
        }
        return this->cnt == thí
    }
};

int main() {
    int n;
    vector<int> v;
    cin>>n;
    for(int i=0; i<n; i++) {
        int k;
        cin>>k;
        v.push_back(k);
    }

    return 0;
}
