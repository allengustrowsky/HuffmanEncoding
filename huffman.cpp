#include <unordered_map>
#include <vector>
#include <queue>
#include "tree_printer.hpp"

using namespace std;

struct Node
{
    char label;
    int frequency;
    const Node *right;
    const Node *left;

    Node(int frq, char lab = '_', const Node *right = nullptr, const Node *left = nullptr)
    {
        this->frequency = frq;
        this->label = lab;
        this->right = right;
        this->left = left;
    }

    ~Node()
    {
        delete this->right;
        delete this->left;
    }

    int get_frequency() const
    {
        return this->frequency;
    }

    bool is_leaf() const
    {
        return ((this->left == nullptr) && (this->right == nullptr));
    }
};

// big thanks to Matteo Italia from
// https://stackoverflow.com/questions/11836643/
// sorting-of-priority-queue-elements-that-are-pointer-type
// This struct and its call in the priority queues
// below is adapted from their solution
template <typename T>
struct CompNodePtrs
{
    bool operator()(const T *left, const T *right)
    {
        return left->frequency > right->frequency;
    }
};

// Takes two Node pointers and combines them into a single
// tree by making them the left and right nodes of a root.
// The root's frequency is the sum of the two nodes' frequencies
Node *huffman_combine(const Node *smaller, const Node *larger)
{
    int sum = smaller->get_frequency() + larger->get_frequency();
    return new Node(sum, '_', larger, smaller);
}

// Takes a reference to a priority queue and performs one
// iteration of the "huffman algorithm." This means it pops
// the top two elemens and combines them into a single tree
// by calling huffman_combine()
void huffman_iterate(std::priority_queue<Node *, std::vector<Node *>, CompNodePtrs<Node>> &huff_queue)
{
    Node *top = huff_queue.top();
    huff_queue.pop();
    Node *next = huff_queue.top();
    huff_queue.pop();
    huff_queue.push(huffman_combine(top, next));
}

// Takes a reference to a priority queue and performs the
// "huffman algorithm" by calling huffman_iterate() until
// the queue contains only one tree
void build_huff_tree(std::priority_queue<Node *, std::vector<Node *>, CompNodePtrs<Node>> &huff_queue)
{
    while (huff_queue.size() > 1)
    {
        huffman_iterate(huff_queue);
    }
}

// Takes a pointer to a root Node, reference to a unordered map,
// and a string representing a character encoding. Performs a
// recursive preorder traversal of the root tree to calculate
// the huffman encodings of each letter in the unordered map.
void calc_order(const Node *root, std::unordered_map<char, string> &codes, string code = "")
{
    if (root->is_leaf())
    {
        codes[root->label] = code;
    }
    if (root->left)
    {
        calc_order(root->left, codes, code + "0");
    }
    if (root->right)
    {
        calc_order(root->right, codes, code + "1");
    }
}

int main()
{
    std::unordered_map<char, int> frequencies;
    char letters[26] = {'A', 'B', 'C', 'D', 'E',
                        'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                        'V', 'W', 'X', 'Y', 'Z'};
    int sum = 0;
    char letter;
    vector<Node *> nodes;

    // a deeply-heartfelt thanks to the author of this for showing
    // me how to terminate reading a file in stdin on EOF:
    // https://cplusplus.com/reference/ios/ios/eof/
    while (std::cin.get(letter))
    {
        if (isalpha(letter))
        {
            std::cout << (char)toupper(letter);
            frequencies[(char)toupper(letter)]++;
        }
    }

    // print frequencies for each letter and total
    std::cout << "\n\nCounts:\n"
              << "-------\n";
    for (char ltr : letters)
    {
        std::cout << ltr << ": " << frequencies[ltr] << "\n";
        // add to sum
        sum = sum + frequencies[ltr];
    }
    std::cout << "Total = " << sum << "\n";
    std::cout << "---------------------------------\n\n\n";

    // make new node and push to priority queue for later use
    for (char letter : letters)
    {
        nodes.push_back(new Node(frequencies[letter], letter));
    }
    std::priority_queue huffman_queue(nodes.begin(), nodes.end(),
                                      CompNodePtrs<Node>());

    // huffman algorithm on priority queue
    if (huffman_queue.size() > 1)
    {
        build_huff_tree(huffman_queue);
    }

    // print tree
    print_tree(huffman_queue.top(), nullptr, false, sum);
    std::cout << "---------------------------------\n";

    // calculate codes for each letter
    std::unordered_map<char, string> codes;
    calc_order(huffman_queue.top(), codes);
    std::cout << endl;

    // print letter/huffman encoding pair
    for (char letter : letters)
    {
        std::cout << letter << ": " << codes[letter] << endl;
    }

    // calculate bit requirement for huffman encoding
    int huff_bits = 0;
    for (char letter : letters)
    {
        huff_bits = huff_bits + (frequencies[letter] * codes[letter].length());
    }

    // print constant and huffman bit requirements
    std::cout << "\n  Fixed encoding: " << (sum * 5) << " bits\n";
    std::cout << "Huffman encoding: " << huff_bits << " bits\n\n";

    // free heap memory
    delete huffman_queue.top();
}
