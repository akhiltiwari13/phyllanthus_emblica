#include <iostream>
#include <map>

struct new_order
{
    uint64_t order_id;
    char     side; // 'B' = Buy , 'S' = Sell
    int32_t  price;
    uint32_t quantity;
};

struct change_order
{
    uint64_t order_id;
    int32_t  new_price;
    uint32_t new_quantity;
};

struct cancel_order
{
    uint64_t order_id;
};

class OrderBook
{
    // Using a custom comparator for the buy map to have decreasing order
    std::map<int32_t, uint32_t, std::greater<>> buys;
    std::map<int32_t, uint32_t> sells;
    std::map<uint64_t, new_order> order_map;

public:
    void OnNewOrder(const new_order& order)
    {
        if (order.side == 'B')
            buys[order.price] += order.quantity;
        else
            sells[order.price] += order.quantity;
        
        order_map[order.order_id] = order;
    }

    void OnChangeOrder(const change_order& order)
    {
        auto old_order = order_map.find(order.order_id);
        if (old_order != order_map.end())
        {
            // Remove old quantity
            if (old_order->second.side == 'B')
                buys[old_order->second.price] -= old_order->second.quantity;
            else
                sells[old_order->second.price] -= old_order->second.quantity;

            // Add new quantity
            if (old_order->second.side == 'B')
                buys[order.new_price] += order.new_quantity;
            else
                sells[order.new_price] += order.new_quantity;

            // Update the order map
            old_order->second.price = order.new_price;
            old_order->second.quantity = order.new_quantity;
        }
    }

    void OnCancelOrder(const cancel_order& order)
    {
        auto old_order = order_map.find(order.order_id);
        if (old_order != order_map.end())
        {
            // Remove old quantity
            if (old_order->second.side == 'B')
                buys[old_order->second.price] -= old_order->second.quantity;
            else
                sells[old_order->second.price] -= old_order->second.quantity;

            order_map.erase(old_order);
        }
    }

    void Print()
    {
        std::cout << "Buys\n";
        std::cout << "Price Quantity\n";
        for (auto& [price, quantity] : buys)
        {
            if(quantity > 0)
                std::cout << price << " " << quantity << "\n";
        }

        std::cout << "\nSells\n";
        std::cout << "Price Quantity\n";
        for (auto& [price, quantity] : sells)
        {
            if(quantity > 0)
                std::cout << price << " " << quantity << "\n";
        }
    }
};

int main()
{
    OrderBook book;

    book.OnNewOrder({1, 'B', 100, 5000});
    book.OnNewOrder({2, 'B', 100, 5000});
    book.OnNewOrder({3, 'S', 102, 7000});
    book.OnNewOrder({4, 'B', 99, 2000});
    book.OnNewOrder({5, 'B', 98, 1000});
    book.OnNewOrder({6, 'S', 103, 2000});
    book.OnNewOrder({7, 'S', 104, 9000});

    book.Print();

    return 0;
}
