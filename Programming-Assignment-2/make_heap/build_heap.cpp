#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void WriteData() const {
    for (int i = 0; i < data_.size(); ++i) {
      cout << data_[i] << ", ";
    }
    cout << "\n";
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void SiftDown(int i, vector<int>& data_, vector< pair<int, int> >& swaps_) {
    int max_idx = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    const int n = data_.size();
    if (l <= n - 1 && data_[l] < data_[max_idx]) max_idx = l;
    if (r <= n - 1 && data_[r] < data_[max_idx]) max_idx = r;
    if (i != max_idx) {
        swap(data_[i], data_[max_idx]);
        swaps_.push_back(make_pair(i, max_idx));
        SiftDown(max_idx, data_, swaps_);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    //for (int i = 0; i < data_.size(); ++i)
    //  for (int j = i + 1; j < data_.size(); ++j) {
    //    if (data_[i] > data_[j]) {
    //      swap(data_[i], data_[j]);
    //      swaps_.push_back(make_pair(i, j));
    //    }
    //  }
    for (int i = (data_.size() + 1) / 2; i >= 0; --i) {
        SiftDown(i, data_, swaps_);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
    //WriteData();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
