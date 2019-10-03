#include <iostream>
#include <boost/signals2/signal.hpp>

float product(float x, float y) { return x * y; }
float quotient(float x, float y) { return x / y; }
float sum(float x, float y) { return x + y; }
float difference(float x, float y) { return x - y; }

typedef boost::signals2::signal<float (float, float)> float_func;

template<typename FulfilledRequest>
struct DistributeRequest {
  typedef FulfilledRequest* result_type;

  template<typename InputIterator>
  result_type operator()(InputIterator first, InputIterator last) const
  {
    while (first != last) {
      if (result_type fulfilled = *first)
        return fulfilled;
      ++first;
    }
    return 0;
  }
};

// combiner which returns the maximum value returned by all slots
template<typename T>
  struct maximum {
    typedef T result_type; // result_type is used by Boost, so must be incuded.

    template<typename InputIterator> // InputIterator is the name for the argument, which for the functions above are x, y
    T operator()(InputIterator first, InputIterator last) const {

      // If there are no slots to call, just return the default-constructed value
      if(first == last ) return T();

      T max_value = *first++;
      while (first != last) {
        if (max_value < *first)
          max_value = *first;
        ++first;
      }

      return max_value;
    }
};

// aggregate_values is a combiner which places all the values returned
// from slots into a container
template<typename Container>
struct aggregate_values {
  typedef Container result_type;

  template<typename InputIterator>
  Container operator()(InputIterator first, InputIterator last) const {
    Container values;
    while(first != last) {
      values.push_back(*first);
      ++first;
    }
    return values;
  }
};

int main() {
 
  float_func sig; // behaves as per the default behaviour, see note below!

  boost::signals2::signal<float (float, float), maximum<float> >  sig_max; // returns the maximum value, from all objects (slots) signalled.
  boost::signals2::signal<float (float, float), aggregate_values<std::vector<float> > > sig_agg; // returns a container of all results

  boost::signals2::connection c1 ;
  boost::signals2::connection c2 ;
  boost::signals2::connection c3 ;

  c1 = sig.connect(&product);
  sig.disconnect(&product);
  c1 = sig.connect(&quotient);
  sig.disconnect(&quotient);
  c1 = sig.connect(&sum);
  sig.disconnect(&sum);
  c1 = sig.connect(&difference);
  sig.disconnect(&difference);

  c2 = sig_max.connect(&product);
  c2 = sig_max.connect(&quotient);
  c2 = sig_max.connect(&sum);
  c2 = sig_max.connect(&difference);

  sig_agg.connect(&product);
  sig_agg.connect(&quotient);
  sig_agg.connect(&sum);
  sig_agg.connect(&difference);


  /* default behavior of a signal that has a return type is to call all slots
     and then return a boost::optional containing the result returned by the last slot called. 
     This behavior is irrelevant in this exampe, because slots have no side effects and the
     result is the last slot (float difference) connected.
  */

  std::cout << *sig(5, 3) << std::endl; // ensure a single object is pointed to, unless a combiner is specified
  c1.disconnect();
  std::cout << sig_max(5, 3) << std::endl; // connect to all, since a combiner is specified in the declaration, use with sig defined with maximum

/*
  {
    boost::signals2::scoped_connection c(sig.connect(ShortLived()));
    sig(); // will call ShortLived function object
  } // scoped_connection goes out of scope and disconnects

  sig(); // ShortLived function object no longer connected to sig

*/
   
  std::vector<float> results = sig_agg(5, 3);
  std::cout << "Container values: ";
  std::copy(results.begin(), results.end(), std::ostream_iterator<float> (std::cout, " ") );
  std::cout << std:: endl;

  return 0;
}




















