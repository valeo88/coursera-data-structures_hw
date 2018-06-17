#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

struct Worker {
    int number; // number of worker from 0 to n
    long long priority; // sum of durations of all jobs assigned to this worker
};

bool operator<(const Worker& lhs, const Worker& rhs) {
    if (lhs.priority!=rhs.priority) {
        return lhs.priority < rhs.priority;
    }
    return lhs.number < rhs.number;
}

class JobQueue {
 private:
  int num_workers_;
  int size_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  vector<Worker> h; // vector for min-heap of Workers

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    //assigned_workers_.resize(jobs_.size());
    //start_times_.resize(jobs_.size());
    //vector<long long> next_free_time(num_workers_, 0);
    //for (int i = 0; i < jobs_.size(); ++i) {
    //  int duration = jobs_[i];
    //  int next_worker = 0;
    //  for (int j = 0; j < num_workers_; ++j) {
    //    if (next_free_time[j] < next_free_time[next_worker])
    //      next_worker = j;
    //  }
    //  assigned_workers_[i] = next_worker;
    //  start_times_[i] = next_free_time[next_worker];
    //  next_free_time[next_worker] += duration;
    //}

    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    h.resize(num_workers_);
    // initialize min-heap vector
    for (int i = 0; i < num_workers_; ++i) {
        h[i] = {i, 0};
    }
    for (int i = 0; i < jobs_.size(); ++i) {
        int duration = jobs_[i];
        assigned_workers_[i] = h[0].number;
        start_times_[i] = h[0].priority;
        ChangePriority(0, h[0].priority+duration); // add duration to worker priority
        //std::cout << "h = ";
        //for (int m = 0; m < h.size(); ++m) {
        //    std::cout<< h[m] << " ";
        //}
        //std::cout << "\n";
        //std::cout << "h_idx = ";
        //for (int m = 0; m < h_idx.size(); ++m) {
        //   std::cout<< h_idx[m] << " ";
        //}
        //std::cout << "\n";
    }
    }


  void SiftUp(int i) {
    while (i > 1 && h[i] < h[(i-1)/2]) {
        swap(h[(i-1)/2], h[i]);
        i = (i-1) / 2;
    }
  }

  void SiftDown(int i) {
    int max_idx = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    const int n = h.size();
    if (l <= n - 1 && h[l] < h[max_idx]) max_idx = l;
    if (r <= n - 1 && h[r] < h[max_idx]) max_idx = r;
    if (i != max_idx) {
        swap(h[i], h[max_idx]);
        SiftDown(max_idx);
    }
  }

  void ChangePriority(int i, long long p) {
    long long oldp = h[i].priority;
    h[i].priority = p;
    if (p < oldp) {
        SiftUp(i);
    } else {
        SiftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
