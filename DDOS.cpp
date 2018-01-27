//операции над матрицами
#include <iostream>
#include <iomanip>
using namespace std;

double **countFunction(int N, double **a, double **b, char operation) {
	double **mas = new double*[N];
	for (int i = 0; i < N; i++) {
		mas[i] = new double[N];
	}

	switch (operation) {
	case '-':
        for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				mas[i][j] = a[i][j] - b[i][j];
			}
    break;
	case '+':
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				mas[i][j] = a[i][j] + b[i][j];
			}
    break;
    case '*':
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
                mas[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    mas[i][j] += a[i][k] * b[k][j];
                }

			}
    break;
	default:
	    cout << "Недопустимый знак операции!" << endl;
	}
	return mas;
}

int main()
{
    setlocale(0, "");
	char operation;
	int N;

	cout << "Введите число строк/стоблцов матрицы (N): ";
	cin >> N;

	//динамическое выделение памяти для двумерного массива
	double** a = new double*[N];
    double** b = new double*[N];
    for (int i = 0; i < N; i++) {
        a[i] = new double[N];
        b[i] = new double[N];
    }
    //ввод матриц
    cout << "Введите первую матрицу (" << N*N << " чисел) :" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> a[i][j];
    cout << "Введите вторую матрицу (" << N*N << " чисел) :" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> b[i][j];
    //ввод операции
    cout << "Введите знак операции (+/-/*): ";
    cin >> operation;
    //вывод результата
    double **result = countFunction(N, a, b, operation);
    if (result == NULL) return 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(5) << result[i][j];
        cout << endl;
    }

    return 0;
}

