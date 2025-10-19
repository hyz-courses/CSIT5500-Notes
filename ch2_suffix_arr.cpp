#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Node {
    public:
        pair<int, int> value;
        Node* next;
        Node(pair<int, int> value){
            this->value = value;
            this->next = nullptr;
        }
};

vector<pair<Node*, Node*>> insert_to_linked_list(
    vector<pair<int, int>> pair_list,
    int max_value,
    int (*criterion) (pair<int, int>)
){
    vector<pair<Node*, Node*>> linked_list_arr(max_value + 1);
    for (int i=0; i<pair_list.size(); i++){
        Node* node = new Node(pair_list[i]);
        
        int criteria = criterion(pair_list[i]);

        if (!linked_list_arr[criteria].first){
            linked_list_arr[criteria].first = node;
            linked_list_arr[criteria].second = nullptr;
        }else if (
            linked_list_arr[criteria].first &&
            !linked_list_arr[criteria].second
        ){
            linked_list_arr[criteria].first->next = node;
            linked_list_arr[criteria].second = linked_list_arr[criteria].first;
        } else{
            Node *head = linked_list_arr[criteria].first;
            Node *tail_before = linked_list_arr[criteria].second;
            Node *tail = tail_before->next;
            tail->next = node;
            linked_list_arr[criteria].second = tail;
        }
    }
    return linked_list_arr;
}

vector<pair<int, int>> flatten_linked_list(
    vector<pair<Node*, Node*>> linked_list_arr,
    int size
){ 
    vector<pair<int, int>> flattened_linked_list;

    for (int i=0; i<linked_list_arr.size(); i++){
        if (!linked_list_arr[i].first) continue;
        if (linked_list_arr[i].first && !linked_list_arr[i].second){
            flattened_linked_list.push_back(linked_list_arr[i].first->value);
            continue;
        }
        Node *head = linked_list_arr[i].first;
        while (head){
            flattened_linked_list.push_back(head->value);
            head = head->next;
        }
    }

    return flattened_linked_list;
}

int sort_pairs(
    vector<pair<int, int>> pair_list,
    int max_value
){
    vector<pair<Node*, Node*>> second_elem_arr = insert_to_linked_list(
        pair_list,
        max_value,
        [](pair<int, int> pair){
            return pair.second;
        }
    );

    vector<pair<int, int>> second_sorted_pair_list = flatten_linked_list(
        second_elem_arr,
        pair_list.size()
    );

    vector<pair<Node*, Node*>> first_elem_arr = insert_to_linked_list(
        second_sorted_pair_list,
        max_value,
        [](pair<int, int> pair){
            return pair.first;
        }
    );

    vector<pair<int, int>> first_sorted_pair_list = flatten_linked_list(
        first_elem_arr,
        pair_list.size()
    );
    
    for (int i=0; i<first_sorted_pair_list.size(); i++){
        cout << first_sorted_pair_list[i].first << " " << first_sorted_pair_list[i].second << endl;
    }

    return 0;
}

int main(){
    // string sample = "aabccaba";

    // long long string_size = sample.size();

    sort_pairs(
        {{1, 2}, {2, 1}, {1, 3}, {2, 3}, {1, 4}, {2, 4}, {1, 5}, {2, 5}, {1, 6}, {2, 6}},
        6
    );
}