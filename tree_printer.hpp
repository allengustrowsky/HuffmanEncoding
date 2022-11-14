#pragma once 
#include <iostream>
#include <iomanip>

using namespace std;

// Adapted from 
// https://www.techiedelight.com/c-program-print-binary-tree/

const std::string HORIZONTAL_LINE = "--";
const std::string VERTICAL_LINE = "|";
const std::string RIGHT_BRANCH = ".--";
const std::string LEFT_BRANCH  = "`--";
const std::string CONNECTOR    = "     |";


struct Trunk {
    Trunk *prev;
    std::string str;
 
    Trunk(Trunk *prev, std::string str) {
        this->prev = prev;
        this->str = str;
    }
};
 
// Helper function to print branches of the binary tree
void show_trunks(Trunk *p) {
    if (p) {
        show_trunks(p->prev);
        std::cout << p->str;
    }
}


// Type T must be a pointer to a struct or class
// with a printable public member named frequency and 
// public members named  left and right that have 
// same type as T.
// You may need to adapt the code here based on the
// specifics of your tree node type.
template <typename T>
void print_tree(T root, Trunk *prev, bool is_left, int total_bits) {
    if (root) {
        std::string prev_str = "      ";
        Trunk *trunk = new Trunk(prev, prev_str);
        print_tree(root->right, trunk, true, total_bits);
        if (!prev) {
            trunk->str = HORIZONTAL_LINE;
        } else if (is_left) {
            trunk->str = RIGHT_BRANCH;
            prev_str = CONNECTOR;
        } else {
            trunk->str = LEFT_BRANCH;
            prev->str = prev_str;
        }
        show_trunks(trunk);
        if (root->label == '_')
        {
           std::cout << " (" << fixed << setprecision(6) << ((double)root->frequency / total_bits) << ")\n"; 
        } else 
        {
            std::cout << " [" << root->label << ":" << fixed << setprecision(6) << ((double)root->frequency / total_bits) << "]\n";
        }
        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = CONNECTOR;
        print_tree(root->left, trunk, false, total_bits);
    }
}
