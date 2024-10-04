#include <iostream>
#include <string>
using namespace std;

// UN POINTER NO ES MAS QUE:
//       a) guardar el valor de un address en una variable 
//       b) tener un built in operator * para acceder al valor



// Declare a function before defining it so you can use it in the code
void some_function_for_pass_by_reference(int xf, int &yf);
int sum_elements_of_array(int* A, int size);
void print_elements_of_array(char* cA);

int main(){
    //      int * const * 
    // Backward .. it is a Pointer to a constant pointer to an integer

    cout << "Hello World \n";
    int a;
    int *p; //Pointer to an integer. int* p is equivalent;
    p = &a; 

    a = 1025;

    cout << "Pointer p:    " << p << "\n";
    cout << "Address of a: " << &a << "\n";
    cout << "Pointer p as int: " << reinterpret_cast<uintptr_t>(p)  << "\n";
    int *store_p = p;

    cout << "Dereferenced p, *p: " << *p << "\n";
    cout << "a: " << a << "\n";

    // Pointer arithmetic
    // p++-> increments the pointer enough to go out of the memory space. For an int, it will go to &a + 4
    cout << "\n\nPOINTER ARITHMETIC\n";
    p++;
    cout << "Pointer p: " << p << "\n";
    cout << "Address of a: " << &a << "\n";
    cout << "Pointer p as int: " << reinterpret_cast<uintptr_t>(p)  << "\n";
    cout << "Difference in hex: " << p - store_p << "\n";
    cout << "Difference in int: " << reinterpret_cast<uintptr_t>(p) - reinterpret_cast<uintptr_t>(store_p) << "\n";

    // Pointer typed dependencies
    // Pointers are typed because they store memory + memory range from where to read (dereference)

    char* pchar; // Memory size of 1
    //pchar = (char*)p; // With this typecast, we will reference to the same start addres, but only grab 1 byte
    // This is important because in memory, the values are written in binary, and the binary 1s can be spread across different bytes (value or sign)
    pchar = reinterpret_cast<char*>(p);
    cout << "Pointer pchar: " << static_cast<void*>(pchar)<< "\n";
    cout << "*pchar: " << static_cast<int>(*pchar)  << "\n";

    // Pointer to Pointer
    cout << "\n\nPOINTER TO POINTER\n";
    int int_p2p = 5; // 4 bytes
    int *p_p2p = &int_p2p;
    int **p2p = &p_p2p;
    cout << "OG integer: " << int_p2p << "\n";
    cout << "Address of p_p2p: " << p_p2p << "\n";
    cout << "Dereferenced p2p, *p: " << *p2p << "\n";
    cout << "Double Dereferenced p2p, *p: " << **p2p << "\n";

    // Pointer as function arguments
        // When you pass a variable to a function, a copy of that variable needs to be created.
        // This copy consumes memory, as well as the return for example.
        // Functions called create a stack frame in the stack. The stack frame is cleared after finishing.
        // main has its own stack rame.
    cout << "\n\nPOINTER AS ARGUMENT\n";
    int x = 1;
    int y = 2;
    cout << "address variable x outside function: " << &x << "\n";
    cout << "address variable x outside function: " << &y << "\n";
    some_function_for_pass_by_reference(x, y);
    // En C:
    // void function(int *xf)
    // function(&x)

    // Pointers and arrays
    cout << "\n\nARRAYS\n";
    int A[] = {1, 2, 3, 4, 5}; // 20 bytes
    A[0]; // Address X
    A[1]; // Address X + 4 (size int)
    A[2]; // Address X + 8 (size int)
    A[3]; // Address X + 12 (size int)
    A[4]; // Address X + 16 (size int)
    int *pA = A;
    cout << "p: " << pA << "\n"; // ya es un address de por si
    cout << "*p: " << *pA << "\n";

    cout << "variable A  (en realidad es imprimir un pointer, que escribe un address!!): " << A << "\n";     //    Ojo como variable A en realidad es un address, no una lista estilo python!!

    cout << "address variable A: " << &A << "\n";
    cout << "address variable A[0]: " << &A[0] << "\n";
    cout << "address variable A[1]: " << &A[1] << "\n";
    cout << "address variable (A + 1): " << (A + 1) << "\n";

    cout << "variable A[0]: " << A[0] << "\n";
    cout << "deference variable *A: " << *A << "\n";
    cout << "variable A[1]: " << A[1] << "\n";
    cout << "deference variable *(A + 1): " << *(A + 1) << "\n";
  
    // Conclusion: los arrays en realidad son un bloque de pointers especial.
    //    El usar corchetes [] es un shortcut de C para simplificar el hacer *(A+1), que es equivalente de acuerdo a pointer arithmetic
    //    Ojo como variable A en realidad es un address, no una lista estilo python!!


    cout << "\n\nARRAY AS FUNCTION ARGUMENTS\n";
    int array_sum_result;
    int sum = 0;

    int size = sizeof(A) / sizeof(A[0]);  // 20 / 4
    cout << "size in main: " << size << "\n";
    array_sum_result = sum_elements_of_array(A, size); // This is actually a call by reference
    cout << "sum of elements: " << array_sum_result << "\n";


    cout << "\n\nCHARACTER ARRAYS - STRINGS\n";
    // Summary: like an integer array but with the "smart" method of printing by default the whole string instead of the adress

    // C LANGUAGE
    // SIZE OF ARRAY >= Number of characters + 1  (that corresponds to null character to indicate end of string)
    // char C[4];
    // C[0] = "J";
    // C[1] = "O"; 
    // C[2] = "H"; 
    // C[3] = "N"; 
    // print("%s", C);   -> bunch of weird characters after John
    // C[4] = "\0"; 
    // print("%s", C);   -> only John
    // int len = strlen(C);
    // printf("Length of string = %d\n", len); -> 4; gracias a null character sabe incluso la longitud real

    // char c1[6] = "Hello"; -> include null pointer at the end
    //char* C2;
    //C2 = C1; -> esto es un address de por si, al igual que los arrays

    // ASCII table contains the correspondence between hex/bin and characters
    const char* name = "Cherno"; // This is an actual string. MUST BE CONSTANT
    std::string name_library = "Cherno"; // This is an actual string too CONST!!. Contains null pointer at the end
    char name2[6] = {'C', 'h', 'e', 'r', 'n', 'o'}; // This is a caracter array. CAN BE NON CONSTANT!
    char name2_ended_with_null[7] = {'C', 'h', 'e', 'r', 'n', 'o', 0}; // This is a character array ended in null. 
    char name3[7] = "Cherno"; // If written like this, we need one extra memory slot for the null terminator, which is implicit
    cout << "name: " << name << "\n";
    cout << "name_library " << name_library << "\n";
    cout << "char array without end character: " << name2 << "\n";
    cout << "char array with end character:: " << name2_ended_with_null << "\n";
    name3[1] = 'b';
    cout << "name with position 1 modifier: " << name3 << "\n";
    *(name3 + 2) = 'z'; // Again, name aint nothing but a pointer to the beggining of the array
    cout << "name with position 2 modifier: " << name3 << "\n";

    print_elements_of_array(name3);

    // Concatenation

    //The std::string class has an overloaded operator+ that allows you to concatenate another string (like a C-style string " Hello") 

    std::string name_concatenation_fail = "Cherno"; //+ " Hello"; // Ilegal!!
    //This implicitly constructs a std::string object from the string literal "Cherno".
    cout << "name_concatenation_fail: " << name_concatenation_fail << "\n";
    name_concatenation_fail += " this is valid instead"; 
    cout << "name_concatenation_fail " << name_concatenation_fail << "\n";

    std::string name_concatenation_good = std::string("Cherno") + " Hello"; 
    //This explicitly constructs a std::string object from the string literal "Cherno".
    cout << "name_concatenation_good " << name_concatenation_good << "\n";
    cout << "std::string(Cherno) " << std::string("Cherno") << "\n";

    cout << "name_concatenation_good.find(no): " << name_concatenation_good.find("no") << "\n";


    return 0;
}

void some_function_for_pass_by_reference(int xf, int &yf){
    cout << "address variable x inside function: " << &xf << "\n";
    cout << "address variable x inside function: " << &yf << "\n";
    cout << "observe how yf is equal to y \n";
}

int sum_elements_of_array(int* A, int size){  // The compiler only copies the variable with the first address -> int* A
    int sum = 0;

    // We cannot use this with arrays
    // for (; A!=nullptr; ++A)
    //     sum += *A;
    //     cout << "sum: " << sum << "\n";

    // int size = sizeof(A) / sizeof(A[0]); // Sizeof A will not be 20, it will be 4
    // cout << "size in function: " << size << "\n";

    // This is why we need to pass the size as unction argument and not calculated in situ
    int i;
    for (i = 0; i<size; ++i){
        sum += *(A+i);
        //sum += A[i];
        cout << "sum: " << *(A + i) << "\n";
    }
    return sum;
}

void print_elements_of_array(char* cA){
    // Here we are passing a pointer to the first memory slot. By specifying const, the +1 effect is +1 byte
    while (*cA != '\0')
    {
        cout << "\n" << *cA;
        cA++; // advance the memory in +1 position -> 1 byte for char
    }
    cout << "\n";
}
