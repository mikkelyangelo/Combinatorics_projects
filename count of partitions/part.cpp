#include <iostream>
#include <vector>

#define ERR_INPUT_N 1
#define ERR_INPUT_M 2

using namespace std;


void optimize(vector<pair<int, int>> &values){
    int i = 0;
    int check = 0;
    for (auto x : values) {
        int k = 0;
        for (auto j : values) {
            if (j.second == x.second && i != k) {
                values[i].first += j.first;
                values.erase(values.begin() + k);
                check = 1;
                break;
            }

            k++;
        }
        if (check == 1) {
            break;
        }
        i++;
    }
    if (check == 0) {
        return;
    }
    optimize(values);
}

void print(vector<pair<int, int>> &values) {
    cout << endl;
    unsigned long last_element = values.size() - 1;
    for (auto x : values) {
        cout << x.first << "*" << x.second;
        if (x.first != values[last_element].first || x.second != values[last_element].second) {
            cout << " + ";
        }
    }
    cout << endl;
}

int calc_sum(vector<pair<int, int>> &values) {
    int sum = 0;
    for (auto x : values){
        sum = sum + (x.first * x.second);
    }
    return sum;
}

void k_more_1(vector<pair<int, int>> &values) {
    unsigned long last_element = values.size() - 1;
    int except = 2 * values[last_element].second;
    int add = 1 + values[last_element].second;

    pair<int, int> remain = make_pair(values[last_element].first * values[last_element].second - add, 1);

//    cout << "Исключить: " << except << "*1" << endl << "Добавить: 1*"
//         << add <<  endl << "Остаток: " << remain.first << "*1" << endl;

    values[last_element] = make_pair(1, add);
    values.insert(values.cend(), remain);

    if (values[last_element + 1].first == 0) {
        values.pop_back();
    }
}


void k_equally_1(vector<pair<int, int>>& values) {
    unsigned long len_vector = values.size() - 1;
    auto add_new_value = make_pair(1, values[len_vector - 1].second + 1);
    vector<pair<int, int>> delete_value;
//    cout << "Добавить: " << add_new_value.first << "*" << add_new_value.second << endl;

    delete_value.push_back(values[len_vector]);
    delete_value.push_back(values[len_vector - 1]);
    values.pop_back();
    values.pop_back();

//    cout << "Удаление: ";
//    cout << delete_value[0].first << "*" << delete_value[0].second << ", ";
//    cout << delete_value[1].first << "*" << delete_value[1].second << endl;

    values.push_back(add_new_value);

    int sum_delete = calc_sum(delete_value);

//    cout << "Остаток: ";

    if (sum_delete - add_new_value.second != 0) {
        values.emplace_back(make_pair(sum_delete - add_new_value.second, 1));
//        cout << values[len_vector].first << "*1" << endl;
    } else {
//        cout << "0" << endl;
    }
}

int main() {
    int n, m;
    cout << "Введите число n: ";
    cin >> n;
    if (n <= 0) {
        cout << "Число должно быть больше 0" << endl;
        return ERR_INPUT_N;
    }
    cout << "Введите число m: ";
    cin >> m;
    cout << endl;
    if (m <= 0) {
        cout << "Число должно быть больше 0" << endl;
        return ERR_INPUT_M;
    }

    vector<pair<int, int>> multi_values;
    multi_values.emplace_back(n, 1);

    while (multi_values[0].second != n) {
        if (multi_values[multi_values.size() - 1].first == 1) {
            k_equally_1(multi_values);
        } else {
            k_more_1(multi_values);
        }
        optimize(multi_values);

        int max = 0;
        for (auto x : multi_values){
            if (x.second > max) {
                max = x.second;
            }
        }

        if (max == m) {
            print(multi_values);
        }
    }

    return 0;
