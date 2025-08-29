#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>


namespace vector
{
template<typename T>
/**
 * @brief Sort the given vector in order, can only be arithmetic.
 * 
 * @note Will give compile problem if the vector is a non-artihmetic type due to the static assert
 * 
 * @param [in] data The given vector to sort.
 */
void sort(std::vector<T>& data)
{
    std::cout << "Sorting the vector...\n";
    static_assert(std::is_arithmetic_v<T>, "Non-arithmetic type specified in vector::sort!");
    std::sort(data.begin(), data.end()); // Use std::sort for sorting
    std::cout << "The vector has been sorted succesfully\n";
}
/**
* @brief Print vector without specifying index.
* 
* @param [in] data The vector to print.
*/
void printVector(const std::vector<int>& data)
{
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "|Vector|\n";
    for (const auto& i: data)
    {
        std::cout << "|" << i << "|" << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}
/**
 * @brief Find and print the next biggest element in the vector, 
 * the function has a saftey net if element has the same value.
 * 
 * @param [in] data The vector to find the next biggest element in
 */
template<typename T>
void getNextLargest(std::vector<T>& data)
{
    int nextlargestindex = 2;
    std::cout << "Getting the next largest element in the vector\n";

    // Ta reda på maxtalet x, exempelvis med en funktion döpt getLargest.
    // Itera igenom vektorn, spara det största talet y som ej är lika med det allra talet x.

    while (true)
    {
        static_assert(std::is_arithmetic_v<T>, "Non-arithmetic type specified in vector::getNextLargest!");
        int vectorsize = data.size();
        if (data[vectorsize - 1] != data[vectorsize - nextlargestindex] )
        {
            std::cout << "The next largest element in the vector is: " << data[vectorsize - nextlargestindex] << "\n";
            break;
        }
        else{
            nextlargestindex ++;
        }
    }
    }
} // namespace vector


int main()
{
    std::vector<int> v1{1, 18, 7, 3, 5, 44, 20 ,20, 44, 40, 18, 29, 87, 98, 98, 98, 98, 40, 54, 54};

    vector::printVector(v1);
    vector::sort(v1);
    vector::printVector(v1);
    vector::getNextLargest(v1);

}


