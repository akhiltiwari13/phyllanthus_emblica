#include <iostream>

/* MyVector Implementation. */
template <typename T> class MyVector {
public:
  /* default constructor */
  MyVector() : size_(0), capacity_(1), data_{new T[1]} {}

  /* parameterized constructor */
  MyVector(size_t cap) : size_(0), capacity_(cap), data_{new T[cap]} {}

  /* destructor */
  ~MyVector() { delete[] data_; }

  /* copy constructor */
  /* A copy constructor is a special constructor that is used to create a new
   * object as a copy of an existing object. It takes a single argument, which
   * is a const reference to an object of the same type as the object being
   * constructed. */
  MyVector(const MyVector<T> &obj)
      : size_(obj.size_), capacity_(obj.capacity_),
        data_{new T[obj.capacity_]} {
    std::cout << "copy constructor" << std::endl;
    for (auto i = 0; i < capacity_; ++i) {
      data_[i] = obj.data_[i];
    }
  }

  /* copy assignment operator */
  /* A copy assignment operator is a special assignment operator that is used to
   * assign the value of one object to another object of the same type. It takes
   * a single argument, which is a const reference to an object of the same type
   * as the object being assigned to. */
  MyVector &operator=(const MyVector<T> &rhs) {
    /* check if the two objects are not already same. */
    if (this != &rhs) {
      delete[] data_; // free existing values.

      capacity_ = rhs.capacity_;
      size_ = rhs.size_;
      data_ = new T[size_];

      for (auto i = 0; i < capacity_; ++i) {
        data_[i] = rhs.data_[i];
      }
    }

    return *this;
  }

  /* move constructor */
  /* A move constructor is a special constructor in C++ that allows the
   * efficient transfer of ownership of resources from one object to another,
   * without the need for costly deep copies. It is typically used to optimize
   * the performance of object creation and destruction in scenarios where
   * copying the entire contents of an object is unnecessary. */

  /* The move constructor takes an rvalue reference (T&&) as its parameter,
   * where T is the class type. It is responsible for "stealing" the resources
   * from the source object and leaving it in a valid but unspecified state. */

  /* move constructor's parameter is not a const since the ownership of it's
   * resources would be transferred. */
  MyVector(MyVector<T> &&other)
      : size_(std::move(other.size_)), capacity_(std::move(other.capacity_)),
        data_(new T[other.capacity_]) {
    std::cout << "move constructor" << std::endl;
    for (auto i = 0; i < capacity_; ++i) {
      data_[i] = std::move(other.data_[i]);
    }

    /* invalidate the object being moved */
    other.size_ = 0;
    other.capacity_ = 0;
    delete[] other.data_;
    other.data_ = nullptr;
  }

  /* move assignment operator */
  /* The move assignment operator is a special member function in C++ that
   * allows efficient transfer of resources from one object to another through
   * assignment. It is used to reassign the contents of an existing object by
   * moving the resources from the right-hand side (RHS) object to the left-hand
   * side (LHS) object. */
  MyVector &operator=(MyVector<T> &&rhs) {
    if (this != &rhs) {
      delete[] data_;

      capacity_ = std::move(rhs.capacity_);
      size_ = std::move(rhs.size_);
      for (auto i = 0; i < capacity_; ++i) {
        data_[i] = std::move(rhs.data_[i]);

        /* invalidate rhs */
        rhs.size_ = 0;
        rhs.capacity_ = 0;
        delete[] rhs.data_;
        rhs.data_ = nullptr;
      }
    }

    return (*this);
  }

  // push_back
  void push_back(const T &val) { data_[size_++] = val; }

  // emplace_back
  // @todo: ?
  /* void emplace_back(const T& val){ */
  /*     data_[size_++] = val; */
  /* } */

  size_t Size() { return size_; }

  size_t Capacity() { return capacity_; }

  T &at(size_t idx) { return data_[idx]; }

  T &operator[](size_t idx) { return data_[idx]; }

private:
  T *data_;
  std::size_t capacity_{0};
  std::size_t size_{0};
};

// test MyVector
int main(int argc, char *argv[]) {
  MyVector<int> mvec0{};
  mvec0.push_back(34);

  MyVector<int> mvec1{30};
  for (int i = 0; i < mvec1.Capacity(); ++i) {
    mvec1.push_back((3 + i) * i);
  }

  for (int i = 0; i < mvec1.Size(); ++i) {
    std::cout << "mvec1[" << i << "]:" << mvec1[i] << std::endl;
  }

  auto mvec2{mvec1};
  for (int i = 0; i < mvec2.Size(); ++i) {
    std::cout << "mvec2[" << i << "]:" << mvec2[i] << std::endl;
  }

  auto mvec3(std::move(mvec1));
  for (int i = 0; i < mvec3.Size(); ++i) {
    std::cout << "mvec3[" << i << "]:" << mvec3[i] << std::endl;
  }

  return 0;
}
