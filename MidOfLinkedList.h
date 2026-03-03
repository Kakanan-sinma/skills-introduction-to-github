Node* findMid(Node* head){
  if(head == nullptr || head->next == nullptr) return head;
  Node* fast = head;
  Node* slow = head;
  while(fast != nullptr && fast->next != nullptr){
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
