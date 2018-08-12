#include <iostream>
#include "measure.hpp"
#include "test_manager.hpp"

using namespace std;

int main() {
    auto time = cuttle::measure<std::chrono::nanoseconds>::execution([] {
        try {
            run_tests();
            cout << "ok" << endl;
        }
        catch (const std::logic_error &e) {
            cout << "logic_error: " << e.what() << endl;
        }
    });
    cout << "Elapsed " << time / 1e6 << " ms" << endl;
//	getchar();
}
