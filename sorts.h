#ifndef sorts
#define sorts

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <ctime>
#include <algorithm> 
#include <cstdint>  

void Menu();
void MenuList1(int32_t);
void MenuSorts(int32_t, int32_t);

struct Student {
	int32_t course;
	int32_t group_number;
	std::string full_name;
	int32_t grades[3];
};

inline bool operator>(const Student& a, const Student& b) {
	if (a.course != b.course) {
		return a.course > b.course;
	}
	if (a.group_number != b.group_number) {
		return a.group_number > b.group_number;
	}
	return a.full_name > b.full_name;
}

inline bool operator<(const Student& a, const Student& b) {
	if (a.course != b.course) {
		return a.course < b.course;
	}
	if (a.group_number != b.group_number) {
		return a.group_number < b.group_number;
	}
	return a.full_name < b.full_name;
}

inline std::ostream& operator<<(std::ostream& os, const Student& s) {
	os << "Course: " << s.course
		<< ", Group: " << s.group_number
		<< ", Full Name: " << s.full_name
		<< ", Grades: [" << s.grades[0] << "," << s.grades[1] << "," << s.grades[2] << "]";
	return os;
}

template <class T>
inline bool IsSorted(T* array, int32_t size) {
	for (int32_t i{}; i < size - 1; ++i) {
		if (array[i] > array[i + 1]) {
			return false;
		}
	}
	return true;
}

template <class T>
inline void PrintArray(T* array, int32_t size) {
	for (int32_t i{}; i < size; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << "\n";
}
	
template <class T>
inline void BubbleSort(T* arr, int32_t size, bool isDescending) {
	bool isSwaped{};
	for (int32_t i{}; i < size - 1; ++i) {
		isSwaped = false;
		for (int32_t j{}; j < size - i - 1; ++j) {
			if ((arr[j] > arr[j + 1]) xor isDescending) {
				std::swap(arr[j], arr[j + 1]);
				isSwaped = true;
				PrintArray(arr, size);
			}
		}
		if (!isSwaped) {
			break;
		}
	}
}

template <class T>
inline void ShakerSort(T* arr, int32_t size, bool isDescending) {
	bool swapped{ true };
	int32_t start{};
	int32_t end{ size - 1 };

	while (swapped) {
		swapped = false;
		for (int32_t i{ start }; i < end; ++i) {
			if ((arr[i] > arr[i + 1]) xor isDescending) {
				std::swap(arr[i], arr[i + 1]);
				swapped = true;
				PrintArray(arr, size);
			}
		}
		if (!swapped) {
			break;
		}
		swapped = false;
		--end;
		for (int32_t i{ end - 1 }; i >= start; --i) {
			if ((arr[i] > arr[i + 1]) xor isDescending) {
				std::swap(arr[i], arr[i + 1]);
				swapped = true;
				PrintArray(arr, size);
			}
		}
		++start;
	}
}

template <class T>
inline void CombSort(T* arr, int32_t size, bool isDescending) {
	int32_t gap{ size };
	const float shrink{ 1.3f };
	bool sorted{ false };

	while (!sorted) {
		gap = static_cast<int32_t>(gap / shrink);
		if (gap <= 1) {
			gap = 1;
			sorted = true;
		}
		for (int32_t i{}; i + gap < size; ++i) {
			if ((arr[i] > arr[i + gap]) xor isDescending) {
				std::swap(arr[i], arr[i + gap]);
				sorted = false;
				PrintArray(arr, size);
			}
		}
	}
}

template <class T>
inline void InsertionSort(T* arr, int32_t size, bool isDescending) {
	for (int32_t i{ 1 }; i < size; ++i) {
		T key = arr[i];
		int32_t j{ i - 1 };
		while (j >= 0 && ((arr[j] > key) xor isDescending)) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		PrintArray(arr, size);
	}
}

template <class T>
inline void SelectionSort(T* arr, int32_t size, bool isDescending) {
	for (int32_t i{}; i < size - 1; ++i) {
		int32_t extreme_idx{ i };
		for (int32_t j{ i + 1 }; j < size; ++j) {
			if ((arr[extreme_idx] > arr[j]) xor isDescending) {
				extreme_idx = j;
			}
		}
		if (extreme_idx != i) {
			std::swap(arr[extreme_idx], arr[i]);
			PrintArray(arr, size);
		}
	}
}

template <class T>
inline int32_t partition(T* arr, int32_t low, int32_t high, bool isDescending) {
	T pivot{ arr[high] };
	int32_t i{ (low - 1) };
	for (int32_t j{ low }; j <= high - 1; ++j) {
		if ((pivot > arr[j]) xor isDescending) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[high]);
	return (i + 1);
}

template <class T>
inline void QuickSort(T* arr, int32_t low, int32_t high, bool isDescending) {
	if (low < high) {
		int32_t pi{ partition(arr, low, high, isDescending) };
		PrintArray(arr, high + 1);
		QuickSort(arr, low, pi - 1, isDescending);
		QuickSort(arr, pi + 1, high, isDescending);
	}
}

template <class T>
inline void merge(T* arr, int32_t l, int32_t m, int32_t r, bool isDescending) {
	int32_t n1{ m - l + 1 };
	int32_t n2{ r - m };

	T* L = new T[n1];
	T* R = new T[n2];

	for (int32_t i{}; i < n1; i++) {
		L[i] = arr[l + i];
	}
	for (int32_t j{}; j < n2; j++) {
		R[j] = arr[m + 1 + j];
	}

	int32_t i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (((L[i] < R[j] || !(R[j] < L[i]))) xor isDescending) { 
			arr[k++] = L[i++];
		}
		else {
			arr[k++] = R[j++];
		}
	}
	while (i < n1) {
		arr[k++] = L[i++];
	}
	while (j < n2) {
		arr[k++] = R[j++];
	}

	delete[] L;
	delete[] R;
}

