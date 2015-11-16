#include <iostream>

using namespace std;

int main()
{
    int A[10] = {1,20,3,4,5,6,40,20,9,10};
    cout << "Hello world!" << endl;
    int num = 10;
    for (int i = 0; i < num; i++)
    {
        if (A[i] == 20)
        {
            for (int j = i; j > 0; j--)
            {
                A[j] = A[j-1];
            }
            A[0] = 0;
        }
    }
    for (int i = 0; i < num; i++)
    {
        cout << A[i] << endl;
    }



    return 0;
}
