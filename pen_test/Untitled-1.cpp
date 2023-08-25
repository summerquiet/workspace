// 把2个有序的数组合并成一个数组使用vector

bool mergeArray(const std::vector& v1, const std::vector& v2, std::vector& out)
{
    if (v1.empty()) {
        out = v2;
        return true;
    }

    if (v2.empty()) {
        out = v1;
        return true;
    }

    std::vector::iterate it1 = v1.begin();
    std::vector::iterate it2 = v1.begin();

    while (it1 != v1.end()
        && it2 != v2.end()) {
        
        if (*it1 < *it2) {
            out.push_back(*it1);
            ++it1;
        }
        else {
            out.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != v1.end()) {
        out.push_back(*it1);
        ++it1;
    }

    if (it2 != v2.end()) {
        out.push_back(*it2);
        ++it2;
    }

    return true;
}
