template<typename T>
T* copy_pointer(T* oldval) {
    return new T(*oldval);
}
