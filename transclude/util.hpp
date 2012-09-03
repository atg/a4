namespace furrow {
    
    template<T, M>
    bool contains(const T<M>& container, const M& val) {
        for (const M& otherval : container) {
            if (val == otherval)
                return true;
        }
        return false;
    }
    
    bool isa(furrow::any box, std::string typenamestr) {
        return box.is_subtype_of(typenamestr);
    }
    
    template<T, S>
    bool mod(T a, S b) {
        
        if (is_integral(T) && is_integral(S)) {
            if (a >= (T)0)
                return std::mod(a, b);
            else
                return std::mod(std::mod(a, b) + b, b);
        }
        else {
            if (a >= (T)0)
                return std::fmod(a, b);
            else
                return std::fmod(std::fmod(a, b) + b, b);
        }
        
    }
}