template <class T>
inline void MergeSort(T* arr, int32_t left, int32_t right, bool isDescending) {
	if (left >= right) return;
	int32_t mid{ left + (right - left) / 2 };
	MergeSort(arr, left, mid, isDescending);
	MergeSort(arr, mid + 1, right, isDescending);
	merge(arr, left, mid, right, isDescending);
	PrintArray(arr, right + 1);
}

void CountingSort(int32_t* arr, int32_t);
void CountingSort(char* arr, int32_t);

uint64_t Factorial(int32_t);
template <class T>
inline void GeneratePermutationByIndex(int64_t k, T* original, T* result, int32_t size) {
	T* temp = new T[size];
	for (int32_t i{}; i < size; ++i) {
		temp[i] = original[i];
	}
	bool* used = new bool[size]();
	for (int32_t i{}; i < size; ++i) {
		uint64_t f{ Factorial(size - 1 - i) };
		int32_t index_in_temp{ static_cast<int32_t>(k / f) };
		k %= f;
		int32_t current_pos{};
		for (int32_t j{}; j < size; ++j) {
			if (!used[j]) {
				if (current_pos == index_in_temp) {
					result[i] = temp[j];
					used[j] = true;
					break;
				}
				current_pos++;
			}
		}
	}
	delete[] temp;
	delete[] used;
}

template <class T>
inline void BogoSort(T* arr, int32_t size) {
	if (size > 20) {
		std::cerr << "Size is too big for bogosort\n";
		system("pause");
		Menu();
	}
	uint64_t total_permutations = Factorial(size);
	T* original = new T[size];
	for (int32_t i{}; i < size; ++i) {
		original[i] = arr[i];
	}
	for (int64_t i{}; i < total_permutations; ++i) {
		GeneratePermutationByIndex(i, original, arr, size);
		PrintArray(arr, size);
		if (IsSorted(arr, size)) {
			break;
		}
	}
	delete[] original;
}

template<class T>
inline void heapify(T* arr, int32_t n, int32_t i) {
	int32_t extreme{ i };
	int32_t left{ 2 * i + 1 };
	int32_t right{ 2 * i + 2 };

	if (left < n && (arr[extreme] < arr[left])) {
		extreme = left;
	}
	if (right < n && (arr[extreme] < arr[right])) {
		extreme = right;
	}

	if (extreme != i) {
		std::swap(arr[i], arr[extreme]);
	}
}

