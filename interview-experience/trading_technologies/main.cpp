#include <cstdint>
#include <stdexcept>
#include <iostream>

enum Side { NONE, LEFT, RIGHT };

class ChainLink
{
public:
    void append(ChainLink* rightPart)
    {
        if (this->right != NULL)
            throw std::logic_error("Link is already connected.");

        this->right = rightPart;
        rightPart->left = this;
    }

    Side longerSide()
    {
        /* throw std::logic_error("Waiting to be implemented"); */
        auto cur = left;
        uint32_t leftLen{0};
        uint32_t rightLen{0};
        while((cur != nullptr) && (cur != right)){
            cur = cur->left;
            ++leftLen;
        }
        if(cur == right)
            return Side::NONE;
        // reset curr
        cur = right;
        while(cur != nullptr) {
            cur = cur->right;
            ++rightLen;
        }
        if (rightLen == leftLen )
            return Side::NONE;

        return rightLen>leftLen? Side::RIGHT : Side::LEFT;
    }

private:
    ChainLink* left;
    ChainLink* right;
};

#ifndef RunTests
int main()
{
    ChainLink* left = new ChainLink();
    ChainLink* middle = new ChainLink();
    ChainLink* right = new ChainLink();
    left->append(middle);
    middle->append(right);

    std::cout << left->longerSide();
}
#endif
