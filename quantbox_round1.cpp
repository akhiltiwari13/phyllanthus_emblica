/* ================== implement the type_trait std::is_same. ============================= */
Std::is_same

Template <typename T1, typename T2>
Void foo() {
 If constexpr (std::is_same<T1, T2>::value) {
 … 
}
Else {
…
}
} 



Template <typename T, typename U>
Struct is_same : std::false_type {
};

Template <typename T>
Struct is_same<T,T> : std::true_type {
};


Template <>
//typename t1, typename t2
Class Is_Same(){
Public:
	Int value;
	Is
	std::type_of(t1) == type_of(t2)
	

};


/* ================== shared_ptr implementation ============================= */

Shared_ptr

Template <typename t>
Class SharedPtr{
    T* ptr;
    Uint_32t* refCount{};

public:
    ShraedPtr():ptr(nullptr), refCount(new int(1)){}

    SharedPtr(T* rawptr):ptr(rawptr){
    if(ptr){
     refCount = new int();
     ++(*refCount);       
}
}

    ~SharedPtr(){--(*refCount);
      if(!(*refcount)){ if(ptr)delete ptr;
     delete refCount;
}
}
    SharedPtr(const SharedPtr& obj):ptr(obj.ptr), refCount(obj.refCoutt){++(*refCount);}

    SharedPtr& operator=(const SharedPtr& lhs, SharedPtr& rhs){}
    ShredPtr(const SharedPtr&& obj){}
    SharedPtr(cont

};


Void foo () {
Sharedptr <int> p;
// p -> 1
SharedPtr<int> q(p);
// p,q -> 2
}



/* ================== implement a memory pool ============================= */


Memory Pool


Class MemoryPool {
Public:
   MemoryPool() {
  }

  T* ptr; // new T[const_size];
array<int>(const_size);
list<int>;

deallocation(T* p){
P - ptr
}
};


