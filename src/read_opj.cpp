#include <string>

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export(name="read.opj")]]
List read_opj(const std::string & file) {

    CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;

    return z ;
}
