#include "sorts.h"

uint64_t Factorial(int32_t n) {
    uint64_t res = 1;
    for (int32_t i{ 2 }; i <= n; ++i) {
        res *= i;
    }
    return res;
}


void Menu() {
    int32_t choice{};
    do {
        system("cls");
        std::cout << "======================================Menu=====================================\n";
        std::cout << "Select the operating mode: \n";
        std::cout << "1.Console input and text file output\n";
        std::cout << "2.Generating data using a random number generator and writing it to a text file\n";
        std::cout << "3.Input from a text file and output to the console\n";
        std::cout << "=============================== 0.Exit programm ===============================\n";
        std::cin >> choice;
       

        if (choice >= 1 && choice <= 3) {
            MenuList1(choice);
        }
        else if (choice == 0) {
            exit(0);
        }
        else {
            std::cout << "Wrong number try again.\n";
            system("pause");
        }
    } while (choice != 0);
}

void MenuList1(int32_t ioM) {
    int32_t choice{};
    do {
        system("cls");
        std::cout << "======================================Menu=====================================\n";
        std::cout << "Selected mode: " << ioM<< std::endl;
        std::cout << "Select the data type to work with: \n";
        std::cout << "1.Integer\n";
        std::cout << "2.Real\n";
        std::cout << "3.Char\n";
        std::cout << "4.String\n";
        std::cout << "5.Student\n";
        std::cout << "============================= 0.Back to main menu =============================\n";
        std::cin >> choice;


        if (choice >= 1 && choice <= 5) {
            MenuSorts(ioM, choice);
        }
        else if (choice != 0) {
            std::cout << "Wrong number try again.\n";
            system("pause");
        }
    } while (choice != 0);
    Menu();
}

bool MenuSortOrder(int32_t ioM, int32_t dataType) {
    bool order{};
    int32_t select{};
        system("cls");
        std::cout << "============================== Select sort mode ==============================\n";
        std::cout << "1. Ascending          2. Descending\n";
        std::cout << "==================================== 0. Back ===================================\n";
        std::cin >> select;
        switch (select)
        {
        case 1:
            return(false);
            break;
        case 2:
            return(true);
            break;
        case 0:
            MenuSorts(ioM, dataType);
            break;
        default:
            std::cout << "Try again\n";
            system("pause");
            MenuSortOrder(ioM, dataType);
            break;
        }
}

void MenuSorts(int32_t ioM, int32_t dataType) {
    int32_t choice{};
    system("cls");
    std::cout << "============================== Select sort method ==============================\n";
    std::cout << "1. BubbleSort         6. QuickSort\n";
    std::cout << "2. ShakerSort             7. MergeSort\n";
    std::cout << "3. CombSort          8. CountingSort (only int/char)\n";
    std::cout << "4. InsertionSort          9. BogoSort\n";
    std::cout << "5. SelectionSort           10. HeapSort\n";
    std::cout << "==================================== 0. Back ===================================\n";
    std::cin >> choice;
    if (choice < 0 || choice > 10) {
        std::cout << "Wrong number try again.\n";
        system("pause");
        MenuSorts(ioM, dataType);
        return;
    }
    if (choice == 0) {
        MenuList1(ioM);
    }
    bool isDescending{ MenuSortOrder(ioM,dataType) };
    

    switch (dataType) {
    case 1: HandleSortingProcess<int32_t>(ioM, choice, isDescending);
        break;
    case 2: HandleSortingProcess<double>(ioM, choice, isDescending);
        break;
    case 3: HandleSortingProcess<char>(ioM, choice, isDescending);
        break;
    case 4: HandleSortingProcess<std::string>(ioM, choice, isDescending);
        break;
    case 5: HandleStudentSorting(ioM, choice, isDescending);
        break;
    }
}

void FillZero(int32_t* arr, int32_t size) {
    for (int32_t i{}; i < size; ++i) {
        arr[i] = 0;
    }
}
void CountingSort(int32_t* arr, int32_t size) {
    if (size == 0) {
        return;
    }
    int32_t max{ arr[0] }, min{ arr[0] };

    for (int32_t i{ 1 }; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    int32_t range{ max - min + 1 };
    int32_t* count = new int32_t[range];
    FillZero(count, range);
    int32_t* output = new int32_t[size];

    for (int32_t i{}; i < size; i++) {
        count[arr[i] - min]++;
    }
    for (int32_t i{ 1 }; i < range; i++) {
        count[i] += count[i - 1];
    }
    for (int32_t i{ size - 1 }; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int32_t i{}; i < size; i++) {
        arr[i] = output[i];
        PrintArray(arr, size);
    }
    delete[] count;
    delete[] output;
}

void CountingSort(char* arr, int32_t size) {
    char* output = new char[size];
    int32_t count[256] = { 0 };

    for (int32_t i{}; i < size; ++i) {
        count[arr[i]]++;
    }
    for (int32_t i{ 1 }; i <= 255; ++i) {
        count[i] += count[i - 1];
    }
    for (int32_t i{ size - 1 }; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        --count[arr[i]];
    }
    for (int32_t i{}; i < size; ++i) {
        arr[i] = output[i];
        PrintArray(arr, size);
    }
    delete[] output;
}

void HandleStudentSorting(int32_t ioM, int32_t sortSelector, bool isDescending) {
    int32_t size{};
    std::cout << "Input student array size: ";
    std::cin >> size;

    if (size <= 0) {
        return;
    }

    Student* arr = new Student[size];

    if (ioM == 1) {
        for (int32_t i{}; i < size; ++i) {
            std::cout << "Student " << i + 1 << " (Course Group Fullname Grade1 Grade2 Grade3):\n";
            std::cin >> arr[i].course >> arr[i].group_number;
            std::cin.ignore();
            getline(std::cin, arr[i].full_name);
            std::cin >> arr[i].grades[0] >> arr[i].grades[1] >> arr[i].grades[2];
        }
    }
    else {
        std::cout << "This mode is not implemented for students.\n";
        delete[] arr;
        return;
    }

    RunSort(sortSelector, arr, size, isDescending);

    delete[] arr;
    system("pause");
}