template<class T>
inline void HeapSort(T* arr, int32_t size) {
	for (int32_t i{ size / 2 - 1 }; i >= 0; i--) {
		heapify(arr, size, i);
	}
	for (int32_t i{ size - 1 }; i > 0; i--) {
		std::swap(arr[0], arr[i]);
		PrintArray(arr, size);
		heapify(arr, i, 0);
		PrintArray(arr, size);
	}
}

template <class T>
inline void RunSort(int32_t sortSelector, T* arr, int32_t size, bool isDescending) {
	std::cout << "Origin array: \n";
	PrintArray(arr, size);
	std::cout << "--- StartSort ---\n";
	auto start = std::chrono::high_resolution_clock::now();
	switch (sortSelector) {
	case 1: BubbleSort(arr, size, isDescending);
		break;
	case 2: ShakerSort(arr, size, isDescending);
		break;
	case 3: CombSort(arr, size, isDescending);
		break;
	case 4: InsertionSort(arr, size, isDescending);
		break;
	case 5: SelectionSort(arr, size, isDescending);
		break;
	case 6: QuickSort(arr, 0, size - 1, isDescending);
		break;
	case 7: MergeSort(arr, 0, size - 1, isDescending);
		break;
	case 8:
		if  constexpr (std::is_same_v<T, int32_t> || std::is_same_v<T, char>) {
			CountingSort(arr, size);
		}
		else {
			std::cout << "Sorting by count is not supported for this data type.\n";
		}
		break;
	case 9: BogoSort(arr, size);
		break;
	case 10: HeapSort(arr, size);
		break;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;


	std::cout << "--- Sort completed ---" << std::endl;
	std::cout << "Sorting time: " << duration.count() << " seconds\n";
	std::cout << "Sorted array\n";
	PrintArray(arr, size);
}
void FillZero(int32_t*, int32_t);
void HandleStudentSorting(int32_t, int32_t, bool);

template<class T>
inline void HandleSortingProcess(int32_t ioM, int32_t sortSelector, bool isDescending) {
	int32_t size;
	std::cout << "Input arr size: ";
	std::cin >> size;

	if (size <= 0) {
		std::cout << "Wrong size.\n";
		return;
	}

	T* arr = new T[size];
	std::string filename = "output.txt";

	switch (ioM) {
	case 1:
		std::cout << "Input " << size << " elements:\n";
		for (int32_t i{}; i < size; ++i) {
			std::cin >> arr[i];
		}
		break;
	case 2:
	{
		std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

		if (std::is_same_v<T, int32_t>) {
			std::uniform_int_distribution<int32_t> distribution(0, 99);
			for (int32_t i{}; i < size; ++i) {
				arr[i] = distribution(generator);
			}
		}
		else if (std::is_same_v<T, double>) {

			std::uniform_real_distribution<double> distribution(0.0, 100.0);
			for (int32_t i{}; i < size; ++i) {
				arr[i] = distribution(generator);
			}
		}
		else if (std::is_same_v<T, char>) {

			std::uniform_int_distribution<int32_t> distribution('a', 'z');
			for (int32_t i{}; i < size; ++i) {
				arr[i] = static_cast<char>(distribution(generator));
			}
		}
		else {
			std::cout << "Random generation is not exist for this type.\n";
		}
	}
	break;
	case 3:
		std::cout << "Input filename for read: ";
		std::cin >> filename;
		{
			std::ifstream inFile(filename);
			if (!inFile) {
				std::cerr << "Open file error" << filename << std::endl;
				delete[] arr;
				return;
			}
			for (int32_t i{}; i < size; ++i) {
				inFile >> arr[i];
			}
			inFile.close();
		}
		break;
	}


	RunSort(sortSelector, arr, size, isDescending);

	if (ioM == 1 || ioM == 2) {
		std::ofstream outFile(filename);
		if (!outFile) {
			std::cerr << "Open output file error\n";
		}
		else {
			for (int32_t i{}; i < size; ++i) {
				outFile << arr[i] << " ";
			}
			outFile.close();
			std::cout << "Sorted data in file" << filename << std::endl;
		}
	}
	delete[] arr;
	system("pause");
}
#endif