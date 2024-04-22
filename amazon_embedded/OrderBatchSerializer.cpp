#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// typedef enum {
//     STATUS_SUCCESS,
//     STATUS_INSUFFICIENT_OUTPUT_BUFFER,
//     STATUS_NULL_INPUT
// } FuncStatus_t;

// struct OrderBatch {
//     uint32_t order_count;
//     uint64_t batch_id;
//     struct Order * orders;
// };

// struct Order {
//     uint16_t quantity;
//     uint64_t order_id;
//     uint8_t part_number[16];
//     char email_address[32]; /* NULL terminated string */
// };


// size_t getSerialSize(const OrderBatch *ob){
//     size_t serial_sz = sizeof(OrderBatch) - sizeof(Order*) + ((ob->order_count)*sizeof(Order));
//     return serial_sz;
// }

// FuncStatus_t serialize_order(const struct OrderBatch *order_batch, const size_t out_max_length, uint8_t *out) {
//     /* Warning: You can use stdout for debugging, but doing so will cause the test cases to fail. */
//     auto tptr{out};
//     int_fast32_t payload_len{};
//     auto face = 0xFACE;
//     if(!order_batch) return STATUS_NULL_INPUT;
//     else{
//         //process a valid orderbatch;
//         payload_len = getSerialSize(order_batch) + 10;
//         if(payload_len < out_max_length) return STATUS_INSUFFICIENT_OUTPUT_BUFFER;
//         //memcpy(tptr, &face, sizeof(face));
//         *tptr = face;
//         tptr+=sizeof(face);
//         //memcpy(tptr, &payload_len, sizeof(payload_len));
//         *tptr= payload_len;
//         tptr+=sizeof(payload_len);
//         //memcpy(tptr,&order_batch,12); //serialize order_count & batch_id
//         *tptr=order_batch->order_count;
//         tptr+=4;
//         *tptr=order_batch->batch_id;
//         tptr+=8;
//         auto ord_count = order_batch->order_count;
//         auto ords = order_batch->orders;
//         while(ord_count && ords){
//             //memcpy(tptr,&ords,sizeof(Order)); //serialize order_count & batch_id
//             //tptr+=sizeof(Order);
//             *tptr = ords->quantity; tptr+=2;
//             *tptr = ords->order_id; tptr+=8;
//             //*tptr = ords->part_number; 
//             memcpy(tptr, ords->part_number, 16);
//             tptr+=16;
//             memcpy(tptr, ords->email_address, 32);
//             tptr+=32;
//             ++ords; --ord_count;
//         }
//     }
    
//     return STATUS_SUCCESS;
// }

// generated serialization code
// TODO: test this code.
// Note that this implementation assumes that the output buffer has already been allocated and is of the correct size.
// It also assumes that the data types used in the OrderBatch and Order structures have the expected sizes and endianness.
// To make the serialization more robust and platform-independent, one could consider using fixed-size data types from the <cstdint> header and/or adding code to convert endianness if necessary.

// bool serialize_order(const OrderBatch *order_batch, const size_t out_max_length, uint8_t *out) {
// // check if output buffer is large enough to store serialized data
// size_t expected_size = sizeof(OrderBatch) + sizeof(Order) * order_batch->order_count;
// if (expected_size > out_max_length) {
// return false;
// }
// // serialize the OrderBatch header
// uint8_t *p = out;
// memcpy(p, &order_batch->order_count, sizeof(order_batch->order_count));
// p += sizeof(order_batch->order_count);
// memcpy(p, &order_batch->batch_id, sizeof(order_batch->batch_id));
// p += sizeof(order_batch->batch_id);

// // serialize each Order in the batch
// for (uint32_t i = 0; i < order_batch->order_count; i++) {
//     const Order *order = &order_batch->orders[i];
//     memcpy(p, &order->quantity, sizeof(order->quantity));
//     p += sizeof(order->quantity);
//     memcpy(p, &order->order_id, sizeof(order->order_id));
//     p += sizeof(order->order_id);
//     memcpy(p, &order->part_number, sizeof(order->part_number));
//     p += sizeof(order->part_number);
//     memcpy(p, order->email_address, sizeof(order->email_address));
//     p += sizeof(order->email_address);
// }

// return true;
// }
#include <cstdint>
#include <cstring>

struct Order {
    uint16_t quantity;
    uint64_t order_id;
    uint8_t part_number[16];
    char email_address[32];
};

struct OrderBatch {
    uint32_t order_count;
    uint64_t batch_id;
    Order* orders;
};

enum FuncStatus_t {
    STATUS_SUCCESS,
    STATUS_INSUFFICIENT_OUTPUT_BUFFER,
    STATUS_NULL_INPUT
};

