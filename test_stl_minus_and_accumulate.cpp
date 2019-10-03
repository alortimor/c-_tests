#include <iostream>
#include <algorithm>

double calc_sum_of_squares1(std::vector<double> & vld);
double calc_sum_of_squares2(std::vector<double> & vld);
int sq(int c, int d) {return c+d*d;}

int main () {
  std::vector<double> vld1 { 600,470,170,430, 300};
  std::vector<double> vld2 { 3, 21, 98, 203, 17, 9};
  std::vector<double> vld3 {7, 6, 8, 4, 2, 7, 6, 7, 6, 5};

  double sum_of_squares = calc_sum_of_squares1(vld2); // http://www.mathsisfun.com/data/standard-deviation.html
  std::cout << "Variance 1: " << sum_of_squares/(vld2.size()-1) << " Std Deviation 1: " << sqrt(sum_of_squares/(vld2.size()-1)) << std::endl;

  sum_of_squares = calc_sum_of_squares2(vld2); // http://www.statisticshowto.com/how-to-find-the-sample-variance-and-standard-deviation-in-statistics/
  std::cout << "Variance 2: " << sum_of_squares/(vld2.size()-1) << " Std Deviation 2: " << sqrt(sum_of_squares/(vld2.size()-1)) << std::endl;

  sum_of_squares = calc_sum_of_squares2(vld3); // http://www.statisticshowto.com/how-to-find-the-sample-variance-and-standard-deviation-in-statistics/
  std::cout << "Variance 3: " << sum_of_squares/(vld3.size()-1) << " Std Deviation 3: " << sqrt(sum_of_squares/(vld3.size()-1)) << std::endl;
  return 0;
}

// http://www.mathsisfun.com/data/standard-deviation.html
double calc_sum_of_squares1(std::vector<double> & vld) {
  double mean = std::accumulate(begin(vld), end(vld), 0.0) / vld.size();
  std::vector<double> diff(vld.size());
  std::transform(begin(vld), end(vld), begin(diff), std::bind2nd(std::minus<double>(), mean));
  return std::inner_product(begin(diff), end(diff), begin(vld), 0.0);
}

// http://www.statisticshowto.com/how-to-find-the-sample-variance-and-standard-deviation-in-statistics/
double calc_sum_of_squares2(std::vector<double> & vld) {
  double sum = std::accumulate(begin(vld), end(vld), 0.0); // step1
  sum = (sum*sum) / vld.size(); // step 2
  sum = std::accumulate(begin(vld), end(vld), 0.0,  sq) - sum; // step3&4
  return sum; // step5&6 occur after return
}
