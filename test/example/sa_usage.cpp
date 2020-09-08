#include <atcoder/string>
#include <string>
#include <vector>

using namespace std;
using namespace atcoder;

int main() {
    string s = "missisippi";

    vector<int> sa = suffix_array(s);

    vector<string> answer = {
        "i",
        "ippi",
        "isippi",
        "issisippi",
        "missisippi",
        "pi",
        "ppi",
        "sippi",
        "sisippi",
        "ssisippi",
    };

    assert(sa.size() == answer.size());
    for (int i = 0; i < int(sa.size()); i++) {
        assert(s.substr(sa[i]) == answer[i]);
    }
}
