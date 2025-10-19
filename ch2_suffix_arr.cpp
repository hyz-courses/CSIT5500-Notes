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

vector<pair<int, int>> sort_pairs(
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
    
    // for (int i=0; i<first_sorted_pair_list.size(); i++){
    //     cout << first_sorted_pair_list[i].first << " " << first_sorted_pair_list[i].second << endl;
    // }

    return first_sorted_pair_list;
}

int main(){
    // string sample = "aabccaba";

    // long long string_size = sample.size();

    string sample;
    cin >> sample;


    int num_stages = 1;
    int length = sample.size();
    int _length = length;
    while(_length > 0){
        _length = _length >> 1;
        num_stages++;
    }
    int pad_length = (1 << num_stages) - length;
    sample += string(pad_length, '$');
    length = sample.size();

    vector<pair<int, int>> pair_list;
    map<string, int> substring_map;

    // Convert char to int to sort
    map<int, int> set;
    for(int i=0; i<length; i++){
        if (set.find((int) sample[i]) != set.end()) continue;
        pair_list.push_back((pair<int, int>){sample[i], i});
        set[(int) sample[i]] = i;
    }

    pair_list = sort_pairs(pair_list, 200);
    
    // Convert int back to char, then to string.
    for(int i=0; i<pair_list.size(); i++){
        pair<int, int> this_pair = pair_list[i];
        char c = this_pair.first;
        string s = string(1, c);
        substring_map[s] = i + 1;
    }


    for (int i=1; i<num_stages + 1; i++){
        vector<pair<int, int>> stage_pair_list;
        map<pair<int, int>, string> substring_pair_map;

        for(int j=0; j<length - (1 << i); j++){
            string substring = sample.substr(j, (1 << i));
            int first_half = substring_map[
                substring.substr(0, substring.size() >> 1)];
            int second_half = substring_map[substring.substr(
                substring.size() >> 1, 
                substring.size() >> 1)];
            if (
                substring_pair_map.find({first_half, second_half}) != substring_pair_map.end()
            ) continue;

            stage_pair_list.push_back((pair<int, int>){first_half, second_half});
            substring_pair_map.insert({(pair<int, int>){first_half, second_half}, substring});
        }

        vector<pair<int, int>> sorted_pair_list = sort_pairs(stage_pair_list, length - num_stages);
        
        vector<string> sorted_substrings;
        for(int j=0; j<sorted_pair_list.size(); j++){
            cout << j + 1 << " "<< substring_pair_map[sorted_pair_list[j]] << " => " << sorted_pair_list[j].first << " " << sorted_pair_list[j].second << endl;
            sorted_substrings.push_back(substring_pair_map[sorted_pair_list[j]]);
            substring_map.insert({
                substring_pair_map[sorted_pair_list[j]], j + 1});
        }
        cout << "\n";
    }
}