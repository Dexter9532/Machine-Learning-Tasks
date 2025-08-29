#include <vector>
#include <iostream>
#include <algorithm>

namespace vector 
{
/**
 * @brief Print vector specifying index 
 * 
 * @param [in] data Vector
 */
void IndexPrint(const std::vector<int>& data)
{
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "|Index Print|\n";
    for (std::size_t i{}; i < data.size(); i++)
    {
        std::cout << "|" << data[i] << "|" << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}

/**
 * @brief Print vector without specifying index.
 * 
 * @param [in] data The vector to print.
 */
void RangedPrint(const std::vector<int>& data)
{
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "|Ranged Print|\n";
    for (const auto& i: data)
    {
        std::cout << "|" << i << "|" << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}
/**
 * @brief Print vector in a fucked up way.
 * 
 * @param [in] data Vector.
 */
void Iterator(const std::vector<int>& data)
{
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "|Iterator Print|\n";
    for (auto it{data.begin()}; it < data.end(); ++it)
    {
        const int number{*it};
        std::cout << "|" << number << "|" << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n\n";
}
/**
 * @brief Print the largest int in the given vector
 * 
 * @param [in]
 */
int getLargestInt(const std::vector<int>& data)
{
    if (data.empty()){
        std::cout << "Empty vector\n";
        return 0;
    }
    else{
    auto it = std::max_element(data.begin(), data.end());
    return *it;
    }
}
void printLargestInt(const std::vector<int>& data)
{
    int largestInt = vector::getLargestInt(data);
    std::cout << "The largest element in the vector is: " << largestInt << "\n";
}
} // Namespace vector


int main ()
{    
    std::vector<int> v1{1, 2, 3, 8, 0, 7}; 

    vector::printLargestInt(v1);
    
    vector::IndexPrint(v1);
    vector::RangedPrint(v1);
    vector::Iterator(v1);

    /* Resize vector too 10*/
    v1.resize(10);

    /* Print vector size*/
    std::size_t size = v1.size();
    std::cout << "The vector size: " << size <<"\n\n";

    /* Add number in the end of vector */
    v1.push_back(2);

    /* Erase the first element of the vector*/
    v1.erase(v1.begin());
    /* Erase the last element of the vector*/
    v1.pop_back();

    /* Empty the vector*/
    v1.clear();
    std::cout << "Vector has been cleared" << "\n\n";

    /* Check if vector is empty or not*/
    if (v1.empty())
    {
        std::cout << "Vector has no elements" << "\n\n";
    }
    else{
        std::cout << "Vector contains elements" << "\n\n";
    }
    std::vector<int> v2{1, 2, 3};   

    vector::IndexPrint(v1);
    vector::RangedPrint(v1);
    vector::Iterator(v1);

    /**
     * 3. jag hade skickat en pass-by-refrence för att spara plats
     *  och undvika kopier, den sparar utrymmen för att den pekar istället för att kopierar
     */



}