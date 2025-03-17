//pa6_1.cpp
//Name: Matthew Norman
#include <iostream>
#include <stack>

using namespace std;
//insert at bottom
void insertAtBottom(stack<int>& st, int x) {
    if (st.empty()) {
        st.push(x);
        return;
    }
    int temp = st.top();
    st.pop();
    insertAtBottom(st, x);
    st.push(temp);
}
//reverse stack
void reverseStack(stack<int>& st) {
    if (st.empty()) {
        return;
    }
    int x = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, x);
}

int main() {
    stack<int> myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    myStack.push(4);

    cout << "Original Stack (top to bottom): ";
    stack<int> tempStack = myStack;
    while (!tempStack.empty()) {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;

    reverseStack(myStack);

    cout << "Reversed Stack (top to bottom): ";
    tempStack = myStack;
    while (!tempStack.empty()) {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;

    return 0;

}
    