FuncStatus_t serialize_order(const OrderBatch* order_batch, const size_t out_max_length, uint8_t* out) {
    if (!order_batch) {
        return STATUS_NULL_INPUT;
    }

    size_t payload_len = 10 + 8 + 4 + order_batch->order_count * (2 + 8 + 16 + 32);
    if (out_max_length < payload_len) {
        return STATUS_INSUFFICIENT_OUTPUT_BUFFER;
    }

    // Write the header
    out[0] = 0xCE;
    out[1] = 0xFA;
    memcpy(out + 2, &payload_len, sizeof(payload_len));
    memcpy(out + 6, &order_batch->batch_id, sizeof(order_batch->batch_id));
    memcpy(out + 14, &order_batch->order_count, sizeof(order_batch->order_count));

    // Write the orders
    uint8_t* p = out + 18;
    for (uint32_t i = 0; i < order_batch->order_count; ++i) {
        const Order& order = order_batch->orders[i];
        memcpy(p, &order.quantity, sizeof(order.quantity));
        p += sizeof(order.quantity);
        memcpy(p, &order.order_id, sizeof(order.order_id));
        p += sizeof(order.order_id);
        memcpy(p, order.part_number, sizeof(order.part_number));
        p += sizeof(order.part_number);
        memcpy(p, order.email_address, sizeof(order.email_address));
        p += sizeof(order.email_address);
    }

    return STATUS_SUCCESS;
}

#define ORDER_BATCH_NUM_BYTES (22)
#define ORDER_NUM_BYTES (58)
#define OUTPUT_BUFFER_EXTRA (10)

int read_in_order(struct Order *order) {
    char line[1024];
    unsigned short quantity = 0;
    unsigned long order_id = 0;
    uint8_t part_number[16] = {0};
    char email_address[32] = {'\0'};
    
    fgets(line, 1024, stdin);
    if (2 != sscanf(line, "%hu %ld", &quantity, &order_id)) {
        printf("Error occured at line %d of test code.\n", __LINE__);
        return 3;
    }
        
    fgets(line, 1024, stdin);
    if (16 != sscanf(line, "%hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu", 
                     &part_number[0], &part_number[1], &part_number[2], &part_number[3], 
                     &part_number[4], &part_number[5], &part_number[6], &part_number[7], 
                     &part_number[8], &part_number[9], &part_number[10], &part_number[11], 
                     &part_number[12], &part_number[13], &part_number[14], &part_number[15])) {
        printf("Error occured at line %d of test code.\n", __LINE__);
        return 3;
    }
          
    fgets(line, 1024, stdin);
    if (1 != sscanf(line, "%32s", email_address)) {
        printf("Error occured at line %d of test code.\n", __LINE__);
        return 3;
    }
    
    order->quantity = quantity;
    order->order_id = order_id;
    memcpy(order->part_number, part_number, 16);
    memcpy(order->email_address, email_address, 32);
    
    return 0;
}

int main() {
    int32_t order_count = -1;
    int32_t batch_id = -1;
    struct OrderBatch batch = {0};
    uint8_t *output = NULL;
    size_t output_size = 0;
    FuncStatus_t ret_status = STATUS_SUCCESS;
    
    //Read number of orders to get from input
    char line[1024];
    fgets(line, 1024, stdin);
    if (2 != sscanf(line, "%d %d", &order_count, &batch_id)) {
        printf("Error occured at line %d of test code.\n", __LINE__);
        return 1;
    }
    
    if (0 < order_count) {
        batch.order_count = order_count;
        batch.batch_id = batch_id;
        batch.orders = (struct Order*)malloc(sizeof(struct Order) * order_count);
        if (NULL == batch.orders) {
            printf("Error occured at line %d of test code.\n", __LINE__);
            return 1;
        }
        // Read in all the orders from stdin
        for (int32_t i = 0; i < order_count; ++i) {
            if (0 != read_in_order(&(batch.orders[i]))){
                printf("Error occured at line %d of test code.\n", __LINE__);
                return 1;
            }
        }
        // Allocate memory for the output buffer
        output_size = ORDER_BATCH_NUM_BYTES + (ORDER_NUM_BYTES * order_count);
        output = (uint8_t*)malloc(output_size + OUTPUT_BUFFER_EXTRA);
        if (NULL == output) {
            printf("Error occured at line %d of test code.\n", __LINE__);
            return 1;
        }
        // Initialize all the output data
        for (size_t i = 0; i < (output_size + OUTPUT_BUFFER_EXTRA); ++i) {
            output[i] = 0xA5;
        }
    }
    
    if (-1 == order_count) {
        uint8_t out[16];
        ret_status = serialize_order(NULL, 16, out);
    } else if (-2 == order_count) {
        ret_status = serialize_order(&batch, 16, NULL);
    } else if (-3 == order_count) {
        uint8_t out[256];
        batch.order_count = 2;
        batch.orders = (struct Order*)malloc(sizeof(struct Order) * 2);
        ret_status = serialize_order(&batch, 32, out);
        free(batch.orders);
        batch.orders = NULL;
    } else {
        ret_status = serialize_order(&batch, output_size, output);
    }
    
    printf("%d\n", ret_status);
    
    if (NULL != batch.orders) {
        free(batch.orders);
    }
    
    if (NULL != output) {
        for (size_t i = 0; i < (output_size + OUTPUT_BUFFER_EXTRA); ++i) {
            printf("%02X ", output[i]);
            output[i] = 0xA5;
        }
        free(output);
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}