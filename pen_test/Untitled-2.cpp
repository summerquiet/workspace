/*
假设有围栏类
class Fence {
public:
   bool Intersects(const Fence& other); 
   void Union(const Fence& other);
};

Intersects()判断两个围栏之间是否相交；Union()对围栏进行合并，这两个函数假设已经可用，现在对一组围栏进行合并，请给出合并结果.

比如输入A,B,C,D,E,F,G共7个原始围栏,其中A与B相交，B与C相交，D与E相交。 那么输出，就应该只有A,B,C合并后的数据，D,E合并后的数据，以及F,G这4个结果围栏。

以下函数的参数fences既是输入变量，也是输出变量

void MergeFence(std::vector<Fence>& fences);
*/

void MergeFence(std::vector<Fence>& fences)
{
    std::vector<bool> mark;
    for (int i = 0; i < fences.size(); i++) {
        mark.push_back(true);
    }

    for (int i = 0; i < fences.size() - 1; i++) {
        if (!mark[i]) {
            continue;
        }

        for (int j = i + 1; j < fences.size(); j++) {
            if (fences[i].Intersects(fences[j])) {
                fences[i].Union(fences[j]);
                mark[j] = false;
            }
        }
    }

    std::vector<Fence> copy = fences;
    fences.clear();

    for (int i = 0; i < copy.size(); i++) {
        if (mark[i]) {
            fences.push_back(copy[i]);
        }
    }
}
