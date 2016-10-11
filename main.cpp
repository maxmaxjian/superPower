#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cassert>

using std::string;
using std::vector;
using std::queue;
using std::stack;

class solution {
  public:
    string superPow(int a, const vector<int> & b) {
        string result{"1"};
        for (size_t i = b.size()-1; b.size() > i; --i) {
            string exp(std::to_string(b[i]));
            size_t j = b.size()-i;
            while (j-- > 1)
                exp.append("0");
            result = times(result, power(std::to_string(a), exp));
        }

        string n{"1"};
        while (!largerThan(times("1337",n), result))
            n = times(n, "2");
        string lower, upper = n;
        lower = dividedBy2(upper);        
        // std::cout << "lower = " << lower << ", upper = " << upper << std::endl;
        // std::cout << "result = " << result << std::endl;
        if (equal(times("1337",upper),result))
            return "0";
        else {
            string found;
            while (true) {
                if (!equal(add(lower,"1"), upper)) {
                    string mid = dividedBy2(add(lower,upper));
                    if (equal(times("1337",mid),result)) {
                        return "0";
                    }
                    else if (!largerThan(times("1337",mid), result)) {
                        lower = mid;
                    }
                    else {
                        upper = mid;
                    }
                }
                else
                    break;
            }
	    
            // std::cout << "lower = " << lower << ", upper = " << upper << std::endl;
	    // std::cout << "times(""1337"", lower) = " << times("1337",lower) << std::endl;
	    // std::cout << "times(""1337"", upper) = " << times("1337",upper) << std::endl;
            // std::cout << "result-lower = " << subtract(result, times("1337",lower)) << std::endl;
            // std::cout << "upper-result = " << subtract(times("1337",upper), result) << std::endl;

	    if (equal(result, times("1337", upper)))
	      return "0";
	    else
	      return subtract(result, times("1337", lower));
        }
    }

  public:
    string dividedBy2(const string & num) {
        string result = times(num,"5");
        result.erase(result.end()-1);
        return result;
    }
    
    string subtract(const string & num1, const string & num2) {
      assert(largerThan(num1, num2));
        stack<int> n1, n2;
        for (auto ch : num1)
            n1.push(std::stoi(string(1,ch)));
        for (auto ch : num2)
            n2.push(std::stoi(string(1,ch)));

        string result;
        int temp, decr=0;
        while (!n1.empty() && !n2.empty()) {
            temp = n1.top()-n2.top()-decr >= 0 ? n1.top()-n2.top()-decr : 10+n1.top()-n2.top()-decr;
            decr = n1.top()-n2.top()-decr >= 0 ? 0 : 1;
            n1.pop();
            n2.pop();
            result.insert(0, std::to_string(temp));
        }
        while (!n1.empty()) {
            temp = n1.top()-decr >= 0 ? n1.top()-decr : 10+n1.top()-decr;
            decr = n1.top()-decr >= 0 ? 0 : 1;
            n1.pop();
            result.insert(0, std::to_string(temp));
        }
        while (!n2.empty()) {
            temp = n2.top()-decr >= 0 ? n2.top()-decr : 10+n2.top()-decr;
            decr = n2.top()-decr >= 0 ? 0 : 1;
            n2.pop();
            result.insert(0, std::to_string(temp));
        }

	while (*(result.begin()) == '0')
	  result.erase(result.begin());
        return result;
    }
    
    bool equal(const string & larger, const string & smaller) {
        if (larger.size() != smaller.size())
            return false;
        else {
            for (size_t i = 0; i < larger.size(); ++i)
                if (larger[i] != smaller[i])
                    return false;
            return true;
        }
    }
    
    bool largerThan(const string & larger, const string & less) {
        if (larger.size() != less.size())
            return larger.size() > less.size();
        else {
            for (size_t i = 0; i < larger.size(); ++i) {
                if (larger[i] != less[i])
                    return larger[i] > less[i];
            }
            return false;
        }
    }
    
    string power(const string & base, const string & exp) {
        string result{"1"};
        for (string it{"0"}; largerThan(exp, it); it = add(it,"1")) {
            result = times(result, base);
        }
        return result;
    }
    
    string times(const string & num1, const string & num2) {
        string result {"0"};
        for (size_t i = num2.size()-1; num2.size() > i; --i) {
            string temp = timesSingleDigit(num1, num2[i]);
            size_t j = num2.size()-i;
            while (j > 1) {
                temp.append("0");
                j--;
            }
            result = add(result, temp);
        }
        return result;
    }

    string timesSingleDigit(const string & num, char digit) {
        string result{"0"};
        for (size_t i = num.size()-1; num.size() > i; --i) {
            string temp = std::to_string(std::stoi(num.substr(i,1))*std::stoi(string(1,digit)));
            size_t j = num.size()-i;
            while (j > 1) {
                temp.append("0");
                j--;
            }
            result = add(result, temp);
        }
        return result;
    }

    string add(const string & num1, const string & num2) {
        queue<int> n1, n2;
        for (auto it = num1.rbegin(); it != num1.rend(); ++it)
            n1.push(std::stoi(string(1,*it)));
        for (auto it = num2.rbegin(); it != num2.rend(); ++it)
            n2.push(std::stoi(string(1,*it)));
        int tsum = 0, inc = 0, rest = 0;
        string result;
        while (!n1.empty() && !n2.empty()) {
            tsum = n1.front()+n2.front()+inc;
            rest = tsum%10;
            inc = tsum/10;
            n1.pop();
            n2.pop();
            result.insert(0, std::to_string(rest));
        }

        while (!n1.empty()) {
            tsum = n1.front()+inc;
            rest = tsum%10;
            inc = tsum/10;
            n1.pop();
            result.insert(0, std::to_string(rest));
        }
        while (!n2.empty()) {
            tsum = n2.front()+inc;
            rest = tsum%10;
            inc = tsum/10;
            n2.pop();
            result.insert(0, std::to_string(rest));
        }
        if (inc != 0)
            result.insert(0, std::to_string(inc));
        
        return result;
    }
};

int main() {
    int a = 345;
    vector<int> b{1,2,1};
    
    solution soln;
    
    std::cout << soln.superPow(a,b) << std::endl;    
}
