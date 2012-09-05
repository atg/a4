// The purpose of this class is to have optional types without heap allocation
// For example you can do
//    optional<int> x;
//    x.set(10);
// and no heap allocation will occur.

template<class T>
struct optional {
    
    bool isSet;
    char data[sizeof(T)];
    
    optional() : isSet(false) { }
    optional(const T&& ref) {
        // move ref into data
    }
    optional(const T& ref) : isSet(true) {
        new (data)(ref);
    }
    
    void set(const T&& ref) {
        
    }
    void set(const T& ref) {
        
    }
    
    int32_t hash() const {
        if (!isSet)
            return 1793809660;
        
        const T& val = *reinterpret_cast<T*>(data);
        return furrow::hash(val);
    }
    
    ~optional() {
        reinterpret_cast<T*>(data)->~T();
    }
};