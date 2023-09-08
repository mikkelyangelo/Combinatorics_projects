#include <iostream>
#include <vector>
#include <map>

using namespace std;

#include <iostream>
#include <fstream>
#include <new>

using namespace std;

#define filename "matrix.txt"

int** create_matrix(int rows, int cols) //Создание матрицы
{
    int** matrix = new int* [rows];
        for(int i = 0; i < cols; i++)
	{
            matrix[i] = new int [cols];
        }
    return matrix;
}

void delete_matrix(int** matrix, int rows) //Удаление матрицы
{
    for (int i = 0; i < rows; i++)
    {
        delete [] matrix[i];
    }
}

// Формат файла: число строк, число столбцов, матрица
int** read_matrix_from_file(int &rows, int &cols)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Неверное имя файла" << endl;
    }
    fin >> rows >> cols;//Считывание количества строк и столбцов
    int** matrix = create_matrix(rows, cols);//Формирование матрицы
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
	{
            fin >> matrix[i][j];
        }
    }
    fin.close();
    return matrix;
}

void print_matrix(int** matrix, int rows, int cols)
{
    cout << "Матрица:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
	{
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "Количество строк:" << ' ' << rows << endl;
    cout << "Количество столбцов:" << ' ' << cols << endl;

}

vector <vector <int> > create_families(int** matrix, int rows, int cols) //Функция создания семейства подмножеств
{
    vector <vector <int> > S;
    
    for (int i = 0; i < rows; i++)
    {
        vector<int> family;
        for (int j = 0; j < cols; j++)
	{
            if (matrix[i][j] == 1)
	    {
                family.push_back(j + 1);
            }
        }
        S.push_back(family);
    }
    return S;
}

bool elem_in_vector (int x, vector<int> v) //Функция для проверки, есть ли элемент в Т0
{
    for (int i = 0; i < v.size(); i++)
    {
        if (x == v[i])
	{
            return true;
        }
    }
    return false;
}

vector<int> create_T0 (vector <vector<int> > S) //Функция инициализации Т0
{
    vector<int> T0;

    for (int i = 0; i < S.size(); i++) //Проходимся по подмножествам
    {
        bool set_new_elem = true;//переменная, для проверки, выбрали ли элемент из данного подмножества(если false - уже выбрали)
        bool can_have_elem = false;//переменная для проверки, был ли добавлен в Т0 элемент из подмножества
        for (int j = 0; j < S[i].size() && set_new_elem; j++)//Проходимся по элементам подмножества
 	{
            if (!elem_in_vector(S[i][j], T0)) //Если элемент еще не присутствует в Т0
	    {
                T0.push_back(S[i][j]);//Добавляем
		cout << "S" << i << "=T(" << S[i][j] << "); ";
                set_new_elem = false;
                can_have_elem = true;
            }
	    else
	    {
                can_have_elem = false;
            }
        }
        if (!can_have_elem) //если все элементы подмножества уже присутствуют в Т0, выход их функции
        {
            return T0;
        }
    }
    return T0;
}

void print_vector(vector<int> v) //Вывод вектора
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }
    cout << endl;
}

vector<int> stick_vectors(vector<int> L, vector<int> S) //Функция добавления элементов подмножеств в L
{
    for (int i = 0; i < S.size(); i++)
    {
        if (!elem_in_vector(S[i], L))
	{
            L.push_back(S[i]);
        }
    }
    return L;
}

int index_in_vector(int x, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (x == v[i])
	{
            return i;
        }
    }
    return -1;
}

int index_in_added_families(map<int, vector<int> >& added_families, int x, int after = -1)
{
    int i = 0;
    for (auto it = added_families.begin(); it != added_families.end(); it++)
    {
        i = it->first;
        if (i > after) {
            if (elem_in_vector(x, added_families[i])) {
                return i;
            }
        }
    }
    return -1;
}

vector<int> finding_of_next_elem(vector<int>& T, vector< vector<int> >& S) //Функция замены представителя и расширения Т
{
    vector<int> L;
    vector<int> T_new = T;
    int next_agent = T.size();

    L = S[next_agent];  // L_0

    cout << endl << "L0:" << endl;
    print_vector(L);

    int i = 0;
    int j = index_in_vector(L[i], T);//проверка, есть ли элемент подмножества в Т
    map<int , vector<int> > added_families;
    while (j != -1) {
        added_families[j] = S[j];
        L = stick_vectors(L, S[j]);//добавления элементов подмножеств к L
        cout << endl << "L"<< i + 1 << ":"<< endl;
        print_vector(L);

        i++;
        j = index_in_vector(L[i], T);
    }


    int new_agent = L[i];
    int agent_to_swap = 0;
    int replace_index = -1;

    while(!elem_in_vector(new_agent, S[next_agent]))
    {
        replace_index = index_in_added_families(added_families, new_agent, replace_index);
        agent_to_swap = T_new[replace_index];
        T_new[replace_index] = new_agent;

        new_agent = agent_to_swap;
    }

    T_new.push_back(new_agent);
    cout << endl << "T" << endl;
    print_vector(T_new);
    return T_new;
}

int main()
{
    int rows = 0, cols = 0;
    int** matrix = read_matrix_from_file(rows, cols); //Чтение матрицы из файла с помощью функции read_matrix_from_file
    print_matrix(matrix, rows, cols);//Вывод матрицы

    vector <vector <int> > S = create_families(matrix, rows, cols);//Создание семейства подмножеств

    cout << endl << "Семейства:" << endl;
    for (int i = 0; i < S.size(); i++)
    {
        cout << "S" << i + 1 << ": ";
        print_vector(S[i]);//Вывод подмножеств
    }
    cout << endl << "Инициализация Т: ";
    vector <int> T = create_T0(S);//Инициализация Т0
    cout << endl << "T0:" << endl;
    print_vector(T);
    int size_T0 = T.size();
    for (int i = 0; T.size() != rows; i++)
    {
        cout << endl << i + 1 << ") Выбор представителя S" << i+size_T0 + 1 << ":" << endl;
        T = finding_of_next_elem(T, S); //Замена представителя и расширение Т
    }

    delete_matrix(matrix, rows);
    return 0;
