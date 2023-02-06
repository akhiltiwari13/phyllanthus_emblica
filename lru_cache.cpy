typedef std::unordered_map<int,std::pair<int,std::list<int>::iterator>> Cache;

class LRUCache {
private:
    int _capacity;
    Cache _cache;
    std::list<int> _lru_queue;
    
    void moveToTop(int value,  const Cache::iterator& citr){
        _lru_queue.erase(citr->second.second);
        _lru_queue.emplace_front(value);
        citr->second.second = _lru_queue.begin();
    }
    
public:
    LRUCache(int capacity):_capacity(capacity) {}
    
    int get(int key) {
        auto ritr = _cache.find(key); 
        if( ritr == _cache.end()){
            return -1;
        }
        else{
            moveToTop(ritr->second.first,ritr);
            return ritr->second.first;
        }
    }
    
    void put(int key, int value) {
        auto ritr = _cache.find(key); 
        //exists
        if(ritr != _cache.end()){
            _lru_queue.erase(ritr->second.second);
            _lru_queue.emplace_front(value);
        }
            //check capacity breach
            if(_cache.size() == _capacity){
                _cache.erase(_lru_queue.back());
                _lru_queue.pop_back();
            }
            _lru_queue.emplace_front();
            _cache[key]= {value, _lru_queue.begin()};
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 