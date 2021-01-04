#pragma once

#include <string>



// Macro to handle erros in VCL
//
// - assert_vcl( condition, error message ) : check condition and call error if condition if false. The error message is displayed if the condition is false.
// - assert_vcl_no_msg( condition ) : same as before, but without the need to specify a specific error message.
// - error_vcl( error message ) : call and error with the given message. 
//
// Error in vcl are typically aimed at stopping the program using abort after displaying some debug message.
//   VCL error are related to extra checks. For full efficiency, these check can be disabled in defining VCL_NO_DEBUG
//   The default abort behavior when an error is detected can also be converted to exception using VCL_ERROR_EXCEPTION


namespace vcl
{
[[noreturn]] void call_error(std::string const& error, std::string const& message, std::string const& filename, std::string const& function_name, int line);
}

#ifndef VCL_NO_DEBUG
#define assert_vcl(X, MSG)   {if( (X)==false ) {vcl::call_error(#X,MSG,__FILE__,__func__ ,__LINE__);} }
#define assert_vcl_no_msg(X) {if( (X)==false ) {vcl::call_error(#X,"",__FILE__,__func__ ,__LINE__);} }
#else
#define assert_vcl(X, MSG)
#define assert_vcl_no_msg(X)
#endif

#define error_vcl(MSG)  {vcl::call_error("",MSG,__FILE__,__func__,__LINE__); }

// Default behavior of VCL error is to abort the program.
//  The default behavior can be switched to throwing exception in defining VCL_ERROR_EXCEPTION
// #define VCL_ERROR_EXCEPTION



