#include <iostream>
#include "stack.hpp" // or include both .hpp and .cpp if needed

template<class T>
void Stack<T>::push(T c){
  if(topIndex > MAXSIZE-1){
    cout<<"Stack overflow"<<endl;
    return;
  }
  arr[topIndex + 1] = c;
  topIndex++;
}

template<class T>
T Stack<T>::pop(){
  if(topIndex < 0){
    cout<<"Cannot delete. Stack empty."<<endl;
  }

  return arr[topIndex--];
}

template<class T>
T Stack<T>::peek(){
  if(topIndex < 0){
    cout<<"Cannot peek. Stack empty."<<endl;
  }
  return arr[topIndex];
}

template<class T>
int Stack<T>::size(){
  return topIndex+1;
}

template<class T>
void Stack<T>::display(){
  for(int i=topIndex; i>=0; --i){
    cout<<arr[i]<<"\t";
  }
  cout<<endl;
}

template class Stack<char>;
template class Stack<int>;

int main() {
/*  
    // Create a stack of int
    Stack<int> st;

    // Test pushing
    std::cout << "Pushing 10, 20, 30 onto the stack..." << std::endl;
    st.push(10);
    st.push(20);
    st.push(30);

    // Display current stack
    std::cout << "Current stack (top to bottom): ";
    st.display(); // Expected output: "30    20    10"

    // Size check
    std::cout << "Stack size: " << st.size() << std::endl; // Expected: 3

    // Peek top
    std::cout << "Top element (peek): " << st.peek() << std::endl; // Expected: 30

    // Pop once
    std::cout << "Popped element: " << st.pop() << std::endl; // Expected: 30
    std::cout << "Stack after popping: ";
    st.display(); // Expected: "20    10"

    // Pop until underflow
    std::cout << "Popping elements until stack underflows..." << std::endl;
    st.pop(); // Popping 20
    st.pop(); // Popping 10
    st.pop(); // Attempt pop on empty => "Cannot delete. Stack empty."

    // Overflow test
    // NOTE: This will fill or exceed the stack. 
    // Use a smaller loop if you don't want to fill 100000 items.
    std::cout << "Attempting to push beyond max size for overflow test." << std::endl;
    for(int i = 0; i < 100002; i++){
        st.push(i);
    }
    // Expect multiple "Stack overflow" messages once capacity is reached.

    return 0;
*/
}

